#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
int sensorPin=A0;
int voltage;
void setup()
{
  lcd.init();                      // initialize the lcd 
  
}


void loop()
{
  voltage= analogRead(sensorPin);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Voltage=");
  lcd.setCursor(0,1);
  lcd.print(voltage);
  delay(1000);
  lcd.clear();
   
}
