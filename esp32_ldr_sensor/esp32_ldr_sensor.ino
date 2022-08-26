const int ldr_sensor = 33;   // Port A 

float intensity = 0.0;

void setup() {
  pinMode(ldr_sensor, INPUT);

  Serial.begin(9600);
  Serial.println("LDR test");
}

void loop() {
  intensity = analogRead(ldr_sensor);
  Serial.print("LDR Value: ");
  Serial.println(intensity);

  delay(2000);
}
