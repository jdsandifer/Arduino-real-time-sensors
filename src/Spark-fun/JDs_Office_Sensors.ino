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
int calibratedLightLevel = -2; // used to store the calibrated lightLevel (footcandles)
int maxThreshold = 0;     // used for setting the "max" light level
int minThreshold = 1023;   // used for setting the "min" light level

void setup()
{
  Serial.begin(9600);

  // Initialize the 16x2 LCD, clear it, and say hi
  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.clear();  //Clear any old data displayed on the LCD
  lcd.print("- JD's Office -"); // Display a message on the LCD!
}

void loop()
{
  // Read and calibrate light level
  lightLevel = analogRead(photoSensorPin);  // reads the voltage on the sensorPin
  calibrateLightLevel(25);    // calibrates the light level with a calculated calibration ratio
  
  // Log light levels (uncalibrated and calibrated) to serial port ("xxx,  xx fc")
  Serial.print("Light - Voltage: ");
  Serial.print(lightLevel);
  Serial.print(", Footcandles: ");
  Serial.print(calibratedLightLevel);
  Serial.print(";     ");

  // Setup for temperature gathering
  float voltage;
  float degreesC;
  float degreesF;

  // Get temperature from sensor
  voltage = getVoltage(temperaturePin); //Measure the voltage at the analog pin

  // Convert raw data to Fahrenheit and Celsius
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0 / 5.0) + 32.0;
  
  // Now print to the Serial monitor lines of data like this:
  // "voltage: 0.73 deg C: 22.75 deg F: 72.96"
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

  // Display sensor info on the LCD
  lcd.setCursor(0, 1);   // Start from to column 0, row 1 (second row)
  lcd.print(" ");
  lcd.print(degreesFChars);
  lcd.print((char)223);   // 223 represents '°' on this LCD (HD44780?)
  lcd.print("F  ");
  if (calibratedLightLevel < 10 && calibratedLightLevel >= 0) lcd.print("0");   // add a zero for single digits
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
  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 5.0 value that is the true voltage
  // being read at that pin.
  return (analogRead(pin) * 0.004882814); 
}
