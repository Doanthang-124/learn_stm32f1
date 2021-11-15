#include "stm32f10x.h"                  // Device header

void enable_exti(void);
void gpio_config(void);
void config_exti(void);
//void EXTI0_IRQHandler(void);

void clear_pendingFlag(void);
int main(void)
{
		gpio_config();
	  config_exti();
	  enable_exti();

		while(1)
		{
		
		}
		
}
void config_exti(void)
{
		/*enable clock for AF*/	
		RCC->APB2ENR |= 0x01u;
		/*config external interrupt configuration register 1 - PA0 pin*/
		//AFIO->EXTICR[1] &= ~(0x0Fu);
		AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA;
		/*config Rising trigger selection resgiter*/
		EXTI->RTSR |= 0x01u;
	  EXTI->FTSR  = 0x00u;
}
void enable_exti(void)
{
		/*ebale external interrupt line 0*/ 
		EXTI->IMR |= 0x01u;
	  /*config exti_IRQ in NVIC*/
	  NVIC_EnableIRQ(EXTI0_IRQn);
	
}
void gpio_config(void)
{
	  RCC->APB2ENR |= (1 << 4); 
		GPIOC->CRH |= ((1<<20)|(1<<21));
		GPIOC->CRH &= ~(0x11u << 22);
}
void clear_pendingFlag(void)
{
		/*clear pending flag*/
		EXTI->PR |= 0x01u;
}
void EXTI0_IRQHandler(void)
{
	   clear_pendingFlag();
		 GPIOC->ODR ^= (1u << 13);
	   
}
