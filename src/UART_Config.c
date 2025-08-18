#include "UART_Config.h"
#include "PCC_Register.h"
#include "PORT_Register.h"
#include "LPUART_Register.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void UART0_Config(void)
{
}

void UART1_Config(unsigned int BaudRate, unsigned int clock, int DataBit, int StopBit, int ParityBit)
{
	/* LPUART Interrupt config */
	*(volatile uint32_t *)(0xE000E104) |= 1 << 1; /* LPUART1 ID 33 */

	/* Setting Tx/Rx pin */
	PCC->PCC_PORTC |= 1 << 30;	/* Enable clock for port C */
	PORTC->PORT_PCR6 |= 2 << 8; /* Port C6: MUX = ALT2, UART1 TX */
	PORTC->PORT_PCR7 |= 2 << 8; /* Port C7: MUX = ALT2, UART1 RX */

	/* Select source LPUART */
	PCC->PCC_LPUART1 &= ~(1 << 30); /* Clock disable */
	PCC->PCC_LPUART1 |= 6 << 24;	/* PCS = 6 SPLLDIV2 */
	PCC->PCC_LPUART1 |= (1 << 30);	/* Clock enable */

	/* Setting baud rate */
	uint32_t moduloDivisor, oversampling, oversamplingRatio;
	uint32_t remain = clock % (BaudRate * 8);
	for (oversampling = 8; oversampling <= 32; oversampling++)
	{
		if ((remain >= clock % (BaudRate * oversampling)) & (clock / (BaudRate * oversampling) <= 8191))
		{
			remain = clock % (BaudRate * oversampling);
			moduloDivisor = clock / (BaudRate * oversampling);
			oversamplingRatio = oversampling;
		}
	}
	uint32_t BAUD_CONFIG = LPUART1->BAUD;
	BAUD_CONFIG &= ~(0xFFF << 0);
	BAUD_CONFIG |= (moduloDivisor) << 0; /* Modulo divisor */
	BAUD_CONFIG &= ~(0x1F << 24);
	BAUD_CONFIG |= (oversamplingRatio - 1) << 24; /* Oversampling Ratio = 17 */

	/* Setting frame */
	if (StopBit == STOP_BIT_1)
	{
		BAUD_CONFIG &= ~(1 << 13); /* One stop bit */
	}
	else if (StopBit == STOP_BIT_2)
	{
		BAUD_CONFIG |= (1 << 13); /* Two stop bits */
	}

	LPUART1->BAUD = BAUD_CONFIG;

	uint32_t CTRL_CONFIG = LPUART1->CTRL;
	CTRL_CONFIG &= ~(1 << 11); /* Receiver and transmitter use 8-bit to 10-bit data characters */
	if (DataBit == 8 && ParityBit == NO_PARITY)
	{
		CTRL_CONFIG &= ~(1 << 4); /* 8 bit character */
	}
	else
	{
		CTRL_CONFIG |= 1 << 4; /* 9 bit character */
	}

	if (ParityBit == NO_PARITY)
	{
		CTRL_CONFIG &= ~(1 << 1); /* No parity bits */
	}
	else if (ParityBit == ODD_PARITY)
	{
		CTRL_CONFIG |= 1 << 1; /* Parity enable */
		CTRL_CONFIG |= 1 << 0; /* Odd parity */
	}
	else if (ParityBit == EVEN_PARITY)
	{
		CTRL_CONFIG |= 1 << 1;	  /* Parity enable */
		CTRL_CONFIG &= ~(1 << 0); /* Even parity */
	}

	/* Enable transmitter & receiver */
	CTRL_CONFIG |= 0x3 << 18u;
	LPUART1->CTRL = CTRL_CONFIG;
}

void UART2_Config(void)
{
}

void UART0_Interrupt_Config(int Pin, unsigned int BaudRate, unsigned int clock, int DataBit, int StopBit, int ParityBit)
{
	/* LPUART Interrupt config */
	*(volatile uint32_t *)(0xE000E100) |= 1 << 31; /* LPUART0 ID 31 */

	/* Setting Tx/Rx pin */
	if (Pin == UART0_A3TX_A2RX)
	{
		PCC->PCC_PORTA |= 1 << 30;	/* Enable clock for port A */
		PORTA->PORT_PCR3 |= 6 << 8; /* Port A3: MUX = ALT6, UART0 TX */
		PORTA->PORT_PCR2 |= 6 << 8; /* Port A2: MUX = ALT6, UART0 RX */
	}
	else if (Pin == UART0_B1TX_B0RX)
	{
		PCC->PCC_PORTB |= 1 << 30;	/* Enable clock for port B */
		PORTB->PORT_PCR1 |= 2 << 8; /* Port B1: MUX = ALT2, UART0 TX */
		PORTB->PORT_PCR0 |= 2 << 8; /* Port B0: MUX = ALT2, UART0 RX */
	}
	else if (Pin == UART0_C3TX_C2RX)
	{
		PCC->PCC_PORTC |= 1 << 30;	/* Enable clock for port C */
		PORTC->PORT_PCR3 |= 4 << 8; /* Port C3: MUX = ALT4, UART0 TX */
		PORTC->PORT_PCR2 |= 4 << 8; /* Port C2: MUX = ALT4, UART0 RX */
	}

	/* Select source LPUART */
	PCC->PCC_LPUART0 &= ~(1 << 30); /* Clock disable */
	PCC->PCC_LPUART0 |= 6 << 24;	/* PCS = 6 SPLLDIV2 */
	PCC->PCC_LPUART0 |= (1 << 30);	/* Clock enable */

	/* Setting baud rate */
	uint32_t moduloDivisor, oversampling, oversamplingRatio;
	uint32_t remain = clock % (BaudRate * 8);
	for (oversampling = 8; oversampling <= 32; oversampling++)
	{
		if ((remain >= clock % (BaudRate * oversampling)) & (clock / (BaudRate * oversampling) <= 8191))
		{
			remain = clock % (BaudRate * oversampling);
			moduloDivisor = clock / (BaudRate * oversampling);
			oversamplingRatio = oversampling;
		}
	}
	uint32_t BAUD_CONFIG = LPUART0->BAUD;
	BAUD_CONFIG &= ~(0xFFF << 0);
	BAUD_CONFIG |= (moduloDivisor) << 0; /* Modulo divisor */
	BAUD_CONFIG &= ~(0x1F << 24);
	BAUD_CONFIG |= (oversamplingRatio - 1) << 24; /* Oversampling Ratio = 17 */

	/* Setting frame */
	if (StopBit == STOP_BIT_1)
	{
		BAUD_CONFIG &= ~(1 << 13); /* One stop bit */
	}
	else if (StopBit == STOP_BIT_2)
	{
		BAUD_CONFIG |= (1 << 13); /* Two stop bits */
	}

	LPUART0->BAUD = BAUD_CONFIG;

	uint32_t CTRL_CONFIG = LPUART0->CTRL;
	CTRL_CONFIG &= ~(1 << 11); /* Receiver and transmitter use 8-bit to 10-bit data characters */
	if (DataBit == 8 && ParityBit == NO_PARITY)
	{
		CTRL_CONFIG &= ~(1 << 4); /* 8 bit character */
	}
	else
	{
		CTRL_CONFIG |= 1 << 4; /* 9 bit character */
	}

	if (ParityBit == NO_PARITY)
	{
		CTRL_CONFIG &= ~(1 << 1); /* No parity bits */
	}
	else if (ParityBit == ODD_PARITY)
	{
		CTRL_CONFIG |= 1 << 1; /* Parity enable */
		CTRL_CONFIG |= 1 << 0; /* Odd parity */
	}
	else if (ParityBit == EVEN_PARITY)
	{
		CTRL_CONFIG |= 1 << 1;	  /* Parity enable */
		CTRL_CONFIG &= ~(1 << 0); /* Even parity */
	}

	/* Enable transmitter & receiver */
	CTRL_CONFIG |= 0x3 << 18;
	CTRL_CONFIG |= 1 << 20 | 1 << 21; /* IDLE, RIE = 1 */

	LPUART0->CTRL = CTRL_CONFIG;
}

void UART1_Interrupt_Config(int Pin, unsigned int BaudRate, unsigned int clock, int DataBit, int StopBit, int ParityBit)
{
	/* LPUART Interrupt config */
	*(volatile uint32_t *)(0xE000E104) |= 1 << 1; /* LPUART1 ID 33 */

	if (Pin == UART1_C7TX_C6RX)
	{
		PCC->PCC_PORTC |= 1 << 30;	/* Enable clock for port C */
		PORTC->PORT_PCR7 |= 2 << 8; /* Port C7: MUX = ALT2, UART1 TX */
		PORTC->PORT_PCR6 |= 2 << 8; /* Port C6: MUX = ALT2, UART1 RX */
	}
	else if (Pin == UART1_D14TX_D13RX)
	{
		PCC->PCC_PORTD |= 1 << 30;	 /* Enable clock for port D */
		PORTD->PORT_PCR14 |= 3 << 8; /* Port D14: MUX = ALT3, UART1 TX */
		PORTD->PORT_PCR13 |= 3 << 8; /* Port D13: MUX = ALT3, UART1 RX */
	}
	else if (Pin == UART1_C9TX_C8RX)
	{
		PCC->PCC_PORTC |= 1 << 30;	/* Enable clock for port C */
		PORTC->PORT_PCR9 |= 2 << 8; /* Port C9: MUX = ALT2, UART1 TX */
		PORTC->PORT_PCR8 |= 2 << 8; /* Port C8: MUX = ALT2, UART1 RX */
	}

	/* Select source LPUART */
	PCC->PCC_LPUART1 &= ~(1 << 30); /* Clock disable */
	PCC->PCC_LPUART1 |= 6 << 24;	/* PCS = 6 SPLLDIV2 = 36MHz */
	PCC->PCC_LPUART1 |= (1 << 30);	/* Clock enable */

	/* Setting baud rate */
	uint32_t moduloDivisor, oversampling, oversamplingRatio;
	uint32_t remain = clock % (BaudRate * 8);
	for (oversampling = 8; oversampling <= 32; oversampling++)
	{
		if ((remain >= clock % (BaudRate * oversampling)) && (clock / (BaudRate * oversampling) <= 8191))
		{
			remain = clock % (BaudRate * oversampling);
			moduloDivisor = clock / (BaudRate * oversampling);
			oversamplingRatio = oversampling;
		}
	}

	uint32_t BAUD_CONFIG = LPUART1->BAUD;
	BAUD_CONFIG &= ~(0x1FFF << 0); 		 /* Xóa 13 bits SBR */
	BAUD_CONFIG |= (moduloDivisor) << 0; /* Modulo divisor */
	BAUD_CONFIG &= ~(0x1F << 24);		 /* Xóa 5 bits Ratio */
	BAUD_CONFIG |= (oversamplingRatio - 1) << 24; /* Oversampling Ratio = 17 */

	/* Setting frame */
	if (StopBit == STOP_BIT_1)
	{
		BAUD_CONFIG &= ~(1 << 13); /* One stop bit */
	}
	else if (StopBit == STOP_BIT_2)
	{
		BAUD_CONFIG |= (1 << 13); /* Two stop bits */
	}

	LPUART1->BAUD = BAUD_CONFIG;

	uint32_t CTRL_CONFIG = LPUART1->CTRL;
	CTRL_CONFIG &= ~(1 << 11); /* Receiver and transmitter use 8-bit to 10-bit data characters */
	if (DataBit == 8 && ParityBit == NO_PARITY)
	{
		CTRL_CONFIG &= ~(1 << 4); /* 8 bit character */
	}
	else
	{
		CTRL_CONFIG |= 1 << 4; /* 9 bit character */
	}

	if (ParityBit == NO_PARITY)
	{
		CTRL_CONFIG &= ~(1 << 1); /* No parity bits */
	}
	else if (ParityBit == ODD_PARITY)
	{
		CTRL_CONFIG |= 1 << 1; /* Parity enable */
		CTRL_CONFIG |= 1 << 0; /* Odd parity */
	}
	else if (ParityBit == EVEN_PARITY)
	{
		CTRL_CONFIG |= 1 << 1;	  /* Parity enable */
		CTRL_CONFIG &= ~(1 << 0); /* Even parity */
	}

	/* Enable transmitter & receiver */
	CTRL_CONFIG |= 0x3 << 18;
	CTRL_CONFIG |= 1 << 20 | 1 << 21; /* IDLE, RIE = 1 */

	LPUART1->CTRL = CTRL_CONFIG;
}

void UART2_Interrupt_Config(void)
{
}

void UART1_SendChar(char sendChar)
{
	while (!(LPUART1->STAT & 1 << 23))
		;
	LPUART1->DATA = sendChar;
}
void UART1_SendString(char sendString[])
{
	uint32_t i = 0;
	while (sendString[i] != '\0')
	{
		UART1_SendChar(sendString[i]);
		i++;
	}
}