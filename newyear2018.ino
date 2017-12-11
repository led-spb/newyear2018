#include "LowPower.h"

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
//#define DEBUG 1

// Color scheme codes
#define CODE_RED     0x1
#define CODE_GREEN   0x2
#define CODE_BLUE    0x4
#define CODE_YELLOW  CODE_RED+CODE_GREEN
#define CODE_MAGENTA CODE_RED+CODE_BLUE
#define CODE_CYAN    CODE_GREEN+CODE_BLUE
#define CODE_WHITE   CODE_RED+CODE_GREEN+CODE_BLUE

#define AUTO_CHANGE_BIT  8

byte old  = 0;
byte curr = 0;

byte prog = START_PROG;

int tim  = SPEED / 20 + 2;
int tim2 = SPEED + 70;

unsigned long changed = 0;
unsigned long waked = 0;
//byte debug = 0;


void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);
  // now we only wake on button
  attachInterrupt( digitalPinToInterrupt(BUTTON), wake_up, FALLING );
  
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
#ifdef DEBUG
//  Serial.println("Now we go to sleep");
#endif
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  
  //attachInterrupt( digitalPinToInterrupt(BUTTON), wake_up, FALLING );
  //delay(100);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  //detachInterrupt( digitalPinToInterrupt(BUTTON) );
}


void next_prog(){
   byte next = prog&(AUTO_CHANGE_BIT-1);
   if( (++next)>4 ) next = 1;
   prog = next | (prog&AUTO_CHANGE_BIT) ;
   
#ifdef DEBUG
   Serial.print( "changed to prog: ");
   Serial.print( (byte)prog&(AUTO_CHANGE_BIT-1) );
   Serial.print( " auto change: ");
   Serial.println( (prog&AUTO_CHANGE_BIT)>1 );
#endif

   changed = millis();

   digitalWrite(R, LOW);
   digitalWrite(G, LOW);
   digitalWrite(B, LOW);
   delay(300);
}


void change_prog_timer()
{
  if( (prog&AUTO_CHANGE_BIT) && ((millis()-changed) >= AUTO_CHANGE_INTERVAL) ){
     next_prog();
  }
}

void lightCode(byte code, short dir, int tm){
  for(int level=dir>0?0:255; (dir>0 && level<=255) || (dir<0 && level>=0); level=level+dir){
     if(code&1) analogWrite(R,level);
     if(code&2) analogWrite(G,level);
     if(code&4) analogWrite(B,level);
     delay(tm);
  }
}


void prog_1(){
  switch(curr){
     case CODE_RED:     curr = CODE_BLUE;    break;
     case CODE_BLUE:    curr = CODE_YELLOW;  break;
     case CODE_YELLOW:  curr = CODE_GREEN;   break;
     case CODE_GREEN:   curr = CODE_MAGENTA; break;
     case CODE_MAGENTA: curr = CODE_CYAN;    break;
     default:           curr = CODE_RED;     
  }
  lightCode(curr, 1, tim);
  lightCode(curr,-1, tim);
  delay(tim+500);

  old = curr;  
}

void prog_2(){
  analogWrite( R, random(0,256) );
  analogWrite( G, random(0,256) );
  analogWrite( B, random(0,256) );
  delay( tim2 );
}


void prog_3(){/*
  curr = (curr+1) & 7;
  if(curr==7) curr=1;*/
  do{
    curr = random(1,8);
  }while(curr==old);

  for(int level=0; level<=255; level++){ 
    // Red 
    if( (old&1)==0 && (curr&1) ){
      analogWrite(R, level);
    } 
    if( old&1 && (curr&1)==0 ){
      analogWrite(R, 255-level);
    }

    // Green 
    if( (old&2)==0 && (curr&2) ){
      analogWrite(G, level);
    }
    if( old&2 && (curr&2)==0 ){
      analogWrite(G, 255-level);
    }

    // Blue
    if( (old&4)==0 && (curr&4) ){
      analogWrite(B, level);
    }
    if( old&4 && (curr&4)==0 ){
      analogWrite(B, 255-level);
    }
    delay(10);
  }
  delay(1000);
  old = curr;
}


void prog_4(){
  curr = (curr+1)&7;
  if( curr==7 ) curr=1;
  
  // Blink color twice
  for(byte j=0; j<2; j++){
    lightCode(curr,  1, 0);
    delay(tim2);
    lightCode(curr, -1, 0);
    delay(tim2);
  }
  old = curr;
}



void loop() {
  //if( debug>0 ) return; 
  change_prog_timer();

  #ifdef DEBUG
    Serial.println( digitalRead( BUTTON ) );
  #endif

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

  if( (millis()-waked) >= SLEEP_INTERVAL ){
    sleep();
  }
  //debug = 1;
}
