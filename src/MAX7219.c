#include "MAX7219.h"

extern void SPI1_Send(uint16_t SendData);

void MAX7219_Innit(void)
{
	MAX7219_Display(0x0C, 0x01); /* Normal operation */
	MAX7219_Display(0x0A, 0x02); /* Intensity */
	MAX7219_Display(0x0B, 0x07); /* Display all digits */
	MAX7219_Display(0x09, 0xFF); /* Code B decode for 7 digits */
}

void MAX7219_Display(uint8_t Address, uint8_t Data)
{
	uint16_t Data16bit;
	Data16bit = Address << 8 | Data;
	SPI1_Send(Data16bit);
}

void MAX7219_TimeDisplay(unsigned int p_hour, unsigned int p_minute, unsigned int p_second)
{
	MAX7219_Display(DIGIT7, p_hour / 10);
	MAX7219_Display(DIGIT6, p_hour % 10);

	MAX7219_Display(DIGIT5, DASH_LED_CODE);

	MAX7219_Display(DIGIT4, p_minute / 10);
	MAX7219_Display(DIGIT3, p_minute % 10);

	MAX7219_Display(DIGIT2, DASH_LED_CODE);

	MAX7219_Display(DIGIT1, p_second / 10);
	MAX7219_Display(DIGIT0, p_second % 10);
}

void MAX7219_DateDisplay(unsigned int p_day, unsigned int p_month, unsigned int p_year)
{
	MAX7219_Display(DIGIT7, p_day / 10);
	MAX7219_Display(DIGIT6, p_day % 10 | (1 << 7));

	MAX7219_Display(DIGIT5, p_month / 10);
	MAX7219_Display(DIGIT4, p_month % 10 | (1 << 7));

	MAX7219_Display(DIGIT0, p_year % 10);
	p_year = p_year / 10;
	MAX7219_Display(DIGIT1, p_year % 10);
	p_year = p_year / 10;
	MAX7219_Display(DIGIT2, p_year % 10);
	p_year = p_year / 10;
	MAX7219_Display(DIGIT3, p_year % 10);
}

void MAX7219_Intensity(int p_level)
{
	MAX7219_Display(0x0A, p_level); /* Intensity */
}
