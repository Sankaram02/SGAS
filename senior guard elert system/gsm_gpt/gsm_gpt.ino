#include <SoftwareSerial.h>

// Define the TX and RX pins for SoftwareSerial communication with the SIM800L module
#define SIM800_TX D7 // Connect this pin to SIM800L's RX pin
#define SIM800_RX D8  // Connect this pin to SIM800L's TX pin

// Create a SoftwareSerial object to communicate with the SIM800L module
SoftwareSerial sim800(SIM800_TX, SIM800_RX);

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging
  sim800.begin(9600);  // Initialize SoftwareSerial communication with SIM800L

  delay(2000);  // Give SIM800L some time to initialize
  Serial.println("SIM800L Ready");
}

void loop() {
  // Check if there's incoming data from SIM800L
  if (sim800.available()) {
    char c = sim800.read();
    Serial.write(c);
  }

  // Send an SMS
  sendSMS("+918790025546", "Hello from SIM800L!");

  // Make a call
  makeCall("8790025546");

  delay(5000);  // Wait for 5 seconds before repeating
}

void sendSMS(const char* phoneNumber, const char* message) {
  sim800.println("AT+CMGF=1");  // Set SMS mode to text
  delay(1000);
  sim800.print("AT+CMGS=\"");
  sim800.print(phoneNumber);
  sim800.println("\"");
  delay(1000);
  sim800.print(message);
  sim800.write(0x1A);  // End the message with Ctrl+Z
  delay(1000);
}

void makeCall(const char* phoneNumber) {
  sim800.print("ATD");
  sim800.print(phoneNumber);
  sim800.println(";");
  delay(10000);  // Wait for 10 seconds (adjust as needed)
  sim800.println("ATH");  // End the call
}
