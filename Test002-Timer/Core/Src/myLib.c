/*
 * myLib.c
 *
 *  Created on: Nov 15, 2024
 *      Author: user
 */
#include "main.h"
extern UART_HandleTypeDef huart2;
//int __io_getchar(void)
int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, &ch, 1, 10 );
	return ch;
}

void StandBy()
{
	while(1)
	  {
		  if(!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13))
			  break;
	  }
}

void ProgramStart(char * str)
{
	printf("\033[2J\033[0;0H");
	printf("Program Start - %s\r\n",str);
	printf("Press Blue-button(B1) to Start...\r\n");
	StandBy();
}

