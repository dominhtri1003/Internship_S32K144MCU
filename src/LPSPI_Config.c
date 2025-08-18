#include "LPSPI_Config.h"

void LPSPI0_CONFIG(void);
void LPSPI2_CONFIG(void);

void LPSPI1_CONFIG(void)
{
	/* Step 1: */
	/* Disable clock to modify PCS */
	PCC->PCC_LPSPI1 &= ~(1<<30);
	PCC->PCC_LPSPI1 |= 6<<24;		/* Enable PCS=SPLL_DIV2 (36 MHz clock) */
	PCC->PCC_LPSPI1 |= (1<<30); 	/* enable clock */
	
	/* Step 2: */
	LPSPI1->CR = 0x00000000; 		/* Disable module for configuration */
	LPSPI1->IER = 0x00000000; 		/* Interrupts not used */
	LPSPI1->DER = 0x00000000; 		/* DMA not used */
	LPSPI1->CFGR0 = 0x00000000; 	/* Default */

	/* Step 3: */
	/* CFGR1 - 0x00000009 */
	LPSPI1->CFGR1 |= 1<<0; 			/* Master mode */
	LPSPI1->CFGR1 &= ~(1<<1); 		/* SAMPLE=0: Input data is sampled on SCK edge */
	LPSPI1->CFGR1 &= ~(1<<2); 		/* AUTOPCS=0: Automatic PCS generation is disabled */
	LPSPI1->CFGR1 |= (1<<3); 		/* NOSTALL=1: Transfers will not stall when the transmit FIFO is empty */
	LPSPI1->CFGR1 &= ~(0xF<<8); 	/* PCSPOL=0: PCS is active low */
	LPSPI1->CFGR1 &= ~(0x7<<16); 	/* MATCH=0: Match disable */
	LPSPI1->CFGR1 &= ~(0x3<<24); 	/* PINCFG=0: SIN is input, SOUT is output - default */
	LPSPI1->CFGR1 &= ~(1<<26); 		/* OUTCFG=0: Output data retains last value when CS negated */
	LPSPI1->CFGR1 &= ~(1<<27); 		/* PCSCFG=0: PCS[3:2] are enabled */
	
	/* Step 4: */
	/* TCR - Transmit command register - 0x5310000F */
	uint32_t SPI_TCR_CONFIG = LPSPI1->TCR;
	SPI_TCR_CONFIG &= ~(0xFFF<<0);	
	SPI_TCR_CONFIG |= 0xF<<0; 		/* FRAMESZ=15: # bits in frame = 15+1=16 */
	SPI_TCR_CONFIG &= ~(0x3<<16); 	/* WIDTH=0: Single bit transfer */
	SPI_TCR_CONFIG &= ~(1<<18); 	/* Transmit Data Mask = 0: Normal transfer */
	SPI_TCR_CONFIG &= ~(1<<19); 	/* Receive Data Mask = 0: Normal transfer */
	SPI_TCR_CONFIG &= ~(1<<20);
	SPI_TCR_CONFIG &= ~(1<<21); 	/* Continuous transfer disabled */
	SPI_TCR_CONFIG &= ~(1<<22); 	/* Byte Swap disabled */
	SPI_TCR_CONFIG &= ~(1<<23); 	/* Data is transferred MSB first */
	SPI_TCR_CONFIG |= 3<<24; 		/* Transfer using LPSPI_PCS[3] */
	SPI_TCR_CONFIG |= 2<<27; 		/* Prescaler = 2 -> divide by 2*2 => 36MHz/4 = 9MHz */
	SPI_TCR_CONFIG &= ~(1<<30); 	/* CPHA = 0: Data sampled on leading edge (first edge) */
	SPI_TCR_CONFIG &= ~(1<<31); 	/* CPOL = 0: The inactive state value of SCK is low */
	LPSPI1->TCR = SPI_TCR_CONFIG;

	/* Step 5: */
	/* CCR: Clk dividers based on prescaled func'l clk of 111.111 nsec */
	uint32_t SPI_CCR_CONFIG = LPSPI1->CCR;
	SPI_CCR_CONFIG |= 7<<0; 		/* SCKDIV = 7 => Div 7+2 => 9MHz/9 = 1MHz */
	SPI_CCR_CONFIG |= 7<<8; 		/* DBT=7: Delay between Transfers = 7+2 = 9 (1 usec)  */
	SPI_CCR_CONFIG |= 8<<16; 		/* PCSSCK=8: PCS to SCK delay = 8+1 = 9 (1 usec) */
	SPI_CCR_CONFIG |= 4<<24; 		/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (5.555 nsec) */
	LPSPI1->CCR = SPI_CCR_CONFIG;

	/* Step 6: */
	/* FCR - FIFO control register */
	LPSPI1->FCR |= 3<<0; 			/* Tx flags set when Tx FIFO <= 3  */
	LPSPI1->FCR &= ~(3<<16); 		/* RXWATER=0: Rx flags set when Rx FIFO > 0  */

	/* Step 7: */
	/* CR - Control register */
	LPSPI1->CR &= ~(1<<1); 			/* Module is not reset */
	LPSPI1->CR &= ~(1<<2); 			/* module is enabled in doze mode */
	LPSPI1->CR |= 1<<3; 			/* Module is enabled in debug mode */
	LPSPI1->CR |= 1<<0; 			/* Module is enabled */
}

void PORT_SPI_CONFIG(void)
{
	PCC->PCC_PORTB |= 1<<30;
	/* Config mux */
	PORTB->PORT_PCR14 |= 3<<8;
	PORTB->PORT_PCR15 |= 3<<8;
	PORTB->PORT_PCR16 |= 3<<8;
	PORTB->PORT_PCR17 |= 3<<8;
}

void SPI1_Send(uint16_t SendData)
{
	// Check flag TDF
	while(!(LPSPI1->SR & 1<<0));
	LPSPI1->TDR = SendData;
}