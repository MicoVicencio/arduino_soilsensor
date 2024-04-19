#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the address if necessary
#define sensorPin A0
#define relayPin 8

void setup() {
  Serial.begin(9600);
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  ; // Note the space after the colon
  pinMode(relayPin, OUTPUT); // Set relay pin as output
}

void loop() {
  int sensorValue = readSensor();
  Serial.println(sensorValue);
  
  
  
  if (sensorValue < 500) {
    digitalWrite(relayPin, HIGH); // Turn on relay if analog value < 500
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SoilLevel: ");
    lcd.setCursor(0, 1);
    lcd.print("Relay: OFF ");
    lcd.setCursor(10, 0); // Move cursor to position after "SensorValue: "
    lcd.print("WET"); // Print the sensor value
  } else {
    digitalWrite(relayPin, LOW); // Turn off relay if analog value >= 500
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SoilLevel: ");
    lcd.setCursor(0, 1);
    lcd.print("Relay: ON");
    lcd.setCursor(10, 0); // Move cursor to position after "SensorValue: "
    lcd.print("DRY"); // Print the sensor value
  }
  
  delay(1000);
}

int readSensor() {
  int val = analogRead(sensorPin);
  return val;
}
