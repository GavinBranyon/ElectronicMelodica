// https://docs.arduino.cc/built-in-examples/basics/DigitalReadSerial

  // Use digital pin 2
  // ez clap
  // Follow design make sure ground is connected dumbass
  // Resistor from switch to ground
  // circuit must be set up prior to upload <---- this is a worry
  // halfway point on board across ground / power strips that cause ground not being read?
#include "Waveshare_LCD1602_RGB.h"

Waveshare_LCD1602_RGB lcd(16,2);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.print("test");
  lcd.init();
  lcd.clear();
  pinMode(2,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(2);
  Serial.println(sensorValue);
  if(sensorValue == HIGH)
  {
    lcd.setCursor(0,0);
    lcd.send_string("C4");
    lcd.setCursor(0,1);
    lcd.send_string("100");
    delay(500);

  } else {
    lcd.clear();
  }
  
  delay(300);  // delay in between reads for stability
}
