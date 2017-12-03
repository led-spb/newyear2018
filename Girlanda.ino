


#define R 6           // 6 пин красный
#define G 5           // 5 пин зеленый
#define B 3           // 3 пин синй
#define pot A1        // к  А1 подключаем потенциометр

int tim = 0;         // переменная хранения длительности задержки для 1 и 2 программы
int tim2 = 0;        // переменная хранения длительности задержки для 3 программы
int prog = 0;        // переменная хранения номера прграммы 


void setup() {
  pinMode(R, OUTPUT);      // пин R на выход
  pinMode(G, OUTPUT);      // пин G на выход
  pinMode(B, OUTPUT);      // пин B на выход

attachInterrupt (0,PROG,RISING);    // Прерывание 0 (вывод 2), выполняет программу PROG,при изменении состояния кнопки от - к +
}
void PROG()                         // Программа выполняющаяся по прерыванию 
{
  if (prog<5){                      // если включена программа меньше чем №5 то при нажатии увеличить на 1
    prog++;
    }
    if (prog==5){                   // если включили программу №5 то сбросить на №0
      prog=0;
      }
}

void loop() {
 int r, g, b;                         // переменные хранения заполнения ШИМ для цветов 

tim = (analogRead(pot)/20)+2;         //читаем значение потенциометра
tim2 = analogRead(pot)+70;            //читаем значение потенциометра


//---------------------Первая программа-------------------------
if (prog==0 | prog==3){       // Выполнять если включена программа №0 или №3
for (r = 0; r < 255; r++) { 
    analogWrite(R, r);
  delay(tim);}
for (r =255; r >= 0; r--) { 
    analogWrite(R, r);
  delay(tim);}
delay(tim+500);
  
for (r = 0; r < 255; r++) { 
    analogWrite(B, r);
  delay(tim);}
for (r = 255; r >= 0; r--) { 
    analogWrite(B, r);
  delay(tim);}
delay(tim+500);
  
  for (r = 0; r < 255; r++) { 
    analogWrite(R, r);
    analogWrite(G, r);
    delay(tim);}
for (r = 255; r >= 0; r--) { 
    analogWrite(R, r);
    analogWrite(G, r);
  delay(tim);}
  delay(tim+500);
  
for (r = 0; r < 255; r++) { 
    analogWrite(G, r);
  delay(tim);}
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
 //---------------------------Еретья программа-------------------------------
 if(prog==2 | prog==3){         // Выполнять если включена программа №2 или №3
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
  
  
}
