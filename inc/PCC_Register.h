/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, Fri Jul  5 09:57:24 2024

**
**     Abstract:
**         Peripheral Access Layer for module PCC
**     Author: PhucToan
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#if !defined(PCC_REGISTER_H_)  /* Check if memory map has not been already included */
#define PCC_REGISTER_H_

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/* PCC  */
typedef struct {
	/* Dummy Data to fulfill struct*/
  unsigned int Dummy70[32];
  /* PCC FTFC Register */
  volatile unsigned int PCC_FTFC;
  /* PCC DMAMUX Register */
  volatile unsigned int PCC_DMAMUX;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy7[2];
  /* PCC FlexCAN0 Register */
  volatile unsigned int PCC_FlexCAN0;
  /* PCC FlexCAN1 Register */
  volatile unsigned int PCC_FlexCAN1;
  /* PCC FTM3 Register */
  volatile unsigned int PCC_FTM3;
  /* PCC ADC1 Register */
  volatile unsigned int PCC_ADC1;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy8[3];
  /* PCC FlexCAN2 Register */
  volatile unsigned int PCC_FlexCAN2;
  /* PCC LPSPI0 Register */
  volatile unsigned int PCC_LPSPI0;
  /* PCC LPSPI1 Register */
  volatile unsigned int PCC_LPSPI1;
  /* PCC LPSPI2 Register */
  volatile unsigned int PCC_LPSPI2;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy9[2];
  /* PCC PDB1 Register */
  volatile unsigned int PCC_PDB1;
  /* PCC CRC Register */
  volatile unsigned int PCC_CRC;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy10[3];
  /* PCC PDB0 Register */
  volatile unsigned int PCC_PDB0;
  /* PCC LPIT Register */
  volatile unsigned int PCC_LPIT;
  /* PCC FTM0 Register */
  volatile unsigned int PCC_FTM0;
  /* PCC FTM1 Register */
  volatile unsigned int PCC_FTM1;
  /* PCC FTM2 Register */
  volatile unsigned int PCC_FTM2;
  /* PCC ADC0 Register */
  volatile unsigned int PCC_ADC0;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy11[1];
  /* PCC RTC Register */
  volatile unsigned int PCC_RTC;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy12[2];
  /* PCC LPTMR0 Register */
  volatile unsigned int PCC_LPTMR0;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy13[8];
  /* PCC PORTA Register */
  volatile unsigned int PCC_PORTA;
  /* PCC PORTB Register */
  volatile unsigned int PCC_PORTB;
  /* PCC PORTC Register */
  volatile unsigned int PCC_PORTC;
  /* PCC PORTD Register */
  volatile unsigned int PCC_PORTD;
  /* PCC PORTE Register */
  volatile unsigned int PCC_PORTE;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy14[6];
  /* PCC SAI0 Register */
  volatile unsigned int PCC_SAI0;
  /* PCC SAI1 Register */
  volatile unsigned int PCC_SAI1;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy15[4];
  /* PCC FlexIO Register */
  volatile unsigned int PCC_FlexIO;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy16[6];
  /* PCC EWM Register */
  volatile unsigned int PCC_EWM;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy17[4];
  /* PCC LPI2C0 Register */
  volatile unsigned int PCC_LPI2C0;
  /* PCC LPI2C1 Register */
  volatile unsigned int PCC_LPI2C1;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy18[2];
  /* PCC LPUART0 Register */
  volatile unsigned int PCC_LPUART0;
  /* PCC LPUART1 Register */
  volatile unsigned int PCC_LPUART1;
  /* PCC LPUART2 Register */
  volatile unsigned int PCC_LPUART2;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy19[1];
  /* PCC FTM4 Register */
  volatile unsigned int PCC_FTM4;
  /* PCC FTM5 Register */
  volatile unsigned int PCC_FTM5;
  /* PCC FTM6 Register */
  volatile unsigned int PCC_FTM6;
  /* PCC FTM7 Register */
  volatile unsigned int PCC_FTM7;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy20[1];
  /* PCC CMP0 Register */
  volatile unsigned int PCC_CMP0;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy21[2];
  /* PCC QSPI Register */
  volatile unsigned int PCC_QSPI;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy22[2];
  /* PCC ENET Register */
  volatile unsigned int PCC_ENET;
} PCC_Type;

#define PCC_BASE_ADDRS (0x40065000)
#define PCC ((PCC_Type*)PCC_BASE_ADDRS)


#endif  /* #if !defined(PCC_REGISTER_H_) */
