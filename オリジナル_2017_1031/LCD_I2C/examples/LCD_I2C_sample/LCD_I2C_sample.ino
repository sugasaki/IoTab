#include <Wire.h>
#include <LCD_I2C.h>
// Circuit
// RESET    - 1 RST
// Analog 5 - 2 SCL (internally pulled up)
// Analog 4 - 3 SDA (internally pulled up)
// GND      - 4 GND
// 5V       - 5 VSS

void setup()
{
  Serial.begin(9600);
  
  // LCD
  LCD.begin(30); // specify contrast

  LCD.move(0); // move cursor
  LCD.print("Welcome to");
  LCD.move(0x41); // move cursor to 2nd line
  LCD.print("Arduino");
  delay(3000);
}

void loop()
{
  LCD.clear();
  for (;;) {
    while (!Serial.available());
    byte c = Serial.read();
    if (c < 0x20) break;
    LCD.print(c);
  }
}