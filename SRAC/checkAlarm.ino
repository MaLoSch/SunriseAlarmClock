void checkAlarm() {
  if(alarmMode == true) {
    if(currentHour == alarmHour && currentMinute == alarmMinute) {
      digitalWrite(13, HIGH);
      //sunrise();
    }
  }
}
