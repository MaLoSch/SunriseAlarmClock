void sunrise() {
  for(int ledIndex = 0; ledIndex < numPixelPerMatrix; ledIndex ++) {
    rgbLEDMatrix[ledIndex] = CHSV(c_hue,c_sat,c_val);
  }
  FastLED.show();
  c_val = c_val + 1;
}
