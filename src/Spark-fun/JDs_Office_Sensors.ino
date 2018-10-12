/******************************************************************
 * This sketch draws inspiration and some code from:
 * SparkFun Inventor's Kit
 * Example sketches 06, 07, & 15
 * 
 * PHOTO RESISTOR
 *  Use a photoresistor (light sensor) to control the brightness
 *  of a LED.
 *  
 * Version 2.0 6/2012 MDG
 * Version 2.1 9/2014 BCH
 * 
 * TEMPERATURE SENSOR
 *   Use the "serial monitor" window to read a temperature sensor.
 *   
 * Version 2.0 6/2012 MDG
 * 
 * LIQUID CRYSTAL DISPLAY (LCD)
 *  This sketch will show you how to connect an LCD to your Arduino
 *  and display any data you wish.
 *
 * Version 1.0 2/2013 MDG
 * 
 * Those sketches were written by SparkFun Electronics,
 * with lots of help from the Arduino community.
 * This code is completely free for any use.
 * Visit http://learn.sparkfun.com/products/2 for SIK information.
 * Visit http://www.arduino.cc to learn about the Arduino.
 */
/*****************************************************************/


// Load the LiquidCrystal library to interface with the LCD
#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int photoSensorPin = A0;
const int temperaturePin = A1;

int lightLevel = -1;
int calibratedLightLevel = -2; // in footcandles
int maxThreshold = 0;     // for light level
int minThreshold = 1023;   // for light level

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.clear();
  lcd.print("- JD's Office -");
}

void loop()
{
  lightLevel = analogRead(photoSensorPin);
  calibrateLightLevel(25);    // calibrates the light level with a calculated calibration ratio
  
  Serial.print("Light - Voltage: ");
  Serial.print(lightLevel);
  Serial.print(", Footcandles: ");
  Serial.print(calibratedLightLevel);
  Serial.print(";     ");

  float voltage;
  float degreesC;
  float degreesF;

  voltage = getVoltage(temperaturePin);

  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0 / 5.0) + 32.0;
  
  Serial.print("Temperature - Voltage: ");
  Serial.print(voltage);
  Serial.print(", °C: ");
  Serial.print(degreesC);
  Serial.print(", °F: ");
  Serial.print(degreesF);
  Serial.println(";");

  // Round temp to 1 decimal place
  char degreesFChars[10];
  dtostrf(degreesF, 3, 1, degreesFChars);

  lcd.setCursor(0, 1);   // Start from to column 0, row 1 (second row)
  lcd.print(" ");
  lcd.print(degreesFChars);
  lcd.print((char)223);   // 223 represents '°' on this LCD (HD44780?)
  lcd.print("F  ");
  if (calibratedLightLevel < 10 && calibratedLightLevel >= 0) lcd.print("0");
  lcd.print(calibratedLightLevel);
  lcd.print(" fc"); 
  
  delay(1000);
}

void calibrateLightLevel(int calibrationConstant)
{
  calibratedLightLevel = lightLevel / calibrationConstant;
}

float getVoltage(int pin)
{
  // Convert 10-bit value to real voltage (0.0v - 5.0v)
  return (analogRead(pin) * 0.004882814); 
}
