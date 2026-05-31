#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== WIFI =====
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ===== THINGSPEAK =====
String apiKey = "YOUR_THINGSPEAK_API_KEY";
const char* server = "http://api.thingspeak.com/update";

// ===== OLED =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ===== RGB LED =====
#define RED 4
#define GREEN 5
#define BLUE 18

// ===== GLOBAL ARRAYS =====
int channelCount[14];
int channelRSSISum[14];

int bestChannel = 0;
int bestAvgRSSI = -100;
int minCount = 999;

String bestSSID = "";
String networkHealth = "";

unsigned long lastUploadTime = 0;


// ================= BOOT ANIMATION =================
void bootAnimation() {

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(25, 10);
  display.println("SMART CHANNEL");

  display.setCursor(22, 22);
  display.println("RECOMMENDATION");

  display.setCursor(46, 34);
  display.println("SYSTEM");

  display.display();
  delay(1500);

  display.clearDisplay();
  display.setCursor(20, 15);
  display.println("Initializing...");
  display.drawRect(14, 35, 100, 10, WHITE);

  for (int i = 0; i <= 96; i += 4) {
    display.fillRect(16, 37, i, 6, WHITE);
    display.display();
    delay(60);
  }

  delay(500);
  display.clearDisplay();
  display.display();
}
// ===================================================


void setup() {

  Serial.begin(115200);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  bootAnimation();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}


void loop() {

  int n = WiFi.scanNetworks();

  for (int i = 0; i < 14; i++) {
    channelCount[i] = 0;
    channelRSSISum[i] = 0;
  }

  Serial.println("\nScanning WiFi Networks...");
  Serial.println("Individual Network Details:");

  for (int i = 0; i < n; i++) {

    int ch = WiFi.channel(i);
    int rssi = WiFi.RSSI(i);

    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" | Channel: ");
    Serial.print(ch);
    Serial.print(" | RSSI: ");
    Serial.println(rssi);

    channelCount[ch]++;
    channelRSSISum[ch] += rssi;
  }

  Serial.println("\nChannel Occupancy Summary:");
  for (int ch = 1; ch <= 13; ch++) {
    if (channelCount[ch] > 0) {
      Serial.print("Channel ");
      Serial.print(ch);
      Serial.print(": ");
      Serial.print(channelCount[ch]);
      Serial.println(" network(s)");
    }
  }

  minCount = 999;
  bestAvgRSSI = -100;

  // ===== SMART SELECTION (YOUR ORIGINAL LOGIC) =====
  for (int ch = 1; ch <= 13; ch++) {

    if (channelCount[ch] > 0) {

      int avg = channelRSSISum[ch] / channelCount[ch];

      if (channelCount[ch] < minCount ||
         (channelCount[ch] == minCount && avg > bestAvgRSSI)) {

        minCount = channelCount[ch];
        bestChannel = ch;
        bestAvgRSSI = avg;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (WiFi.channel(i) == bestChannel) {
      bestSSID = WiFi.SSID(i);
      break;
    }
  }

  // ===== HEALTH CLASSIFICATION =====
  if (minCount <= 1 && bestAvgRSSI > -60)
    networkHealth = "HEALTHY";
  else if (minCount <= 3 && bestAvgRSSI > -75)
    networkHealth = "MODERATE";
  else
    networkHealth = "POOR";

  int healthNumeric = 0;
  if (networkHealth == "HEALTHY") healthNumeric = 2;
  else if (networkHealth == "MODERATE") healthNumeric = 1;
  else healthNumeric = 0;


  Serial.println("\n===== SMART ANALYSIS RESULT =====");
  Serial.print("Recommended Channel: ");
  Serial.println(bestChannel);
  Serial.print("Detected Network Name: ");
  Serial.println(bestSSID);
  Serial.println("Decision Basis: Least congestion and minimum interference among detected channels.");
  Serial.print("Network Health: ");
  Serial.println(networkHealth);


  // ===== OLED DISPLAY =====
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("SMART RESULT");

  display.setCursor(0, 15);
  display.print("Channel: ");
  display.println(bestChannel);

  display.setCursor(0, 30);
  display.print("Network:");
  display.println(bestSSID);

  display.setCursor(0, 45);
  display.print("Health:");
  display.println(networkHealth);

  int bars = 1;
  if (bestAvgRSSI > -50) bars = 5;
  else if (bestAvgRSSI > -60) bars = 4;
  else if (bestAvgRSSI > -70) bars = 3;
  else if (bestAvgRSSI > -80) bars = 2;

  for (int i = 0; i < bars; i++) {
    display.fillRect(95 + (i * 6), 54, 4, 8, WHITE);
  }

  display.display();


  // ===== RGB LED =====
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  if (healthNumeric == 2) digitalWrite(GREEN, HIGH);
  else if (healthNumeric == 1) digitalWrite(BLUE, HIGH);
  else digitalWrite(RED, HIGH);


  // ===== THINGSPEAK (15 SEC UPDATE) =====
  if (millis() - lastUploadTime > 15000) {

    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;

      String url = String(server) + "?api_key=" + apiKey +
                   "&field1=" + String(bestChannel) +
                   "&field2=" + String(bestAvgRSSI) +
                   "&field3=" + String(minCount) +
                   "&field4=" + String(healthNumeric);

      http.begin(url);
      int httpResponseCode = http.GET();

      Serial.print("ThingSpeak Response: ");
      Serial.println(httpResponseCode);

      http.end();
    }

    lastUploadTime = millis();
  }

  delay(3000);   // Serial refresh every 3 seconds
}
