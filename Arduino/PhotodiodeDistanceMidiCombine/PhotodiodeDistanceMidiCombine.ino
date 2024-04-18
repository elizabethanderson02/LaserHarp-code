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


int sensorPin0 = A0 ;
int sensorPin1 = A1;
int sensorPin2 = A2;
int sensorPin3 = A3;
int sensorPin4 = A4;
int sensorPin5 = A5;
int sensorPin6 = A6;
int sensorPin7 = A7;
int sensorPin8 = A8;

int sensorValue0 = 0;
int sensorValue1 = 0; 
int sensorValue2 = 0; 
int sensorValue3 = 0; 
int sensorValue4 = 0;
int sensorValue5 = 0;
int sensorValue6 = 0;
int sensorValue7 = 0;
int sensorValue8 = 0; 

int volume = 127;

const int trigPin = 23;
const int echoPin = 53;

float duration, distance;                                                                                                                                 

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin0,INPUT);
  pinMode(sensorPin1,INPUT);
  pinMode(sensorPin2,INPUT);
  pinMode(sensorPin3,INPUT);
  pinMode(sensorPin4,INPUT);
  pinMode(sensorPin5,INPUT);
  pinMode(sensorPin6,INPUT);
  pinMode(sensorPin7,INPUT);
  pinMode(sensorPin8,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("VS1053 MIDI test");
  
  VS1053_MIDI.begin(31250); // MIDI uses a 'strange baud rate'
  
  pinMode(VS1053_RESET, OUTPUT);
  digitalWrite(VS1053_RESET, LOW);
  delay(10);
  digitalWrite(VS1053_RESET, HIGH);
  delay(10);
  
  midiSetChannelBank(0, VS1053_BANK_MELODY);
  midiSetInstrument(0, VS1053_GM1_HARP);
  midiSetChannelVolume(0, 127);
}

void loop() {  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  if (distance > 20){
    volume = 127;}
  else if (distance > 15) {
      volume = 95;}
  else if (distance >  10) {
      volume = 64;}
  else {
      volume =32;}

// put your main code here, to run repeatedly:
  sensorValue0= analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
  sensorValue5 = analogRead(sensorPin5);
  sensorValue6 = analogRead(sensorPin6);
  sensorValue7 = analogRead(sensorPin7);
  sensorValue8 = analogRead(sensorPin8);
  if (sensorValue0 > 10){
    Serial.println("Photodiode 0 ON");
    midiNoteOn(0, 30, volume);}
  if (sensorValue1 > 10) {
    Serial.println("Photodiode 1 ON");
    midiNoteOn(0, 31, volume);}
  if (sensorValue2 > 10) {
    Serial.println("Photodiode 2 ON");
    midiNoteOn(0, 32, volume);}
  if (sensorValue3 > 10) {
    Serial.println("Photodiode 3 ON");
    midiNoteOn(0, 33, volume);}
  if (sensorValue4 > 10) {
    Serial.println("Photodiode 4 ON");
    midiNoteOn(0, 34, volume);}
  if (sensorValue5 > 10) {
    Serial.println("Photodiode 5 ON");
    midiNoteOn(0, 35, volume);}
  if (sensorValue6 > 10) {
    Serial.println("Photodiode 6 ON");
    midiNoteOn(0, 36, volume);}
  if (sensorValue7 > 10) {
    Serial.println("Photodiode 7 ON");
    midiNoteOn(0, 37, volume);}
  if (sensorValue8 > 10) {
    Serial.println("Photodiode 8 ON");
    midiNoteOn(0, 38, volume);}
  else {
    Serial.println("OFF");}

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
