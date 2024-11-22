/*
 * lcd1602.c
 *
 *  Created on: Nov 21, 2024
 *      Author: user
 *   Function   :   1602 LCD device control
 */

#include "main.h"
extern I2C_HandleTypeDef *hi2c;
//extern I2C_HandleTypeDef hi2c2; // 이거보단 포인터 타입이 낫다

#define I2C_ADDR 0x4E // 0x27 << 1
I2C_HandleTypeDef *hi2c = NULL;

int i2c_init(I2C_HandleTypeDef *p)
{
   hi2c = p;
}
int i2c_scan()
{
   if(hi2c == NULL) return;
   for(int addr = 0; addr < 128; addr++)
   {
      if(HAL_I2C_IsDeviceReady(hi2c, addr, 1, 10) == HAL_OK)
      {
         printf(" %02x ", addr);
      }
      else
      {
         printf("  . ");
      }
      if((addr % 16) == 0) printf("\r\n");
   }
}


void lcd_command(char cmd) // cmd_bit : abcd efgh
{
   char n1, n2, n3, n4, dd[4];
   n1 = cmd & 0xf0; // 상위 4비트만 가져오겠다 n1: abcd_0000 upper nibble
   n2 = (cmd & 0x0f) << 4; // 하위 4비트만 가져오겠다 n2: efgh_0000 lower hibble to upper
   n3 = (1<<3) | (1<<2) | 0 | 0; // RW | EN_1 | NC | RS => 0x0c
   n4 = (1<<3) | 0      | 0 | 0; // RW | EN_0 | NC | RS => 0x08
   // RS = 0: cmd, RS = 1: data
   dd[0] = n1 | n3; // nibble은 enable신호가 1과 0이 반복될 때까지 동일한 신호값이 유지가 되어야 한다
   dd[1] = n1 | n4;
   dd[2] = n2 | n3;
   dd[3] = n2 | n4;
   HAL_I2C_Master_Transmit(hi2c, I2C_ADDR, dd, 4, 10);
}

void lcd_data(char ch)
{
   char n1, n2, n3, n4, dd[4];
   n1 = ch & 0xf0; // 상위 4비트만 가져오겠다 n1: abcd_0000 upper nibble
   n2 = (ch & 0x0f) << 4; // 하위 4비트만 가져오겠다 n2: efgh_0000 lower hibble to upper
   n3 = (1<<3) | (1<<2) | 0 | (1<<0); // RW | EN_1 | NC | RS => 0x0d
   n4 = (1<<3) | 0      | 0 | (1<<0); // RW | EN_0 | NC | RS => 0x09
   // RS = 0: cmd, RS = 1: data
   dd[0] = n1 | n3; // nibble은 enable신호가 1과 0이 반복될 때까지 동일한 신호값이 유지가 되어야 한다
   dd[1] = n1 | n4;
   dd[2] = n2 | n3;
   dd[3] = n2 | n4;
   HAL_I2C_Master_Transmit(hi2c, I2C_ADDR, dd, 4, 10);

}

void lcd_init()
{
   lcd_command(0x01); // screen clear
   lcd_command(0x02); // cursor home
   lcd_command(0x06);
   lcd_command(0x0f);
   HAL_Delay(10);
}

void lcd_print(char *str)
{
   while(*str)lcd_data(*str++);
}
void lcd_printEx(char *str, int ln)
{
	if(ln == 0)lcd_command(0x80);
	if(ln) lcd_command(0xc0);
	lcd_print(str);
}


