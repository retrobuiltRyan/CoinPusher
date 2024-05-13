/*Coin Pusher V0_2 by Ryan Bates (c) 2016 Retro Built Games
Features: Tilt sensor, Tilt LED, speed adjustment for stepper. 
Basic operation to drive a UNIPOLAR stepper motor with a button and a ULN2803 (8 arrary darlington stepper)
Code will also work with four TIP120 darlington transistors. If using a Arduino Motor Sheild you'll have to modify this code. 

*/
const int button3Shot = 11;
const int buttonSkill = 12;
const int led = 13;
const int tiltRelay = 8;
const int tiltSense = A5;
long timeout = 86400000; //~1 day in millis
int speedValue =0;
int potPin =A0;

long StepperRPM = 100;  // default speed and hold variable
int buttonState3Shot = HIGH;  
int buttonStateSkill = HIGH; 

#include <Stepper.h>
 
const int stepsPerRevolution = 200;  //
Stepper Ystepper(stepsPerRevolution, 2,3,4,5);  

void setup() {
  Serial.begin(9600);
   pinMode(button3Shot, INPUT_PULLUP); //enable intermal pull ups. Note all functioning logic must trigger low.
   pinMode(buttonSkill, INPUT_PULLUP);
   pinMode(tiltSense, INPUT_PULLUP);
   pinMode(tiltRelay, OUTPUT);
   
  pinMode(led, OUTPUT); 
  digitalWrite(led,LOW);
  digitalWrite(tiltRelay,HIGH);

}

void loop() { 
  speedValue = analogRead(potPin); //read the voltage at the potentiometer ( 0 - 5v)  
                                    //then convert this reading to the analog resolution number (0-1023)
                                    
  if (digitalRead(tiltSense)==LOW) { //if the tilt sensor is not connected, this IF statement will never trigger.
    digitalWrite(led,HIGH);
    digitalWrite(tiltRelay, LOW);            // relay triggers on LOW
    delay(1000); digitalWrite(tiltRelay, HIGH); 
    delay(1500); //this longer delay is to "wait out" the swinging plum blob. After a hard tilt, 
                 //the plum bob will continue to swing and may continue to trigger the bell until dampened
    delay(timeout); // essentially redering the machine out of service [tilt] until the reset button is pressed on the atmega
  }
  
 //----------Stepper Forward-----------------------------------------------------------------------------
Ystepper.setSpeed(speedValue/10 + 10);      // will give a stepper speed range of ~10 RPM - 110 RPM. Max speed is ~120RPM. if you go beyond 120RPM, motor will skip steps            
  while ((digitalRead(buttonSkill)==LOW) && (digitalRead(tiltSense)==HIGH)) {     //If button is pressed and tilt has not been activated, drive motor
    //digitalWrite(led,HIGH);                //when button is pressed (goes low) turn led on and move stepper 200 steps 
    Ystepper.step(10);                     //200 steps = 1 rotation
                      }
//----------Stepper Backward---------------------------------------------------------------------------  
 Ystepper.setSpeed(speedValue/10 + 10);      //optional to have 2nd button or alternate motor drive profile
  while (digitalRead(button3Shot) == LOW) { 
digitalWrite(led,HIGH);    
    Ystepper.step(-600);                     //-200 steps = 1 rotation (opposite rotation)
                      }
                       
digitalWrite(2,LOW); //disables hold (no current supplied to stepper when idle)
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);

digitalWrite(led,LOW);
        
}

