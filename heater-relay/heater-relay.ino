// Test Relay signal when button is pressed
// Use PIN 7 to send signal to relay
// Turn on LED when the button is pressed to test Sketch code
// and keep it on after it is released
// including simple de-bouncing
//

// BMP180 SENSOR
#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
#define ALTITUDE 10 // Altitude of SparkFun
// BMP180 SENSOR

#define LED 13                    // the pin for the LED
#define BUTTON 2              // the input pin where the pushbutton is connected
#define RELAY 7                 // PIN for relay signal
 
int val=0;                               // val will be used to store the state of the input pin                                          // 
int old_val=0;                      // this variable stores the previous value of "val"
int state=1;                          //0=LED off and 1 = LED on

void setup(){
 pinMode(LED, OUTPUT);               // tell arduino LED is an output
 pinMode(BUTTON, INPUT_PULLUP);           // and BUTTON is an input
 pinMode(RELAY, OUTPUT);          // tells arduino RELAY is an output
 Serial.begin(9600);
 
 // INITIALIZE BMP180 SENSOR
 if (!pressure.begin())
 {
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
 }
}

void loop(){
  char status;
  double T,P,p0,a;
 
 val=digitalRead(BUTTON);         // read input value and store it -- new input

//Wait for the RaspPi to ping us with the ! character
if(Serial.available())
  {
    byte incoming = Serial.read();
    if(incoming == '!')
    {
       status = pressure.startTemperature();
        if (status != 0)  //Read temperature from BMP180 sensor
        {
          // Wait for the measurement to complete:
          delay(status);
      
          // Retrieve the completed temperature measurement:
          // Note that the measurement is stored in the variable T.
          // Function returns 1 if successful, 0 if failure.
      
          status = pressure.getTemperature(T);
          if (status != 0)
          {
            // Print out the measurement:
            Serial.println((9.0/5.0)*T+32.0,2);
          }
        } 
    }
    else if(incoming == '#') //Read current relay status
    {
       if(state==1)
       {
          Serial.println("ON");
       }
       else
       {
         Serial.println("OFF");
       }
     }
    else if(incoming == '@') //Switch relay to ON if OFF, and OFF if ON
    {
       if(state==1)
       {
          state=0;
       }
       else
       {
         state=1;
       }
     }
     
  }


                                  
 // check if there was a transition
 if ((val==HIGH) && (old_val==LOW)){
   state = 1 - state;
   delay(10);
 }

 old_val=val;                    // val is now old, let's store it

 if (state == 1){
  digitalWrite(LED,HIGH);           // turn LED ON
  digitalWrite(RELAY,HIGH);      // turn RELAY ON
//  Serial.println("ON");
 }else{
  digitalWrite(LED,LOW);            // turn LED OFF
  digitalWrite(RELAY,LOW);       // turn RELAY OFF
//  Serial.println("OFF");
 }
 
} 