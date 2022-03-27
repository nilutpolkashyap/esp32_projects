#include <esp_now.h>
#include <WiFi.h>
#include <M5Core2.h>
#include <Wire.h>


// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0xA4,0xCF,0x12,0x8D,0x0E,0x7C};

// Define variables to store BME280 readings to be sent
float temperature;
float humidity;
float moisture;
float ldr_val;
float air_qual;

// Define variables to store incoming readings
float incomingTemp;
float incomingHum;
float incomingMoist;
float incomingLdr;
float incomingAir;

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
//void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//  Serial.print("\r\nLast Packet Send Status:\t");
//  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
//  if (status ==0){
//    success = "Delivery Success :)";
//  }
//  else{
//    success = "Delivery Fail :(";
//  }
//}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingTemp = incomingReadings.temp;
  incomingHum = incomingReadings.hum;
  incomingMoist = incomingReadings.moist;
  incomingLdr = incomingReadings.ldr;
  incomingAir = incomingReadings.air;
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  M5.begin();
  M5.Lcd.begin(); 
  M5.Lcd.setTextSize(4);

  M5.Lcd.fillScreen(GREEN);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
//  esp_now_register_send_cb(OnDataSent);
  
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
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
//  getReadings();
 
  // Set values to send
//  BME280Readings.temp = temperature;
//  BME280Readings.hum = humidity;
//  BME280Readings.pres = pressure;

  // Send message via ESP-NOW
//  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &BME280Readings, sizeof(BME280Readings));
   
//  if (result == ESP_OK) {
//    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  updateDisplay();
  Serial.println(incomingReadings.temp);
  Serial.println(incomingReadings.hum);
  Serial.println(incomingReadings.moist);
  Serial.println(incomingReadings.ldr);
  Serial.println(incomingReadings.air);

  M5.Lcd.fillScreen(GREEN);

  M5.Lcd.setCursor(65, 10); 
  M5.Lcd.setTextColor(BLACK); 
  M5.Lcd.setTextSize(4);  
  M5.Lcd.print("FARM CARE");

  M5.Lcd.setCursor(15, 50); 
  M5.Lcd.setTextColor(BLACK); 
  M5.Lcd.setTextSize(3);  
  M5.Lcd.print("Temp : ");
  M5.Lcd.setCursor(180, 50); 
  M5.Lcd.print(incomingReadings.temp); 

  M5.Lcd.setCursor(15, 80); 
  M5.Lcd.setTextColor(BLACK); 
  M5.Lcd.setTextSize(3);  
  M5.Lcd.print("Humid : ");
  M5.Lcd.setCursor(180, 80); 
  M5.Lcd.print(incomingReadings.hum); 

  M5.Lcd.setCursor(15, 110); 
  M5.Lcd.setTextColor(BLACK); 
  M5.Lcd.setTextSize(3);  
  M5.Lcd.print("Moist : ");
  M5.Lcd.setCursor(180, 110); 
  M5.Lcd.print(incomingReadings.moist); 

  M5.Lcd.setCursor(15, 140); 
  M5.Lcd.setTextColor(BLACK); 
  M5.Lcd.setTextSize(3);  
  M5.Lcd.print("Light : ");
  M5.Lcd.setCursor(180, 140); 
  M5.Lcd.print(incomingReadings.ldr); 

  M5.Lcd.setCursor(15, 170); 
  M5.Lcd.setTextColor(BLACK); 
  M5.Lcd.setTextSize(3);  
  M5.Lcd.print("Air Ql : ");
  M5.Lcd.setCursor(180, 170); 
  M5.Lcd.print(incomingReadings.air); 

  M5.update(); 

  delay(10000);
}


//void getReadings(){
//  temperature = bme.readTemperature();
//  humidity = bme.readHumidity();
//  pressure = (bme.readPressure() / 100.0F);
//}

void updateDisplay(){
  // Display Readings on OLED Display
//  display.clearDisplay();
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0, 0);
//  display.println("INCOMING READINGS");
//  display.setCursor(0, 15);
//  display.print("Temperature: ");
//  display.print(incomingTemp);
//  display.cp437(true);
//  display.write(248);
//  display.print("C");
//  display.setCursor(0, 25);
//  display.print("Humidity: ");
//  display.print(incomingHum);
//  display.print("%");
//  display.setCursor(0, 35);
//  display.print("Pressure: ");
//  display.print(incomingPres);
//  display.print("hPa");
//  display.setCursor(0, 56);
//  display.print(success);
//  display.display();
  
  // Display Readings in Serial Monitor
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
}
