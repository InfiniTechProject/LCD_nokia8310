#include <LCD_nokia8310.h>
/*	3 - XRES_pin
	4 - XCS_pin
	5 - SDA_pin
	6 - SCLK_pin */
NokiaLCD lcd(3,4,5,6); //84 x 48

void setup() {
  lcd.Init(); //initialization screen
}

void loop() {
  lcd.Clear(); //clear screen
  for(int x = 0; x < 84; x++)
  {
    lcd.Print(x, sin((x/pi)*0.3)+24);
  }
  lcd.Update();	//update screen
  delay(1000);
}
