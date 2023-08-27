void func_5s()
{
  pressure = bmp.readPressure();
	temperature = bmp.readTemperature();
  Serial.print(F("Pressure: "));
    Serial.print(pressure);
    Serial.print(" Pa");
    Serial.print("\t");
    Serial.print(("Temp: "));
    Serial.print(temperature);
    Serial.println();
  //=======================================================================================================INA219
  shuntvoltage_0x40 = ina219_0x40.getShuntVoltage_mV();
  busvoltage_0x40 = ina219_0x40.getBusVoltage_V();
  current_mA_0x40 = ina219_0x40.getCurrent_mA();
  power_mW_0x40 = ina219_0x40.getPower_mW();
  loadvoltage_0x40 = busvoltage_0x40 + (shuntvoltage_0x40 / 1000);
  
  Serial.print("ina219_0x40  Bus Voltage:   "); Serial.print(busvoltage_0x40); Serial.println(" V");
  Serial.print("ina219_0x40  Shunt Voltage: "); Serial.print(shuntvoltage_0x40); Serial.println(" mV");
  Serial.print("ina219_0x40  Load Voltage:  "); Serial.print(loadvoltage_0x40); Serial.println(" V");
  Serial.print("ina219_0x40  Current:       "); Serial.print(current_mA_0x40); Serial.println(" mA");
  Serial.print("ina219_0x40  Power:         "); Serial.print(power_mW_0x40); Serial.println(" mW");
  Serial.println("");
  
  
  shuntvoltage_0x44 = ina219_0x44.getShuntVoltage_mV();
  busvoltage_0x44 = ina219_0x44.getBusVoltage_V();
  current_mA_0x44 = ina219_0x44.getCurrent_mA();
  power_mW_0x44 = ina219_0x44.getPower_mW();
  loadvoltage_0x44 = busvoltage_0x44 + (shuntvoltage_0x44 / 1000);
  
  Serial.print("ina219_0x44  Bus Voltage:   "); Serial.print(busvoltage_0x44); Serial.println(" V");
  Serial.print("ina219_0x44  Shunt Voltage: "); Serial.print(shuntvoltage_0x44); Serial.println(" mV");
  Serial.print("ina219_0x44  Load Voltage:  "); Serial.print(loadvoltage_0x44); Serial.println(" V");
  Serial.print("ina219_0x44  Current:       "); Serial.print(current_mA_0x44); Serial.println(" mA");
  Serial.print("ina219_0x44  Power:         "); Serial.print(power_mW_0x44); Serial.println(" mW");
  Serial.println("");
  
  //======================================================================================================INA219
  if (SD.begin(pinCS))
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

  myfile = SD.open("textFile.txt", FILE_WRITE);
   if (myfile)
  {
    Serial.print("Writing to the text file...");
    myfile.println("Congratulations! You have successfully wrote on the text file.");
    myfile.println(a);
    myfile.close();
  } else
  {
    Serial.println("error opening the text file!");
  }
}