#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include "clock_and_modes.h"
#include "FTFC.h"
#include "GPIO_Config.h"
#include "GPIO_Register.h"
#include "LPIT_Config.h"
#include "LPIT_Register.h"
#include "LPSPI_Config.h"
#include "LPSPI_Register.h"
#include "LPUART_Register.h"
#include "MAX7219.h"
#include "PCC_Register.h"
#include "PORT_Register.h"
#include "SCG_Register.h"
#include "SysTick.h"
#include "UART_Config.h"

void flash_wait_ready(void);
void flash_execute_command(void);
void flash_program_partition(void);
void flash_set_flexram_to_eeprom(void);
void EEPROM_Write(uint32_t address, uint8_t *data, size_t size);
void EEPROM_Read(uint32_t address, uint8_t *data, size_t size);

#endif