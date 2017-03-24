void showAlarmTime(String _number) {
  for(int ledIndex = 0; ledIndex < numPixelPerMatrix; ledIndex ++) {
    if(_number.charAt(ledIndex) == '1') {
      c_val = 255;
    } else {
      c_val = 0;
    }
    rgbLEDMatrix[ledIndex] = CHSV(c_hue,c_sat,c_val);
  }
  FastLED.show();
  c_val = 0;
}
