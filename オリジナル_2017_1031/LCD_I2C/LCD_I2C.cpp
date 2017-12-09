/*
 LCD_I2C: Strawberry Linux I2C LCD (ST7032i) Library for Arduino
   created by NeoCat <neocat@neocat.jp>
*/

#include "LCD_I2C.h"
#include <string.h>

LCD_I2C LCD;

void LCD_I2C::write(uint8_t pre, const uint8_t *x, int size)
{
  Wire.beginTransmission(LCD_addr);
  do {
    Wire.write(pre | (size ? 0x80 : 0));
    Wire.write(*x++);
  } while (--size);
  Wire.endTransmission();
}

void LCD_I2C::print(const char *s)
{
  write(0x40, (const uint8_t*)s, strlen(s));
}

void LCD_I2C::icon(uint8_t addr, uint8_t x)
{
  uint8_t cmd[] = {0x39, 0x40 | (addr&0xf)};
  write(0x00, cmd, sizeof(cmd));
  writeData(x);
  const uint8_t cmd2[] = {0x38, 0x80};
  write(0x00, cmd2, sizeof(cmd2));
}

void LCD_I2C::begin(uint8_t contrast)
{
  const uint8_t cmd2[] = {0x38, 0x0c, 0x01};

//  Wire.begin();

  // initialize the LCD
  delay(40);

  uint8_t cmd1[] = {
    0x38,
    0x39,
    0x14,
    0x70 | (contrast & 0x0f),
    0x5c | ((contrast >> 4) & 3), // for 3.3V
//    0x58 | ((contrast >> 4) & 3), // for 5V
    0x6c
  };

  write(0, cmd1, sizeof(cmd1));
  delay(250);
  write(0, cmd2, sizeof(cmd2));
  delay(1);
}

void LCD_I2C::end()
{
	delay(10);
	Wire.end();
	delay(10);
}
