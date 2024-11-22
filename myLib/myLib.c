/*
 * myLib.c
 *
 *  Created on: Nov 15, 2024
 *      Author: user
 */
#include "main.h"
extern UART_HandleTypeDef huart2;
//I2C_HandleTypeDef *hi2c = NULL;

//#include "C:\Users\user\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.1\Drivers\STM32F4xx_HAL_Driver\inc\stm32f4xx_hal_i2c.h"

int __io_putchar(int ch) // Lowest output Function
{
   HAL_UART_Transmit(&huart2, &ch, 1, 10); // timeout: 10ms
   return ch;
}
void ProgramStart(char *str)
{
   //printf("\033[2J\033[0;0H"); // printf("\033[2J"); : 화면 Clear
   cls();
   Cursor(0,0);
   printf("Program Name - %s\r\n", str);
   printf("Press Blue-button(B1) to Start ...\r\n");
   standby();
}

void standby()
{
   while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin));
}

void cls() // 화면 clear
{
   printf("\033[2J");
}

void Cursor(int x, int y)
{
   char buf[20];
   sprintf(buf, "\033[%d;%dH", y,x);
   puts(buf);
}


