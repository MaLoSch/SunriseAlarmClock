/*
 * Arduino code for Sunrise Alarm Clock
 * Last updated 2017-03-21
 * 
 * Code by Markus Lorenz Schilling
 * http://malosch.com/
 * 
 * GitHub
 * https://github.com/MaLoSch/SunriseAlarmClock
*/
 
/* LIBRARIES */
#include "FastLED.h" // Include FastLED library http://fastled.io/
#include <Wire.h> // Allows devices to communicate with the Two Wire Interface Bus
#include <Time.h> // Include time library
#include <DS1307RTC.h> // Include DS1307 RTC library for the tiny RTC module
#include <Encoder.h> // Include the encoder library to easily read the rotary encoder

/* CONSTANT VARIABLES */
const int rgbLEDMatrixPin = 9; // Pin # for lower light
const int numPixelPerMatrix = 64; // # of pixels per LED strip
const int buttonPin = 12; // pin the push button is connected to
char* numbers[] = {
  "0000000000000000111111111111111111000011110000111111111111111111", // #0
  "0000000000000000000000000000000000000000000000001111111111111111", // #1
  "0000000000000000111110111111101111011011110110111101111111011111", // #2
  "0000000000000000110110111101101111011011110110111111111111111111", // #3
  "0000000000000000000111110001111100011000000110001111111111111111", // #4
  "0000000000000000110111111101111111011011110110111111101111111011", // #5
  "0000000000000000111111111111111111011011110110111111101111111011", // #6
  "0000000000000000000000110000001100000011000000111111111111111111", // #7
  "0000000000000000111111111111111111011011110110111111111111111111", // #8
  "0000000000000000110111111101111111011011110110111111111111111111"  // #9
  };

/* NEOPIXEL */
CRGB rgbLEDMatrix[numPixelPerMatrix]; // RGB LED Matrix

/* TIME */
tmElements_t tm; // Initiate a tmElements_t object called tm that can access the current time
int currentHour; // variable to store current hour as an integer
int currentMinute; // variable to store current minute as an integer

/* ALARM */
int alarmHour = 22; // variable to store the hour of the set alarm time
int alarmMinute = 29; // variable to store the minute of the set alarm time
boolean alarmMode = false; // boolean to store whether an alarm is set or not

/* LIGHT */
int c_hue = 30; // variable to store hue value of color
int c_sat = 255; // variable to store saturation value of color
int c_val = 0; // variable to store brightness value of color
boolean sunriseMode = false;

/* BUTTON */
int currentButtonState = 0; // variable to store current state of button
int prevButtonState = -1; // variable to store previous state of button

/* ENCODER */
long prevPosition = 0; // variable to store old position of encoder
long currentPosition = -999; // variable to store current position of encoder
int encVal = 0; // value of encoder (0-10)
Encoder myEnc(2,3); // Encoder is connected to digital pins 2 and 3 (both of which have interrupt capability)
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

/* NON BLOCKING */
unsigned long prevMillis = 0; // variable to store last time code was updated
unsigned long currentMillis = 0; // variable to store how long the code has been running for
const long interval = 100; // variable to store interval in which code will be updated (could have more than one)

void setup() { 
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); // Initialize buttonPin as an Input
  FastLED.addLeds<WS2812B, rgbLEDMatrixPin, GRB>(rgbLEDMatrix, numPixelPerMatrix);
}

void loop() {

  currentMillis = millis();
  if(currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;
    
    // Update code
    readEnc(); // Read encoder
    readTime(); // Read current time
    readBttn();  // Read button and turn ON/OFF alarm
    if(sunriseMode) {
      sunrise();
    }
    checkAlarm(); // Check if alarm is ON and if currentTime == alarmTime
  }
}
