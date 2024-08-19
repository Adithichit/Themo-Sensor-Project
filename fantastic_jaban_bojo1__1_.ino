// C++ code

int buzzer = 5; //buzzer to Arduino pin 8
void setup()
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
int sensorPin=A0;
int voltage;
void setup()
{
  pinMode(3, OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 8 as an output
  lcd.init();  
}

void loop()
{
  digitalWrite(3, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(3, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
//TMP36 Pin Variables
 //the analog pin the TMP36's Vout (sense) pin is connected to
                       //the resolution is 10 mV / degree centigrade with a
                       //500 mV offset to allow for negative temperatures
     
    /*
     * setup() - this function runs once when you turn your Arduino on
     * We initialize the serial connection with the computer
     */
  
    //Start the serial connection with the computer
                           //to view the result open the serial monitor 

     //getting the voltage reading from the temperature sensor
    int reading = analogRead(sensorPin);  
     
     // converting that reading to voltage, for 3.3v arduino use 3.3
    float voltage = reading * 5.0;
    voltage /= 1024.0; 
     
     // print out the voltage
    Serial.print(voltage); Serial.println(" volts");
     
     // now print out the temperature
    float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree with 500 mV offset
                                                   //to degrees ((voltage - 500mV) times 100)
    Serial.print(temperatureC); Serial.println(" degrees C");
     
     // now convert to Fahrenheit
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    Serial.print(temperatureF); Serial.println(" degrees F");
     
     delay(1000); //waiting a second
  	 tone(buzzer, 1000); // Send 1KHz sound signal...
	 delay(1000); // ...for 1 sec
	 noTone(buzzer); // Stop sound...
	 delay(1000); // ...for 1sec
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