#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial

#include <CayenneMQTTESP32.h>
#include "DHT.h"

#define DHTTYPE DHT11

// WiFi network info.
char ssid[] = "SSID_NAME";
char wifiPassword[] = "PASSWORD";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT Username";
char password[] = "MQTT Password";
char clientID[] = "Client ID";

float ldr_val = 0.0;
float moisture = 0.0;
float humid = 0.0;
float temp = 0.0;
float mq_value = 0.0;

const int ldr = 34;
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
}

void loop()
{
  Cayenne.loop();

  ldr_val = analogRead(ldr);
  ldr_val = map(ldr_val, 0, 4095, 0, 1023);
  Serial.println(ldr_val);
  Cayenne.virtualWrite(1,ldr_val,"analog_sensor","null");

  digitalWrite(moist_power, HIGH);
  delay(10);
  moisture = analogRead(moist_sensor);
  digitalWrite(moist_power, LOW);
  Serial.println(moisture);
  Cayenne.virtualWrite(2, moisture, "analog_sensor", "null");

  humid = dht.readHumidity();
  Serial.println(humid);
  Cayenne.virtualWrite(3, humid, "analog_sensor", "null");
  
  temp = dht.readTemperature();
  Serial.println(temp);
  Cayenne.virtualWrite(4, temp, "analog_sensor", "null");

  mq_value = analogRead(mq_pin);
  Serial.println(mq_value);
  Cayenne.virtualWrite(5, mq_value, "analog_sensor", "null");
  
  
}
