/*
 *  iotab.h
 *
 *  Control library for IoTAB(Compact Arduino Module for IoT)
 *
 *  Release:
 *   - R1.0  2017.10.10  1st Release(A.D)
 *
 *  Notes:
 *   - For controlling peripheral devices, you can use the following library included:
 *       RTCZero, mma8451q, stts751, lcdi2c,
 *
 *  Copyright(c) 2017 TABrain Inc. All rights reserved.
 */

#ifndef _iotab2_H_
#define _iotab2_H_

#include <Arduino.h>

/*
 *  Constants
 */
#define ioSuccess     0
#define ioError       1
/*
 *  Define pins
 */ 
#define io3gimPowerOnPin  9     // 3GIM PWR_ON pin
#define ioTactSwitchPin   5     // Tact switch pin (0:pushed/1:released)
#define ioLed2Pin     13      // LED2 pin (0:turn off/1:turn on) - same as pre-defined LED_BUILTIN
#define ioMMA8451QInt1Pin 6     // INT1 pin of MMA8451Q
#define ioMMA8451QInt2Pin 7     // INT2 pin of MMA8451Q
#define ioInputVoltagePin A5      // Pins that can read 1/4 of the input voltage

/*
 *  Serial port
 */
#define ioSerial      SerialUSB // USB Serial port(not Serial)
#define io3gimSerial    Serial    // 3GIM Serial port



#define ledCommandOn "$YL 1"  //LED ON Command
#define ledCommandOff "$YL 0"   //LED OFF Command

#define timeoutInterval 50000  //TIMEOUT

#define DEBUG (1)

/*
 *  Class iotab
 */
class IOTAB2 {
  public:

    int start(int );

    // Board control
    int begin(void);          // Begin to use the iotab

    //３GIMが起動するまで待機する
    String waitWakeUp3Gim();

    String gpsBegin();

    
    // LED2 control
    void LedSetIoTab(bool);          // Turn led1 on(1) or off(0)


    // 3GIM control
    void turnOnOff3GIM();        // Turn on/Off 3GIM
    
    // 3GIM control
    //void turnOnOff3GIM(bool);        // Turn on/Off 3GIM

    // Supply power control
    int getVIN(void);         // return value: Supply voltage(VBAT) [mV]

    //3gim light on/off
    String LedSetGIM(bool); //3gim light on/off

    //3G経由で時刻取得
    String GetDateTimeBy3G();

    //
    String GetGPS(String method = "", String option = ""); //

    void debug_write(String);
  

  private:
    boolean hasInitialized = false;
    void (*alarmHandler)(void) = NULL;

    String sendCommand_led(String);
    String sendCommand_Gps(String);
    
};


extern IOTAB2  iotab2;

#endif // _iotab_H_

