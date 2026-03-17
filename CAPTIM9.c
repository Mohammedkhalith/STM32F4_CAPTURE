#include"stm32f401xe.h"
#include"stdint.h"
#include<stdio.h>

#define GPIOAEN (0X1UL<<0U)

#define MODER3_AF_0010 (0X2UL<<6U)
#define AFRL3_AF03_0011 (0X3UL<<12U)

#define RS (1U<<8)
#define RW (1U<<9)
#define EN (1U<<10)

#define TIM9EN (0X1UL<<16U)
#define CC2S_0001 (0X1UL<<8U)
#define CC2E_0001 (0X1UL<<4U)
#define CEN_0001 (0X1UL<<0U)

void delay_ms(uint32_t ms)
{
    for(uint32_t i=0;i<ms*4000;i++);
}

void lcd_cmd(unsigned char cmd)
{
    GPIOA->ODR &= ~0x00FF;
    GPIOA->ODR |= cmd;

    GPIOA->ODR &= ~RS;
    GPIOA->ODR &= ~RW;
    GPIOA->ODR |= EN;
    delay_ms(2);
    GPIOA->ODR &= ~EN;
}

void lcd_data(unsigned char data)
{
    GPIOA->ODR &= ~0x00FF;
    GPIOA->ODR |= data;

    GPIOA->ODR |= RS;
    GPIOA->ODR &= ~RW;
    GPIOA->ODR |= EN;
    delay_ms(2);
    GPIOA->ODR &= ~EN;
}

void lcd_init()
{
    delay_ms(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void TIM9_INPUT_CAPTURE()
{

	RCC->AHB1ENR |= GPIOAEN;

	// Configure PA3 as alternate function (AF3 for TIM9_CH2)
	GPIOA->MODER |= MODER3_AF_0010;
	GPIOA->AFR[0] |= AFRL3_AF03_0011;

    // Timer 9 configuration
	RCC->APB2ENR |= TIM9EN;
	TIM9->PSC = 16000 - 1 ;
	TIM9->ARR = 4000 ;
	TIM9->CNT = 0 ;

	TIM9->CCMR1 |= CC2S_0001;
	TIM9->CCER |= CC2E_0001;
	TIM9->CR1 |= CEN_0001;
}

int main()
{
	RCC->AHB1ENR |= GPIOAEN;

    GPIOA->MODER &= ~(0x003FFFFF);
	GPIOA->MODER |=  (0x00155555);

	char result[50];

	lcd_init();
	TIM9_INPUT_CAPTURE();

	lcd_cmd(0x80);
	lcd_string("CAPTURED VALUE");

	while(1)
	{
		lcd_cmd(0xc0);
		sprintf(result,"%04lu",TIM9->CCR2);
		lcd_string(result);
	}
}
