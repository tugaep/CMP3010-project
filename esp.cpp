#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Serial connection with Arduino
SoftwareSerial arduinoSerial(D5, D6); // RX, TX

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";             // Update this
const char* password = "YOUR_WIFI_PASSWORD";     // Update this

// Firebase info
const char* firebaseHost = "YOUR_FIREBASE_HOST"; // Update this
const char* firebaseAuth = "YOUR_FIREBASE_AUTH"; // Update this

void setup() {
  Serial.begin(115200);
  arduinoSerial.begin(9600);

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }

  Serial.println("\n✅ WiFi connected!");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
}

void loop() {
  if (arduinoSerial.available()) {
    String json = arduinoSerial.readStringUntil('\n');

    Serial.println("📥 Received JSON from Arduino:");
    Serial.println(json);

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.print("❌ JSON parse failed: ");
      Serial.println(error.c_str());
      return;
    }

    // Send to firebase
    sendToFirebase(json);
  }
}

void sendToFirebase(String json) {
  WiFiClientSecure client;
  client.setInsecure();  // Use if you don't want to validate SSL cert

  String url = String("/sensorData.json?auth=") + firebaseAuth;

  if (!client.connect(firebaseHost, 443)) {
    Serial.println("❌ Failed to connect to Firebase server");
    return;
  }

  String request =
    String("PUT ") + url + " HTTP/1.1\r\n" +
    "Host: " + firebaseHost + "\r\n" +
    "Content-Type: application/json\r\n" +
    "Content-Length: " + json.length() + "\r\n\r\n" +
    json;

  client.print(request);
  Serial.println("📡 Sending data to Firebase...");

  // Read response (optional)
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  Serial.println("✅ Data sent to Firebase.");
  client.stop();
}