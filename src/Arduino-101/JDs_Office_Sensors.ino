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
int calibratedLightLevel = -2; // in footcandles
int maxThreshold = 0;     // for light level
int minThreshold = 1023;   // for light level

// Define the B-value of the thermistor.
// This value is a property of the thermistor used in the Grove - Temperature Sensor,
// and used to convert from the analog value it measures and a temperature value.
const int B = 3975;

const int colorR = 0;
const int colorG = 96;
const int colorB = 128;

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.setRGB(colorR, colorG, colorB);
  lcd.clear();
  lcd.print("- JD's Office -");
}

void loop()
{
  lightLevel = analogRead(photoSensorPin);

  // Conversion for using 5v power instead of 3.3v
  lightLevel = lightLevel / 1.515151;
  
  calibrateLightLevel(25);    // calibrates the light level with a calculated calibration ratio
  
  Serial.print("Light - Voltage: ");
  Serial.print(lightLevel);
  Serial.print(", Footcandles: ");
  Serial.print(calibratedLightLevel);
  Serial.print(";     ");

  float resistance;
  float degreesC;
  float degreesF;

  resistance = getResistance(temperaturePin);

  degreesC = 1/(log(resistance/10000)/B+1/298.15)-273.15;

  // Conversion for using 5v power instead of 3.3v
  // not sure why yet, but seems to be needed twice...
  degreesC = degreesC / 1.515151;
  degreesC = degreesC / 1.515151;
    
  degreesF = degreesC * (9.0 / 5.0) + 32.0;
  
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

  lcd.setCursor(0, 1);   // Move to column 0, row 1 (second row)
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

float getResistance(int pin)
{
  int rawValue = analogRead(pin);
  float resistance = (float)(1023-rawValue)*10000/rawValue;
  return resistance;
}
