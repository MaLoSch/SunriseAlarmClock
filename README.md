# SunriseAlarmClock
Files to build and code the DIY Sunrise Alarm Clock

ToDo's
- BUG: Alarm can be set even though RTC is not available or needs to be initialized
	- To view bug in console set encVal != 0 and press button when RTC is not available or needs to be initialized
- Clean up code
	- remove unnecessary variables
	- tighten up code
- Set alarm time
	- Turn on light on alarm
- Simulate sunrise
- Display current time and alarm time with LED ring
- Feedback when alarm is set through button LED ring lighting up
- Check battery in RTC module
- ...

Components
- Arduino UNO R3 - https://www.adafruit.com/products/50
- Solid Machine Metal Knob -  https://www.adafruit.com/products/2056
- Rugged Metal ON/OFF Switch with white LED ring - https://www.adafruit.com/products/917
- 2x Adafruit NeoPixel NeoMatrix 8x8 - https://www.adafruit.com/products/1487
- Half-sized Breadboard - https://www.adafruit.com/product/64

Wishlist
- Add sound capability
	- https://www.adafruit.com/products/94
	- https://www.adafruit.com/products/1788
	- https://www.adafruit.com/products/1790
	- https://www.adafruit.com/products/175
- Add Ethernet capability
	- https://www.adafruit.com/products/418
