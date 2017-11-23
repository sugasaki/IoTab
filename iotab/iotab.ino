// Sample skecth for iotab - Blink LED2
const unsigned long baudrate = 115200;
//const unsigned long baudrate = 9600;

#include "iotab.h"

#define DEBUG (1)
String gps;
void setup() {
  if DEBUG SerialUSB.begin(baudrate);
  Serial.begin(baudrate);
 
  //3GIMの電源を入れ直す
  iotab.begin();

  iotab.gpsBegin();

  //gps init
  iotab.gpsBegin();
  iotab.debug_write("\n----------- gps init -------------");


  //LEDを５回点滅させる
  for (int i = 0; i < 5; i++) {
    iotab.LedSetGIM(true); delay(10);
    iotab.LedSetGIM(false); delay(10);
  }
  
  iotab.debug_write("\n----------- ready -------------");

}

#define INTERVAL  (50)

void loop() {
    Serial.setTimeout(10000); // タイムアウト設定

    static unsigned long tim = millis(); //現在の通算秒をtimにセット

    //String date = iotab.GetDateTimeBy3G();
    //iotab.debug_write("date=" + date);

    /*
    String result = Serial.readStringUntil('\n');
    iotab.debug_write("result:" + result);

    gps = iotab.GetGPS(); //GPSを取得
    iotab.debug_write("GPS=" + gps);
*/

}



