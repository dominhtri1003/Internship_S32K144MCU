/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, Fri Jul  5 09:57:24 2024

**
**     Abstract:
**         Peripheral Access Layer for module LPIT
**     Author: MinhTri
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#if !defined(LPIT_REGISTER_H_)  /* Check if memory map has not been already included */
#define LPIT_REGISTER_H_

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/* LPIT  */
typedef struct {
  /* Version ID Register */
  volatile const unsigned int VERID;
  /* Parameter Register */
  volatile const unsigned int PARAM;
  /* Module Control Register */
  volatile unsigned int MCR;
  /* Module Status Register */
  volatile unsigned int MSR;
  /* Module Interrupt Enable Register */
  volatile unsigned int MIER;
  /* Set Timer Enable Register */
  volatile unsigned int SETTEN;
  /* Clear Timer Enable Register */
  volatile unsigned int CLRTEN;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy23[1];
  /* Timer Value Register */
  volatile unsigned int TVAL0;
  /* Current Timer Value */
  volatile const unsigned int CVAL0;
  /* Timer Control Register */
  volatile unsigned int TCTRL0;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy24[1];
  /* Timer Value Register */
  volatile unsigned int TVAL1;
  /* Current Timer Value */
  volatile const unsigned int CVAL1;
  /* Timer Control Register */
  volatile unsigned int TCTRL1;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy25[1];
  /* Timer Value Register */
  volatile unsigned int TVAL2;
  /* Current Timer Value */
  volatile const unsigned int CVAL2;
  /* Timer Control Register */
  volatile unsigned int TCTRL2;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy26[1];
  /* Timer Value Register */
  volatile unsigned int TVAL3;
  /* Current Timer Value */
  volatile const unsigned int CVAL3;
  /* Timer Control Register */
  volatile unsigned int TCTRL3;
} LPIT_Type;

#define LPIT_BASE_ADDRS (0x40037000)
#define LPIT ((LPIT_Type*)LPIT_BASE_ADDRS)


#endif  /* #if !defined(LPIT_REGISTER_H_) */
