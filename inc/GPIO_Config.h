#pragma once
#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#define INTERRUPT_0_LOGIC 0x8
#define INTERRUPT_1_LOGIC 0xC
#define INTERRUPT_RISING_EDGE 0x9
#define INTERRUPT_FALLING_EDGE 0xA
#define INTERRUPT_EITHER_EDGE 0xB

void GPIO_Input_Config(char GPIO_Port, int Port_Pin);
void GPIO_Output_Config(char GPIO_Port, int Port_Pin);
void GPIO_Input_Interrupt_Config(char GPIO_Port, int Port_Pin, int detectType);

#endif