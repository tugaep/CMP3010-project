#include <SoftwareSerial.h>
#include <ArduinoJson.h>

const int buttonPin = 3;
const int buzzerPin = 8;
const int pirPin = 2;
const int waterSensorPin = A0;
const int reedPin = A3;
const int gasSensorPin = A5;

//esp connection
SoftwareSerial esp(10, 11); // RX, TX


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(reedPin, INPUT_PULLUP);

  digitalWrite(buzzerPin, LOW);


  Serial.begin(9600);
  esp.begin(9600);
}

void loop() {
  bool buttonPressed = digitalRead(buttonPin) == LOW;
  bool motionDetected = digitalRead(pirPin) == HIGH;
  int reedState   = digitalRead(reedPin) == HIGH;
  int waterLevel = analogRead(waterSensorPin);
  int gasLevel = analogRead(gasSensorPin);
  
  if (digitalRead(buttonPin) == LOW) { //button pressed
   digitalWrite(buzzerPin, HIGH);
   delay(20);
  }
  if(digitalRead(buttonPin) == HIGH){ //button released
    digitalWrite(buzzerPin, LOW);
  }
  
  // build json to send esp
  StaticJsonDocument<200> doc;
  doc["gasLevel"] = gasLevel;
  doc["motionDetected"] = motionDetected;
  doc["fridgeDoorOpen"] = reedState;
  doc["waterLevel"] = waterLevel;
  doc["timestamp"] = millis();
  doc["buttonPressed"] = buttonPressed;

  String output;
  serializeJson(doc, output);

  // send json to esp
  esp.println(output);

  // debug
  Serial.println("Sent to ESP:");
  Serial.println(output);

  delay(2000); // delay to avoid flooding the esp with messages
}
