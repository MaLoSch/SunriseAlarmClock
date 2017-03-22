void readTime() {
  if(RTC.read(tm)) {
    currentHour = tm.Hour;
    currentMinute = tm.Minute;
  }
}
