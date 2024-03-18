#include <LiquidCrystal_I2C.h>
#include "MIDIUSB.h"
#include <Waveshare_LCD1602_RGB.h>

Waveshare_LCD1602_RGB lcd(16,2);
//LiquidCrystal_I2C lcd(0x27,16,2);

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

 // 11 Ports / Keys on first row of ports Set # as 12
int PrevsensorValue[37] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW}; // 37 Keys
const char* NoteValue[37] = {"C4","D4","D4#","E4","F4","F4#","G4","G4#","A4","A4#","B4","C5","C5#","D5","D5#","E5","F5","F5#","G5","G5#","A5","A5#","B5","C6","C6#","D6","D6#","E6","F6","F6#","G6","G6#","A6","A6#"}; // 37 Keys
int sensorValue[37];
int NumberofKeys=37;

void setup() {

  lcd.init();
   lcd.clear();
   //pinMode(2,INPUT);
 
   Serial.begin(115200);
   Serial.print("test");


pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
pinMode(5,INPUT);
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
pinMode(12,INPUT);
pinMode(13,INPUT);
pinMode(22,INPUT);
pinMode(23,INPUT);
pinMode(24,INPUT);
pinMode(25,INPUT);
pinMode(26,INPUT);
pinMode(27,INPUT);
pinMode(28,INPUT);
pinMode(29,INPUT);
pinMode(30,INPUT);
pinMode(31,INPUT);
pinMode(32,INPUT);
pinMode(33,INPUT);
pinMode(34,INPUT);
pinMode(35,INPUT);
pinMode(36,INPUT);
pinMode(37,INPUT);
pinMode(38,INPUT);
pinMode(39,INPUT);
pinMode(40,INPUT);
pinMode(41,INPUT);
pinMode(42,INPUT);
pinMode(43,INPUT);
pinMode(44,INPUT);
pinMode(45,INPUT);
pinMode(46,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
sensorValue[0] = digitalRead(2);
sensorValue[1] = digitalRead(3);
sensorValue[2] = digitalRead(4);
sensorValue[3] = digitalRead(5);
sensorValue[4] = digitalRead(6);
sensorValue[5] = digitalRead(7);
sensorValue[6] = digitalRead(8);
sensorValue[7] = digitalRead(9);
sensorValue[8] = digitalRead(10);
sensorValue[9] = digitalRead(11);
sensorValue[10] = digitalRead(12);
sensorValue[11] = digitalRead(13);
sensorValue[12] = digitalRead(22);
sensorValue[13] = digitalRead(23);
sensorValue[14] = digitalRead(24);
sensorValue[15] = digitalRead(25);
sensorValue[16] = digitalRead(26);
sensorValue[17] = digitalRead(27);
sensorValue[18] = digitalRead(28);
sensorValue[19] = digitalRead(29);
sensorValue[20] = digitalRead(30);
sensorValue[21] = digitalRead(31);
sensorValue[22] = digitalRead(32);
sensorValue[23] = digitalRead(33);
sensorValue[24] = digitalRead(34);
sensorValue[25] = digitalRead(35);
sensorValue[26] = digitalRead(36);
sensorValue[27] = digitalRead(37);
sensorValue[28] = digitalRead(38);
sensorValue[29] = digitalRead(39);
sensorValue[30] = digitalRead(40);
sensorValue[31] = digitalRead(41);
sensorValue[32] = digitalRead(42);
sensorValue[33] = digitalRead(43);
sensorValue[34] = digitalRead(44);
sensorValue[35] = digitalRead(45);
sensorValue[36] = digitalRead(46);


int p = 0;

  for(int j = 0; j <= NumberofKeys; j++)
  {

  p = j;
  
  
    if(sensorValue[p] == HIGH && PrevsensorValue[p] != sensorValue[p])
    {
     
      
      const int inputPin = 0;
      
      
      Serial.println("Sending note on");
      lcd.setCursor(0,0);
      lcd.send_string(NoteValue[p]);
      lcd.setCursor(0,1);
      lcd.send_string("Insert Velocity Here");
      noteOn(0, 48+p, 100);   // Channel 0, middle C, normal velocity
      MidiUSB.flush();
      PrevsensorValue[p] = HIGH;
      
    } 
    else if (sensorValue[p] == LOW && PrevsensorValue[p] != sensorValue[p])
    {
      Serial.println("Sending note off");
      noteOff(0, 48+p, 100);  // Channel 0, middle C, normal velocity
      MidiUSB.flush();
      lcd.clear();
      PrevsensorValue[p] = LOW;
      
    }
  }
}
