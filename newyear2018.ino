/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

#define RED 9
#define GREEN 3
#define BLUE 5

#define DELAY 10

int cycle = 0;
int led = RED;
int leds[3] = {RED,GREEN,BLUE};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  led = leds[ (cycle++) % 3];
  
  int i=0;
  for(; i<255; ++i){
     analogWrite( led, i);
     delay(DELAY);
  }
  for(;i>0;--i){
    analogWrite( led, i);
    delay(DELAY);
  }
  analogWrite(led,0);
}
