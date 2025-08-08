#pragma once
#ifndef SYSTICK_H
#define SYSTICK_H

typedef struct
{
    /* Systick Control and Status Register */
    volatile unsigned int SYST_CSR;
    /* Systick Reload Value Register */
    volatile unsigned int SYST_RVR;
    /* Systick Current Value Register */
    volatile unsigned int SYST_CVR;
    /* Systick Calibration Value Register */
    volatile const unsigned int SYST_CALIB;
} SysTick_Type;

#define SYSTICK_BASE_ADDRESS 0xE000E010
#define SYSTICK ((SysTick_Type*)SYSTICK_BASE_ADDRESS)

#endif