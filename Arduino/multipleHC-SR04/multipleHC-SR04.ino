                       /*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */

const int trigPin1 = 53;
const int trigPin2 = 51;
const int trigPin3 = 49;

const int echoPin1 = 52;
const int echoPin2 = 50;
const int echoPin3 = 48;
int minimum = 0;

float duration1, distance1, duration2, distance2, duration3, distance3;
long duration, distance, sensor1, sensor2, sensor3;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Serial.begin(9600);
}

void loop() {

  SonarSensor(trigPin1, echoPin1);
  sensor1  = distance;
  SonarSensor(trigPin2, echoPin2);
  sensor2 = distance;
  SonarSensor(trigPin3, echoPin3);
  sensor3 = distance;
  
  Serial.print(sensor1);
  Serial.print(" - ");
  Serial.print(sensor2);
  Serial.print(" - ");
  Serial.println (sensor3);
  delay(100);
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
