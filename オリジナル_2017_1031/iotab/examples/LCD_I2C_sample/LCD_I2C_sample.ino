// Sample sketch for iotab - I2C LCD(Akiduki mini I2C LCD)

#include <Wire.h>
#include <iotab.h>
#include <LCD_I2C.h>

void setup()
{
  Wire.begin();
  iotab.begin();
  
  LCD.begin(30); // specify contrast

  LCD.move(0); // move cursor
  LCD.print("Welcome to");
  LCD.move(0x41); // move cursor to 2nd line
  LCD.print("Arduino");
  delay(3000);
}

void loop()
{
    static int count = 0;
    char buf[9];
    count++;

    LCD.clear();
    sprintf(buf, "%d", count);
    LCD.move(0); // move cursor
    LCD.print(buf);

    delay(1000);
}

