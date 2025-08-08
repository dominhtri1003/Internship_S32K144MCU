#pragma once
#ifndef CLOCK_AND_MODES_H
#define CLOCK_AND_MODES_H

#define FIRC_CLK_SOURCE 48000000
#define SIRC2MHZ_CLK_SOURCE 2000000
#define SIRC8MHZ_CLK_SOURCE 8000000
#define SOSC_CLK_SOURCE 8000000

#define MODE_CCR_SCS_SOSC 1
#define MODE_CCR_SCS_SIRC 2
#define MODE_CCR_SCS_FIRC 3
#define MODE_CCR_SCS_SPLL 6

#define CLOCK_DIV1_3BIT 0
#define CLOCK_DIV2_3BIT 8
#define CLOCKDIV_0_DISABLE 0
#define CLOCKDIV_DIV_BY_1 1
#define CLOCKDIV_DIV_BY_2 2
#define CLOCKDIV_DIV_BY_4 3
#define CLOCKDIV_DIV_BY_8 4
#define CLOCKDIV_DIV_BY_16 5
#define CLOCKDIV_DIV_BY_32 6
#define CLOCKDIV_DIV_BY_64 7

#define SPLL_SOSC_SOURCE 0
#define SPLL_FIRC_SOURCE 1

#define SIRC_2MHZ 0
#define SIRC_8MHZ 1

void SOSC_INIT_8MHZ(void);
void FIRC_INIT(void);
/* SIRC_Range = SIRC_2MHZ OR SIRC_8MHZ */
void SIRC_INIT(int SIRC_Range);
void SPLL_INIT(int SPLL_Source, int SPLL_Source_Clk, int SPLL_Clk);
void NORMAL_RUN_MODE(int SCS, int Core_Source_Clk, int Core_Clk, int BUS_Clk, int FLASH_Clk);

#endif