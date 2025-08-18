#include "clock_and_modes.h"
#include "SCG_Register.h"
#include <stdint.h>

void SOSC_INIT_8MHZ(void)
{
	/* Disable the System Oscillator (SOSC) to Allow Configuration */
	uint32_t SOSCCSR_CONFIG = SCG->SCG_SOSCCSR;
	SOSCCSR_CONFIG &= ~(1<<23);				/* LK = 0: SOSCCSR can be written */
	SCG->SCG_SOSCCSR = SOSCCSR_CONFIG;
	SOSCCSR_CONFIG &= ~(1<<0);				/* SOSCEN = 0: System OSC is disabled */
	SCG->SCG_SOSCCSR = SOSCCSR_CONFIG;
	
	/* SOSCDIV config */
	uint32_t SOSCDIV_CONFIG = SCG->SCG_SOSCDIV;
	SOSCDIV_CONFIG &= ~(0x7<<0 | 0x7<<8);
	SOSCDIV_CONFIG |= (CLOCKDIV_DIV_BY_1<<0 | CLOCKDIV_DIV_BY_1<<8);	/* SOSCDIV1 = SOSCDIV2 = 001: divide by 1  */
	SCG->SCG_SOSCDIV = SOSCDIV_CONFIG;									/* SOSC_DIV1_CLK = SOSC_DIV2_CLK = 8MHz */

	/* SOSCCFG config */
	uint32_t SOSCCFG_CONFIG = SCG->SCG_SOSCCFG;
	SOSCCFG_CONFIG |= 1<<2;					/* EREFS = 1: Internal crystal oscillator of OSC selected */
	SOSCCFG_CONFIG &= ~(1<<3);				/* HGO = 0: low-gain operation */
	SOSCCFG_CONFIG &= ~(0x3<<4);
	SOSCCFG_CONFIG |= 2<<4;					/* RANGE = 10: Medium frequency range (1-8MHz) */
	SCG->SCG_SOSCCFG = SOSCCFG_CONFIG;

	/* SOSCCSR config -> Enable SOSC */
	SOSCCSR_CONFIG = SCG->SCG_SOSCCSR;
	SOSCCSR_CONFIG &= ~(1<<23);				/* LK = 0: SOSCCSR can be written */
	SCG->SCG_SOSCCSR = SOSCCSR_CONFIG;
	SOSCCSR_CONFIG &= ~(1<<17);				/* SOSCCMRE = 0: Clock Monitor generates interrupt when error detected */
	SOSCCSR_CONFIG &= ~(1<<16);				/* SOSCCM = 0: System OSC Clock Monitor is disabled */
	SOSCCSR_CONFIG |= 1<<0;					/* SOSCEN = 1: System OSC is enabled */
	SCG->SCG_SOSCCSR = SOSCCSR_CONFIG;
	while(!(SCG->SCG_SOSCCSR & 1<<24));		/* Wait for System OSC is enabled and output clock is valid (SOSCVLD = 1) */
}

void FIRC_INIT(void)
{
	/* When FIRC is disable */
	uint32_t FIRCCSR_CONFIG = SCG->SCG_FIRCCSR;
	FIRCCSR_CONFIG &= ~(1<<23);	/* LK = 0: FIRCCSR can be written */
	SCG->SCG_FIRCCSR = FIRCCSR_CONFIG;
	FIRCCSR_CONFIG &= ~(1<<0);	/* FIRCEN = 0: FIRC is disabled */
	SCG->SCG_FIRCCSR = FIRCCSR_CONFIG;

	/* FIRCDIV Config */
	uint32_t FIRCDIV_CONFIG = SCG->SCG_FIRCDIV;
	FIRCDIV_CONFIG &= ~(0x7<<0 | 0x7<<8);
	FIRCDIV_CONFIG |= (CLOCKDIV_DIV_BY_1<<0 | CLOCKDIV_DIV_BY_1<<8);	/* FIRCDIV1 = FIRCDIV2 = 001: divide by 1 => FIRC_DIV1_CLK = FIRC_DIV2_CLK = 8MHz */
	SCG->SCG_FIRCDIV = FIRCDIV_CONFIG;

	/* FIRCCFG Config */
	uint32_t FIRCCFG_CONFIG = SCG->SCG_FIRCCFG;
	FIRCCFG_CONFIG &= ~(3<<0);	/* Range = 00 */
	SCG->SCG_FIRCCFG = FIRCCFG_CONFIG;

	/* FIRCCSR Config */
	FIRCCSR_CONFIG = SCG->SCG_FIRCCSR;
	FIRCCSR_CONFIG &= ~(1<<23);	/* LK = 0: FIRCCSR can be written */
	SCG->SCG_FIRCCSR = FIRCCSR_CONFIG;
	FIRCCSR_CONFIG &= ~(1<<3);	/* FIRCREGOFF = 0: Fast IRC Regulator is enabled */
	FIRCCSR_CONFIG |= 1<<0;			/* FIRCEN = 1: FIRC is enabled */
	SCG->SCG_FIRCCSR = FIRCCSR_CONFIG;
	while(!(SCG->SCG_FIRCCSR & 1<<24));	/* Wait for FIRC is enabled and output clock is valid (FIRCVLD = 1) */
}

void SIRC_INIT(int SIRC_Range)
{
	/* When SIRC is disable */
	uint32_t SIRCCSR_CONFIG = SCG->SCG_SIRCCSR;
	SIRCCSR_CONFIG &= ~(1<<23);	/* LK = 0: SIRCCSR can be written */
	SCG->SCG_SIRCCSR = SIRCCSR_CONFIG;
	SIRCCSR_CONFIG &= ~(1<<0);	/* SIRCEN = 0: SIRC is disabled */
	SCG->SCG_SIRCCSR = SIRCCSR_CONFIG;

	/* SIRCDIV Config */
	uint32_t SIRCDIV_CONFIG = SCG->SCG_SIRCDIV;
	SIRCDIV_CONFIG &= ~(0x7<<0 | 0x7<<8);
	SIRCDIV_CONFIG |= (CLOCKDIV_DIV_BY_1<<0 | CLOCKDIV_DIV_BY_1<<8);	/* SIRCDIV1 = SIRCDIV2 = 001: divide by 1 => SIRC_DIV1_CLK = SIRC_DIV2_CLK = 8MHz */
	SCG->SCG_SIRCDIV = SIRCDIV_CONFIG;

	/* SIRCCFG Config */
	uint32_t SIRCCFG_CONFIG = SCG->SCG_SIRCCFG;
	if (SIRC_Range == SIRC_2MHZ)
	{
		SIRCCFG_CONFIG &= ~(1<<0);
	}
	else if (SIRC_Range == SIRC_8MHZ)
	{
		SIRCCFG_CONFIG |= 1<<0;
	}
	SCG->SCG_SIRCCFG = SIRCCFG_CONFIG;

	/* SIRCCSR Config */
	SIRCCSR_CONFIG = SCG->SCG_SIRCCSR;
	SIRCCSR_CONFIG &= ~(1<<23);	/* LK = 0: SIRCCSR can be written */
	SCG->SCG_SIRCCSR = SIRCCSR_CONFIG;
	SIRCCSR_CONFIG &= ~(1<<2);	/* SIRCLPEN = 0: Slow IRC is disabled in VLP modes */
	SIRCCSR_CONFIG &= ~(1<<1);	/* SIRCSTEN = 0: Slow IRC is disabled in supported Stop modes */
	SIRCCSR_CONFIG |= 1<<0;			/* SIRCEN = 1: SIRC is enabled */
	SCG->SCG_SIRCCSR = SIRCCSR_CONFIG;
	while(!(SCG->SCG_SIRCCSR & 1<<24));	/* Wait for SIRC is enabled and output clock is valid (SIRCVLD = 1) */
}

void SPLL_INIT(int SPLL_Source, int SPLL_Source_Clk, int SPLL_Clk)
{
	/* When SPLL is disabled */
	uint32_t SPLLCSR_CONFIG = SCG->SCG_SPLLCSR;
	SPLLCSR_CONFIG &= ~(1<<23);	/* LK = 0: SPLLCSR can be written */
	SCG->SCG_SPLLCSR = SPLLCSR_CONFIG;
	SPLLCSR_CONFIG &= ~(1<<0); 	/* SPLLEN = 0: System PLL is disabled */
	SCG->SCG_SPLLCSR = SPLLCSR_CONFIG;

	/* SPLLDIV config */
	uint32_t SPLLDIV_CONFIG = SCG->SCG_SPLLDIV;
	SPLLDIV_CONFIG &= ~(0x7<<CLOCK_DIV1_3BIT | 0x7<<CLOCK_DIV2_3BIT);
	SPLLDIV_CONFIG |= (CLOCKDIV_DIV_BY_2<<CLOCK_DIV1_3BIT | CLOCKDIV_DIV_BY_4<<CLOCK_DIV2_3BIT);
	SCG->SCG_SPLLDIV = SPLLDIV_CONFIG;

	/* SPLLCFG config: SPLL_Clk = 144MHz, VCO_CLK = 288MHz = SOURCE/(PREDIV + 1)*(MULT + 16) */
	uint32_t SPLLCFG_CONFIG = SCG->SCG_SPLLCFG;
	if (SPLL_Source == SPLL_SOSC_SOURCE)
	{
		SPLLCFG_CONFIG &= ~(1<<0);	/* SPLL SOURCE = 0: SOSC */
	}
	else SPLLCFG_CONFIG |= (1<<0);	/* SPLL SOURCE = 1: FIRC */
	SPLLCFG_CONFIG &= ~(0x7<<8 | 31<<16);
	int PreDivFactor = 1, MultFactor = 16;
	for (MultFactor = 16; MultFactor <= 47; MultFactor++)
	{
		for (PreDivFactor = 1; PreDivFactor <= 8; PreDivFactor++)
		{
			if (SPLL_Clk*2 == SPLL_Source_Clk/(PreDivFactor)*MultFactor)
			{
				break;
			}
		}
		if (SPLL_Clk*2 == SPLL_Source_Clk/(PreDivFactor)*MultFactor)
		{
			break;
		}
	}
	/* PreDivFactor: 1-8 */
	SPLLCFG_CONFIG |= (PreDivFactor-1)<<8;	/* PREDIV = PreDivFactor - 1 */
	/* MultFactor: 16-47 */
	SPLLCFG_CONFIG |= (MultFactor-16)<<16;	/* MULT = MultFactor - 16 */
	SCG->SCG_SPLLCFG = SPLLCFG_CONFIG;

	/* SPLLCSR config -> Enable SPLL */
	SPLLCSR_CONFIG = SCG->SCG_SPLLCSR;
	SPLLCSR_CONFIG &= ~(1<<23);	/* LK = 0: SPLLCSR can be written */
	SCG->SCG_SPLLCSR = SPLLCSR_CONFIG;
	SPLLCSR_CONFIG &= ~(1<<17);	/* SPLLCMRE = 0: Clock Monitor generates interrupt when error detected */
	SPLLCSR_CONFIG &= ~(1<<16);	/* SPLLCCM = 0: System PLL Clock Monitor is disabled */
	SPLLCSR_CONFIG |= 1<<0; 		/* SPLLEN = 1: System PLL is enabled */
	SCG->SCG_SPLLCSR = SPLLCSR_CONFIG;
	while(!(SCG->SCG_SPLLCSR & 1<<24)); /* Wait for System PLL is enabled and output clock is valid (SPLLVLD = 1) */
}

void NORMAL_RUN_MODE(int SCS, int Core_Source_Clk, int Core_Clk, int BUS_Clk, int FLASH_Clk)
{
	/* RCCR config */
	uint32_t RCCR_CONFIG = SCG->SCG_RCCR;
	RCCR_CONFIG &= ~(0xF<<24);
	RCCR_CONFIG |= SCS<<24;		/* SPLL is System Clock Source */

	int DivCoreFactor, DivBusFactor, DivSlowFactor;

	RCCR_CONFIG &= ~(0xF<<16);
	DivCoreFactor = Core_Source_Clk/Core_Clk;
	RCCR_CONFIG |= (DivCoreFactor-1)<<16;		/* DIVCORE: CORE_CLK = 144/2 = 72MHz */

	RCCR_CONFIG &= ~(0xF<<4);
	DivBusFactor = Core_Clk/BUS_Clk;
	RCCR_CONFIG |= (DivBusFactor-1)<<4; 		/* DIVBUS: BUS_CLK = 72/2 = 36MHz */

	RCCR_CONFIG &= ~(0xF<<0);
	DivSlowFactor = Core_Clk/FLASH_Clk;
	RCCR_CONFIG |= (DivSlowFactor-1)<<0;		/* DIVSLOW: FLASH_CLK = 72/4 = 18MHz */
	
	SCG->SCG_RCCR = RCCR_CONFIG;

	/* Check current configured system clock */
	while(SCG->SCG_CSR != SCG->SCG_RCCR);	/* Wait for CSR = RCCR */
}