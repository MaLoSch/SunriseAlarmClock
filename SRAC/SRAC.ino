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

/* ENCODER */
long prevPosition = -999; // variable to store old position of encoder
long currentPosition; // variable to store current position of encoder
Encoder myEnc(2,3); // Encoder is connected to digital pins 2 and 3 (both of which have interrupt capability)
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

void setup() { 
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, lowerLight_Pin, GRB>(bottomLight, numPixelPerLight);
  FastLED.addLeds<WS2812B, rightLight_Pin, GRB>(rightLight, numPixelPerLight);
}

void loop() {
  readEnc(); // read encoder
  //readTime(); // read current time
   //for(uint8_t hue = 0; hue < 255 ; hue = hue + 1) {
      //for(int ledIndex = 0; ledIndex < numPixelPerLight; ledIndex ++) {
        //bottomLight[ledIndex] = CHSV(hue,255,255);
        //rightLight[ledIndex] = CHSV(hue-128,255,255);
      //}
      //FastLED.show();
}

void readEnc() {
  currentPosition = myEnc.read()/4; // read encoder, divide value by 4 and store it in currentPosition 
  //(since it is a quadrature encoder it puts out the values 1,2,3,4 on one turn but we only want it to put out the value 1)
  if(currentPosition != prevPosition) {
    prevPosition = currentPosition; // if prevPosition is unqual currentPosition we update prevPosition to currentPosition
    Serial.println(currentPosition); // print currentPosition
  }
}

void readTime() {
  if(RTC.read(tm)) {
    //store time in variable
    currentHour = tm.Hour;
    currentMinute = tm.Minute;
    Serial.print(currentHour);
    Serial.print(":");
    Serial.print(currentMinute);
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      // RTC chip is present but stopped. 'SetTime' needs to be run to initialize time.
      Serial.println("Hmmm... the DS1307 is stopped.  Please run the 'SetTime' example to initialize the time.");
      Serial.println();
    } else {
      // RTC cannot be deteced. Check circuitry.
      Serial.println("Uh-oh... Couldn't read the DS1307! Please check the circuitry.");
      Serial.println();
    }
  }
}
