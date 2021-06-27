#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial

#include <CayenneMQTTESP32.h>
#include "DHT.h"

#define DHTTYPE DHT11

/* Declare LCD object for SPI
 Adafruit_PCD8544(CLK,DIN,D/C,CE,RST); */
Adafruit_PCD8544 display = Adafruit_PCD8544(18, 23, 4, 15, 2);
int contrastValue = 60; // Default Contrast Value
const int adcPin = 34;
int adcValue = 0;

char ssid[] = "SSID_NAME";
char wifiPassword[] = "PASSWORDD";

char username[] = "Cayenne Username";
char password[] = "Cayenne Password";
char clientID[] = "Cayenne Dashboard Client ID";

float ldr_val = 0.0;
float moisture = 0.0;
float humid = 0.0;
float temp = 0.0;
float mq_value = 0.0;

const int ldr = 33;
const int moist_sensor = 35;
const int moist_power = 25;
const int dht_pin = 27;
const int mq_pin = 32;

DHT dht(dht_pin, DHTTYPE);

void setup()
{
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

  pinMode(ldr, INPUT);
  pinMode(moist_sensor, INPUT);
  pinMode(moist_power, OUTPUT);
  pinMode(dht_pin, INPUT);
  pinMode(mq_pin, INPUT);
  Serial.begin(115200);
  dht.begin();
  
  
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
  display.println("Moist: ");
  display.setCursor(0,16);
  display.println("Humid: ");
  display.setCursor(0,24);
  display.println("Air Q: ");
  display.setCursor(0,32);
  display.println("Light: ");
  display.display();
  delay(2000);
}

void loop()
{
  /* You can implement your own display logic here*/  
  Cayenne.loop();

  ldr_val = analogRead(ldr);
  ldr_val = map(ldr_val, 0, 4095, 0, 1023);
  Serial.println("Light Intensity: ");
  Serial.println(ldr_val);
  Cayenne.virtualWrite(1,ldr_val,"analog_sensor","null");

  digitalWrite(moist_power, HIGH);
  delay(10);
  moisture = analogRead(moist_sensor);
  digitalWrite(moist_power, LOW);
  moisture = map(moisture, 0, 4095, 0, 100);
  Serial.println("Soil Moisture: ");
  Serial.println(moisture);
  Cayenne.virtualWrite(2, moisture, "analog_sensor", "null");

  humid = dht.readHumidity();
  Serial.println("Humidity: ");
  Serial.println(humid);
  Cayenne.virtualWrite(3, humid, "analog_sensor", "null");
  
  temp = dht.readTemperature();
  Serial.println("Temperature: ");
  Serial.println(temp);
  Cayenne.virtualWrite(4, temp, "analog_sensor", "null");

  mq_value = analogRead(mq_pin);
  mq_value = map(mq_value, 0, 4095, 0, 200);
  Serial.println("Air Quality: ");
  Serial.println(mq_value);
  Cayenne.virtualWrite(5, mq_value, "analog_sensor", "null");

  display.clearDisplay();
  
  display.setTextColor( BLACK);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Temp: ");
  display.setCursor(45,0);
  display.println(temp);
  
  display.setCursor(0,8);
  display.println("Moist: ");
  display.setCursor(45,8);
  display.println(moisture);
  
  display.setCursor(0,16);
  display.println("Humid: ");
  display.setCursor(45,16);
  display.println(humid);
  
  display.setCursor(0,24);
  display.println("Air Q: ");
  display.setCursor(45,24);
  display.println(mq_value);
  
  display.setCursor(0,32);
  display.println("Light: ");
  display.setCursor(45,32);
  display.println(ldr_val);
  
  display.display();
  delay(2000);
}
