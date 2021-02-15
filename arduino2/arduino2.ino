
// Dmytro Kuzmyk dkuzmy3
// Aaron Lau alau8 
  
// include the library code:
#include <LiquidCrystal.h>
//#include <String.h>

// Determine all the pins attached to the Liquid Crystal display (16x2)
// initialize the library by associating any needed LCD interface pin with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int left = 2;
int mid = 3;
int right = 4;
char c = ' ';

// conting rounds to keep track of the role
int count = 0;
int hp = 1000;
bool chooseRole = true;
bool moved = false;
bool received = false;
bool attack=false;
bool defend=false;
int role;

bool defLeft=false;
bool defMid=false;
bool defRight=false;

void setup() {
  lcd.begin(16, 2); // LCD used to debug
  Serial.begin(9600); // serial used to communicate btw arduinos
  pinMode(left, INPUT);
  pinMode(mid, INPUT);
  pinMode(right, INPUT);
}

// 1 = attack left, 2 = attack mid, 3 = attack right
// 4 = defend left, 5 = defend mid, 6 = defend right
// 7 = arduino 2 is defending, 8 = arduino 2 is attacking, 9 = moved=true;


void loop() {
  
  
  c = Serial.read();  // Read incoming command
  if(chooseRole == true){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Arduino Duel");
    delay(2000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Flipping coin...");
    c = Serial.read();  // Read incoming command
    delay(999);
    c = Serial.read();  // Read incoming command
    Serial.println(c);
    
    if(c == '7'){
      lcd.setCursor(3,1);
      lcd.print("You defend");
      role = 999;
      count = 2;
      delay(1000);
      chooseRole = false;
      lcd.clear();
     }

     else if(c == '8'){
       lcd.setCursor(3,1);
       lcd.print("You attack");
       role = 999;
       count = 1;
       delay(1000);
       chooseRole = false;
       lcd.clear();
     }
  }
  
  if(count%2 != 0){attack=true; defend=false;}
  else if(count%2 == 0){attack=false; defend=true;}
  
  if(attack == true && moved == false){ // if count is odd, we attack 
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    lcd.setCursor(4,0);
    lcd.print(hp);
            
    lcd.setCursor(0,1);
    lcd.print("Choose your ATK");
       
    if(digitalRead(left) == HIGH){lcd.clear(); lcd.print("Attacking left"); Serial.write('1'); moved=true; while(left == HIGH){}}
    if(digitalRead(mid) == HIGH){lcd.clear(); lcd.print("Attacking middle"); Serial.write('2'); moved=true; while(mid == HIGH){}}
    if(digitalRead(right) == HIGH){lcd.clear(); lcd.print("Attacking right"); Serial.write('3'); moved=true; while(right == HIGH){}}
  }

  else if(defend == true && moved==false){
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    lcd.setCursor(4,0);
    lcd.print(hp);
            
    lcd.setCursor(0,1);
    lcd.print("Choose your DEF");
       
    if(digitalRead(left) == HIGH){lcd.clear(); lcd.print("Defending left"); Serial.write('4'); moved=true; while(left == HIGH){}}
    if(digitalRead(mid) == HIGH){lcd.clear(); lcd.print("Defending middle"); Serial.write('5'); moved=true; while(mid == HIGH){}}
    if(digitalRead(right) == HIGH){lcd.clear(); lcd.print("Defending right"); Serial.write('6'); moved=true; while(right == HIGH){}}
  }
  //c = Serial.read();  // Read incoming command

  if(c == '1' && defLeft == true && moved == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    lcd.setCursor(4,0);
    lcd.print(hp);
    lcd.setCursor(0,1);
    lcd.print("Parried the ATK!");
  }
  
  else if(c == '1' && defLeft == false && moved == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    hp = hp - (50+random(50, 100));
    lcd.setCursor(4,0);
    lcd.print(hp);
    lcd.setCursor(0,1);
    lcd.print("You've been hit");
  }

  else if(c == '2' && defMid == true && moved == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    lcd.setCursor(4,0);
    lcd.print(hp);
    lcd.setCursor(0,1);
    lcd.print("Parried the ATK!");
  }

  else if(c == '2' && defMid == false && moved == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    hp = hp - (50+random(50, 100));
    lcd.setCursor(4,0);
    lcd.print(hp);
    lcd.setCursor(0,1);
    lcd.print("You've been hit");
  }

  else if(c == '3' && defRight == true && moved == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    lcd.setCursor(4,0);
    lcd.print(hp);
    lcd.setCursor(0,1);
    lcd.print("Parried the ATK!");
  }

  else if(c == '3' && defRight == false && moved == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HP: ");
    hp = hp - (50+random(50, 100));
    lcd.setCursor(4,0);
    lcd.print(hp);
    lcd.setCursor(0,1);
    lcd.print("You've been hit");
  }
      

}
  
void clearDef(){
  defLeft=false;
  defMid=false;
  defRight=false;
}

void increaseCount(){
  count++;
}
  
