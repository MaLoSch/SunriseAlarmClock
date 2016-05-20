void readTime() {
  if(RTC.read(tm)) {
    //store time in variable
    currentHour = tm.Hour;
    currentMinute = tm.Minute;
    Serial.print("Current time: ");
    Serial.print(currentHour);
    Serial.print(":");
    Serial.print(currentMinute);
    Serial.println();
    alarmHour = currentHour + encVal;
    if(alarmHour >= 24) {
      alarmHour = alarmHour - 24;
    }
    alarmMinute = currentMinute;
    Serial.print("Alarm time: ");
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
  }
}
