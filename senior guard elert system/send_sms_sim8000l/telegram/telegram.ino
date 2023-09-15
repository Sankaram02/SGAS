#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>

const char* ssid = "POCO X3";
const char* password = "rajcharan";
const char* botToken = "6544199889:AAHN1xoa8OV4OCt6J-986JLF2UBN7Xbwnro";

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

void setup() {
    Serial.begin(115200);
    delay(10);

    // Connect to Wi-Fi
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Send a message to a specific chat ID
    int chat_id = 4088246932; // Replace with the chat ID of your recipient
    String text = "Alert! This is a test message.";

    if (bot.sendMessage(chat_id, text, "Markdown")) {
        Serial.println("Message sent successfully!");  
    } else {
        Serial.println("Failed to send message.");
    }

    delay(60000); // Send a message every 60 seconds (adjust as needed)
}
