#include "BluetoothSerial.h"
#include <M5Core2.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

String direction = "STOP";

BluetoothSerial bluetooth;

char rec= 'A';

float accX = 0.0F; 
float accY = 0.0F;  
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float temp = 0.0F;

void setup(){
  M5.begin(); 
  M5.IMU.Init();
  M5.Lcd.begin(); 
  M5.Lcd.setTextSize(4);
  M5.Lcd.print("BlueTooth ON");
  
  Serial.begin(9600);
  Serial.println("Serial ready");

  bluetooth.begin("M5Stack ESP32test");
  bluetooth.println("Bluetooth ready");
}

void loop(){
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ); //Stores the triaxial accelerometer.  存储三轴加速度计数据
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);  //Stores the inertial sensor attitude.  存储惯性传感器的姿态
  M5.IMU.getTempData(&temp);

  if(accX > 0.50)
  {
    Serial.println("LEFT");
    direction = "LEFT";
  }
  else if(accX < -0.50)
  {
    Serial.println("RIGHT");
    direction = "RIGHT";
  }
  else if(accY > 0.5)
  {
    Serial.println("BACK");
    direction = "BACK";
  }
  else if(accY < -0.5)
  {
    Serial.println("FRONT");
    direction = "FRONT";
  }
  else{
    Serial.println("STOP");
    direction = "STOP";
  }
  
  if(bluetooth.available()){
//    rec = bluetooth.read(); // read 1 char
    bluetooth.println(direction);
    Serial.println(direction);
//    Serial.println(rec);    // Printout throught Serial the Char just read.
  }   
//  if(rec == 'Z'){ // If rec char is Z          
//    Serial.println("Serial: Z"); // Printout throught Serial
//    bluetooth.println("Bluetooth: Z"); // Printout throught Bluetooth
//    rec = 'A'; // reset rec to A to avoid inf loop
//  }
  //Wait ten milliseconds to decrease unnecessary hardware strain
   delay(500);
}
