// Low power interrupt

#include "LPIT_Config.h"
#include "LPIT_Register.h"
#include "PCC_Register.h"

/*Hàm LPIT_Config(channel, timerSecond) làm các việc sau:

Bật ngắt NVIC cho LPIT channel tương ứng.

Bật clock và nguồn clock (LPO 128kHz) cho LPIT.

Bật LPIT module và cho phép hoạt động khi debug.

Gán thời gian timer theo giá trị đầu vào.

Cấu hình chế độ periodic 32-bit và bật timer kênh đó.
*/

void LPIT_Config(int channel, float timerSecond)
{
	// Base address of NVIC_ISER1
  *(volatile uint32_t *)(0xE000E104) |= 1<<(16+channel); /* nvic LPIT0 */

	PCC->PCC_LPIT |= 7<<24; /* PCS = LPO128_CLK */
	PCC->PCC_LPIT |= 1<<30; /* Enable clock */

	LPIT->MCR |= 1<<0; /* MCEN = 1 - Module clock enable */
	LPIT->MCR |= 1<<3; /* DBG_EN = 1 - Debug enable */

	LPIT->MIER |= 1<<channel; /* TIM0 interrupt enable */

  	int timerVal = 0;
  	timerVal = (int)(timerSecond*128000);

	// LPIT->TVAL0 = timerVal; /* TIM0 Val start */
  	*(volatile uint32_t *)(LPIT_BASE_ADDRS+0x20+0x10*channel) = timerVal;

	// LPIT->TCTRL0 &= ~(3<<2); /* TIM0 MODE 00 32bit periodic counter */
	// LPIT->TCTRL0 |= 1<<0; /* TIM0 channel 0 enable */
	*(volatile uint32_t *)(LPIT_BASE_ADDRS+0x28+0x10*channel) &= ~(1<<0); /* Disable timer channel */
  	*(volatile uint32_t *)(LPIT_BASE_ADDRS+0x28+0x10*channel) &= ~(3<<2); /* 32-bit Periodic counter */
  	*(volatile uint32_t *)(LPIT_BASE_ADDRS+0x28+0x10*channel) |= 1<<0;	  /* Enable timer */
}


// Tắt timer cho kênh LPIT cụ thể
void LPIT_Disable(int channel)
{
	*(volatile uint32_t *)(LPIT_BASE_ADDRS+0x28+0x10*channel) &= ~(1<<0); /* Disable timer channel */
}         