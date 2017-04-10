void showAlarmTime(int _encVal) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      //int bitValue = bitRead(numbers[_encVal][i],j);
      if(bitRead(minutes[_encVal][i],j) == 1) {
        c_val = 50;
      } else {
        c_val = 0;
      }
      rgbLEDMatrix[(i*8)+(7-j)] = CHSV(c_hue,c_sat,c_val);
    }
  }
  FastLED.show();
  c_val = 0;
}
