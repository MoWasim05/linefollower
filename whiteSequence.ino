void whiteSequence() {
  
  // when sensor sees nothing (white space)
  if (sensorSum == 0) {
    
    // stopwatch starts right after
    if (whiteTimer == false) {
      whiteStartTime = millis();
      whiteTimer= true;
    }

    // white space for more than pushduration (1 sec in this case)
    if (millis() - whiteStartTime >= pushDuration) {
      
      // TIMEOUT REACHED! We successfully pushed the box.
      reverse();
      uTurn();
      
      whiteTimer = false; // Reset the timer so it doesn't loop forever

      // clean slate: resets stop conditions
      onJunction = false;
      junctionBuffer = 0;
      offBuffer = 30; // Pre-load the off buffer just to be safe

      whiteStartTime = millis();
    }
  } 
}