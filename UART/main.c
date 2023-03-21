#include "stm32f10x.h"                  // Device header

#update by thang doan van

int main(void)
{
		/*enable clock for UART1 adn GPIOA*/
		RCC->APB2ENR |= (1u << 14)|(1u << 2)|(1u << 0);
		/* config PA9 Alternate function */
		GPIOA->CRH |= (0x03u << 4)|(0x02u << 6);
		GPIOA->CRH |= (0x01 << 10);
		/*config remap pin for UART1 PA9PA10*/
		//AFIO->MAPR |= (1u << 2);
		/*config data baudrate 9600*/
		USART1->BRR = 0x1D4C;
		/*Enable interrupt flag*/
		USART1->CR1 |= USART_CR1_TXEIE|USART_CR1_RXNEIE;

		/*Enable UART1 RE, TE, UE*/
		USART1->CR1 |= USART_CR1_RE|USART_CR1_TE|USART_CR1_UE;
		/* Enable interrupt USART1*/
    NVIC_EnableIRQ( USART1_IRQn);
	
		while(1)
		{



		}
	
	
}
void USART1_IRQHandler(void)
{
			if(USART1->SR & USART_SR_RXNE)//if RXNE not empty
			{
				char temp = USART1->DR ;
				USART1->DR = temp;
				while(!(USART1->SR &USART_SR_TC));
			}
}

