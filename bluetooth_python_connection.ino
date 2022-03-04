#include "BluetoothSerial.h"
#include <M5Core2.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial bluetooth;

char rec= 'A';

void setup(){
  M5.begin(); //Init M5Core.  初始化 M5Core
  M5.IMU.Init();
  M5.Lcd.begin(); 
  M5.Lcd.setTextSize(4);
  M5.Lcd.print("BlueTooth ON");
  
  //Initialize Serial for debugging purposes
  Serial.begin(9600);
  Serial.println("Serial ready");
  //Initialize the bluetooth
  bluetooth.begin("M5Stack ESP32test");
  bluetooth.println("Bluetooth ready");
}

void loop(){
  if(bluetooth.available()){
    rec = bluetooth.read(); // read 1 char
    Serial.println(rec);    // Printout throught Serial the Char just read.
  }   
  if(rec == 'Z'){ // If rec char is Z          
    Serial.println("Serial: Z"); // Printout throught Serial
    bluetooth.println("Bluetooth: Z"); // Printout throught Bluetooth
    rec = 'A'; // reset rec to A to avoid inf loop
  }
  //Wait ten milliseconds to decrease unnecessary hardware strain
   delay(10);
}
