#include <SoftwareSerial.h>

const int trigPin = 2;
const int echoPin = 3;

const int bluetoothTx = 11; 
const int bluetoothRx = 10; 

const int buzzerPin = 6;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

const int BUZZER_OFF = 0;
const int BUZZER_ON = 1;

int buzzerState = BUZZER_OFF;

void setup() {

  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); 
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.034 / 2;

  if (distance < 90 && buzzerState == BUZZER_OFF) { // Lower threshold

    digitalWrite(buzzerPin, HIGH);
    buzzerState = BUZZER_ON;

    bluetooth.println("Object Detected");
  } 
  else if (distance > 100 && buzzerState == BUZZER_ON) { 
    // Turn off buzzer
    digitalWrite(buzzerPin, LOW);
    buzzerState = BUZZER_OFF;
  }

  delay(1000); 
}
