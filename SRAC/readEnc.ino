void readEnc() {
  currentPosition = myEnc.read()/4; // read encoder, divide value by 4 and store it in currentPosition 
  //(since it is a quadrature encoder it puts out the values 1,2,3,4 on one turn but we only want it to put out the value 1)
  
  if(currentPosition != prevPosition) {
    if(currentPosition > prevPosition) {
      encVal ++;
    } else {
      encVal --;
    }
    encVal = constrain(encVal, 0, 9);
    prevPosition = currentPosition; // if prevPosition is unqual currentPosition we update prevPosition to currentPosition
    showAlarmTime(numbers[encVal]);
  }
}
