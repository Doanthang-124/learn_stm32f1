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
		/* enable clock for GPIOC */
		RCC->APB2ENR |= (1 << 4); 
}
void gpio_config(void)
{
		GPIOC->CRH |= ((1<<20)|(1<<21));
		GPIOC->CRH &= ~(0x11u << 22);
}
void time2_config(void)
{
		/*Auto-reload preload enable*/
		TIM2->CR1 |=	(1u << 1);
		/* enable update event */
		TIM2->CR1 |=  (1u << 2);
		/* init timer2*/
		TIM2->CNT = 0;
		TIM2->PSC = 72;
		TIM2->ARR = 1000;
	
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
