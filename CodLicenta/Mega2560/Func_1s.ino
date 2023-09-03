void func_1s()
{
  pressure = bmp.readPressure();
	temperature = bmp.readTemperature()-1.0;
  aht.getEvent(&humidity, &temp);

  total_0x40_mA=0;
  total_0x40_mW=0;
  total_0x40_V =0;
  total_0x44_mA=0;
  total_0x44_mW=0;
  total_0x44_V =0;
  for(int i=0;i<10;i++){
    total_0x40_mA=total_0x40_mA+achizitii_0x40_mA[i];
    
    total_0x40_mW=total_0x40_mW+achizitii_0x40_mW[i];
    total_0x40_V =total_0x40_V+achizitii_0x40_V[i];
    total_0x44_mA=total_0x44_mA+achizitii_0x44_mA[i];
    total_0x44_mW=total_0x44_mW+achizitii_0x44_mW[i];
    total_0x44_V =total_0x44_V+achizitii_0x44_V[i];
  }
  //Serial.println(total_0x40_mA);
  
  if(digitalRead(pinSelectOLED) == HIGH){//====================================================  afisare date INA,ATH,BMP
   

    display.clearDisplay();
	  display.setTextSize(1);
	  display.setCursor(0  ,0  );display.print("MCU_0x44:");
    display.setCursor(0  ,8  );display.print(round(total_0x44_mW/10));
    display.setCursor(40 ,8  );display.print("mW");
    display.setCursor(0  ,16 );display.print(total_0x44_mA/10.0);
    display.setCursor(40 ,16 );display.print("mA");
    display.setCursor(0  ,24 );display.print(total_0x44_V/10.0);
    display.setCursor(40 ,24 );display.print("V");
  
	  display.setCursor(0  ,32 );display.print("X.Y_0x40:");
    display.setCursor(0  ,40 );display.print(round(total_0x40_mW/10));
    display.setCursor(40 ,40 );display.print("mW");
    display.setCursor(0  ,48 );display.print(total_0x40_mA/10.0);
    display.setCursor(40 ,48 );display.print("mA");
    display.setCursor(0  ,56 );display.print(total_0x40_V/10.0);
    display.setCursor(40 ,56 );display.print("V");

    display.setCursor(60 ,0 );display.print("Presiune:");
    display.setCursor(60 ,8 );display.print(pressure);
    display.setCursor(115,8 );display.print("Pa");

    display.setCursor(60 ,16 );display.print("Temp:");
    display.setCursor(60 ,24 );display.print("T1:");
    display.setCursor(80 ,24 );display.print(temperature);
    display.setCursor(118,24 );display.print("C");
    display.setCursor(60 ,32 );display.print("T2:");
    display.setCursor(80 ,32);display.print(temp.temperature);
    display.setCursor(118,32);display.print("C");

    display.setCursor(60 ,40 );display.print("Umiditate:");
    display.setCursor(60 ,48 );display.print(humidity.relative_humidity);
    display.setCursor(118,48 );display.print("%");

	  display.display();
  }else{//=====================================================================================afisare date ADXL ADC (pozitie panou)
  

    display.clearDisplay();
	  display.setTextSize(1);
	  display.setCursor(60 ,8  );display.print("Tracking:");
    display.setCursor(60 ,16 );display.print("P1:");
    display.setCursor(80 ,16 );display.print(punct1);
    display.setCursor(60 ,24 );display.print("P2:");
    display.setCursor(80 ,24 );display.print(punct2);
    display.setCursor(60 ,32 );display.print("P3:");
    display.setCursor(80 ,32);display.print(punct3);
    display.setCursor(60 ,40 );display.print("P4:");
    display.setCursor(80 ,40 );display.print(punct4);

	  display.display();
  }

  cursor=0;

  //la dimensiunea 1 , caracterele au 5x8 pixeli // NU STERGE!!!!!!!!!!!!!!!!!
}
