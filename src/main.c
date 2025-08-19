#include "MY_LIBRARY.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define CORE_CLK 72000000
#define BUS_CLK 36000000
#define FLASH_CLK 18000000
#define SPLL_CLK 144000000

#define LED_GREEN 16

#define RX_BUFFER_SIZE 30
#define EEPROM_ADDR 0x14000000u

char receiveData;
char receiveBuffer[RX_BUFFER_SIZE];
char TimeDate_RxBuff[12];
int string_index = 0;
int doneReceive = 0;
int dataValid = 0;
volatile uint8_t transmit = 0;

char TimeDate_TxBuff[12] = {0xAA, 0x55, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75};

volatile uint8_t enable = 0;

unsigned int day = 1, month = 1, year = 1971;
unsigned int hour = 0, minute = 0, second = 0;
uint8_t intensityLevel = 15;
int counter500ms = 0;
int counter1s = 0;
int DisplayMode = 1;

uint8_t NumberLEDcode[] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x00}; /* 0-9 */

extern uint32_t SystemCoreClock;
extern void SystemCoreClockUpdate(void);

void PORTC_IRQHandler(void);
void LPUART1_RxTx_IRQHandler(void);
void LPIT0_Ch0_IRQHandler(void);
void LPIT0_Ch1_IRQHandler(void);
void LPIT0_Ch2_IRQHandler(void);
int StringToNum(char numString[]);
void ProcessTransmitData(unsigned int hour, unsigned int minute, unsigned int second, unsigned int day, unsigned int month, unsigned int year);

void ProcessReceiveData(void);
int ValidateCheckSum(void);
char CalculateCheckSum(char StringCheckSum[]);

void MAX7219DisplayMode(int mode);
unsigned int DayinMonth(int p_month, int p_year);

void SaveToEEPROM(void);
void LoadFromEEPROM(void);

int main(void)
{
	/* CLOCK Config */
	SOSC_INIT_8MHZ();
	SPLL_INIT(SPLL_SOSC_SOURCE, SOSC_CLK_SOURCE, SPLL_CLK); /* SPLLDIV2 = SPLL_CLK/4 = 144MHz/4 = 36MHz */
	NORMAL_RUN_MODE(MODE_CCR_SCS_SPLL, SPLL_CLK, CORE_CLK, BUS_CLK, FLASH_CLK);

	/* GPIO Config */
	GPIO_Output_Config('D', LED_GREEN);
	GPIOD->PSOR |= 1 << LED_GREEN; /* LED OFF */

	GPIO_Input_Config('C', 12);
	GPIO_Input_Config('C', 13);
	GPIO_Input_Interrupt_Config('C', 12, INTERRUPT_FALLING_EDGE); /* Button1 select display mode */
	GPIO_Input_Interrupt_Config('C', 13, INTERRUPT_FALLING_EDGE); /* Button2 decrease intensity of LED */

	/* UART1 Config */
	/**
	 * Thực tế là 38461.54 bps (~0.16%)
	 * Ratio = 26
	 * SBR = 36
	 */
	UART1_Interrupt_Config(UART1_C7TX_C6RX, 38400, SPLL_CLK / 4, 8, 1, NO_PARITY);

	/* SPI1 Config */
	PORT_SPI_CONFIG();
	LPSPI1_CONFIG();

	MAX7219_Innit();
	MAX7219_DateDisplay(day, month, year);
	MAX7219_TimeDisplay(hour, minute, second);

	/* Timer Config */
	LPIT_Config(0, 1); /* Timer0 channel0 1s */
	LPIT_Config(1, 1); /* Timer0 channel1 1s */

	while (1)
	{
		if (doneReceive)
		{
			doneReceive = 0;
			ProcessReceiveData();
			string_index = 0;
		}
		if (intensityLevel > 1)
		{
			MAX7219_Display(0x0C,0x01);
			MAX7219_Intensity(intensityLevel);
		}
		else
		{
			MAX7219_Display(0x0C, 0x00);
		}

		if (DisplayMode == 1) /* Mode auto */
		{
			if (!(LPIT->TCTRL2 & (1u << 0u))) /* Timer0 channel2 is not enabled */
			{
				LPIT_Config(2, 1); /* enable Timer0 channel2 1s */
			}
		}
		else
		{
			LPIT_Disable(2); /* Disable Timer0 channel2 */
		}
		MAX7219DisplayMode(DisplayMode);

		if (transmit == 1)
		{
			transmit = 0;
			ProcessTransmitData(hour, minute, second, day, month, year);
		}
	}
}

void LPUART1_RxTx_IRQHandler(void)
{
	if (LPUART1->STAT & 1 << 21) /* Recevie Data */
	{
		receiveData = LPUART1->DATA;
		if (string_index == 0)
		{
			memset(receiveBuffer, 0, RX_BUFFER_SIZE);
		}
		receiveBuffer[string_index] = receiveData;
		string_index++;
	}
	if (LPUART1->STAT & (1 << 20)) /* Idle */
	{
		doneReceive = 1;
		LPUART1->STAT |= 1 << 20; /* Clear Idle flag */
	}
}

void ProcessReceiveData(void)
{
	if (receiveBuffer[0] == 0xAA && receiveBuffer[1] == 0x55 && receiveBuffer[string_index - 1] == 0x75)
	{	
		/* Send data from PC -> S32K144 display day month year */
		if (receiveBuffer[2] == 0x01)
		{
			memcpy(TimeDate_RxBuff, receiveBuffer, strlen(receiveBuffer));
			hour = TimeDate_RxBuff[3];
			minute = TimeDate_RxBuff[4];
			second = TimeDate_RxBuff[5];
			day = TimeDate_RxBuff[6];
			month = TimeDate_RxBuff[7];
			year = TimeDate_RxBuff[8] * 256 + TimeDate_RxBuff[9];
		}
		/* Send data from PC -> S32K144 change mode display */
		else if (receiveBuffer[2] == 0x02)
		{
			memcpy(TimeDate_RxBuff, receiveBuffer, strlen(receiveBuffer));
			DisplayMode = TimeDate_RxBuff[3];
		}
		/* Send data from PC -> S32K144 change intensity */
		else if (receiveBuffer[2] == 0x03)
		{
			memcpy(TimeDate_RxBuff, receiveBuffer, strlen(receiveBuffer));
			intensityLevel = TimeDate_RxBuff[3];
		}
	}
}

void ProcessTransmitData(unsigned int hour, unsigned int minute, unsigned int second, unsigned int day, unsigned int month, unsigned int year)
{
	TimeDate_TxBuff[0] = 0xAA;
	TimeDate_TxBuff[1] = 0x55;
	TimeDate_TxBuff[2] = 0x01;
	TimeDate_TxBuff[3] = hour;
	TimeDate_TxBuff[4] = minute;
	TimeDate_TxBuff[5] = second;
	TimeDate_TxBuff[6] = day;
	TimeDate_TxBuff[7] = month;
	TimeDate_TxBuff[8] = ((year >> 8u) & 0xFF); /* Year MSB */
	TimeDate_TxBuff[9] = (year & 0xFF);
	TimeDate_TxBuff[10] = CalculateCheckSum(TimeDate_TxBuff);
	TimeDate_TxBuff[11] = 0x75;

	UART1_SendString(TimeDate_TxBuff);
	UART1_SendChar('\n');
}

int ValidateCheckSum(void)
{
	uint8_t f_calculateCRC = 0xFF;
	uint8_t f_receivedCRC = receiveBuffer[strlen(receiveBuffer) - 2];
	for (unsigned int i = 3; i < strlen(receiveBuffer) - 2; i++)
	{
		f_calculateCRC ^= receiveBuffer[i];
		for (int j = 0; j < 8; j++)
		{
			if ((f_calculateCRC & 0x80) != 0)
			{
				f_calculateCRC = (f_calculateCRC << 1) ^ 0x36;
			}
			else
			{
				f_calculateCRC <<= 1;
			}
		}
	}
	if (f_calculateCRC != f_receivedCRC)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

char CalculateCheckSum(char StringCheckSum[])
{
	uint8_t f_CRC = 0xFF;
	for (unsigned int i = 3; i < strlen(StringCheckSum) - 2; i++)
	{
		f_CRC ^= receiveBuffer[i];
		for (int j = 0; j < 8; j++)
		{
			if ((f_CRC & 0x80) != 0)
			{
				f_CRC = (f_CRC << 1) ^ 0x36;
			}
			else
			{
				f_CRC <<= 1;
			}
		}
	}
	return f_CRC;
}

void PORTC_IRQHandler(void)
{
	if (PORTC->PORT_PCR12 & 1 << 24) /* Bit ISF PTC12 Interrupt detected */
	{
		// Ghi 1 vào ISF để xóa cờ ngắt
		PORTC->PORT_PCR12 |= 1 << 24;
		if (DisplayMode < 3)
		{
			DisplayMode++;
		}
		else if (DisplayMode == 3)
		{
			DisplayMode = 1;
		}
	}
	if (PORTC->PORT_PCR13 & 1 << 24) /* Bit ISF PTC13 Interrupt detected */
	{
		PORTC->PORT_PCR13 |= 1 << 24;
		if (intensityLevel > 1)
		{
			intensityLevel -= 3;
		}
		else
		{
			intensityLevel = 15;
			MAX7219_Display(0x0C, 0x01);
		}
//		MAX7219_Intensity(intensityLevel);
	}
}

void MAX7219DisplayMode(int mode)
{
	switch (mode)
	{
	case 1:
		if (counter1s < 5)
		{
			MAX7219_TimeDisplay(hour, minute, second);
		}
		else if (counter1s < 10)
		{
			MAX7219_DateDisplay(day, month, year);
		}
		else
			counter1s = 0;
		break;

	case 2:
		MAX7219_DateDisplay(day, month, year);
		break;

	case 3:
		MAX7219_TimeDisplay(hour, minute, second);
		break;

	default:
		break;
	}
}

void LPIT0_Ch0_IRQHandler(void) /* Time Clock */
{
	if (LPIT->MSR & 1 << 0)
	{
		LPIT->MSR |= 1 << 0;
		GPIOD->PTOR |= 1 << LED_GREEN;

		if (second < 60) {
			second++;
		}
		if (second == 60) {
			second = 0;
			minute++;
		}
		if (minute == 60) {
			minute = 0;
			hour++;
		}
		if (hour == 24) {
			hour = 0;
			day++;
		}
		if (day > DayinMonth(month, year)) {
			day = 1;
			month++;
		}
		if (month > 12) {
			month = 1;
			year++;
		}
	}
}

// Trigger truyền dữ liệu định kỳ
void LPIT0_Ch1_IRQHandler(void)
{
	// Kiểm tra cờ ngắt
	if (LPIT->MSR & (1u << 1u)) {
		LPIT->MSR |= (1u << 1u);
		transmit = 1;
	}
}

void LPIT0_Ch2_IRQHandler(void) /* Display Time */
{
	if (LPIT->MSR & (1u << 2u))
	{
		LPIT->MSR |= (1u << 2u);
		counter1s++;
	}
}

unsigned int DayinMonth(int p_month, int p_year)
{
	if (p_month == 1 || p_month == 3 || p_month == 5 || p_month == 7 || p_month == 8 || p_month == 10 || p_month == 12)
	{
		return 31;
	}
	else if (p_month != 2)
	{
		return 30;
	}
	else if (p_year % 400 == 0 || (p_year % 4 == 0 && p_year % 100 != 0))
	{
		return 29;
	}
	else
	{
		return 28;
	}
}