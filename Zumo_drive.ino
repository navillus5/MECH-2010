/*  
   ##################################################################### 
   ##                                                                 ## 
   ##                    Zumo_Drive                                   ## 
   ##                                                                 ## 
   ##                    Daniel J. Sullivan                           ## 
   ##                    November 2016                                ## 
   ##                                                                 ##
   #####################################################################

   Drive the Zumobot. 
   Go forward for 2 seconds, pause and beep,
   Go backward for 2 seconds, pause and beep,
   Spin one direction for 4 seconds, pause and beep,
   Spin the other direction for 4 seconds, pause and beep,
   repeat 3 times 
*/
#include <ZumoMotors.h>                // initialize libraries to be used by program
#include <ZumoBuzzer.h>

ZumoMotors motors;                     // create motor object
ZumoBuzzer buzzer;                     // create buzzer object


// Define Global variables                                       
int zumoButton  = 12;     // create name for Zumo button    
int led         = 13;     // create name for Indicator LED
int ledState    = LOW;    // create Indicator LED state and initialize value
long interval   = 100;                      // indicator LED delay variable
unsigned long previousMillis = 0;           // delay variable for use with blinkLED()
int loopCount = 0;

int mspeed      = 100;    // define value for motor speeds (0-400)
  
void setup()
{
  pinMode(zumoButton,INPUT_PULLUP);         // set button pin to input and turn on internal pullup resistor (pin reads HIGH until button is pushed)
  pinMode(led, OUTPUT);                     // set indicator LED pin to output
    
  while (digitalRead(zumoButton) == HIGH)   // while loop will call blinkLED() until button is pressed
  {
    blinkLED();                  // user defined function that blinks LED                             
    }
     
  digitalWrite(led,LOW);         // turn off Indicator LED
  delay(2000);                   // delay for user to get finger away from button    
}

void loop()
{
  while(loopCount < 3){

    loopCount++   // Increase the value of the loop counter by one
    
// Go forward
     motors.setLeftSpeed(mspeed);
     motors.setRightSpeed(mspeed);
     delay(1000); 
   
     pauseBeep();

// Go backward
     motors.setLeftSpeed(-mspeed);
     motors.setRightSpeed(-mspeed);
     delay(1000); 

     pauseBeep();

// Spin to the right
     motors.setLeftSpeed(mspeed);
     motors.setRightSpeed(-mspeed);
    delay(1000);

   pauseBeep();

// Spin to the left
     motors.setLeftSpeed(-mspeed);
     motors.setRightSpeed(mspeed);
     delay(1000);

     pauseBeep();
     
}

    


//************************************** blinkLED() ********************************************

void blinkLED(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {  
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(led, ledState);
  }
}


//************************************** pauseBeep() ********************************************

void pauseBeep(){
   motors.setLeftSpeed(0);
   motors.setRightSpeed(0);
   delay(100);
   buzzer.play(">g32>>c32");
   delay(100);  
}
