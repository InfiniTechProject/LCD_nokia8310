/*
	LCD_nokia8310.cpp - Library for Nokia 8310 LCD.
	Created by Alextrim/Alextrimux(Aleksei) , July 27 2015.
*/
 
#include <Arduino.h>
#include <LCD_nokia8310.h>

const byte AddCache[8] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000};
 
NokiaLCD::NokiaLCD(int XRES_pin, int XCS_pin, int SDA_pin, int SCLK_pin)
{
	pinMode(XRES_pin,OUTPUT);
	pinMode(XCS_pin ,OUTPUT);
	pinMode(SDA_pin ,OUTPUT);
	pinMode(SCLK_pin,OUTPUT);
	XRES = XRES_pin;
	XCS = XCS_pin;
	SDA = SDA_pin;
	SCLK = SCLK_pin;
}
 
void NokiaLCD::Init()
{
	digitalWrite(XRES,LOW);
	delay(40);
	digitalWrite(XRES,HIGH);
	
	Cmd( B00100100, LCD_CMD ); // 0010 0100 write VOP register ... contrast
	Cmd( B10010000, LCD_CMD ); // 1001 0000
	Cmd( B10100100, LCD_CMD ); // 1010 0100 all on/normal display
	Cmd( B00101111, LCD_CMD ); // 0010 1111 Power control set(charge pump on/off)
	Cmd( B01000000, LCD_CMD ); // 0100 0000 set start row address = 0
	Cmd( B10110000, LCD_CMD ); // 1011 0000 set Y-address = 0
	Cmd( B00010000, LCD_CMD ); // 0001 0000 set X-address, upper 3 bits =0
	Cmd( B00000000, LCD_CMD ); // 0000 0000 set X-address, lower 4 bits =0
	Cmd( B11001000, LCD_CMD ); // 1100 1000 mirror Y axis (about X axis)
	//Cmd( B10100001, LCD_CMD ); // 1010 0001 Invert screen in horizontal axis
	Cmd( B10101100, LCD_CMD ); // 1010 1100 set initial row (R0) of the display
	Cmd( B00000111, LCD_CMD ); // 0000 0111
	Cmd( B10101111, LCD_CMD ); // 1010 1111 display ON/OFF
	
	Lcd_Clear(); // clear LCD
	Cmd( B10100111, LCD_CMD ); // 1010 0111 Toggle display to normal to reverse and return at the end of initialisation
	delay(200);
	Cmd( B10100110, LCD_CMD ); // 1010 0110
	delay(200); 
}
 
void NokiaLCD::Cmd(byte data, int mode)
{
	digitalWrite(XCS, LOW);
	
	int i = 8;
	byte mask;
	
	digitalWrite(SCLK,LOW); // tick
	delayMicroseconds(1);
	if (mode == 1)
	{
		digitalWrite(SDA,HIGH);
	}else{
		digitalWrite(SDA,LOW) ;
	}
	digitalWrite(SCLK,HIGH); // tock
	delayMicroseconds(1);
	
	while(0 < i){
		mask = 0x01 << --i;
		digitalWrite(SCLK,LOW); // tick
		delayMicroseconds(1);
		
		if(data & mask){
			digitalWrite(SDA,HIGH);
		}else{
			digitalWrite(SDA,LOW);
		}
		digitalWrite(SCLK,HIGH); // tock
		delayMicroseconds(1);
	}
	digitalWrite(XCS, HIGH);
}
void NokiaLCD::Update()
{
  for (int i = 0; i < LCD_CACHE_SIZE; i++)
  {
    Cmd( LcdCache[i], LCD_DATA );
  }
}
void NokiaLCD::Lcd_Clear(void){
  unsigned int i;
  Cmd( B01000000, LCD_CMD ); // Y = 0
  Cmd( B10110000, LCD_CMD );
  Cmd( B00010000, LCD_CMD ); // X = 0
  Cmd( B00000000, LCD_CMD );
  Cmd( B10101110, LCD_CMD ); // disable display;
  
  for(i=0;i<LCD_CACHE_SIZE;i++){
    Cmd( B00000000, LCD_DATA );
  }
  Cmd( B10101111, LCD_CMD ); // enable display;
}
void NokiaLCD::Clear (void){
  int i;
  
  for ( i = 0; i < LCD_CACHE_SIZE; i++ )
  {
    LcdCache[i] = 0x00;
  }
  Cmd( B01000000, LCD_CMD ); // Y = 0
  Cmd( B10110000, LCD_CMD );
  Cmd( B00010000, LCD_CMD ); // X = 0
  Cmd( B00000000, LCD_CMD );
}
void NokiaLCD::Print(int x, int y)
{
  int p = ((y/8) * 84)+x;
  int u = y%8;
  
  LcdCache[p] = LcdCache[p] | AddCache[u];
}
