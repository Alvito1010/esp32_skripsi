#include <Arduino.h>
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

const int trigPin1 = 5;
const int echoPin1 = 18;
const int trigPin2 = 19;
const int echoPin2 = 21;
const int trigPin3 = 22;
const int echoPin3 = 23;
const int ledPin = 13;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm1, distanceCm2, distanceCm3;

#define AWS_IOT_PUBLISH_TOPIC "$aws/things/memilah-1/shadow/name/memilah-1/update"

// Function to get distance from ultrasonic sensor
float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * SOUND_SPEED / 2;
}

// AWS IoT setup
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

// Function to publish sensor data to AWS IoT
void publishMessage(float levelPlastic, float levelPaper, float levelCan, String AWS_TOPIC) {
  StaticJsonDocument<200> doc;
  doc["plastic"] = levelPlastic;
  doc["paper"] = levelPaper;
  doc["can"] = levelCan;  
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

  client.publish(AWS_TOPIC.c_str(), jsonBuffer);
}

// AWS IoT message handler
void messageHandler(char* topic, byte* payload, unsigned int length) {
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

void connectAWS(bool turnOnLed) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED){
    Serial.println("WiFi connected");
  }

  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  client.subscribe(AWS_IOT_PUBLISH_TOPIC);

  Serial.println("AWS IoT Connected!");
  if (turnOnLed) {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  connectAWS(true); // Turn on LED when connecting for the first time
}

void loop() {
  // Check Wi-Fi and AWS IoT connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected, attempting to reconnect");
    digitalWrite(BUILTIN_LED, LOW); // Turn off LED when disconnected
    connectAWS(false); // Don't turn on LED when reconnecting
  } else if (!client.connected()) {
    Serial.println("AWS IoT disconnected, attempting to reconnect");
    digitalWrite(BUILTIN_LED, LOW); // Turn off LED when disconnected
    connectAWS(false); // Don't turn on LED when reconnecting
  } else {
    digitalWrite(BUILTIN_LED, HIGH); // Turn on LED when both Wi-Fi and AWS IoT are connected
  }

  // Read distances from sensors
  distanceCm1 = getDistance(trigPin1, echoPin1);
  delay(1000);
  distanceCm2 = getDistance(trigPin2, echoPin2);
  delay(1000);
  distanceCm3 = getDistance(trigPin3, echoPin3);

  // Print distances to Serial Monitor
  Serial.print("Sensor 1 - Distance (cm): ");
  Serial.println(distanceCm1);
  Serial.print("Sensor 2 - Distance (cm): ");
  Serial.println(distanceCm2);
  Serial.print("Sensor 3 - Distance (cm): ");
  Serial.println(distanceCm3);
  Serial.println();
  Serial.println();
  Serial.println();

  // Publish distances to AWS IoT
  publishMessage(distanceCm1, distanceCm2, distanceCm3, AWS_IOT_PUBLISH_TOPIC);

  // Check if any distance is less than 10 cm
  if (distanceCm1 < 10 || distanceCm2 < 10 || distanceCm3 < 10) {
    // Blink the LED
    for (int i = 0; i < 10; i++) { // Blink 10 times
      digitalWrite(ledPin, HIGH);
      delay(100); // LED on for 100 milliseconds
      digitalWrite(ledPin, LOW);
      delay(100); // LED off for 100 milliseconds
    }
  }

  // Maintain MQTT connection
  client.loop();
  delay(1000); // Wait for 1 second before next measurement
}
