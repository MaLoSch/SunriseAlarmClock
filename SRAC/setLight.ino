void setLight() {
  c_val = map(encVal,0,10,0,255);
  
  for(int ledIndex = 0; ledIndex < numPixelPerLight; ledIndex ++) {
    bottomLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
    rightLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
  }
  //Serial.println(c_val); // Print LED brightness value
  FastLED.show();
}
