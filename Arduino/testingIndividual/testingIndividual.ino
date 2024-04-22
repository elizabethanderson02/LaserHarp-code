// define the pins used
#define VS1053_RX  2 // This is the pin that connects to the RX pin on VS1053

#define VS1053_RESET 9 // This is the pin that connects to the RESET pin on VS1053
// If you have the Music Maker shield, you don't need to connect the RESET pin!

// If you're using the VS1053 breakout:
// Don't forget to connect the GPIO #0 to GROUND and GPIO #1 pin to 3.3V
// If you're using the Music Maker shield:
// Don't forget to connect the GPIO #1 pin to 3.3V and the RX pin to digital #2

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 31
#define VS1053_BANK_DEFAULT 0x00
#define VS1053_BANK_DRUMS1 0x78
#define VS1053_BANK_DRUMS2 0x7F
#define VS1053_BANK_MELODY 0x79

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 32 for more!
#define VS1053_GM1_OCARINA 80
#define VS1053_GM1_CELLO 43
#define VS1053_GM1_APPLAUSE 127
#define VS1053_GM1_KALIMBA 109
#define VS1053_GM1_HARP 47
#define VS1053_GM1_CELESTA 9

#define MIDI_NOTE_ON  0x90
#define MIDI_NOTE_OFF 0x80
#define MIDI_CHAN_MSG 0xB0
#define MIDI_CHAN_BANK 0x00
#define MIDI_CHAN_VOLUME 0x07
#define MIDI_CHAN_PROGRAM 0xC0


#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
  #include <SoftwareSerial.h>
  SoftwareSerial VS1053_MIDI(0, 2); // TX only, do not use the 'rx' side
#else
  //on a Mega/Leonardo you may have to change the pin to one that 
  // software serial support uses OR use a hardware serial port!
  #define VS1053_MIDI Serial1
#endif


int sensorPin0 = 23;
//int sensorPin1 = 25;
int sensorPin2 = A1;
int sensorPin3 = 29;
int sensorPin4 = A7;
int sensorPin5 = 33;
int sensorPin6 = 35;
int sensorPin7 = 37;
int sensorPin9 = 41;
int sensorPin10 = 43;
int sensorPin11 = 45;
int sensorPin12 = 22;
int sensorPin13 = A3;
int sensorPin14 = 26;
int sensorPin16 = 30;
int sensorPin17 = A5;
int sensorPin18 = 34;
int sensorPin19 = 36;
int sensorPin20 = A6;
int sensorPin21 = 40;
int sensorPin22 = 42;

int sensorValue0 = 0;
int sensorValue1 = 0; 
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0; 
int sensorValue5 = 0;
int sensorValue6 = 0;
int sensorValue7 = 0;
int sensorValue9 = 0;
int sensorValue10 = 0; 
int sensorValue11 = 0; 
int sensorValue12 = 0; 
int sensorValue13 = 0;
int sensorValue14 = 0;
int sensorValue16 = 0;
int sensorValue17 = 0;
int sensorValue18 = 0; 
int sensorValue19 = 0;
int sensorValue20 = 0;
int sensorValue21 = 0;
int sensorValue22 = 0;

int nextSensor0 = 0;
int nextSensor1 = 0;
int nextSensor2 = 0;
int nextSensor3 = 0;
int nextSensor4 = 0;
int nextSensor5 = 0;
int nextSensor6 = 0;
int nextSensor7 = 0;
int nextSensor9 = 0;
int nextSensor10 = 0;
int nextSensor11 = 0;
int nextSensor12 = 0;
int nextSensor13 = 0;
int nextSensor14 = 0;
int nextSensor16 = 0;
int nextSensor17 = 0;
int nextSensor18 = 0;
int nextSensor19 = 0;
int nextSensor20 = 0;
int nextSensor21 = 0;
int nextSensor22 = 0;

int volume = 127;
double line;

const int trigPin1 = 53;
const int trigPin2 = 51;
const int trigPin3 = 49;
const int trigPin4 = 47;

const int echoPin1 = 52;
const int echoPin2 = 50;
const int echoPin3 = 48;
const int echoPin4 = 46;

long duration, distance, sensor1, sensor2, sensor3, sensor4, distanceVolume;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin0,INPUT);
//  pinMode(sensorPin1,INPUT);
  pinMode(sensorPin2,INPUT);
  pinMode(sensorPin3,INPUT);
  pinMode(sensorPin4,INPUT);
  pinMode(sensorPin5,INPUT);
  pinMode(sensorPin6,INPUT);
  pinMode(sensorPin7,INPUT);
  pinMode(sensorPin9,INPUT);
  pinMode(sensorPin10,INPUT);
  pinMode(sensorPin11,INPUT);
  pinMode(sensorPin12,INPUT);
  pinMode(sensorPin13,INPUT);
  pinMode(sensorPin14,INPUT);
  pinMode(sensorPin16,INPUT);
  pinMode(sensorPin17,INPUT);
  pinMode(sensorPin18,INPUT);
  pinMode(sensorPin19,INPUT);
  pinMode(sensorPin20,INPUT);
  pinMode(sensorPin21,INPUT);
  pinMode(sensorPin22,INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  VS1053_MIDI.begin(31250); // MIDI uses a 'strange baud rate'
  
  pinMode(VS1053_RESET, OUTPUT);
  digitalWrite(VS1053_RESET, LOW);
  delay(10);
  digitalWrite(VS1053_RESET, HIGH);
  delay(10);
  
  midiSetChannelBank(0, VS1053_BANK_MELODY);
  midiSetInstrument(0, VS1053_GM1_CELLO);
  midiSetChannelVolume(0, 127);

}

void loop() {

  SonarSensor(trigPin1, echoPin1);
  sensor1  = distance;
  SonarSensor(trigPin2, echoPin2);
  sensor2 = distance;
  SonarSensor(trigPin3, echoPin3);
  sensor3 = distance;
  SonarSensor(trigPin4, echoPin4);
  sensor4 = distance;

  distanceVolume = min(sensor1, min(sensor2, min(sensor3, sensor4)));

  if (distanceVolume <= 5){
    volume = 31.75;
  }else if (distanceVolume <= 6){
    volume = 63.5;
  }else if (distanceVolume <= 8){
    volume = 95.25;
  }else{
    volume = 127;
  };
  
  sensorValue0 = digitalRead(sensorPin0);
//  sensorValue1 = digitalRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = digitalRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
  sensorValue5 = digitalRead(sensorPin5);
  sensorValue6 = digitalRead(sensorPin6);
  sensorValue7 = digitalRead(sensorPin7);
  sensorValue9 = digitalRead(sensorPin9);
  sensorValue10 = digitalRead(sensorPin10);
  sensorValue11 = digitalRead(sensorPin11);
  sensorValue12 = digitalRead(sensorPin12);
  sensorValue13 = analogRead(sensorPin13);
  sensorValue14 = digitalRead(sensorPin14);
  sensorValue16 = digitalRead(sensorPin16);
  sensorValue17 = analogRead(sensorPin17);
  sensorValue18 = digitalRead(sensorPin18);
  sensorValue19 = digitalRead(sensorPin19);
  sensorValue20 = analogRead(sensorPin20);
  sensorValue21 = digitalRead(sensorPin21);
  sensorValue22 = digitalRead(sensorPin22);
 
  // put your main code here, to run repeatedly:
  if (sensorValue0 == LOW){
    //Serial.println(sensorValue1);
    if (nextSensor0 == 0){
      line = line + 8388608;
      Serial.println(line);
      nextSensor0 = 1;
      midiNoteOn(0,73,volume);
    }
  }
  else{
    if (nextSensor0 == 1) {
      line = line - 8388608;
      Serial.println(line);
      nextSensor0 = 0;
      midiNoteOff(0,73,127);
    }
  };
  if(sensorValue2 <= 170){
    if (nextSensor2 == 0){
      line = line + 2097152;
      Serial.println(line);
      nextSensor2 = 1;
      midiNoteOn(0,71, volume);
    }
  }
  else{
    if(nextSensor2 == 1){
      line = line - 2097152;
      Serial.println(line);
      nextSensor2 = 0;
      midiNoteOff(0, 71, 127);
    }
  };
 
  if (sensorValue3 == LOW){
    //Serial.println(sensorValue1);
    if (nextSensor3 == 0){
      line = line + 1048576;
      Serial.println(line);
      nextSensor3 = 1;
      midiNoteOn(0,70,volume);
    }
  }
  else{
    if (nextSensor3 == 1) {
      line = line - 1048576;
      Serial.println(line);
      nextSensor3 = 0;
      midiNoteOff(0,70,127);
    }
  };
  if(sensorValue4 <= 10){
    if (nextSensor4 == 0){
      line = line + 524288;
      Serial.println(line);
      nextSensor4 = 1;
      midiNoteOn(0,69, volume);
    }
  }
  else{
    if(nextSensor4 == 1){
      line = line - 524288;
      Serial.println(line);
      nextSensor4 = 0;
      midiNoteOff(0, 69, 127);
    }
  };
 
  if (sensorValue5 == LOW){
    if (nextSensor5 == 0){
      line = line + 262144;
      Serial.println(line);
      nextSensor5 = 1;
      midiNoteOn(0,68,volume);
    }
  }
  else{
    if (nextSensor5 == 1) {
      line = line - 262144;
      Serial.println(line);
      nextSensor5 = 0;
      midiNoteOff(0,68,127);
    }
  };
   if (sensorValue6 == LOW){
    if (nextSensor6 == 0){
      line = line + 131072;
      Serial.println(line);
      nextSensor6 = 1;
      midiNoteOn(0,67,volume);
    }
  }
  else{
    if (nextSensor6 == 1) {
      line = line - 131072;
      Serial.println(line);
      nextSensor6 = 0;
      midiNoteOff(0,67,127);
    }
  };
  if (sensorValue7 == LOW){
    if (nextSensor7 == 0){
      line = line + 65536;
      Serial.println(line);
      nextSensor7 = 1;
      midiNoteOn(0,66,volume);
    }
  }
  else{
    if (nextSensor7 == 1) {
      line = line - 65536;
      Serial.println(line);
      nextSensor7 = 0;
      midiNoteOff(0,66,127);
    }
  };
  if (sensorValue9 == LOW){
    if (nextSensor9 == 0){
      line = line + 16384;
      Serial.println(line);
      nextSensor9 = 1;
      midiNoteOn(0,64,volume);
    }
  }
  else{
    if (nextSensor9 == 1) {
      line = line - 16384;
      Serial.println(line);
      nextSensor9 = 0;
      midiNoteOff(0,64,127);
    }
  };
   if (sensorValue10 == LOW){
    if (nextSensor10 == 0){
      line = line + 8192;
      Serial.println(line);
      nextSensor10 = 1;
      midiNoteOn(0,63,volume);
    }
  }
  else{
    if (nextSensor10 == 1) {
      line = line - 8192;
      Serial.println(line);
      nextSensor10 = 0;
      midiNoteOff(0,63,127);
    }
  };
  if (sensorValue11 == LOW){
    if (nextSensor11 == 0){
      line = line + 4096;
      Serial.println(line);
      nextSensor11 = 1;
      midiNoteOn(0,62,volume);
    }
  }
  else{
    if (nextSensor11 == 1) {
      line = line - 4096;
      Serial.println(line);
      nextSensor11 = 0;
      midiNoteOff(0,62,127);
    }
  };
   if (sensorValue12 == LOW){
    if (nextSensor12 == 0){
      line = line + 2048;
      Serial.println(line);
      nextSensor12 = 1;
      midiNoteOn(0,61,volume);
    }
  }
  else{
    if (nextSensor12 == 1) {
      line = line - 2048;
      Serial.println(line);
      nextSensor12 = 0;
      midiNoteOff(0,61,127);
    }
  };
  if(sensorValue13 <= 5){
    if (nextSensor13 == 0){
      line = line + 1024;
      Serial.println(line);
      nextSensor13 = 1;
      midiNoteOn(0,60, volume);
    }
  }
  else{
    if(nextSensor13 == 1){
      line = line - 1024;
      Serial.println(line);
      nextSensor13 = 0;
      midiNoteOff(0, 60, 127);
    }
  }
 
  if (sensorValue14 == LOW){
    if (nextSensor14 == 0){
      line = line + 512;
      Serial.println(line);
      nextSensor14 = 1;
      midiNoteOn(0,59,volume);
    }
  }
  else{
    if (nextSensor14 == 1) {
      line = line - 512;
      Serial.println(line);
      nextSensor14 = 0;
      midiNoteOff(0,59,127);
    }
  };
  if (sensorValue16 == LOW){
    if (nextSensor16 == 0){
      line = line + 128;
      Serial.println(line);
      nextSensor16 = 1;
      midiNoteOn(0,57,volume);
    }
  }
  else{
    if (nextSensor16 == 1) {
      line = line - 128;
      Serial.println(line);
      nextSensor16 = 0;
      midiNoteOff(0,57,127);
    }
  };
  if(sensorValue17 <= 45){
    if (nextSensor17 == 0){
      line = line + 64;
      Serial.println(line);
      nextSensor17 = 1;
      midiNoteOn(0,56, volume);
    }
  }
  else{
    if(nextSensor17 == 1){
      line = line - 64;
      Serial.println(line);
      nextSensor17 = 0;
      midiNoteOff(0,56, 127);
    }
  }
 
  if (sensorValue18 == LOW){
    if (nextSensor18 == 0){
      line = line + 32;
      Serial.println(line);
      nextSensor18 = 1;
      midiNoteOn(0,55,volume);
    }
  }
  else{
    if (nextSensor18 == 1) {
      line = line - 32;
      Serial.println(line);
      nextSensor18 = 0;
      midiNoteOff(0,55,127);
    }
  };
  if (sensorValue19 == LOW){
    if (nextSensor19 == 0){
      line = line + 16;
      Serial.println(line);
      nextSensor19 = 1;
      midiNoteOn(0,54,volume);
    }
  }
  else{
    if (nextSensor19 == 1) {
      line = line - 16;
      Serial.println(line);
      nextSensor19 = 0;
      midiNoteOff(0,54,127);
    }
  };
  if(sensorValue20 <= 40){
    if (nextSensor20 == 0){
      line = line + 8;
      Serial.println(line);
      nextSensor20 = 1;
      midiNoteOn(0,53, volume);
    }
  }
  else{
    if(nextSensor20 == 1){
      line = line - 8;
      Serial.println(line);
      nextSensor20 = 0;
      midiNoteOff(0, 53, 127);
    }
  }
 
  if (sensorValue21 == LOW){
    if (nextSensor21 == 0){
      line = line + 4;
      Serial.println(line);
      nextSensor21 = 1;
      midiNoteOn(0,52,volume);
    }
  }
  else{
    if (nextSensor21 == 1) {
      line = line - 4;
      Serial.println(line);
      nextSensor21 = 0;
      midiNoteOff(0,52,127);
    }
  };
  if (sensorValue22 == LOW){
    if (nextSensor22 == 0){
      line = line + 2;
      Serial.println(line);
      nextSensor22 = 1;
      midiNoteOn(0,51,volume);
    }
  }
  else{
    if (nextSensor22 == 1) {
      line = line - 2;
      Serial.println(line);
      nextSensor22 = 0;
      midiNoteOff(0,51,127);
    }
  };
  

}

void midiSetInstrument(uint8_t chan, uint8_t inst) {
  if (chan > 15) return;
  inst --; // page 32 has instruments starting with 1 not 0 :(
  if (inst > 127) return;
  
  VS1053_MIDI.write(MIDI_CHAN_PROGRAM | chan);  
  VS1053_MIDI.write(inst);           
}


void midiSetChannelVolume(uint8_t chan, uint8_t vol) {
  if (chan > 15) return;
  if (vol > 127) return;
  
  VS1053_MIDI.write(MIDI_CHAN_MSG | chan);
  VS1053_MIDI.write(MIDI_CHAN_VOLUME);
  VS1053_MIDI.write(vol);
}

void midiSetChannelBank(uint8_t chan, uint8_t bank) {
  if (chan > 15) return;
  if (bank > 127) return;
  
  VS1053_MIDI.write(MIDI_CHAN_MSG | chan);
  VS1053_MIDI.write((uint8_t)MIDI_CHAN_BANK);
  VS1053_MIDI.write(bank);
}

void midiNoteOn(uint8_t chan, uint8_t n, uint8_t vel) {
  if (chan > 15) return;
  if (n > 127) return;
  if (vel > 127) return;
  
  VS1053_MIDI.write(MIDI_NOTE_ON | chan);
  VS1053_MIDI.write(n);
  VS1053_MIDI.write(vel);
}

void midiNoteOff(uint8_t chan, uint8_t n, uint8_t vel) {
  if (chan > 15) return;
  if (n > 127) return;
  if (vel > 127) return;
  
  VS1053_MIDI.write(MIDI_NOTE_OFF | chan);
  VS1053_MIDI.write(n);
  VS1053_MIDI.write(vel);
}
void SonarSensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
}
