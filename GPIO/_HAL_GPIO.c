#include "_HAL_GPIO.h"
#include <stdint.h>

uint32_t PINPOS[16] ={
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C)	
};

 static void gpio_config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type){
		if(pinNumber >= 8)
		{
			switch(mode_type)
			{
				case OUT_PUSH_PULL | INPUT_ANALOG:
					port->CRH &= ~((1u << CNF_POS_BIT1)|(1u << CNF_POS_BIT2));
				  break;
				case OUT_OP | INPUT_FLOAT:
					port->CRH &= ~(1u << CNF_POS_BIT2);
				  port->CRH |= (1u << CNF_POS_BIT1);
					break;
				case AF_PUSH_PULL | INPUT_PU_PD:
					port->CRH |= (1u << CNF_POS_BIT1);
					break;
				case AF_OP:
					port->CRH |= (AF_OP << CNF_POS_BIT1);
				break;
			}
		}
		else
		{
			switch(mode_type)
			{
				case OUT_PUSH_PULL | INPUT_ANALOG:
					port->CRL &= ~((1u << CNF_POS_BIT1)|(1u << CNF_POS_BIT2));
				  break;
				case OUT_OP | INPUT_FLOAT:
					port->CRL &= ~(1u << CNF_POS_BIT2);
				  port->CRL |= (1u << CNF_POS_BIT1);
					break;
				case AF_PUSH_PULL | INPUT_PU_PD:
					port->CRL |= (1u << CNF_POS_BIT1);
					break;
				case AF_OP:
					port->CRL |= (AF_OP << CNF_POS_BIT1);
				break;
			}					
		}
}
 static void gpio_config_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode){
	
		if(pinNumber >= 8)
		{
			if(mode == INPUT_MODE)
			{
				port->CRH &= ~((1 << (PINPOS[pinNumber])) | (1u << (PINPOS[pinNumber] + 1u)));
			}
			else
			{
				port->CRH |= (pinSpeed << pinNumber);
			}
		}
		else
		{
			if(mode == INPUT_MODE)
			{
				port->CRL &= ~((1 << (PINPOS[pinNumber])) | (1u << (PINPOS[pinNumber] + 1u)));
			}
			else
			{
				port->CRL |= (pinSpeed << pinNumber);
			}			
		}
}
 void gpio_init(GPIO_TYPE gpio_type){
	
	if(gpio_type.port == PORTA)
		GPIO_CLOCK_ENABLE_GPIOA;
  else if(gpio_type.port == PORTB)
		   GPIO_CLOCK_ENABLE_GPIOB;
	else if(gpio_type.port == PORTC)
			 GPIO_CLOCK_ENABLE_GPIOC;
	else if(gpio_type.port == PORTD)
			 GPIO_CLOCK_ENABLE_GPIOD;

	
	gpio_config_pin(gpio_type.port, gpio_type.pin, gpio_type.mode_type);
	gpio_config_speed(gpio_type.port, gpio_type.pin, gpio_type.speed ,gpio_type.mode );
}
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state){
		if(state)
		{
			port->BSRR |= (1u << pinNumber);
		}
		else
		{
			port->BSRR |= (1u << (pinNumber+16));
		}
	}
void gpio_toogle(GPIO_TypeDef *port, uint32_t pinNumber){
		port->BSRR ^= (1u << pinNumber);
}
