/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, Fri Jul  5 09:57:24 2024

**
**     Abstract:
**         Peripheral Access Layer for module PORT
**     Author: MinhTri
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#if !defined(PORT_REGISTER_H_)  /* Check if memory map has not been already included */
#define PORT_REGISTER_H_

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/* PORT  */
typedef struct {
  /* Pin control register n */
  volatile unsigned int PORT_PCR0;
  volatile unsigned int PORT_PCR1;
  volatile unsigned int PORT_PCR2;
  volatile unsigned int PORT_PCR3;
  volatile unsigned int PORT_PCR4;
  volatile unsigned int PORT_PCR5;
  volatile unsigned int PORT_PCR6;
  volatile unsigned int PORT_PCR7;
  volatile unsigned int PORT_PCR8;
  volatile unsigned int PORT_PCR9;
  volatile unsigned int PORT_PCR10;
  volatile unsigned int PORT_PCR11;
  volatile unsigned int PORT_PCR12;
  volatile unsigned int PORT_PCR13;
  volatile unsigned int PORT_PCR14;
  volatile unsigned int PORT_PCR15;
  volatile unsigned int PORT_PCR16;
  volatile unsigned int PORT_PCR17;
  volatile unsigned int PORT_PCR18;
  volatile unsigned int PORT_PCR19;
  volatile unsigned int PORT_PCR20;
  volatile unsigned int PORT_PCR21;
  volatile unsigned int PORT_PCR22;
  volatile unsigned int PORT_PCR23;
  volatile unsigned int PORT_PCR24;
  volatile unsigned int PORT_PCR25;
  volatile unsigned int PORT_PCR26;
  volatile unsigned int PORT_PCR27;
  volatile unsigned int PORT_PCR28;
  volatile unsigned int PORT_PCR29;
  volatile unsigned int PORT_PCR30;
  volatile unsigned int PORT_PCR31;
  /* Global Pin Control Low Register */
  volatile unsigned int PORT_GPCLR;
  /* Global Pin Control High Register */
  volatile unsigned int PORT_GPCHR;
  /* Global Interrupt Control Low Register */
  volatile unsigned int PORT_GICLR;
  /* Global Interrupt Control High Register */
  volatile unsigned int PORT_GICHR;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy0[4];
  /* Interrupt Status Flag Register */
  volatile unsigned int PORT_ISFR;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy1[7];
  /* Digital Filter Enable Register */
  volatile unsigned int PORT_DFER;
  /* Digital Filter Clock Register */
  volatile unsigned int PORT_DFCR;
  /* Digital Filter Width Register */
  volatile unsigned int PORT_DFWR;
} PORT_Type;

#define PORTA_BASE_ADDRS (0x40049000)
#define PORTA ((PORT_Type*)PORTA_BASE_ADDRS)

#define PORTB_BASE_ADDRS (0x4004A000)
#define PORTB ((PORT_Type*)PORTB_BASE_ADDRS)

#define PORTC_BASE_ADDRS (0x4004B000)
#define PORTC ((PORT_Type*)PORTC_BASE_ADDRS)

#define PORTD_BASE_ADDRS (0x4004C000)
#define PORTD ((PORT_Type*)PORTD_BASE_ADDRS)

#define PORTE_BASE_ADDRS (0x4004D000)
#define PORTE ((PORT_Type*)PORTE_BASE_ADDRS)



#endif  /* #if !defined(PORT_REGISTER_H_) */
