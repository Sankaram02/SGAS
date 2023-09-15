#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address (0x27 for most I2C backpacks)
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16x2 LCD

void setup() {
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
  // Set the cursor to the home position
  lcd.setCursor(0, 0);
  // Display "Hello" on the first line
  lcd.print("Hello");
}

void loop() {
  // Your main program loop (if needed)
}
