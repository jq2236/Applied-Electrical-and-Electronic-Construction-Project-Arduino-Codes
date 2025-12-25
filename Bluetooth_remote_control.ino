#include <SoftwareSerial.h>

// HC-05 BLUETOOTH ON ANALOG PINS
// A1 = digital pin 15
// A2 = digital pin 16
SoftwareSerial BT(15, 16);  
// RX = 15 (A1)
// TX = 16 (A2)

// MOTOR PINS (your exact pins)
#define ENA 11
#define IN1 1
#define IN2 2

#define ENB 3
#define IN3 12
#define IN4 13

// MOTOR CONTROL FUNCTIONS
void forward() {
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() { 
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() { 
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// SETUP
void setup() {
  BT.begin(9600);   
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();

  Serial.println("Bluetooth Robot READY!");
}

// MAIN LOOP
void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    Serial.print("CMD: ");
    Serial.println(cmd);

    switch (cmd) {
      case 'F': forward();  break;
      case 'B': backward(); break;
      case 'R': turnLeft(); break;
      case 'L': turnRight(); break;
      default: stopCar(); 
    }
  }
}
