int readHour() {
  if(RTC.read(tm)) {
    return tm.Hour;
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