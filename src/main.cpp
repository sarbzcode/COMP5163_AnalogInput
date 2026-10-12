/*Statement of Authorship
I, Sarbjot Singh(0307838), certify that this is my own work and that I have not copied it from any other source.

COMP 5163 - Internet of Things Programming
Lab : Analog Signals 
*/

#include <Arduino.h>

const int LED_GREEN = D5;
const int LED_YELLOW = D6;
const int LED_RED = D7;


const int ADC_MAX = 1023;


const float TEMP_MIN = 0.0;
const float TEMP_MAX = 50.0;


const unsigned long PRINT_INTERVAL_MS = 2000; 
const unsigned long LED_INTERVAL_MS = 100;    

unsigned long lastPrint = 0;
unsigned long lastLed = 0;


float digitizedToTemperature(int iVal)
{
  return TEMP_MIN + ((float)iVal / ADC_MAX) * (TEMP_MAX - TEMP_MIN);
}


String judgeTemperature(float temp)
{
  if (temp < 10.0)
    return "Cold!";
  else if (temp < 15.0)
    return "Cool";
  else if (temp < 25.0)
    return "Perfect";
  else if (temp < 30.0)
    return "Warm";
  else if (temp <= 35.0)
    return "Hot";
  else
    return "Too Hot!";
}


void updateLeds(float temp)
{
  digitalWrite(LED_YELLOW, temp < 15.0 ? HIGH : LOW);  
  digitalWrite(LED_GREEN, (temp >= 15.0 && temp < 25.0) ? HIGH : LOW);
  digitalWrite(LED_RED, temp >= 25.0 ? HIGH : LOW);     
}

void setup()
{
 
  Serial.begin(115200);

 
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}

void loop()
{
  unsigned long now = millis();

  
  int iVal = analogRead(A0);


  float temp = digitizedToTemperature(iVal);

  
  if (now - lastLed >= LED_INTERVAL_MS)
  {
    lastLed = now;
    updateLeds(temp);
  }

  
  if (now - lastPrint >= PRINT_INTERVAL_MS)
  {
    lastPrint = now;

    Serial.println("Digitized output of " + String(iVal) +
                   " is equivalent to a temperature input of " +
                   String(temp, 2) + " deg. C, which is " +
                   judgeTemperature(temp));
  }
}
