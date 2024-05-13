/*
Demonstration sketch for PCF8574T I2C LCD Backpack
http://tronixlabs.com/display/lcd/serial-i2c-backpack-for-hd44780-compatible-lcd-modules/
Uses library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
GNU General Public License, version 3 (GPL-3.0)

If you have the PCF8574T the default I2C bus address is 0x27. 
If you have the PCF8574AT the default I2C bus address is 0x3F
*/



#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7); // 

const int ServoA = 9;

// variables will change:
const byte interruptPin = 2; //tilt button connection
byte tiltState=1;

const int clockwise = 1700;
const int counterclockwise = 1300;
const int ButtonA = 8;
const int ledPin =  13; 
int servoSpeed = 0;
void setup()
{
  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);



 pinMode(interruptPin, INPUT_PULLUP);
 pinMode(ButtonA, INPUT_PULLUP); 
 pinMode(ledPin, OUTPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(interruptPin), tiltActive, CHANGE);
  
}

   
void tiltActive() { // Interrupt Service Routine (ISR)
  if (digitalRead (interruptPin) == HIGH)
    digitalWrite (ledPin, HIGH);
  else
    digitalWrite (ledPin, LOW);
}  // end of switchPressed

void loop(){ 
  lcd.clear(); lcd.home (); // set cursor to 0,0
  lcd.print("RetroBuiltGames.com"); 
   if ((digitalRead(ButtonA) == LOW)){ rotate();}
  delay(1000);
  scroll();

  lcd.setCursor (0,1);        // go to start of 2nd line
  //lcd.print(millis());
  //delay(1000);
  /*lcd.setBacklight(LOW);      // Backlight off
  delay(250);
  lcd.setBacklight(HIGH);     // Backlight on
  delay(1000);*/

  if (tiltState == LOW){
  lcd.home(); lcd.clear();
  for (int blinks = 0; blinks <= 4; blinks ++)
  { lcd.setBacklight(LOW); delay(50); lcd.setBacklight(HIGH); delay(50);}
  lcd.print("No Touching!");
  delay(1000);
  tiltState = HIGH;
  }
}


void scroll(){
  for (int positionCounter = 0; positionCounter < 3; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();  
    delay(250);                                                     }
delay(2000);   
  
 for (int positionCounter = 0; positionCounter < 3; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    delay(250);   // wait a bit                                                         
}}


void rotate(){  
  lcd.home(); lcd.clear();
  lcd.print("Rotating"); lcd.setCursor(0,1);
  lcd.print("speed=");
    for(int i=0; i<57; i++) { // change this to adjust +- full revolution
     digitalWrite(ServoA,HIGH);
     delayMicroseconds(clockwise); 
     digitalWrite(ServoA,LOW);
     delay(18.5); // 18.5ms 
     //delay(50); enable this line to slow servo rotation
    }

}

                                                                 
