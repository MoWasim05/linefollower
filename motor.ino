//motor control
void motor(int lPWM, int rPWM) {

  lPWM = constrain(lPWM, -255, 255);
  rPWM = constrain(rPWM, -255, 255); 

  if(lPWM > 0) {
    digitalWrite(lFwd, HIGH); 
    digitalWrite(lRev, LOW); }
  else if (lPWM < 0) {
    digitalWrite(lFwd, LOW); 
    digitalWrite(lRev, HIGH); }
  else {
    digitalWrite(lFwd, HIGH); 
    digitalWrite(lRev, HIGH); }   

  if(rPWM > 0) {
    digitalWrite(rFwd, HIGH); 
    digitalWrite(rRev, LOW); }
  else if (rPWM < 0) {
    digitalWrite(rFwd, LOW);
    digitalWrite(rRev, HIGH); }
  else {
    digitalWrite(rFwd, HIGH); 
    digitalWrite(rRev, HIGH); }

  analogWrite(PWMb, abs(lPWM));
  analogWrite(PWMa, abs(rPWM));
}