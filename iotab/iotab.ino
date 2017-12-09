const unsigned long baudrate = 115200;
#include "iotab.h"`
#include "iotab2.h"`
#include "a3gim2.h"

#define INTERVAL  (50)

#define LIMITTIME 60000 // ms (3G module start time
#define TGPS  10000
#define TMGPS 60000
#define DEBUG (1)

String URL    = "http://sugasaki.com/3gim/makefile.php?file=";
//String URL = "http://tachibanawangan.com/wan-navi-receiver/api/RunnerSave/";

String fname;
String dtime;
String gps;
String imei;

//2015-12-03T14:42:29$+09:00 | 35.64641833 139.6129596
// ---------------- setup ----------------
void setup() {
  
  while (! SerialUSB);
  

  if (iotab.begin() != SerialUSB) {
    ioSerial.println("iotab.begin(): error.");
    while (1)
      ;       // Stop here
  }

  /*
  delay(3000);
  if DEBUG SerialUSB.begin(baudrate);
  Serial.begin(baudrate);


  if DEBUG   SerialUSB.println("start 3GIM setup()");
  if DEBUG   SerialUSB.println("電源切る");

  pinMode(9, OUTPUT);
  //digitalWrite(9, HIGH); delay(100);//待機重要
  digitalWrite(9, LOW); delay(5); // 3G shield --> digitalWrite(7,HIGH);


  //digitalWrite(io3gimPowerOnPin, HIGH); delay(100);  // Turn on
  //if DEBUG   SerialUSB.println("電源切った");
  //digitalWrite(io3gimPowerOnPin, LOW); delay(5);  // Turn on
  iotab.turnOnOff3GIM(); //電源入れ直し

  if DEBUG   SerialUSB.println("電源入れた");


if DEBUG   SerialUSB.println("on off");


  String str;
  do {
    while (!Serial.available());
    str = Serial.readStringUntil('\n');
if DEBUG     SerialUSB.println(str);
  } while (str.indexOf("3GIM") < 0);
if DEBUG   SerialUSB.println("Connected");

  */
//  imei = com3gim("$YI");
//  imei = imei.substring(7);
//  if DEBUG   SerialUSB.println("imei =" + imei);


if DEBUG   SerialUSB.println("\n----------- ready -------------");
}



void loop() {
//    Serial.setTimeout(10000); // タイムアウト設定

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



