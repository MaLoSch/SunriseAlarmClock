void readBttn() {
  currentButtonState = digitalRead(buttonPin);
  if(currentButtonState != prevButtonState) {
    prevButtonState = currentButtonState;
    Serial.println(currentButtonState);
    if(currentButtonState == 1) {
      setAlarm();
    } else {
    }
  }
}
