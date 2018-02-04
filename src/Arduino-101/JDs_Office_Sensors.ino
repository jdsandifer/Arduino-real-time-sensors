/******************************************************************
 * This sketch draws inspiration and some code from:
 * Arduino 101 & Seeedstudio Grove Starter Kit for Arduino
/*****************************************************************/


// Include libraries for RGB LCD
#include <Wire.h>
#include "rgb_lcd.h"

// Initialize the LCD screen
rgb_lcd lcd;

const int photoSensorPin = A0;
const int temperaturePin = A1;

int lightLevel = -1;
int calibratedLightLevel = -2; // used to store the calibrated lightLevel (footcandles)
int maxThreshold = 0;     // used for setting the "max" light level
int minThreshold = 1023;   // used for setting the "min" light level

// Define the B-value of the thermistor.
// This value is a property of the thermistor used in the Grove - Temperature Sensor,
// and used to convert from the analog value it measures and a temperature value.
const int B = 3975;

// Setup RGB backlight color on LCD
const int colorR = 0;
const int colorG = 96;
const int colorB = 128;

void setup()
{
  Serial.begin(9600);

  // Initialize the 16x2 LCD, clear it, and say hi
  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.setRGB(colorR, colorG, colorB);
  lcd.clear();  //Clear any old data displayed on the LCD
  lcd.print("- JD's Office -"); // Display a message on the LCD!
}

void loop()
{
  // Read and calibrate light level
  lightLevel = analogRead(photoSensorPin);  // reads the voltage on the sensorPin

  // Conversion for using 5v power instead of 3.3v
  lightLevel = lightLevel / 1.515151;
  
  calibrateLightLevel(25);    // calibrates the light level with a calculated calibration ratio
  
  // Log light levels (uncalibrated and calibrated) to serial port ("xxx,  xx fc")
  Serial.print("Light - Voltage: ");
  Serial.print(lightLevel);
  Serial.print(", Footcandles: ");
  Serial.print(calibratedLightLevel);
  Serial.print(";     ");

  // Setup for temperature gathering
  float resistance;
  float degreesC;
  float degreesF;

  // Get temperature from sensor
  resistance = getResistance(temperaturePin); //Measure the voltage at the analog pin

  // Convert raw data to Fahrenheit and Celsius
  degreesC = 1/(log(resistance/10000)/B+1/298.15)-273.15;

  // Conversion for using 5v power instead of 3.3v
  // not sure why yet, but seems to be needed twice...
  degreesC = degreesC / 1.515151;
  degreesC = degreesC / 1.515151;
    
  degreesF = degreesC * (9.0 / 5.0) + 32.0;
  
  // Now print to the Serial monitor lines of data like this:
  // "voltage: 0.73 deg C: 22.75 deg F: 72.96"
  Serial.print("Temperature - Resistance: ");
  Serial.print(resistance);
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

float getResistance(int pin)
{
  // Get the raw value of the temperature sensor.
  int rawValue = analogRead(pin);
  
  /// Determine the current resistance of the thermistor based on the sensor value.
  float resistance = (float)(1023-rawValue)*10000/rawValue;

  return resistance;
}
