#include "GPIO_Config.h"
#include "GPIO_Register.h"
#include "PCC_Register.h"
#include "PORT_Register.h"
#include <stdint.h>

void GPIO_Input_Config(char GPIO_Port, int Port_Pin)
{
    switch (GPIO_Port)
    {
    case 'A':
        /* Enable Port Clock */
        PCC->PCC_PORTA |= 1<<30;

        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTA_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTA_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Input Pin Config */
        GPIOA->PDDR &= ~(1<<Port_Pin);

        break;

    case 'B':
        /* Enable Port Clock */
        PCC->PCC_PORTB |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTB_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTB_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Input Pin Config */
        GPIOB->PDDR &= ~(1<<Port_Pin);
        
        break;

    case 'C':
        /* Enable Port Clock */
        PCC->PCC_PORTC |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTC_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTC_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Input Pin Config */
        GPIOC->PDDR &= ~(1<<Port_Pin);
        
        break;

    case 'D':
        PCC->PCC_PORTD |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTD_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTD_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Input Pin Config */
        GPIOD->PDDR &= ~(1<<Port_Pin);
        
        break;

    case 'E':
        /* Enable Port Clock */
        PCC->PCC_PORTE |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTE_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTE_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Input Pin Config */
        GPIOE->PDDR &= ~(1<<Port_Pin);
        
        break;
    
    default:
        break;
    }
}

void GPIO_Output_Config(char GPIO_Port, int Port_Pin)
{
    switch (GPIO_Port)
    {
    case 'A':
        /* Enable Port Clock */
        PCC->PCC_PORTA |= 1<<30;

        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTA_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTA_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Output Pin Config */
        GPIOA->PDDR |= 1<<Port_Pin;

        break;

    case 'B':
        /* Enable Port Clock */
        PCC->PCC_PORTB |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTB_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTB_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Output Pin Config */
        GPIOB->PDDR |= 1<<Port_Pin;
        
        break;

    case 'C':
        /* Enable Port Clock */
        PCC->PCC_PORTC |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTC_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTC_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Output Pin Config */
        GPIOC->PDDR |= 1<<Port_Pin;
        
        break;

    case 'D':
        PCC->PCC_PORTD |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTD_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTD_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Output Pin Config */
        GPIOD->PDDR |= 1<<Port_Pin;
        
        break;

    case 'E':
        /* Enable Port Clock */
        PCC->PCC_PORTE |= 1<<30;
        
        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTE_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0x07<<8); 
        *(volatile uint32_t *) (PORTE_BASE_ADDRS + 0x0 + 4*Port_Pin) |= 1<<8; /* MUX = 001 GPIO */

        /* Output Pin Config */
        GPIOE->PDDR |= 1<<Port_Pin;
        
        break;
    
    default:
        break;
    }
}

void GPIO_Input_Interrupt_Config(char GPIO_Port, int Port_Pin, int detectType)
{
    /* Detect Type = bit 19-16 */
    switch (GPIO_Port)
    {
    case 'A':
        *(volatile uint32_t *)(0xE000E104) |= 1<<27; /* Interrupt Set-enable Port A (ID 59) */

        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTA_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0xF<<16); /* Clear bit 19-16 */
        *(volatile uint32_t *) (PORTA_BASE_ADDRS + 0x0 + 4*Port_Pin) |= detectType<<16; /* Interrupt detect type */

        break;
    
    case 'B':
        *(volatile uint32_t *)(0xE000E104) |= 1<<28; /* Interrupt Set-enable Port B (ID 60) */

        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTB_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0xF<<16); /* Clear bit 19-16 */
        *(volatile uint32_t *) (PORTB_BASE_ADDRS + 0x0 + 4*Port_Pin) |= detectType<<16; /* Interrupt detect type */

        break;

    case 'C':
        *(volatile uint32_t *)(0xE000E104) |= 1<<29; /* Interrupt Set-enable Port C (ID 61) */

        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTC_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0xF<<16); /* Clear bit 19-16 */
        *(volatile uint32_t *) (PORTC_BASE_ADDRS + 0x0 + 4*Port_Pin) |= detectType<<16; /* Interrupt detect type */

        break;

    case 'D':
        *(volatile uint32_t *)(0xE000E104) |= 1<<30; /* Interrupt Set-enable Port D (ID 62) */

        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTD_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0xF<<16); /* Clear bit 19-16 */
        *(volatile uint32_t *) (PORTD_BASE_ADDRS + 0x0 + 4*Port_Pin) |= detectType<<16; /* Interrupt detect type */

        break;

    case 'E':
        *(volatile uint32_t *)(0xE000E104) |= 1<<31; /* Interrupt Set-enable Port E (ID 63) */

        /* PORT_PCRn Config */
        *(volatile uint32_t *) (PORTE_BASE_ADDRS + 0x0 + 4*Port_Pin) &= ~(0xF<<16); /* Clear bit 19-16 */
        *(volatile uint32_t *) (PORTE_BASE_ADDRS + 0x0 + 4*Port_Pin) |= detectType<<16; /* Interrupt detect type */

        break;
    
    default:
        break;
    }
}