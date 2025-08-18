/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, Fri Jul  5 09:57:24 2024

**
**     Abstract:
**         Peripheral Access Layer for module GPIO
**     Author: MinhTri
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#if !defined(GPIO_REGISTER_H_)  /* Check if memory map has not been already included */
#define GPIO_REGISTER_H_

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/* GPIO  */
typedef struct {
  /* Port Data Output Register */
  volatile unsigned int PDOR;
  /* Port Set Output Register */
  volatile unsigned int PSOR;
  /* Port Clear Output Register */
  volatile unsigned int PCOR;
  /* Port Toggle Output Register */
  volatile unsigned int PTOR;
  /* Port Data Input Register */
  volatile const unsigned int PDIR;
  /* Port Data Direction Register */
  volatile unsigned int PDDR;
  /* Port Input Disable Register */
  volatile unsigned int PIDR;
} GPIO_Type;

// GPIOA: một con trỏ kiểu GPIO_Type trỏ tới địa chỉ GPIOA_BASE_ADDRS
// GPIOA->PDDR
#define GPIOA_BASE_ADDRS (0x400FF000)
#define GPIOA ((GPIO_Type*)GPIOA_BASE_ADDRS)

#define GPIOB_BASE_ADDRS (0x400FF040)
#define GPIOB ((GPIO_Type*)GPIOB_BASE_ADDRS)

#define GPIOC_BASE_ADDRS (0x400FF080)
#define GPIOC ((GPIO_Type*)GPIOC_BASE_ADDRS)

#define GPIOD_BASE_ADDRS (0x400FF0C0)
#define GPIOD ((GPIO_Type*)GPIOD_BASE_ADDRS)

#define GPIOE_BASE_ADDRS (0x400FF100)
#define GPIOE ((GPIO_Type*)GPIOE_BASE_ADDRS)



#endif  /* #if !defined(GPIO_REGISTER_H_) */
