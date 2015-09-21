#include <LCD_nokia8310.h>

NokiaLCD lcd(3,4,5,6); //84 x 48

void setup() {
  lcd.Init(); //initialization screen
}

void loop() {
  lcd.Clear(); //clear screen
  for(int x = 0; x < 84; x++){
    
    lcd.Print(x, 10); //print pixels in memory of screen
  }
  lcd.Update();	//update screen
  delay(1000);
}
