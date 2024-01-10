// https://docs.arduino.cc/built-in-examples/basics/DigitalReadSerial

  // Use digital pin 2
  // ez clap
  // Follow design make sure ground is connected dumbass
  // Resistor from switch to ground
  // circuit must be set up prior to upload <---- this is a worry
  // halfway point on board across ground / power strips that cause ground not being read?

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.print("test");
  pinMode(2,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(2);
  Serial.println(sensorValue);
  delay(300);  // delay in between reads for stability
}
