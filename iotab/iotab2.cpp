/*
 *  iotab2.cpp
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

#include "iotab2.h"

// Define iotab instance
IOTAB2 iotab2;


int IOTAB2::start(int pin)
{
  /*
  if (pin > 0)
    _powerPin = pin;

  // Turn on 3GIM
  if (_powerPin > 0) {
    pinMode(_powerPin, OUTPUT);
    digitalWrite(_powerPin, HIGH);
    delay(200);
    digitalWrite(_powerPin, LOW);
  }

  a3gSerial.begin(9600);

  DEBUG_PRINT(">start()", "Turn on and wait for a moment..");

  delay(15000); // Wait for ready IEM

  DEBUG_PRINT(">start()", "IEM is available now.");

  return a3gsSUCCESS; // OK
  */
}



// begin() -- 
int IOTAB2::begin(void) {
  if (hasInitialized) return ioError;   // already had initialized
  iotab2.debug_write("1`..");

  // Set up GPIOs
  pinMode(io3gimPowerOnPin, OUTPUT); //9番ピン
  iotab2.debug_write("2..");

  digitalWrite(9, HIGH); delay(100);//待機重要
  iotab2.debug_write("3..");
  digitalWrite(9, LOW); delay(5); // 3G shield --> digitalWrite(7,HIGH);
  iotab2.debug_write("4..");
  
/*
  iotab2.turnOnOff3GIM(false); //電源切る
  iotab2.debug_write("3..");
  
  iotab2.turnOnOff3GIM(true); //電源入れる
  iotab2.debug_write("4..");
   */
   
  //LEDのつけ忘れ解除のためにLED消す
  LedSetIoTab(false); //IoTab側
  LedSetGIM(false); //3GIM側
  iotab2.debug_write("3..");
  //
 // pinMode(ioTactSwitchPin, INPUT_PULLUP);
 
  //3GIMが起動するまで待つ
  iotab2.waitWakeUp3Gim();

  // 
  hasInitialized = true;
  return ioSuccess;
}


//電源の入れ直し
void IOTAB2::turnOnOff3GIM() {
  pinMode(io3gimPowerOnPin, OUTPUT);
  digitalWrite(io3gimPowerOnPin, HIGH); 
  delay(100);//待機重要
  //※この間にSerialUSB.println等、余計な処理を入れると動作が固まるので入れては行けない。
  digitalWrite(io3gimPowerOnPin, LOW); 
  delay(5);
}

/*
//
// 3GIMの電源をON／OFF する。
// true : 電源をON
// false: 電源をOFF
void IOTAB2::turnOnOff3GIM(bool on) {
  //iotab2.debug_write("on=.." + String(on) );
  digitalWrite(io3gimPowerOnPin, on ? LOW : HIGH);  // Turn on

  //wait 
  if (on){
    //iotab2.debug_write("delay 5ms...");
    delay(5) ;
  }else{
    //iotab2.debug_write("delay 1000ms...");
    delay(100);//OFF時には100ms待機する。    
  }
  //iotab2.debug_write("turnOnOff3GIM end..." );
}
*/





//
String IOTAB2::gpsBegin(){
   iotab2.debug_write("1..");

  Serial.println("$YA 1"); //ATコマンドパススルーモード切換え
  delay(20);
  //Serial.println("at+wppp=2,4,\"\",\"\"");
  Serial.println("at+wppp=2,4,\"sora\",\"sora\"");
    iotab2.debug_write("1..");
       
  delay(10);
  Serial.println("at+gpsnmea=1,,1");
  delay(10);
   iotab2.debug_write("1..");
   
  //>>が返ってくるまで待機
  String str;
  do {
    str = Serial.readStringUntil('\n');
    debug_write(str);
  } while (str.indexOf(">>") < 0);

}



//３GIMが起動するまで待機する
String IOTAB2::waitWakeUp3Gim() {
  iotab2.debug_write("start waitWakeUp3Gim...");

  String str;
  do {
      while (!Serial.available());
      str = Serial.readStringUntil('\n');
      iotab2.debug_write(str);
  } while (str.indexOf("3GIM") < 0);
  
  iotab2.debug_write("Connected!");

}


//
// IoTab側のLEDをOn/Offする。
// setLed() --
// for example
// iotab2.LedSetIoTab(true);
// 
void IOTAB2::LedSetIoTab(bool on) {
  int sw = on ? HIGH : LOW;
  digitalWrite(ioLed2Pin, sw);
}


int IOTAB2::getVIN(void) {
#define NCOUNTS   5
  int mV = 0;
  for (int n = 0; n < NCOUNTS; n++) {
    mV += analogRead(ioInputVoltagePin) * 4.0 * 3.236;
    delay(10);
  }

  return (mV / NCOUNTS);  
}

/*
//============== get date   =================
String gpsDateTime() {
  String dtime1 = datetime();
  String dtime2 = dtime1.substring(11);
if DEBUG Serial.println("dtime1 = " + dtime1);
if DEBUG Serial.println("dtime2 = " + dtime2);

  return dtime1;
}
*/

//============== get Date Time  =================
String IOTAB2::GetDateTimeBy3G() {
  String dtim;
  if DEBUG Serial.println("start--- datetime");
  uint32_t tm = millis();
  
  do {
    while (!Serial1);
    Serial.println("$YT"); delay(10);
    if DEBUG Serial.println("$YT");
    while (!Serial.available());
    dtim = Serial.readStringUntil('\n');
    if DEBUG Serial.println(dtim);
    delay(100);
  } while ( !(dtim.indexOf("201") == 7) );
  
  dtim.replace(" ", "T"); dtim.replace("/", "-");
  dtim.replace(":", "");
  return (dtim.substring(7));
}









//3gim light on / off
String IOTAB2::GetGPS(String method , String option){
  
  method = method == "" ? "x" : method;
  option = option == "" ? "0" : method;
  
  String command = "$LG " + method + " " + option;
  String gps = sendCommand_Gps(command); //GPSを取得
  return gps;
}


String IOTAB2::sendCommand_Gps(String com) {

  int interval = 200000; //timeoutInterval
  Serial.setTimeout(interval); // タイムアウト設定
  String result;
  bool isTimeout = false;
  
  uint32_t tm = millis();//タイムアウト処理用に現在秒を取得

  debug_write("1");

  //シリアルがONになるまで待つ. ここでタイムアウトは不要？
  while (!Serial1);
  debug_write("2");

  //シリアル経由でコマンドを投げる
  Serial.println(com);
  debug_write("3");

  //シリアアルからの応答を待つ.20秒でタイムアウト
  while (true) {
    if (Serial.available() > 0){
      if (millis() >= tm + interval) {
        debug_write("isTimeout");
        isTimeout = true;
        break;
      }
      
      debug_write("4");
      result = Serial.readStringUntil('\n');
      debug_write(result);
      debug_write("5");
        
      break;
    }
    
    if (millis() >= tm + interval) {
      debug_write("isTimeout");
      isTimeout = true;
      break;
    }
  }
  
  if (isTimeout == true) {
    Serial.setTimeout(500); // タイムアウト設定
    String a  = Serial.readStringUntil('\n');
    debug_write("読み残し" + a);
    debug_write("3gim begin");
    begin();
  }

  debug_write("6");

  return (result);
}






//==============   LED on/off   =================


//3gim light on / off
String IOTAB2::LedSetGIM(bool on){
  return sendCommand_led(on ? ledCommandOn : ledCommandOff);
}

String IOTAB2::sendCommand_led(String com) {
  if(Serial){
      debug_write("Serial OK");
  }else{
     debug_write("Serial NG"); 
  }
  int interval = 6000; //timeoutInterval
  Serial.setTimeout(interval); // タイムアウト設定
  String result;
  bool isTimeout = false;
  
  uint32_t tm = millis();//タイムアウト処理用に現在秒を取得

  debug_write("1");

  //シリアルがONになるまで待つ. ここでタイムアウトは不要？
  while (!Serial1);
  debug_write("2");

  //シリアル経由でコマンドを投げる
  Serial.println(com);
  debug_write("3");

  //シリアアルからの応答を待つ.20秒でタイムアウト
  while (true) {
    if (Serial.available() > 0){
      if (millis() >= tm + interval) {
        debug_write("isTimeout");
        isTimeout = true;
        break;
      }
      
      debug_write("4");
      result = Serial.readStringUntil('\n');
      debug_write(result);
      debug_write("5");
        
      break;
    }
    
    if (millis() >= tm + interval) {
      debug_write("isTimeout");
      isTimeout = true;
      break;
    }
  }
  
  if (isTimeout == true) {
    Serial.setTimeout(500); // タイムアウト設定
    String a  = Serial.readStringUntil('\n');
    debug_write("読み残し" + a);

    debug_write("3gim begin");
    begin();
  }

/*
  //制限時間以内に応答があれば、応答を取得する。
  if (isTimeout == false) {
    debug_write("5");
   Serial.setTimeout(2000); // タイムアウト設定（15秒）
   if (Serial.available() > 0) result = Serial.readStringUntil('\n');
    debug_write("6");
  }else{
    result = "ng";
  }
*/

  debug_write("6");

  return (result);
}



void IOTAB2::debug_write(String value){
  if DEBUG SerialUSB.println(value);
}


// END

