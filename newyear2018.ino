#define R 9           // ������� ���
#define G 3           // ������� ���
#define B 5           // ����� ���

// ��������
byte old  = 0;
byte curr = 0;

int tim = 0;
int tim2 = 0;

int prog = 2;        // ���������� �������� ������ �������� 

int spd = 255;
unsigned long changed = 0;
int debug = 0;

void setup() {
  pinMode(R, OUTPUT);      // ��� R �� �����
  pinMode(G, OUTPUT);      // ��� G �� �����
  pinMode(B, OUTPUT);      // ��� B �� �����
  
  randomSeed(analogRead(0));
  
  tim  = spd / 20 +2;
  tim2 = spd + 70;
}


void change_prog()
{
  if( millis()-changed > 30*1000 ){
    prog = (++prog) % 4 + 1;
    changed = millis();
    
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
    delay(300);
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

byte prog_1_data[] = {1,4, 1,3 };

void prog_1(){
  int r, g, b;

  //if(curr==  
  lightCode(curr, 1, tim);
  lightCode(curr,-1, tim);
  delay(tim+500);

  old = curr;  
/*  
  for( r = 0; r < 255; r++ ){ 
    analogWrite(R, r);
    delay(tim);
  }
  for( r=255; r >= 0; r-- ){ 
    analogWrite(R, r);
    delay(tim);
  }
  delay(tim+500);
    
  for( r = 0; r < 255; r++ ){ 
    analogWrite(B, r);
    delay(tim);
  }
  for (r = 255; r >= 0; r--){ 
    analogWrite(B, r);
    delay(tim);
  }
  delay(tim+500);
    
  for( r = 0; r < 255; r++ ){ 
    analogWrite(R, r);
    analogWrite(G, r);
    delay(tim);
  }
  for( r = 255; r >= 0; r-- ){ 
    analogWrite(R, r);
    analogWrite(G, r);
    delay(tim);
  }
  delay(tim+500);

    
  for( r = 0; r < 255; r++ ){ 
    analogWrite(G, r);
    delay(tim);
  }
  for (r = 255; r >= 0; r--){ 
    analogWrite(G, r);
    delay(tim);
  }
  delay(tim+500);
    
  for( r = 0; r < 255; r++){ 
    analogWrite(R, r);
    analogWrite(B, r);
    delay(tim);
  }
  for( r = 255; r >= 0; r--){ 
    analogWrite(R, r);
    analogWrite(B, r);
    delay(tim);
  }
  delay(tim+500);
    
  for( r = 0; r < 255; r++ ){ 
    analogWrite(G, r);
    analogWrite(B, r);
    delay(tim);
  }
  for( r = 255; r >= 0; r--){ 
    analogWrite(G, r);
    analogWrite(B, r);
    delay(tim);
  }
  delay(tim+500); */
}

void prog_2(){
  analogWrite( R, random(0,255) );
  analogWrite( G, random(0,255) );
  analogWrite( B, random(0,255) );
  delay( tim2 );
}


void prog_3(){
  curr = (curr+1) & 7;
  if(curr==7) curr=1;

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
  if( debug>0 ) return;  
  curr = (curr+1)&7;
  if(curr==7) curr=1;
  
  for(byte j=0; j<2; j++){
    lightCode(curr,  1, 0);
    delay(tim2);
    lightCode(curr, -1, 0);
    delay(tim2);
  }
  old = curr;
}




void loop() {
 // change_prog();

  if( prog==0 || prog==1)  prog_1();
  if( prog==0 || prog==2)  prog_2();
  if( prog==0 || prog==3)  prog_3();
  if( prog==0 || prog==4)  prog_4();
  
  //debug = 1;
}
