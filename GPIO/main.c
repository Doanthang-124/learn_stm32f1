#include "_HAL_GPIO.h"
#include "stm32f10x.h"                  // Device header


void Delay_ms(uint32_t ms);
void Delay_ms(uint32_t ms)
{

	for(uint32_t i = 0;i < ms;i++)
	 for(volatile uint32_t j = 0; j < 525; j++);
}


int  main(void)
{

	GPIO_TYPE myGpio;
	
	myGpio.port = PORTC;
	myGpio.pin  = 13;
	myGpio.mode = OUTPUT_MODE;
	myGpio.mode_type = OUT_PUSH_PULL;
	myGpio.speed = SPEED_50MHZ;
	
	gpio_init(myGpio);


	while(1)
	{
		gpio_write(PORTC, 13,0);
		for(int i = 0; i < 5000000; i++);
		gpio_write(PORTC, 13,1);
		for(int i = 0; i < 5000000; i++);
	}
	
}





