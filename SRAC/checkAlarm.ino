void checkAlarm() {
  if(alarmMode == true && sunriseMode == false) {
    if(currentHour == alarmHour && currentMinute == alarmMinute) {
      digitalWrite(13, HIGH);
      sunriseMode = true;
      c_val = 0;
    }
  }
}
