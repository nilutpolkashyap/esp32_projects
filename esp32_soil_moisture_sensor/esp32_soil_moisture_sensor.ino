const int moist_sensor = 36;   // Port B

float moisture = 0.0;

void setup() {
  pinMode(moist_sensor, INPUT);

  Serial.begin(9600);
  Serial.println("Soil Moisture sensor test");
}

void loop() {
  moisture = analogRead(moist_sensor);
  moisture = map(moisture, 0, 4095, 0, 100);
  Serial.print("Soil Moisture: ");
  Serial.println(moisture);

  delay(2000);
}
