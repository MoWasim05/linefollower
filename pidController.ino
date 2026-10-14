void PIDControl(int baseSpeed, float kp, float kd){

  if (debugMode == true){
    Serial.print(sensorSum);
    Serial.print("\t");
    Serial.print(sensorWeight);
    Serial.print("\t");
    Serial.print(sensorBit);
    Serial.print("\t");
  }

  if (sensorSum > 0)
    linePosition = (float)sensorWeight / sensorSum;

  error = centerPosition - linePosition;

  derivative = error - previousError;

  //motor difference parity
  int leftBase = baseSpeed - adjustSpeed;

  int lMotor = leftBase + (error * kp + derivative * kd);
  int rMotor = baseSpeed - (error * kp + derivative * kd);

  previousError = error;

  if (debugMode == true){
    for (int i = 7; i >= 0; i--)
      Serial.print(irValDigital[i]);

    Serial.print("\t");
    Serial.print("Weight: " + String(sensorWeight));
    Serial.print("\t");
    Serial.print("Error : " + String(error));
    Serial.println(); // Added println to create a clean new line without the motor speeds
  }

  motor(lMotor, rMotor); 
}