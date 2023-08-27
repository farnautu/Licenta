void func_1s()
{
  a=a+1;
  display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0 ,0  );display.print("MCU_0x44:");
  display.setCursor(0 ,8  );display.print(round(power_mW_0x44));
  display.setCursor(40,8  );display.print("mW");
  display.setCursor(0 ,16 );display.print(round(current_mA_0x44*-1));
  display.setCursor(40,16 );display.print("mA");
  display.setCursor(0 ,24 );display.print(busvoltage_0x44);
  display.setCursor(40,24 );display.print("V");

	display.setCursor(0 ,32 );display.print("X.Y_0x40:");
  display.setCursor(0 ,40 );display.print(round(power_mW_0x40));
  display.setCursor(40,40 );display.print("mW");
  display.setCursor(0 ,48 );display.print(round(current_mA_0x40*-1));
  display.setCursor(40,48 );display.print("mA");
  display.setCursor(0 ,56 );display.print(busvoltage_0x40);
  display.setCursor(40,56 );display.print("V");
	display.display();
  //la dimensiunea 1 , caracterele au 5x8 pixeli // NU STERGE!!!!!!!!!!!!!!!!!
  //spatiu liber la de la (50,0)...,(64,0) e jumatatea 
}

