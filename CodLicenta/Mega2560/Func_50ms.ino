void func_50ms()
{
  punct1=analogRead(adc1);
  punct2=analogRead(adc2);
  punct3=analogRead(adc3);
  punct4=analogRead(adc4);
  punct5=analogRead(adc5);

  //control M2
  if(punct4<700){
    digitalWrite(motor2Ren,HIGH);
    analogWrite(motor2R_PWM,255);
    digitalWrite(motor2Len,HIGH);
    analogWrite(motor2L_PWM,0);
  }else if (punct3<500) {
    digitalWrite(motor2Ren,HIGH);
    analogWrite(motor2R_PWM,0);
    digitalWrite(motor2Len,HIGH);
    analogWrite(motor2L_PWM,225);
    }else{
    digitalWrite(motor2Ren,HIGH);
    analogWrite(motor2R_PWM,0);
    digitalWrite(motor2Len,HIGH);
    analogWrite(motor2L_PWM,0);
  }
    
  //========================

  /*
  if(digitalRead(pinSelectOLED) == HIGH){
    digitalWrite(motor2Ren,HIGH);
    analogWrite(motor2R_PWM,0);
    digitalWrite(motor2Len,HIGH);
    analogWrite(motor2L_PWM,225);

    digitalWrite(motor1Ren,HIGH);
    analogWrite(motor1R_PWM,0);
    digitalWrite(motor1Len,HIGH);
    analogWrite(motor1L_PWM,225);
  }else{
    digitalWrite(motor2Len,HIGH);
    analogWrite(motor2L_PWM,0);
    digitalWrite(motor2Ren,HIGH);
    analogWrite(motor2R_PWM,225);

    digitalWrite(motor1Len,HIGH);
    analogWrite(motor1L_PWM,0);
    digitalWrite(motor1Ren,HIGH);
    analogWrite(motor1R_PWM,225);
  }
  */

}
