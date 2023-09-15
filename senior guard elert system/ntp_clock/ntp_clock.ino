#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const char* ssid = "SANKARAM";     // Replace with your Wi-Fi SSID
const char* password = "00000000"; // Replace with your Wi-Fi password

const char* ntpServerName = "pool.ntp,org"; // Use an NTP server in your region
WiFiUDP udp;
NTPClient timeClient(udp, ntpServerName,19800,60000);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.print("Current time: ");
  Serial.println(timeClient.getFormattedTime());

  delay(1000); // Update the time every second
}
