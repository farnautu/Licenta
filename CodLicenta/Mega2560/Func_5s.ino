void func_5s()
{
   
  if (!SD.begin(pinCS))
  {
    //Serial.println("SD card initialization failed");
  }

  myfile = SD.open("Date.txt", FILE_WRITE);
   if (myfile)
  {
    myfile.println(round(total_0x44_mW/10));
    myfile.println(total_0x44_mA/10.0);
    myfile.println(total_0x44_V/10.0);
    myfile.println(round(total_0x40_mW/10));
    myfile.println(total_0x40_mA/10.0);
    myfile.println(total_0x40_V/10.0);
    myfile.println(pressure);
    myfile.println(temperature);
    myfile.println(temp.temperature);
    myfile.println(humidity.relative_humidity);
    myfile.println();
    myfile.println();
    myfile.close();
  } else
  {
    //Serial.println("error opening the text file!");
  }
}
