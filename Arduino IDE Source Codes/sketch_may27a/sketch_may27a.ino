#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16x2 display
void setup ()
{
  lcd.init();
  lcd.backlight(); 
  
}
void loop ()
{ 
  lcd.print("Hello World!");
}

