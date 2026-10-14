// Variables for the Dynamic Lock
unsigned long lockoutTime = 0;
int currentCooldown = 0; // Starts at 0 (No blindfold)

void trackSequence() {
  
  // 1. The Dynamic Lock
  if (millis() - lockoutTime > currentCooldown) {
    readJunction(); // Safe to read!
  } else {
    // We are locked out! Blind the sensors so they can't double-count.
    onJunction = false;
    junctionBuffer = 0;
  }

  // 2. Normal Junction Logic
  if (onJunction == true && isTurning == false) {
    
    isTurning = true; // Lock the counter
    junctionCount++;  // Increment the master count
    
    // --- DEFAULT RESET ---
    // Instantly reset the lock to 0 for every junction automatically
    currentCooldown = 0; 
    
    // --- COMPETITION SEQUENCE MAP ---
    if (junctionCount == 7)
      turnLeft90offset();
    else if (junctionCount == 9)
      turnLeft90offset();
    else if (junctionCount == 12)
      turnLeft90offset();
    else if (junctionCount == 13)
      turnLeft90offset();
    else if (junctionCount == 16) // right before first object
      turnLeft90offset();
    else if (junctionCount == 17){
      currentCooldown = 400; 
      lockoutTime = millis();
    }
    else if (junctionCount == 18){ 
      motor(0, 100);
      delay(50);//object 1 custom
      driveStraight();
      reverse();
      uTurn();
    }
    else if (junctionCount == 21)
      turnLeft90();
    else if (junctionCount == 22){
      turnRight90offset();
      currentCooldown = 400; 
      lockoutTime = millis();
    }
    else if (junctionCount == 23) {
      currentCooldown = 400; 
      lockoutTime = millis(); 
    }
    else if (junctionCount == 24) // exiting first t junction
      turnLeft90();
    else if (junctionCount == 26) {
     // left static, push right
      motor(0, 200); 
      delay(500);    // time required to pass the line
      huntLine(0, 120); 
      goStraight();
      turnRight90();}
    else if (junctionCount == 28)
      turnLeft90(); // there is supposed to be an object here add 2 to the 
    else if (junctionCount == 31){
  // straight
      motor(150 - adjustSpeed, 150); 
      delay(340);      
  
  // pivot turn right
      motor(150, -150); 
      delay(200);      
  
  // pivot hunt
  huntLine(100, -100); 
    }
    else if (junctionCount == 32){
      motor(100, 80);
      delay(100); 
      currentCooldown = 200; 
      lockoutTime = millis();
    }
    else if (junctionCount == 33) // first zener diode entry
      turnRight90();
    else if (junctionCount == 35) {
      huntLine(100, 0);
      currentCooldown = 200; 
      lockoutTime = millis();
    }

    else if (junctionCount == 39) {
      motor(100, 100);
      delay(100);
      huntLine(100, -100);
      currentCooldown = 200; 
      lockoutTime = millis();
    }

    else if (junctionCount == 40)
      turnLeft90offset();
    else if (junctionCount == 41)
      turnLeft90();
    else if (junctionCount == 42) // leaves the diode
      turnRight90();
    else if (junctionCount == 43){
      turnRight45();
      currentCooldown = 200; 
      lockoutTime = millis();
    }
    else if (junctionCount == 45) {//entering semicircle // ending on previous 14 with an additoin 1 because its raised up first (adding another junction)
      turnRight90offset();
      //turnRight90();
    }
    else if (junctionCount == 46){
      motor(100 - adjustSpeed, 100);
      delay(100);
      turnLeft45();
      currentCooldown = 100; 
      lockoutTime = millis(); 
    }
    else if (junctionCount == 48)
      turnRight90();
    else if (junctionCount == 50)
      stopSequence();
  }
  // 3. Reset the lock once readLine() says we left the junction
  else if (onJunction == false) {
    isTurning = false;
  }
}