void setLight(int localEncVal) {
  c_val = map(localEncVal,0,10,0,255);
  //c_val = pow(2,((localEncVal+2)/pEncLight)) - 1; // For more information on this equation visit https://diarmuid.ie/blog/pwm-exponential-led-fading-on-arduino-or-other-platforms/
  
  for(int ledIndex = 0; ledIndex < numPixelPerLight; ledIndex ++) {
    firstLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
    secondLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
    thirdLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
    fourthLight[ledIndex] = CHSV(c_hue,c_sat,c_val);
  }
  FastLED.show();

  // Console
  Serial.println("setLight()");
  Serial.print("c_val: ");
  Serial.println(c_val);
}
