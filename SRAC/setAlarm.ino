void setAlarm() {
  alarmHour = readHour() + encVal;
  if(alarmHour >= 24) {
    alarmHour = alarmHour - 24;
  }
  alarmMinute = readMinute();
  Serial.println("Alarm set to: ");
  Serial.print(alarmHour);
  Serial.print(":");
  Serial.print(alarmHour);
  Serial.println();
}
