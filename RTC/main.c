#include "stm32f10x.h"                  // Device header

void gpio_config(void);
void rtc_config(void);
void gpio_config(void)
{
    /* enable gpio clock */
		RCC->APB2ENR |= (1 << 4); 

		GPIOC->CRH |= ((1<<20)|(1<<21));
		//GPIOC->CRH &= ~((1u<<22)|(1u<<23));
		GPIOC->CRH &= ~(0x11u << 22);
}
void rtc_config(void)
{
		/* enable clock RTC */
		RCC->APB1ENR |= (0x18000000u);
		/* set the DBP bit the Power Control Register (PWR_CR) */
		PWR->CR |= (0x100u);
		/*LSE enable */
	  RCC->BDCR |= 0x01;
		while(((RCC->BDCR >> 1U) & (0x01U))!= 1U);
	  /*Set LSE as RTC clock*/
	  RCC->BDCR |= (0x0100u);
    RCC->BDCR |= (0x8000u);
		/* Configuring RTC registers */
		/* Poll RTOFF, wait until its value goes to '1'*/
		//while(((RTC->CRL >>5u) & 0x01u)!=1U);
		while((RTC->CRL & (0x20u)) == 0U);
 		/* Set the CNF bit to enter configuration mode */
		RTC->CRL |=(1u << 4);
		/* Write to Prescaler RTC registers */ /*32.268kHz*/
		RTC->PRLH = 0U;
		RTC->PRLL = 0x7fffu;
		/*Clear the CNF bit to exit configuration mode*/
		RTC->CRL &= ~(0x10U);	
		/* Poll RTOFF, wait until its value goes to '1'*/
		while(((RTC->CRL >>5u) & 0x01u)!=1U);
		
}
int main(void)
{
		uint32_t u32Counter = 0;
		rtc_config();
		gpio_config();
		while(1)
		{
			if((RTC->CRL & (0x01u))== 1U)
			{
				u32Counter++;
				RTC->CRL &= ~(0x01u);
				if(u32Counter%2 == 0u)
				{
					GPIOC->ODR &= ~(1u << 13);
				}
				else
				{
					GPIOC->ODR |= (1 << 13);
				}
			
			}
		}
}


