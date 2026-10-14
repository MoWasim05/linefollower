// relocate line
void huntLine(int huntLeftSpeed, int huntRightSpeed) {
  while (true) {
    readLine();
    
    // center sensors find a new line
    if (irValDigital[3] == 1 || irValDigital[4] == 1) {
      motor(0, 0); // hunt complete
      break;       // loop exit
    }
    
    // Slower hunting speed passed from the turn function
    motor(huntLeftSpeed, huntRightSpeed); 
  }
}

// =========================================
// -------- all junction conditions --------
// =========================================

void turnLeft45() {
  // 1. left static, push right
  motor(0, 200); 
  delay(150);    // half of 90 degree turn
  
  // pivot hunt left static
  huntLine(0, 120); 
}

void turnRight45() {
  // push left, right static
  motor(200, 0); 
  delay(150);    
  
  // pivot hunt right static
  huntLine(120, 0); 
}

void turnLeft90() {
  // left static, push right
  motor(0, 200); 
  delay(300);    // time required to pass the line
  
  // pivot hunt left static
  huntLine(0, 120); 
}

void leftPivot() {
  motor(-200, 200);
  delay(200);

    // pivot hunt left static
  huntLine(0, 120); 
}

void turnRight90() {
  // push left, right static
  motor(200, 0); 
  delay(300);    // time required to pass the line
  
  // pivot hunt right static
  huntLine(120, 0); 
}

void rightPivot() {
  motor (200, -200);
  delay (200);

    // pivot hunt right static
  huntLine(120, 0); 
}

void driveStraight() {
  // cross the junction by going straight
  motor(150 - adjustSpeed, 150); 
  delay(150); // time taken for sensor to clear the line
}

void reverse() {
  // reverse
  motor(-150, -150);
  delay(500);        // how long it reverses initially 
}

void uTurn() {
  // 180 spin
  motor(150, -150); // spin right
  delay(200);       // TUNE: longer than 90 degree, but less than 180
  
  // slower 180 spin
  huntLine(100, -100); // continue spinning to find line
}

// for sharper turns
void turnLeft90offset() {
  // straight
  motor(150, 150); 
  delay(400);      // how far forwards it goes
  
  // pivot turn left
  motor(-150, 150); 
  delay(200);
  
  // pivot hunt
  huntLine(-100, 100); 
}

void turnRight90offset() {
  // straight
  motor(150, 150); 
  delay(400);      
  
  // pivot turn right
  motor(150, -150); 
  delay(200);      
  
  // pivot hunt
  huntLine(100, -100); 
}

void ignoreJunction() {
  // use to skip a junction
}

void goStraight() {
  motor(200 - adjustSpeed, 200);
  delay(200);
}

// END OF CIRCUIT
void stopSequence() {
  motor (150, 150);
  delay(700);

  while(true){
    motor(0, 0);
  }
}