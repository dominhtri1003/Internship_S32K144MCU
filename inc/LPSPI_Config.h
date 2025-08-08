#pragma once
#ifndef LPSPI_CONFIG_H
#define LPSPI_CONFIG_H

#include "LPSPI_Register.h"
#include "PCC_Register.h"
#include "PORT_Register.h"
#include "stdint.h"

void LPSPI_CONFIG(void);
void LPSPI0_CONFIG(void);
void LPSPI1_CONFIG(void);
void LPSPI2_CONFIG(void);

void PORT_SPI_CONFIG(void);

void SPI1_Send(uint16_t SendData);

#endif