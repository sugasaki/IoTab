/*
 *	Sample skect for IoTAB - 3GIM Monitor
 */

#include <iotab.h>

const unsigned long baudrate = 9600;

void setup() {
  while (! ioSerial)
    ;
  ioSerial.begin(9600);

  // Set up iotab
  if (iotab.begin() != ioSuccess) {
    ioSerial.println("iotab.begin(): error.");
    while (1)
      ;       // Stop here
  }

  // Reset and power on 3GIM
  iotab.turnOff3GIM();
  delay(2000);
  iotab.turnOn3GIM();

  // begin iemSerial
  io3gimSerial.begin(baudrate);

  ioSerial.println("Ready.");
}

void loop() {
  if (io3gimSerial.available() > 0) {
    char c = io3gimSerial.read();
    ioSerial.print(c);
  }

  if (ioSerial.available() > 0) {
    char c = ioSerial.read();
    io3gimSerial.print(c);
    ioSerial.print(c);    // Echo back
  }  
}

