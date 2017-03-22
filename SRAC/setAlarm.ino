void setAlarm() {
  if(RTC.read(tm)) {
//    alarmHour = tm.Hour + encVal;
//    alarmMinute = tm.Minute;
//    if(alarmHour >= 24) {
//      alarmHour = alarmHour - 24;
//    }
    alarmHour = tm.Hour;
    alarmMinute = tm.Minute + encVal;
    if(alarmMinute >= 60) {
      alarmMinute = alarmMinute - 60;
    }
    alarmMode = true;
    Serial.println("setAlarm()");
    Serial.print("Alarm mode: ");
    Serial.println(alarmMode);
    Serial.println("Alarm set to: ");
    Serial.print(alarmHour);
    Serial.print(":");
    Serial.print(alarmMinute);
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      // RTC chip is present but stopped. 'SetTime' needs to be run to initialize time.
      Serial.println("Hmmm... the DS1307 is stopped.  Please run the 'SetTime' example to initialize the time.");
      Serial.println();
    } else {
      // RTC cannot be deteced. Check circuitry.
      Serial.println("Uh-oh... Couldn't read the DS1307! Please check the circuitry.");
      Serial.println();
    }
    alarmMode = false;
  }
}
