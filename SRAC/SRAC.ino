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

void setup() { 
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); // Initialize buttonPin as an Input
  FastLED.addLeds<WS2812B, lowerLight_Pin, GRB>(bottomLight, numPixelPerLight);
  FastLED.addLeds<WS2812B, rightLight_Pin, GRB>(rightLight, numPixelPerLight);
}

void loop() {
  readEnc(); // read encoder
  //readBttn(); // read button
  readTime(); // read current time
}

void readEnc() {
  currentPosition = myEnc.read()/4; // read encoder, divide value by 4 and store it in currentPosition 
  //(since it is a quadrature encoder it puts out the values 1,2,3,4 on one turn but we only want it to put out the value 1)
  if(currentPosition != prevPosition) {
    if(currentPosition > prevPosition) {
      encVal ++;
    } else {
      encVal --;
    }
    encVal = constrain(encVal, 0, 10);
    prevPosition = currentPosition; // if prevPosition is unqual currentPosition we update prevPosition to currentPosition
    setLight();
  }
}

void readBttn() {
  currentButtonState = digitalRead(buttonPin);
  if(currentButtonState != prevButtonState) {
    prevButtonState = currentButtonState;
    Serial.println(currentButtonState);
  }
}

void setLight() {

  c_val = map(encVal,0,10,0,255);
  
  for(int ledIndex = 0; ledIndex < numPixelPerLight; ledIndex ++) {
    bottomLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
    rightLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
  }
  Serial.println(c_val);
  FastLED.show();
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
