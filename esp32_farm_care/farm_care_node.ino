#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "DHT.h"

#define DHTTYPE DHT11

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 23, 4, 15, 2);
int contrastValue = 60; // Default Contrast Value
const int adcPin = 34;
int adcValue = 0;

const int ldr_pin = 33;
const int moist_sensor = 35;
const int moist_power = 25;
const int dht_pin = 27;
const int mq_pin = 32;

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x08,0x3A,0xF2,0x65,0xD8,0xC4};

// Define variables to store BME280 readings to be sent
float temperature;
float humidity;
float moisture;
float ldr_val;
float air_qual;

DHT dht(dht_pin, DHTTYPE);

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    float temp;
    float hum;
    float moist;
    float ldr;
    float air;
} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message SensorReadings;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

//// Callback when data is received
//void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
//  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
//  Serial.print("Bytes received: ");
//  Serial.println(len);
//  incomingTemp = incomingReadings.temp;
//  incomingHum = incomingReadings.hum;
//  incomingPres = incomingReadings.pres;
//}
 
void setup() {
  Serial.begin(115200);

  pinMode(ldr_pin, INPUT);
  pinMode(moist_sensor, INPUT);
  pinMode(moist_power, OUTPUT);
  pinMode(dht_pin, INPUT);
  pinMode(mq_pin, INPUT);
  Serial.begin(115200);
  dht.begin();
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
//  esp_now_register_recv_cb(OnDataRecv);

  /* Initialize the Display*/
  display.begin();

  /* Change the contrast using the following API*/
  display.setContrast(contrastValue);

  /* Clear the buffer */
  display.clearDisplay();
  display.display();
  delay(1000);
  
  /* Now let us display some text */
  display.setTextColor( BLACK);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Temp: ");
  display.setCursor(0,8);
  display.println("Humid: ");
  display.setCursor(0,16);
  display.println("Moist: ");
  display.setCursor(0,24);
  display.println("Air Q: ");
  display.setCursor(0,32);
  display.println("Light: ");
  display.display();
  delay(2000);
}
 
void loop() {
  getReadings();
 
  // Set values to send
  SensorReadings.temp = temperature;
  SensorReadings.hum = humidity;
  SensorReadings.moist = moisture;
  SensorReadings.ldr = ldr_val;
  SensorReadings.air = air_qual;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &SensorReadings, sizeof(SensorReadings));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  updateDisplay();
  delay(10000);
}
void getReadings(){
  temperature = dht.readTemperature();
  
  humidity = dht.readHumidity();
  
  ldr_val = analogRead(ldr_pin);
  ldr_val = map(ldr_val, 0, 4095, 0, 1023);

  air_qual = analogRead(mq_pin);
  air_qual = map(air_qual, 0, 4095, 0, 200);

  digitalWrite(moist_power, HIGH);
  delay(10);
  moisture = analogRead(moist_sensor);
  digitalWrite(moist_power, LOW);
  moisture = map(moisture, 0, 4095, 0, 100);
}

void updateDisplay(){
//  Serial.println("INCOMING READINGS");
//  Serial.print("Temperature: ");
//  Serial.print(incomingReadings.temp);
//  Serial.println(" ºC");
//  Serial.print("Humidity: ");
//  Serial.print(incomingReadings.hum);
//  Serial.println(" %");
//  Serial.print("Pressure: ");
//  Serial.print(incomingReadings.pres);
//  Serial.println(" hPa");
//  Serial.println();

  display.clearDisplay();
  
  display.setTextColor( BLACK);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Temp: ");
  display.setCursor(45,0);
  display.println(temperature);

  Serial.println("Temperature: ");
  Serial.println(temperature);
  
  display.setCursor(0,8);
  display.println("Humid: ");
  display.setCursor(45,8);
  display.println(humidity);

  Serial.println("Humidity: ");
  Serial.println(humidity);
  
  display.setCursor(0,16);
  display.println("Moist: ");
  display.setCursor(45,16);
  display.println(moisture);

  Serial.println("Soil Moisture: ");
  Serial.println(moisture);
  
  display.setCursor(0,24);
  display.println("Air Q: ");
  display.setCursor(45,24);
  display.println(air_qual);

  Serial.println("Air Quality: ");
  Serial.println(air_qual);
  
  display.setCursor(0,32);
  display.println("Light: ");
  display.setCursor(45,32);
  display.println(ldr_val);

  Serial.println("Light Intensity: ");
  Serial.println(ldr_val);
  
  display.display();
}
