/*
 LCD_I2C: Strawberry Linux I2C LCD (ST7032i) Library for Arduino
   created by NeoCat <neocat@neocat.jp>
*/

#ifndef LCD_I2C_h
#define LCD_I2C_h	1

#include <math.h>
#include <Arduino.h>
#include <Wire.h>

// Circuit
// RESET    - 1 RST
// Analog 5 - 2 SCL (internally pulled up)
// Analog 4 - 3 SDA (internally pulled up)
// GND      - 4 GND
// 5V       - 5 VSS

class LCD_I2C {
  const static uint8_t LCD_addr = 0x3e;

  void write(uint8_t pre, const uint8_t *x, int size);
  void writeCmd(uint8_t x)  { write(0x00, &x, 1); }
  void writeData(uint8_t x) { write(0x40, &x, 1); }

public:
  void begin(uint8_t contrast = 15);
  void end(void);

  void print(const char *s);
  void print(char c) { writeData(c); }
  void icon(uint8_t addr, uint8_t x);
  void move(uint8_t p) { writeCmd(0x80 | p); }
  void clear() { writeCmd(0x01); delay(2); move(0); }
};

extern LCD_I2C LCD;

#endif // LCD_I2C_h
