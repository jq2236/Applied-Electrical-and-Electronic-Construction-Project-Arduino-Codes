#include <LiquidCrystal.h>
int counter=0;
LiquidCrystal lcd_1(8,9,4,5,6,7);
int ENA = 11;   
int IN1 = 1;
int IN2 = 2;

int ENB = 12;   
int IN3 = 3;
int IN4 = 13;

int LIR = A1;
int RIR = A2;

// --- Setup ---
void setup() {
  lcd_1.begin(16,2);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


}

void loop() {

  while(counter !=10){
  moveForward(); 
  delay(1000);
  lcd_1.setCursor(0,0);
  lcd_1.print("Time moving:");
  lcd_1.setCursor(0,1);
  counter=counter+1;
  lcd_1.print(counter);
  }
  stop();
}


void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA,130);
  analogWrite(ENB,130);
  
  

  
}
void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA,0);
  analogWrite(ENB,0);
}
