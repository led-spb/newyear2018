


#define R 9           // 6 пин красный
#define G 3           // 5 пин зеленый
#define B 5           // 3 пин синй
#define pot A1        // к  А1 подключаем потенциометр

int tim = 0;         // переменная хранения длительности задержки для 1 и 2 программы
int tim2 = 0;        // переменная хранения длительности задержки для 3 программы
int prog = 2;        // переменная хранения номера прграммы 
int spd = 255;
unsigned long changed = 0;

void setup() {
  pinMode(R, OUTPUT);      // пин R на выход
  pinMode(G, OUTPUT);      // пин G на выход
  pinMode(B, OUTPUT);      // пин B на выход
  
  tim  = spd / 20 +2;
  tim2 = spd + 70;
}

void PROG()                         // Программа выполняющаяся по прерыванию 
{
  if( millis()-changed > 30*1000 ){
    prog = (++prog) % 4;
    changed = millis();
  }
}




void prog_3(){
  byte old = 0;
  for(byte curr=0; curr<7; curr++){
    for(byte level=0; level<255; level++){ 
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
      delay(5);
    }
    if(curr&1) analogWrite(R,0);
    if(curr&2) analogWrite(G,0);
    if(curr&4) analogWrite(B,0);
    old = curr;
  }
}

void prog_4(){
   for(byte i=1;i<7;i++){
     for(byte j=0;j<3;j++){
       if( i & 1 )
          digitalWrite(R, HIGH);
       if( i & 2 )
          digitalWrite(G, HIGH);
       if( i & 4 )
          digitalWrite(B, HIGH);
          
       delay(tim2);
  
       if( i & 1 )
          digitalWrite(R, LOW);
       if( i & 2 )
          digitalWrite(G, LOW);
       if( i & 4 )
          digitalWrite(B, LOW);
       delay(tim2);
     }
  }
}

void loop() {

 // PROG();
 prog_4();
//tim = (analogRead(pot)/20)+2;         //читаем значение потенциометра
//tim2 = analogRead(pot)+70;            //читаем значение потенциометра

/*
//---------------------Первая программа-------------------------
if (prog==0 | prog==3){       // Выполнять если включена программа №0 или №3
for (r = 0; r < 255; r++) { 
    analogWrite(R, r);
    delay(tim);
}

for (r =255; r >= 0; r--) { 
    analogWrite(R, r);
    delay(tim);
}
delay(tim+500);
  
for (r = 0; r < 255; r++) { 
  analogWrite(B, r);
  delay(tim);
}
for (r = 255; r >= 0; r--) { 
  analogWrite(B, r);
  delay(tim);
}
delay(tim+500);
  
for (r = 0; r < 255; r++) { 
    analogWrite(R, r);
    analogWrite(G, r);
    delay(tim);
}

for (r = 255; r >= 0; r--) { 
    analogWrite(R, r);
    analogWrite(G, r);
    delay(tim);
}
delay(tim+500);
  
for (r = 0; r < 255; r++) { 
  analogWrite(G, r);
  delay(tim);
}
for (r = 255; r >= 0; r--) { 
    analogWrite(G, r);
  delay(tim);}
  delay(tim+500);
  
   for (r = 0; r < 255; r++) { 
    analogWrite(R, r);
    analogWrite(B, r);
    delay(tim);}
for (r = 255; r >= 0; r--) { 
    analogWrite(R, r);
    analogWrite(B, r);
  delay(tim);}
  delay(tim+500);
  
  for (r = 0; r < 255; r++) { 
    analogWrite(G, r);
    analogWrite(B, r);
    delay(tim);}
for (r = 255; r >= 0; r--) { 
    analogWrite(G, r);
    analogWrite(B, r);
  delay(tim);}
  delay(tim+500);
}

  //----------------------------Вторая программа----------------------
 if (prog==1 | prog==3){            // Выполнять если включена программа №1 или №3
 for (r = 0; r < 255; r++) { 
    analogWrite(R, r);
  delay(tim);
  }
 
  //от фиолетового к красному
 for (b = 255; b > 0; b--) { 
    analogWrite(B, b);
   delay(tim);
  } 
  // от красного к желтому
  for (g = 0; g < 256; g++) { 
    analogWrite(G, g);
    delay(tim);
  } 
  // от желтого к зеленому
  for (r = 255; r > 0; r--) { 
    analogWrite(R, r);
    delay(tim);
  } 
  //  от зеленого к зеленовато-голубому
  for (b = 0; b < 256; b++) { 
    analogWrite(B, b);
   delay(tim);
  } 
  // от зеленовато-голубого к голубому
  for (g = 255; g > 0; g--) { 
    analogWrite(G, g);
    delay(tim);
  }
 }
*/

 //---------------------------Еретья программа-------------------------------
 /*
 if(prog==2 | prog==3){         // Выполнять если включена программа №2 или №3
 
*/

  /*    
  digitalWrite(R,HIGH);
   delay(tim2);
  digitalWrite(R,LOW);
   delay(tim2);
  digitalWrite(R,HIGH);
   delay(tim2);
  digitalWrite(R,LOW);
   delay(tim2);
   digitalWrite(G,HIGH);
   delay(tim2);
  digitalWrite(G,LOW);
   delay(tim2);
    digitalWrite(G,HIGH);
   delay(tim2);
  digitalWrite(G,LOW);
   delay(tim2);
      digitalWrite(B,HIGH);
   delay(tim2);
  digitalWrite(B,LOW);
   delay(tim2);
    digitalWrite(B,HIGH);
   delay(tim2);
  digitalWrite(B,LOW);
   delay(tim2);
  }
   */
 
  
}
