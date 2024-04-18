//https://thearduinoworkshop.weebly.com/photodiode.html

int sensorPin1 = 23;
int sensorPin2 = 25;
int sensorPin3 = 27;

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;

int nextSensor1 = 0;
int nextSensor2 = 0;
int nextSensor3 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin1,INPUT);
  pinMode(sensorPin2,INPUT);
  pinMode(sensorPin3,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue1= digitalRead(sensorPin1);
  sensorValue2= digitalRead(sensorPin2);
  sensorValue3= digitalRead(sensorPin3);
  
  if (sensorValue1 == HIGH){
    //Serial.println(sensorValue1);
    if (nextSensor1 == 0){
      Serial.println("10");
      nextSensor1 = 1;
    };
  }
  else{
    if (nextSensor1 == 1) {
      Serial.println("00");
      nextSensor1 = 0;
    };
  };
  if (sensorValue2 == HIGH)  {                                                                                                                                                                                                                                                                                                                                    
    //Serial.println("2 ON");
    if (nextSensor2 == 0){
      Serial.println("12");
      nextSensor2 = 1;
    };
  }
  else{
    if (nextSensor2 == 1) {
      Serial.println("02");
      nextSensor2 = 0;
    };
  };
  if (sensorValue3 == HIGH){
    //Serial.println("3 ON");
    if (nextSensor3 == 0){
      Serial.println("13");
      nextSensor3 = 1;
    };
  }
  else{
    if (nextSensor3 == 1) {
      Serial.println("03");
      nextSensor3 = 0;
    };
  };
  

}
