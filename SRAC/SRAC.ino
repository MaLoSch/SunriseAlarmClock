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

/* CONSTANT VARIABLES */
const int lowerLight_Pin = 5; // Pin # for lower light
const int rightLight_Pin = 6; // Pin # for lower light
const int numPixelPerLight = 12; // # of pixels per LED strip

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

void setup() {
  FastLED.addLeds<WS2812B, lowerLight_Pin, GRB>(bottomLight, numPixelPerLight);
  FastLED.addLeds<WS2812B, rightLight_Pin, GRB>(rightLight, numPixelPerLight);
}

void loop() {
  readTime();
  // Move a single white led 
   for(uint8_t hue = 0; hue < 255 ; hue = hue + 1) {
      // Turn our current led on to white, then show the leds
      for(int ledIndex = 0; ledIndex < numPixelPerLight; ledIndex ++) {
        bottomLight[ledIndex] = CHSV(hue,255,255);
        rightLight[ledIndex] = CHSV(hue-128,255,255);
      }

      FastLED.show();

      // Wait a little bit
      delay(100);
   }
}

void readTime() {
  if(RTC.read(tm)) {
    // RTC is running.
  } else {
    if (RTC.chipPresent()) {
      // RTC chip is present but stopped. 'SetTime' needs to be run to initialize time.
    } else {
      // RTC cannot be deteced. Check circuitry.
    }
  }
}
