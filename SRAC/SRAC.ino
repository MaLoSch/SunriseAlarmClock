/*
 * Arduino code for Sunrise Alarm Clock
 * Last updated 2016-05-15
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
const int firstLight_Pin = 5; // Pin # for lower light
const int secondLight_Pin = 6; // Pin # for lower light
const int thirdLight_Pin = 9; // Pin # for lower light
const int fourthLight_Pin = 10; // Pin # for lower light
const int numPixelPerLight = 12; // # of pixels per LED strip
const int buttonPin = 12;

/* NEOPIXEL */
CRGB firstLight[numPixelPerLight]; // 1st LED strip
CRGB secondLight[numPixelPerLight]; // 2nd LED strip
CRGB thirdLight[numPixelPerLight]; // 3rd LED strip
CRGB fourthLight[numPixelPerLight]; // 4th LED strip

/* TIME */
tmElements_t tm; // Initiate a tmElements_t object called tm that can access the current time
int currentHour;
int currentMinute;

/* ALARM */
int alarmHour = 19;
int alarmMinute = 31;
boolean alarmMode = false;

/* LIGHT */
int c_hue = 0;
int c_sat = 0;
int c_val = 0;
float pSunriseLight; // variable to store value in graph equation to calculate perceived light brightness when simulating sunrise
float pEncLight; // variable to store value in graph equation to calculate perceived light brightness when using encoder
const int lightSunriseIntervals = 100;
const int lightEncIntervals = 10;

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
  FastLED.addLeds<WS2812B, firstLight_Pin, GRB>(firstLight, numPixelPerLight);
  FastLED.addLeds<WS2812B, secondLight_Pin, GRB>(secondLight, numPixelPerLight);
  FastLED.addLeds<WS2812B, thirdLight_Pin, GRB>(thirdLight, numPixelPerLight);
  FastLED.addLeds<WS2812B, fourthLight_Pin, GRB>(fourthLight, numPixelPerLight);

  pSunriseLight = ((lightSunriseIntervals+2) * log10(2))/(log10(255)); // calculate pSunriseLight
  pEncLight = ((lightEncIntervals+2) * log10(2))/(log10(255)); // calculate pEncLight
}

void loop() {

  currentMillis = millis();
  if(currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;
    
    // Update code
    readEnc(); // Read encoder and set light accordingly. Also read current time
    setLight(encVal); // Set lights according to encVal
    readBttn();  // Read button and turn ON/OFF alarm
    checkAlarm(); // Check if alarm is ON and if currentTime == alarmTime
    Serial.println("");
    Serial.println("---------------------------------------");
    Serial.println("");
  }
}
