void readBttn() {
  currentButtonState = digitalRead(buttonPin);
  if(currentButtonState != prevButtonState) {
    prevButtonState = currentButtonState;
    if(currentButtonState == 1) {
      if(encVal != 0) {
        setAlarm();
      }
    } else {
      alarmMode = false;
      //alarmOff
    }
  }
}
