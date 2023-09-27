#include "stm32f10x.h"                  // Device header

void enable_clock(void);
void blink_led(void);
void Delay_ms(uint32_t u32Delay);
void gpio_config(void);
void adc_config(void);

int main(void)
{
	 float u16AdcValue;
		enable_clock();
		gpio_config();
		adc_config();
		while(1)
		{
			u16AdcValue = ((ADC1->DR)/4096u)*3.3f;
		}
		
}
void enable_clock(void)
{
		/* enable clock for ADC1 */
		RCC->APB1ENR |= (1u << 9)|(1u << 1);
		/* enable clock for GPIOC and GPIOA */
		RCC->APB2ENR |= (1u << 4)|(1u << 2); 

		
}
void gpio_config(void)
{
		/*config PC13 output*/
		GPIOC->CRH |= ((1<<20)|(1<<21));
		GPIOC->CRH &= ~(0x11u << 22);
		/*config PA0 analog mode*/
		GPIOA->CRL &= ~0x03u;
		GPIOA->CRL |= (1u << 4);
		
}
void adc_config(void)
{
		/* config clock divide 6 <14MHz*/
//		RCC->CFGR |= 0x80;
//		RCC->CFGR &= ~(1u << 14);
		RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
		/*adc1 channel 0*/
		ADC1->CR1 &=	~0x08u;
		/*ADC sample time register 1.5 Cycles */
		ADC1->SMPR2 &= ~0x08u;
		/*Independence mode*/
		ADC1->CR1 &= 0x0f00;
		/*Disable scan mode*/
		ADC1->CR1 &= (1u << 8);
	  /**/
		ADC1->SQR3 |= ADC_SQR3_SQ1_0;
	  /* continuous mode */
		ADC1->CR1 |= (1u<<2);
	  /*enable and start adc*/
	  ADC1->CR2 |= 0x03;
		


		
		
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
abc
def
xxx