void func_100ms()
{
  total_X=0;
  total_Y=0;
  total_Z=0;
  for(int i=0;i<10;i++){
    total_X=total_X+achizitii_X[i];
    total_Y=total_Y+achizitii_Y[i];
    total_Z=total_Z+achizitii_Z[i];
  }
  //=======================================================================================================INA219
  shuntvoltage_0x40 = ina219_0x40.getShuntVoltage_mV();
  busvoltage_0x40 = ina219_0x40.getBusVoltage_V();
  current_mA_0x40 = ina219_0x40.getCurrent_mA();
  power_mW_0x40 = current_mA_0x40*busvoltage_0x40;//ina219_0x40.getPower_mW();
  loadvoltage_0x40 = busvoltage_0x40 + (shuntvoltage_0x40 / 1000);
  
  shuntvoltage_0x44 = ina219_0x44.getShuntVoltage_mV();
  busvoltage_0x44 = ina219_0x44.getBusVoltage_V();
  current_mA_0x44 = ina219_0x44.getCurrent_mA();
  power_mW_0x44 = busvoltage_0x44*current_mA_0x44;//ina219_0x44.getPower_mW();
  loadvoltage_0x44 = busvoltage_0x44 + (shuntvoltage_0x44 / 1000);
  
  achizitii_0x44_mA[indexSample]=fabs(current_mA_0x44);
  achizitii_0x44_mW[indexSample]=power_mW_0x44;
  achizitii_0x44_V[indexSample] =busvoltage_0x44;
  achizitii_0x40_mA[indexSample]=fabs(current_mA_0x40);
  achizitii_0x40_mW[indexSample]=power_mW_0x40;
  achizitii_0x40_V[indexSample] =busvoltage_0x40;
  
  if(indexSample<9){
    indexSample=indexSample+1;
  }else{
    indexSample=0;
  }
  
  //======================================================================================================INA219
  //==========================================desenez un cerc pe OLED , feedback la rularea codului 
  display.fillCircle(62+cursor,60,2,WHITE);
	display.display();
  if(cursor<64){
    cursor=cursor+8;
  }else{
    cursor=0;
  }
}
