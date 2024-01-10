/*
 * MIDIUSB_test.ino
 *
 * Created: 4/6/2015 10:47:08 AM
 * Author: gurbrinder grewal
 * Modified by Arduino LLC (2015)
 */ 
 
// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

#include "MIDIUSB.h"
#include "Waveshare_LCD1602_RGB.h"

Waveshare_LCD1602_RGB lcd(16,2);

int PrevsensorValue = LOW;


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
   lcd.init();
   lcd.clear();
   pinMode(2,INPUT);
   Serial.begin(115200);
   Serial.print("test");
   
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  int sensorValue = digitalRead(2);
  
  if(sensorValue == HIGH && PrevsensorValue != sensorValue)
  {
    lcd.setCursor(0,0);
    lcd.send_string("C4");
    lcd.setCursor(0,1);
    lcd.send_string("50");
    Serial.println("Sending note on");
    noteOn(0, 48, 64);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    PrevsensorValue = HIGH;
    delay(50);
  } 
  else if (sensorValue == LOW && PrevsensorValue != sensorValue)
  {
    Serial.println("Sending note off");
    noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    lcd.clear();
    PrevsensorValue = LOW;
  }
 
  
  delay(25);  // delay in between reads for stability
  
  }

 /* int switchState = digitalRead(switchPin);

  // Do something based on the switch state
   
  if (switchState == HIGH && switchState != PrevswitchState) {

    
    Serial.println("Sending note on");
    noteOn(0, 48, 64);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();

    PrevswitchState = switchState;
    
   
    
  } else if (switchState == LOW && switchState != PrevswitchState) {
    
    Serial.println("Sending note off");
    noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    PrevswitchState = switchState;

    
  
  }
  */
  
/*
  // Add a short delay to avoid reading the switch too quickly
  delay(100);
  Serial.println("Sending note on");
  noteOn(0, 48, 64);   // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(250);
  Serial.println("Sending note off");
  noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(500);
*/
  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
