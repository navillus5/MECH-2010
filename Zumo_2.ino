/*  
   ##################################################################### 
   ##                                                                 ## 
   ##                    Zumo_2                                        ## 
   ##                                                                 ## 
   ##                    Daniel J. Sullivan                           ## 
   ##                    July 2016                                    ## 
   ##                                                                 ##
   #####################################################################

   Zumo bot will move forward until it's sensor array detects a black line.
   The bot will then (i) stop, (ii) back up, (iii) rotate for 500 milliseconds.
   The process will then repeat.
*/

#include <ZumoMotors.h>                // initialize library to be used by program
ZumoMotors motors;                     // create motor library object

// Define Global variables                                       
int irEmit = 2;                        // create name for IR LED's    
int led = 13;                          // create name for Indicator LED
int ledState = LOW;                    // create Indicator LED state and initialize value
long interval = 100;                   // indicator LED delay variable
int zumoButton = 12;                   // create name for Zumo button
unsigned long previousMillis = 0;      // delay variable for use with blinkLED()
int irPin[] = {5, A2, A0, 11, A3, 4};  // create array of IR sensor pins
int irVal[] = {0,0,0,0,0,0};             // create array for IR sensor value
int mspeed = 200;                      // define value for motor speed (0-255)
int threshold = 500;                   // any irValue above this vlaue will indicated a black line.
             
  
void setup()
{                                      
  pinMode(zumoButton,INPUT_PULLUP);         // set button pin to input and turn on internal pullup resistor (pin reads HIGH until button is pushed)
  pinMode(irEmit,OUTPUT);                   // set IR LED control pin to output
  pinMode(led, OUTPUT);                     // set indicator LED pin to output 
  while (digitalRead(zumoButton) == HIGH){  // while loop will call blinkLED() until button is pressed
    blinkLED();                             
    }                                       
  digitalWrite(led,LOW);                   // turn off Indicator LED
  digitalWrite(irEmit,HIGH);               // turn on IR LED's
}                                          
                                           
void loop()                                
{                                          
  irValue();                           // Read IR sensor values
  int flag = 0;                        // define a control flag and set to 0
  for(int i=0; i<6; i++)               // check values of irValue array. If any value
  {                                    // is above threshold, set flag to 1.
    if(irVal[i] > threshold){flag=1;}      
    }                                                       
  if(flag == 0){                       // move forward
     motors.setLeftSpeed(mspeed);          
     motors.setRightSpeed(mspeed);         
  }                                        
  else{                                    
    motors.setLeftSpeed(0);            // stop motors and...
    motors.setRightSpeed(0);            
    delay(200);                        // ...delay for 200 milliseconds                        
    motors.setLeftSpeed(-mspeed);      // reverse motors and...
    motors.setRightSpeed(-mspeed);           
    delay(500);                        // pause for 500 milliseconds
    motors.setLeftSpeed(mspeed);       // set motors to opposite directions... 
    motors.setRightSpeed(-mspeed);     
    delay(500);                        // ...and delay for 500 milliseconds.
  }    
}

//************************************* irValue() **********************************************

void irValue(){
  unsigned long startTime;
  
  for(int i=0; i<6; i++){
    pinMode(irPin[i], OUTPUT);             // Set pin sensor2 to output
    digitalWrite(irPin[i], HIGH);          // Set the pin voltage to +5V
    delayMicroseconds(10);                 // Charge capacitor for 10 usec
    pinMode(irPin[i],INPUT);               // Disable internal pull-up on pin sensor2
    digitalWrite(irPin[i], LOW);           // Drive pin sensor2 LOW allowing the capacitor to dicharge through phototransistor.
    startTime = micros();                  // micros() is the number of microseconds since the program began. 
    while(digitalRead(irPin[i]) == HIGH){  // Loop until capacitor has discharged below ~2.3V.
      }
    irVal[i] = micros() - startTime; // Calculate the amount of time for capacitor to discharge.      
  }   
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
