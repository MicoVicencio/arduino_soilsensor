#include <LiquidCrystal_I2C.h>

// Initialize LCD object with I2C address, columns, and rows
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the address if necessary

// Define sensor and relay pins
#define sensorPin A0
#define relayPin 8

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  // Initialize and turn on the LCD
  lcd.init();
  lcd.backlight();

  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Read sensor value
  int sensorValue = readSensor();

  // Print sensor value to serial monitor
  Serial.println(sensorValue);

  // Check sensor value and control relay and LCD display accordingly
  if (sensorValue < 500) {
    // Turn on relay if sensor value is less than 500
    digitalWrite(relayPin, HIGH);

    // Clear LCD and print messages
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SoilLevel: ");
    lcd.setCursor(0, 1);
    lcd.print("Relay: OFF ");
    lcd.setCursor(10, 0); // Move cursor to position after "SensorValue: "
    lcd.print("WET"); // Print the sensor value
  } else {
    // Turn off relay if sensor value is greater than or equal to 500
    digitalWrite(relayPin, LOW);

    // Clear LCD and print messages
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SoilLevel: ");
    lcd.setCursor(0, 1);
    lcd.print("Relay: ON");
    lcd.setCursor(10, 0); // Move cursor to position after "SensorValue: "
    lcd.print("DRY"); // Print the sensor value
  }

  // Delay for 1 second before the next iteration
  delay(1000);
}

// Function to read sensor value
int readSensor() {
  int val = analogRead(sensorPin);
  return val;
}
