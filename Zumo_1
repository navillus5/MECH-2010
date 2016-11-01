/*  
   ##################################################################### 
   ##                                                                 ## 
   ##                    Zumo_1                                       ## 
   ##                                                                 ## 
   ##                    Daniel J. Sullivan, PhD                      ##
   ##                    Lecturer - Mechanical Engineering            ##
   ##                    UMass Lowell                                 ##
   ##                    July 2016                                    ## 
   ##                                                                 ##
   #####################################################################

   Explicit code that shows how to set up and read the array of six
   IR sensors on the Arduino Zumo bot.
*/

// Define Global variables
int irEmit = 2;                        // create name for IR LED's    
int led = 13;                          // create name for Indicator LED
int ledState = LOW;                    // create Indicator LED state and initialize value
long interval = 100;                   // Indicator LED delay variable
int zumoButton = 12;                   // create name for Zumo button
unsigned long previousMillis = 0;      // delay variable for use with blinkLED()
int irPin[] = {5, A2, A0, 11, A3, 4};  // Create array of IR sensor pins
int irVal[] = {0,0,0,0,0,0};             // Create array for IR sensor value
                                       
                                       
                                       
void setup()                           
{                                      
  Serial.begin(9600);                       // open serial communication link to PC
  pinMode(zumoButton,INPUT_PULLUP);         // set button pin to input and turn on internal pullup resistor (pin reads HIGH until button is pushed)
  pinMode(irEmit,OUTPUT);                   // set IR LED control pin to output
  pinMode(led, OUTPUT);                     // set indicator LED pin to output 
  while (digitalRead(zumoButton) == HIGH){  // while loop will call blinkLED() until button is pressed
    blinkLED();                             
    }                                       
  digitalWrite(led,LOW);                    // turn off Indicator LED
  digitalWrite(irEmit,HIGH);                // turn on IR LED's
}

void loop()
{
  irValue();                                // Read IR sensor values
   



}

//************************************* irValue() **********************************************

void irValue(){
  unsigned long startTime;
  
  for(int i=0; i<6; i++){
    pinMode(irPin[i], OUTPUT);             // Set IR detector pin to an output
    digitalWrite(irPin[i], HIGH);          // Set the pin voltage to +5V and...
    delayMicroseconds(10);                 // ...charge capacitor for 10 usec
    pinMode(irPin[i],INPUT);               // Set IR detector pin to an output
    digitalWrite(irPin[i], LOW);           // Set IR detector pin LOW allowing the capacitor to dicharge through phototransistor.
    startTime = micros();                  // micros() is the number of microseconds since the program began. 
    while(digitalRead(irPin[i]) == HIGH){  // Loop until capacitor has discharged below ~2.3V.
      }
    irVal[i] = micros() - startTime;       // determine the time in microseconds required for capacitor to discharge.
    Serial.print(irVal[i]);                // print the time required to discharge
    Serial.print("   ");                   // from 150-250 microseconds when over white printer paper
                                           // from 1900-2300 microseconds when over black electrical tape  
  }                                        // from 2300-2800 when over edge of a table.
    Serial.println("   ");
    delay(500);    
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
