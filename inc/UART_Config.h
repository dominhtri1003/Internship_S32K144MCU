#pragma once
#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#define STOP_BIT_1 1
#define STOP_BIT_2 2
#define NO_PARITY 0
#define ODD_PARITY 1
#define EVEN_PARITY 2

#define UART0_C3TX_C2RX 0
#define UART0_B1TX_B0RX 1
#define UART0_A3TX_A2RX 2

#define UART1_C7TX_C6RX 0
#define UART1_D14TX_D13RX 1
#define UART1_C9TX_C8RX 2

#define UART2_A9TX_A8RX 0
#define UART2_E12TX_D17RX 1
#define UART2_D7TX_D6RX 2

void UART0_Config(void);
void UART1_Config(unsigned int BaudRate,  unsigned int clock, int DataBit, int StopBit, int ParityBit);
void UART2_Config(void);

void UART0_Interrupt_Config(int Pin, unsigned int BaudRate, unsigned int clock, int DataBit, int StopBit, int ParityBit);
void UART1_Interrupt_Config(int Pin, unsigned int BaudRate, unsigned int clock, int DataBit, int StopBit, int ParityBit);
void UART2_Interrupt_Config(void);

void UART1_SendChar(char sendChar);
void UART1_SendString(char sendString[]);

#endif