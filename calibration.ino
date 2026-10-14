void calibration(){
  readLine();
  for (int i = 7; i >= 0; i--){
    Serial.print(irValues[i]);
    Serial.print("\t");
  }
  for (int i = 7; i >= 0; i--){
    Serial.print(irValDigital[i]);
  }
    Serial.print("\t");
    Serial.print(sensorSum);
    Serial.print("\t");
    Serial.print(sensorWeight);
    Serial.print("\t");
    Serial.print(sensorBit);
    Serial.println();
}