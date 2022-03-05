#include "BluetoothSerial.h"

char Incoming_value = 0;

BluetoothSerial bluetooth;
                
void setup() 
{
  Serial.begin(9600);         
  pinMode(2, OUTPUT);    

  bluetooth.begin("ESP32 Bluetooth");
//  bluetooth.println("Bluetooth ready");
}

void loop()
{
  if(bluetooth.available())  
  {
    Incoming_value = bluetooth.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == '1')             
      digitalWrite(2, HIGH);  
    else if(Incoming_value == '0')       
      digitalWrite(2, LOW);   
  }                            
} 
