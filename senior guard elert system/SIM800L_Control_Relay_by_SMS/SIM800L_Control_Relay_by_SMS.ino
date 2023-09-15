#include <SoftwareSerial.h>

const String PHONE_NUMBER = "8790025546"; // Replace with the phone number you want to send an SMS to and call

#define RX_PIN D9 // Connect SIM800L RX to Arduino Uno digital pin 2
#define TX_PIN D10 // Connect SIM800L TX to Arduino Uno digital pin 3

SoftwareSerial sim800l(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);

  delay(1000); // Wait for SIM800L to initialize

  Serial.println("Initializing SIM800L...");
  sim800l.println("AT"); // Send AT command to check if SIM800L is responding
  delay(1000);

  if (sim800l.find("OK")) {
    Serial.println("SIM800L is ready.");
  } else {
    Serial.println("SIM800L initialization failed. Check connections and restart.");
    while (true); // You may want to add error handling here
  }
}

void loop() {
  sendSMS();
  delay(5000); // Wait for a few seconds before making a call
  makeCall();
  delay(60000); // Call every 60 seconds (adjust as needed)
}

void sendSMS() {
  Serial.println("Sending SMS...");
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);

  sim800l.print("AT+CMGS=\"");
  sim800l.print(PHONE_NUMBER);
  sim800l.println("\""); // Set the destination phone number
  delay(1000);

  sim800l.print("This is a test SMS from SIM800L and Arduino Uno.");
  sim800l.write(26); // Send Ctrl+Z to indicate the end of the SMS
  delay(1000);

  if (sim800l.find("OK")) {
    Serial.println("SMS sent successfully.");
  } else {
    Serial.println("Failed to send SMS.");
  }
}

void makeCall() {
  Serial.println("Making a call...");
  sim800l.println("ATD" + PHONE_NUMBER + ";"); // ATD to dial the number
  delay(10000); // Allow time for the call to establish (adjust as needed)
  sim800l.println("ATH"); // Hang up the call
  delay(1000);
  Serial.println("Call ended.");
}
