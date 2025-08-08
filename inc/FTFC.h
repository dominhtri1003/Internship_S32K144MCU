#ifndef FTFC_H
#define FTFC_H

#include <stdint.h>
#include <stdio.h>
#include "MY_LIBRARY.h"

/** FTFC - Size of Registers Arrays */
#define FTFC_FCCOB_COUNT 12u
#define FTFC_FPROT_COUNT 4u

/** FTFC - Register Layout Typedef */
typedef struct
{
    volatile uint8_t FSTAT;                   /**< Flash Status Register, offset: 0x0 */
    volatile uint8_t FCNFG;                   /**< Flash Configuration Register, offset: 0x1 */
    volatile uint8_t FSEC;                    /**< Flash Security Register, offset: 0x2 */
    volatile uint8_t FOPT;                    /**< Flash Option Register, offset: 0x3 */
    volatile uint8_t FCCOB[FTFC_FCCOB_COUNT]; /**< Flash Common Command Object Registers, array offset: 0x4, array step: 0x1 */
    volatile uint8_t FPROT[FTFC_FPROT_COUNT]; /**< Program Flash Protection Registers, array offset: 0x10, array step: 0x1 */
    uint8_t RESERVED_0[2];
    volatile uint8_t FEPROT; /**< EEPROM Protection Register, offset: 0x16 */
    volatile uint8_t FDPROT; /**< Data Flash Protection Register, offset: 0x17 */
    uint8_t RESERVED_1[20];
    volatile uint8_t FCSESTAT; /**< Flash CSEc Status Register, offset: 0x2C */
    uint8_t RESERVED_2[1];
    volatile uint8_t FERSTAT; /**< Flash Error Status Register, offset: 0x2E */
    volatile uint8_t FERCNFG; /**< Flash Error Configuration Register, offset: 0x2F */
} FTFC_Type, *FTFC_MemMapPtr;

/** Number of instances of the FTFC module. */
#define FTFC_INSTANCE_COUNT (1u)

/* FTFC - Peripheral instance base addresses */
/** Peripheral FTFC base address */
#define FTFC_BASE (0x40020000u)
/** Peripheral FTFC base pointer */
#define FTFC ((FTFC_Type *)FTFC_BASE)
/** Array initializer of FTFC peripheral base addresses */
#define FTFC_BASE_ADDRS {FTFC_BASE}
/** Array initializer of FTFC peripheral base pointers */
#define FTFC_BASE_PTRS {FTFC}
/** Number of interrupt vector arrays for the FTFC module. */
#define FTFC_IRQS_ARR_COUNT (2u)
/** Number of interrupt channels for the COMMAND_COMPLETE type of FTFC module. */
#define FTFC_COMMAND_COMPLETE_IRQS_CH_COUNT (1u)
/** Number of interrupt channels for the READ_COLLISION type of FTFC module. */
#define FTFC_READ_COLLISION_IRQS_CH_COUNT (1u)
/** Interrupt vectors for the FTFC peripheral type */
#define FTFC_COMMAND_COMPLETE_IRQS {FTFC_IRQn}
#define FTFC_READ_COLLISION_IRQS {Read_Collision_IRQn}


#endif