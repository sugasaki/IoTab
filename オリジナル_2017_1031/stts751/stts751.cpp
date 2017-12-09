/*
 *	stts751.cpp - Digital temperature sensor STTS751 control library
 *
 */

#include <Wire.h>
#include "stts751.h" 

// Symbols
#define STTS751_I2C_ADDDR  	0b0111001

// begin() - 
void STTS751::begin() {
    Wire.beginTransmission(STTS751_I2C_ADDDR);
    Wire.write(0x03);
    Wire.write(0b10001100);
    Wire.endTransmission();
}

// getTemperature() - 
int STTS751::getTemperature() {
	Wire.beginTransmission(STTS751_I2C_ADDDR);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(STTS751_I2C_ADDDR, 1);
    int ip = Wire.read();

    Wire.beginTransmission(STTS751_I2C_ADDDR);
    Wire.write(0x02);
    Wire.endTransmission();
    Wire.requestFrom(STTS751_I2C_ADDDR, 1);
    int np = (Wire.read() >> 4) * 625;
	
	return ((ip * 10) + ((np + 500) / 1000));
}

// End of stts751.cpp