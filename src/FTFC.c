#include <stdio.h>
#include <stdint.h>
#include "MY_LIBRARY.h"

void flash_wait_ready(void)
{
    while (!(FTFC->FSTAT & (1u << 7u)))
        ;

    if (FTFC->FSTAT & (1u << 5u))
    {
        FTFC->FSTAT |= (1u << 5u);
    }
    if (FTFC->FSTAT & (1u << 4u))
    {
        FTFC->FSTAT |= (1u << 4u);
    }
}

void flash_execute_command(void)
{
    while (!(FTFC->FSTAT & (1u << 7u)))
        ;

    FTFC->FSTAT |= (1u << 7u);
}

void flash_program_partition(void)
{
    flash_wait_ready();

    FTFC->FCCOB[0] = 0x80u; // Code for the command
    FTFC->FCCOB[1] = 0u;    // Parameters
    FTFC->FCCOB[2] = 0u;
    FTFC->FCCOB[3] = 0u;
    FTFC->FCCOB[4] = 0x02u; // Parameters
    FTFC->FCCOB[5] = 0x03u;

    flash_execute_command();
}

void flash_set_flexram_to_eeprom(void)
{
    flash_wait_ready();

    FTFC->FCCOB[0] = 0x81u; // Code for the command
    FTFC->FCCOB[1] = 0x00u; // Parameters

    flash_execute_command();

    while (!(FTFC->FCNFG & (1u << 0u)))
        ;
}

void flash_write_eeprom(uint32_t *address, uint32_t data)
{
    while (!(FTFC->FSTAT & (1u << 7u)));

    *address = data;
}

uint32_t flash_read_eeprom(uint32_t *address)
{
    while (!(FTFC->FSTAT & (1u << 7u)));

    return *address;
}

void EEPROM_Write(uint32_t address, uint8_t *data, size_t size)
{
    flash_set_flexram_to_eeprom();
    flash_wait_ready();

    for (size_t i = 0; i < size; i += 4)
    {
        uint32_t value = 0;
        for (size_t j = 0; j < 4 && (i + j) < size; j++)
        {
            value |= (data[i + j] << (j * 8));
        }
        flash_write_eeprom((uint32_t *)(address + i), value);
    }
}

void EEPROM_Read(uint32_t address, uint8_t *data, size_t size)
{
    flash_set_flexram_to_eeprom();
    flash_wait_ready();

    for (size_t i = 0; i < size; i += 4)
    {
        uint32_t value = flash_read_eeprom((uint32_t *)(address + i));
        for (size_t j = 0; j < 4 && (i + j) < size; j++)
        {
            data[i + j] = (value >> (j * 8)) & 0xFF;
        }
    }
}