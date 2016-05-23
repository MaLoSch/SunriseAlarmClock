void readBttn() {
  currentButtonState = digitalRead(buttonPin);
  if(currentButtonState != prevButtonState) {
    prevButtonState = currentButtonState;
    Serial.println(currentButtonState);
    if(currentButtonState == 1) {
      if(encVal == 0) {
        Serial.println("Alarm cannot be set!");
      } else { 
        setAlarm();
      }
    } else {
      //alarmOff
    }
  }
}
