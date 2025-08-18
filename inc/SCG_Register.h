/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, Fri Jul  5 09:57:24 2024

**
**     Abstract:
**         Peripheral Access Layer for module SCG
**     Author: MinhTri
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#if !defined(SCG_REGISTER_H_)  /* Check if memory map has not been already included */
#define SCG_REGISTER_H_

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/* SCG  */
typedef struct {
  /* Version ID Register */
  volatile const unsigned int SCG_VERID;
  /* Parameter Register */
  volatile const unsigned int SCG_PARAM;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy2[2];
  /* Clock Status Register */
  volatile const unsigned int SCG_CSR;
  /* Run Clock Control Register */
  volatile unsigned int SCG_RCCR;
  /* VLPR Clock Control Register */
  volatile unsigned int SCG_VCCR;
  /* HSRUN Clock Control Register */
  volatile unsigned int SCG_HCCR;
  /* SCG CLKOUT Configuration Register */
  volatile unsigned int SCG_CLKOUTCNFG;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy3[55];
  /* System OSC Control Status Register */
  volatile unsigned int SCG_SOSCCSR;
  /* System OSC Divide Register */
  volatile unsigned int SCG_SOSCDIV;
  /* System Oscillator Configuration Register */
  volatile unsigned int SCG_SOSCCFG;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy4[61];
  /* Slow IRC Control Status Register */
  volatile unsigned int SCG_SIRCCSR;
  /* Slow IRC Divide Register */
  volatile unsigned int SCG_SIRCDIV;
  /* Slow IRC Configuration Register */
  volatile unsigned int SCG_SIRCCFG;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy5[61];
  /* Fast IRC Control Status Register */
  volatile unsigned int SCG_FIRCCSR;
  /* Fast IRC Divide Register */
  volatile unsigned int SCG_FIRCDIV;
  /* Fast IRC Configuration Register */
  volatile unsigned int SCG_FIRCCFG;
  /* Add the dummy byte data to fulfill struct */
  unsigned int dummy6[189];
  /* System PLL Control Status Register */
  volatile unsigned int SCG_SPLLCSR;
  /* System PLL Divide Register */
  volatile unsigned int SCG_SPLLDIV;
  /* System PLL Configuration Register */
  volatile unsigned int SCG_SPLLCFG;
} SCG_Type;

#define SCG_BASE_ADDRS (0x40064000)
#define SCG ((SCG_Type*)SCG_BASE_ADDRS)


#endif  /* #if !defined(SCG_REGISTER_H_) */
