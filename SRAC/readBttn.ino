void readBttn() {
  currentButtonState = digitalRead(buttonPin);
  if(currentButtonState != prevButtonState) {
    prevButtonState = currentButtonState;
    if(currentButtonState == 1) {
      if(encVal == 0) {
        Serial.println("readBttn()");
        Serial.println(currentButtonState);
        Serial.println("Whooops! Alarm time cannot be the same as current time. It's like setting an alarm for right now. Would be weird.");
      } else { 
        Serial.println("readBttn()");
        Serial.println("Setting alarm time");
        setAlarm();
      }
    } else {
      alarmMode = false;
      Serial.println("readBttn()");
      Serial.println("Alarm off");
      //alarmOff
    }
  }
}
