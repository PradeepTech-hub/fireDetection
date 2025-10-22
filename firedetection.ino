#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your WiFi credentials
const char* ssid = "your ssid";
const char* password = "your password";

// Pin definitions
#define LED1 19
#define LED2 22
#define Buzzer 18
#define Sensor 23
#define LED_BUILTIN 2 // GPIO2 is usually connected to the built-in blue LED

// Replace with your Integromat (Make) Webhook URL
const char* webhookURL = "https://hook.eu2.make.com/Your URl";

void setup() {
  Serial.begin(9600);

  // Set pin modes
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Sensor, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  digitalWrite(LED_BUILTIN, HIGH); // Turn on built-in LED

  // Ensure LED1 is always on at the start
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(Buzzer, LOW);
}

void sendNotification() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(webhookURL);
    http.addHeader("Content-Type", "application/json");

    // JSON payload to send to Integromat
    String jsonPayload = "{\"message\":\"Fire detected\", \"status\":\"ALERT\"}";
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.printf("Webhook POST sent, code: %d\n", httpResponseCode);
    } else {
      Serial.printf("Error sending POST: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}

void loop() {
  int sensor = digitalRead(Sensor);

  if (sensor == 1) {
    // No fire detected
    digitalWrite(LED1, HIGH);  // LED1 on
    digitalWrite(LED2, LOW);   // LED2 off
    digitalWrite(Buzzer, LOW); // Buzzer off
  } else if (sensor == 0) {
    // Fire detected
    Serial.println("WARNING! A fire was detected");
    digitalWrite(LED1, LOW);   // LED1 off
    digitalWrite(LED2, HIGH);  // LED2 on
    digitalWrite(Buzzer, HIGH);// Buzzer on
    sendNotification();        // Notify Integromat
  }

  delay(1000); // Check sensor every 1 second
}
