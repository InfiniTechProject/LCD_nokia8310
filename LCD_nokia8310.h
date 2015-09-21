/*
  LCD_nokia8310.h - Library for Nokia 8310 LCD.
  Created by Alextrim/Alextrimux(Aleksei) , July 27 2015.
*/
#ifndef LCD_nokia8310_h
#define LCD_nokia8310_h

#include <Arduino.h>

#define LCD_X_RES 84 //Resolution X
#define LCD_Y_RES 48 //Resolution Y
#define LCD_CACHE_SIZE ((LCD_X_RES * LCD_Y_RES) / 8)
#define LCD_CMD 0
#define LCD_DATA 1
 
class NokiaLCD
{
  public:
    NokiaLCD(int XRES_pin, int XCS_pin, int SDA_pin, int SCLK_pin);
    void Init();
    void Cmd(byte data, int mode);
	void Update();
	void Clear();
	void Print(int x, int y);
  private:
    int XRES;
	int XCS;
	int SDA;
	int SCLK;
	byte LcdCache[LCD_CACHE_SIZE];
	void Lcd_Clear();
};
 
#endif
