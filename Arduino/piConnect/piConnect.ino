int sensorPin0 = A0 ;
int sensorValue0 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin0,INPUT);
}

void loop() {

  sensorValue0= analogRead(sensorPin0);
  if (sensorValue0 > 10){
    Serial.println('0');
  } else {


  }


  

}
