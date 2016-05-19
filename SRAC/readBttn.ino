void readBttn() {
  currentButtonState = digitalRead(buttonPin);
  if(currentButtonState != prevButtonState) {
    prevButtonState = currentButtonState;
    Serial.println(currentButtonState);
  }
}
