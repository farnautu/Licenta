void func_10ms()
{
  sensors_event_t event; 
  accel.getEvent(&event);
  X_out = event.acceleration.x;
  Y_out = event.acceleration.y;
  Z_out = event.acceleration.z;

  achizitii_X[indexSample_ADXL]=X_out;
  achizitii_Y[indexSample_ADXL]=Y_out;
  achizitii_Z[indexSample_ADXL]=Z_out;

  if(pozFinala){
    

    if(X_out-2.0>total_X/10.0 || X_out+2.0<total_X/10.0 ||
     Y_out-2.0>total_Y/10.0 || Y_out+2.0<total_Y/10.0  ||
     Z_out-2.0>total_Z/10.0 || Z_out+2.0<total_Z/10.0)
     {
      impactDetectat=true;
     }
  }
  if(indexSample_ADXL<9){
    indexSample_ADXL=indexSample_ADXL+1;
  }else{
    indexSample_ADXL=0;
  }

  if(impactDetectat){
      digitalWrite(motor1Ren,HIGH);
      analogWrite(motor1R_PWM,0);
      digitalWrite(motor1Len,HIGH);
      analogWrite(motor1L_PWM,225);
  }
}
