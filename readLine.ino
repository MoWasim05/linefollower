// black line reader
void readLine(){
  sensorSum = 0;
  sensorWeight = 0;
  sensorBit = 0;

  for(int i = 0; i < 8; i++){
    irValues[i] = analogRead(irPins[i]);
    
    //analog to digital
    if(irValues[i] > threshold)
      irValDigital[i] = 1;
    else
      irValDigital[i] = 0;
    
    sensorSum += irValDigital[i];
    sensorWeight += irValDigital[i] * weightVal[i];
    sensorBit += irValDigital[i] * bitWeight[i];
  }
}

/*not used currently 
void sideCalibration(){
  readLine();

  for (int i = 7; i >= 0; i--)
    Serial.print(irValDigital[i]);
    
  Serial.print("\t");
  if (sensorBit == 0b10000000)
    Serial.print("Side: Left");
  else if (sensorBit == 0b00000001)
    Serial.print("Side: Right");
  else
    Serial.print("Side: Null");

  Serial.println();
}*/