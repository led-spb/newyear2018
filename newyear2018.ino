#include "LowPower.h"          
#include "Bounce2.h"

// Pin configuration
#define R 9
#define G 3
#define B 5
#define BUTTON 2

// Predefined settings
#define SPEED 255
#define START_PROG           (0+AUTO_CHANGE_BIT)
#define AUTO_CHANGE_INTERVAL 30L*1000
#define SLEEP_INTERVAL       180L*1000
#define LONG_PRESS_MILLIS    2*1000
//#define DEBUG 1

// Color scheme codes

#define VALUE_RED(v)    (unsigned char)((v)&0xFF)
#define VALUE_GREEN(v)  (unsigned char)((v>>8)&0xFF)
#define VALUE_BLUE(v)   (unsigned char)((v>>16)&0xFF)

#define RGB(r,g,b)      ( ((unsigned long)r&0xFF) + (((unsigned long)g&0xFF)<<8) + (((unsigned long)b&0xFF)<<16) )

#define RED          RGB(255,0,0)
#define GREEN        RGB(0,255,0)
#define BLUE         RGB(0,0,255)
#define YELLOW       RGB(255,255,0)
#define MAGENTA      RGB(255,0,255) 
#define CYAN         RGB(0,255,255)
#define WHITE        RGB(255,255,255)
#define BLACK        RGB(0,0,0)

#define AUTO_CHANGE_BIT  8

unsigned long curr  = 0;
unsigned long color = 0;

byte prog = START_PROG;

int tim  = SPEED / 20 + 2;
int tim2 = SPEED + 70;

int stage = 0;
volatile unsigned long changed = 0;
volatile unsigned long waked = 0;
//byte debug = 0;

Bounce button = Bounce(BUTTON, 15);

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

  randomSeed(analogRead(0));
  next_prog();
}

void wake_up(){
#ifdef DEBUG
  Serial.println("Waked");
#endif
  waked = millis();
}

void sleep(){
  setColor(BLACK);

  attachInterrupt( digitalPinToInterrupt(BUTTON), wake_up, FALLING );
  // Here we sleep
  LowPower.powerDown( SLEEP_FOREVER, ADC_OFF, BOD_OFF );
  // Here we waked
  detachInterrupt( digitalPinToInterrupt(BUTTON) );
}


void next_prog(){
   byte next = prog&(AUTO_CHANGE_BIT-1);
   next = ((next+1) % 3) + 1;
   prog = next | (prog&AUTO_CHANGE_BIT) ;
   
#ifdef DEBUG
   Serial.print( "changed to prog: ");
   Serial.print( (byte)prog&(AUTO_CHANGE_BIT-1) );
   Serial.print( " auto change: ");
   Serial.println( (prog&AUTO_CHANGE_BIT)>1 );
#endif
   changed = millis();

   color = BLACK;
   setColor(BLACK);

   delay(300);
}


void change_prog_timer()
{
  if( (prog&AUTO_CHANGE_BIT) && ((millis()-changed) >= AUTO_CHANGE_INTERVAL) ){
     next_prog();
  }
}

void setColor(unsigned long c){
   curr = c;
   analogWrite(R, VALUE_RED(c) );
   analogWrite(G, VALUE_GREEN(c) );
   analogWrite(B, VALUE_BLUE(c) );
}


// black -> color -> black
void prog_1(){
  if( curr==color ){
     delay( tim+500 );

     stage = (stage+1) % 12;
     switch( stage ){
        case 0:  color = BLACK;   break;
        case 1:  color = RED;     break;
        case 2:  color = BLACK;   break;
        case 3:  color = BLUE;    break;
        case 4:  color = BLACK;   break;
        case 5:  color = YELLOW;  break;
        case 6:  color = BLACK;   break;
        case 7:  color = GREEN;   break;
        case 8:  color = BLACK;   break;
        case 9:  color = MAGENTA; break;
        case 10: color = BLACK;   break;
        case 11: color = CYAN;    break;
     }
  }

  if( VALUE_RED(curr) < VALUE_RED(color) ){
     curr = curr + 1;
  }
  if( VALUE_RED(curr) > VALUE_RED(color) ){
     curr = curr - 1;
  }
  if( VALUE_GREEN(curr) < VALUE_GREEN(color) ){
     curr = curr + (1L<<8);
  }
  if( VALUE_GREEN(curr) > VALUE_GREEN(color) ){
     curr = curr - (1L<<8);
  }
  if( VALUE_BLUE(curr) < VALUE_BLUE(color) ){
     curr = curr + (1L<<16);
  }
  if( VALUE_BLUE(curr) > VALUE_BLUE(color) ){
     curr = curr - (1L<<16);
  }
  setColor( curr );
  delay( tim );
}


// Random color overflow
void prog_2(){
  if( color==curr ){
     color = RGB( random(0,256), random(0,256), random(0,256) );
  }

  if( VALUE_RED(curr) < VALUE_RED(color) ){
     curr = curr + 1;
  }
  if( VALUE_RED(curr) > VALUE_RED(color) ){
     curr = curr - 1;
  }
  if( VALUE_GREEN(curr) < VALUE_GREEN(color) ){
     curr = curr + (1L<<8);
  }
  if( VALUE_GREEN(curr) > VALUE_GREEN(color) ){
     curr = curr - (1L<<8);
  }
  if( VALUE_BLUE(curr) < VALUE_BLUE(color) ){
     curr = curr + (1L<<16);
  }
  if( VALUE_BLUE(curr) > VALUE_BLUE(color) ){
     curr = curr - (1L<<16);
  }
  setColor( curr );
  delay( 8 );
}

// Blink twice
void prog_3(){
  stage = (stage+1) % 24;
  switch( stage ){
     case 0:  color = BLACK;   break;
     case 1:  color = RED;     break;
     case 2:  color = BLACK;   break;
     case 3:  color = RED;     break;

     case 4:  color = BLACK;   break;
     case 5:  color = BLUE;    break;
     case 6:  color = BLACK;   break;
     case 7:  color = BLUE;    break;

     case 8:  color = BLACK;   break;
     case 9:  color = YELLOW;  break;
     case 10: color = BLACK;   break;
     case 11: color = YELLOW;  break;

     case 12: color = BLACK;   break;
     case 13: color = GREEN;   break;
     case 14: color = BLACK;   break;
     case 15: color = GREEN;   break;

     case 16: color = BLACK;   break;
     case 17: color = MAGENTA; break;
     case 18: color = BLACK;   break;
     case 19: color = MAGENTA; break;

     case 20: color = BLACK;   break;
     case 21: color = CYAN;    break;
     case 22: color = BLACK;   break;
     case 23: color = CYAN;    break;
  }
  setColor(color);
  delay( tim2 );
}

void prog_4(){
}

boolean button_active = false;
long button_timer = 0;

void loop() {
  //if( debug>0 ) return; 

  // On long press - sleep, on short - change prog
  button.update();
  if( button.read()==LOW ){
    if( button_timer == 0 ){
       button_timer = millis();
    }

    if( (millis()-button_timer) >= LONG_PRESS_MILLIS ){
        // Long pressed
        button_timer = 0;
        sleep();
    }
  }else{
    if( button_timer>0 ){
        // Short pressed
        button_timer = 0;
        next_prog();
    }
  }

  change_prog_timer();

  switch( prog & (AUTO_CHANGE_BIT-1) ){
     case 1: 
         prog_1();
         break;
     case 2:
         prog_2();
         break;
     case 3:
         prog_3();
         break;
     case 4:
         prog_4();
         break;
  }

  if( SLEEP_INTERVAL>0 &&  (millis()-waked)>=SLEEP_INTERVAL ){
    sleep();
  }
  //debug = 1;
}
