void sunrise() {
  for(int ledIndex = 0; ledIndex < numPixelPerMatrix; ledIndex ++) {
    rgbLEDMatrix[ledIndex] = CHSV(c_hue,c_sat,c_val);
  }
  FastLED.show();
  if(c_val <= 255) {
    c_val = c_val + 1;
  }
}
