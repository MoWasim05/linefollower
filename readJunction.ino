void readJunction(){

  bool crossJunction = (irValDigital[0] == 1 && irValDigital[7] == 1);
  bool leftJunction = (irValDigital[7] == 1 && irValDigital[6] == 1 && irValDigital[0] == 0);
  bool rightJunction = (irValDigital[0] == 1 && irValDigital[1] == 1 && irValDigital[7] == 0);

  // detection of junctions
  if (crossJunction || leftJunction || rightJunction) {
    junctionBuffer++; // increase confidence factor       
    
    // buffer to give sensor time (confirmation)
    if (junctionBuffer >= requiredReads) {
      onJunction = true; // is it on the junciton
      digitalWrite(ledBlue, HIGH);
    }
  } 
  // 3. The sensors lost the line (passed the junction or it was a glitch)
  else {
    junctionBuffer = 0; // Instantly reset the filter!
    
    // Only turn off the lock if the sensors completely clear the junction
    if (sensorSum < 6) { 
      offBuffer++;

      if (offBuffer >= requiredOffReads){
        onJunction = false;
        digitalWrite(ledBlue, LOW);
      }
    }
  }
}