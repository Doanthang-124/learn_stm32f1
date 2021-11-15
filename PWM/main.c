#include "stm32f10x.h"                  // Device header

void enable_clock(void);
void blink_led(void);
void Delay_ms(uint32_t u32Delay);
void gpio_config(void);
void time2_config(void);

int main(void)
{
		enable_clock();
		gpio_config();
		time2_config();
		while(1)
		{
			blink_led();	
		}
		
}
void enable_clock(void)
{
		/* enable clock for TIM2 */
		RCC->APB1ENR |= 0x01u;
		/* enable clock for GPIOC and GPIOA */
		RCC->APB2ENR |= (1u << 4)|(1u << 2); 

	
}
void gpio_config(void)
{
		/*config PC13 output*/
		GPIOC->CRH |= ((1<<20)|(1<<21));
		GPIOC->CRH &= ~(0x11u << 22);
		/*config PA0 Altenate function push pull*/
		GPIOA->CRL |= 0x03u;
		GPIOA->CRL |= (1u << 4);
		
}
void time2_config(void)
{
		/*Auto-reload preload enable*/
		TIM2->CR1 |=	(1u << 1);
		/* enable update event */
		TIM2->CR1 |=  (1u << 2);
		/*init timer2*/
		TIM2->CNT = 0;
		TIM2->PSC = 72;
		TIM2->ARR = 1000;

		/*config PWM mode*/
		/*init value of CRR register*/
		TIM2->CCR1 = 500;
		TIM2->CCMR1 |= 0x60;
		/*enalbe PWM mode 1*/
		TIM2->CCMR1|= (1u << 3);
		/*the auto-reload preload register ARPE bit in the TIMx_CR1 registe*/
	  TIM2->CR1 |= (1u << 7);
		/*setting the UG bit*/
		TIM2->EGR |= (1u << 2);
		/*enable ouput-> set bit CCxE */
		TIM2->CCER |= 0x01;
		/*Counter enable*/
		TIM2->CR1 |= 0x01u;
		TIM2->EGR = 0x01u;
		
		
}
void blink_led(void)
{
	
		GPIOC->ODR |= (1 << 13);
		Delay_ms(2000);
		GPIOC->ODR &= ~(1u << 13);
		Delay_ms(2000);
	
}
void Delay_ms(uint32_t u32Delay)
{
		
		while(u32Delay)
		{
			  TIM2->CNT = 0u;
				while( TIM2->CNT < 1000);
				u32Delay--;
		}
}
