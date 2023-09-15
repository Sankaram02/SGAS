#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LiquidCrystal_I2C library with the address of your I2C module
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change the address to match your LCD

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight (if supported)
  lcd.backlight();

  // Print a welcome message
  lcd.setCursor(0, 0);
  lcd.print("NodeMCU + LCD");
  lcd.setCursor(0, 1);
  lcd.print("Ready!");
  delay(2000);  // Display for 2 seconds
  lcd.clear();  // Clear the LCD screen
}

void loop() {
  // Display your data on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print("25.5°C");  // Replace this with your data source

  delay(1000);  // Update every second (adjust as needed)
}
