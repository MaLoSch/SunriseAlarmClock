void setAlarm() {
  alarmHour = readHour() + encVal;
  if(alarmHour >= 24) {
    alarmHour = alarmHour - 24;
  }
  alarmMinute = readMinute();
  alarmMode = true;
  Serial.println("setAlarm()");
  Serial.print("Alarm mode: ");
  Serial.println(alarmMode);
  Serial.println("Alarm set to: ");
  Serial.print(alarmHour);
  Serial.print(":");
  Serial.print(alarmMinute);
  Serial.println();
}
