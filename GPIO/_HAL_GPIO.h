#ifndef _HAL_GPIO_
#define _HAL_GPIO_

#include "stm32f10x.h"

#define HIGH 1
#define LOW 0
/* Port name */
#define PORTA GPIOA
#define PORTB GPIOB
#define PORTC GPIOC
#define PORTD GPIOD

/* Pin mode */
#define INPUT_MODE    (uint32_t)(0x02)
#define OUTPUT_MODE   (uint32_t)(0x01)

/* Input mode */
#define INPUT_ANALOG     (uint32_t)(0x00)
#define INPUT_FLOAT      (uint32_t)(0x01)
#define INPUT_PU_PD  (uint32_t)(0x02)

/* Output mode */
#define OUT_PUSH_PULL (uint32_t)(0x00)
#define OUT_OP        (uint32_t)(0x01)
#define AF_PUSH_PULL  (uint32_t)(0x02)
#define AF_OP         (uint32_t)(0x03)

/* Pin speed */
#define SPEED_2MHZ    (uint32_t)(0x02)
#define SPEED_10MHZ   (uint32_t)(0x01)
#define SPEED_50MHZ   (uint32_t)(0x03)

/* clock enable */
#define GPIO_CLOCK_ENABLE_ALT_FUNC 		(RCC->APB2ENR |= (1u << 0))
#define GPIO_CLOCK_ENABLE_GPIOA				(RCC->APB2ENR |= (1u << 2))
#define GPIO_CLOCK_ENABLE_GPIOB	 			(RCC->APB2ENR |= (1u << 3))
#define GPIO_CLOCK_ENABLE_GPIOC				(RCC->APB2ENR |= (1u << 4))
#define GPIO_CLOCK_ENABLE_GPIOD				(RCC->APB2ENR |= (1u << 5))

#define CNF_POS_BIT1 									(PINPOS[pinNumber] + 2)
#define CNF_POS_BIT2 									(PINPOS[pinNumber] + 3)

typedef struct {
	GPIO_TypeDef *port;
	uint32_t pin;
	uint32_t mode_type;
	uint32_t mode;
	uint32_t pull;
	uint32_t speed;
	uint32_t alt_fcn;
}GPIO_TYPE;

 static void gpio_config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type);
 static void gpio_config_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode);
void gpio_init(GPIO_TYPE gpio_type);

 void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state);
 void gpio_toogle(GPIO_TypeDef *port, uint32_t pinNumber);

#endif



