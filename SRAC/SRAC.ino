/*
 * Arduino code for Sunrise Alarm Clock
 * Last updated 2016-05-15
 * 
 * Code by Markus Lorenz Schilling
 * http://malosch.com/
 * 
 * GitHub
 * https://github.com/malosch
*/
 
/* LIBRARIES */
#include "FastLED.h" // Include FastLED library http://fastled.io/
#include <Wire.h> // Allows devices to communicate with the Two Wire Interface Bus
#include <Time.h> // Include time library
#include <DS1307RTC.h> // Include DS1307 RTC library for the tiny RTC module
#include <Encoder.h> // Include the encoder library to easily read the rotary encoder

/* CONSTANT VARIABLES */
const int lowerLight_Pin = 5; // Pin # for lower light
const int rightLight_Pin = 6; // Pin # for lower light
const int numPixelPerLight = 12; // # of pixels per LED strip
const int buttonPin = 12;

/* NEOPIXEL */
CRGB bottomLight[numPixelPerLight]; // Bottom LED strip
CRGB rightLight[numPixelPerLight]; // Right LED strip
// CRGB bottomLight[numPixelPerLight]; // Array of LED
// CRGB bottomLight[numPixelPerLight]; // Array of LED

/* TIME */
tmElements_t tm; // Initiate a tmElements_t object called tm that can access the current time
int currentHour;
int currentMinute;
int alarmHour;
int alarmMinute;

/* LIGHT */
int c_hue = 0;
int c_sat = 0;
int c_val = 0;

/* BUTTON */
int currentButtonState = 0; // variable to store current state of pushbutton
int prevButtonState = -1; // variable to store previous state of pushbutton

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
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); // Initialize buttonPin as an Input
  FastLED.addLeds<WS2812B, lowerLight_Pin, GRB>(bottomLight, numPixelPerLight);
  FastLED.addLeds<WS2812B, rightLight_Pin, GRB>(rightLight, numPixelPerLight);
}

void loop() {

  currentMillis = millis();
  if(currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;
    
    // Update code
    readEnc(); // read encoder
    //readBttn(); // read button
    readTime(); // read current time
  }
}
