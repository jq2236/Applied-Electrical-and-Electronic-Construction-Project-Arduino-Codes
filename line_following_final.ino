
// MOTOR PINS 
#define ENA 11
#define IN1 1
#define IN2 2

#define ENB 3
#define IN3 12
#define IN4 13

// IR LINE SENSORS
#define LEFT_SENSOR  A1
#define RIGHT_SENSOR A2

// ENCODERS (UNCHANGED PINS)
#define LEFT_ENCODER  A4   
#define RIGHT_ENCODER A3   

volatile long leftTicks = 0;
volatile long rightTicks = 0;

// ENCODER PARAMETERS
const float PULSES_PER_REV       = 20.0;
const float WHEEL_CIRCUMFERENCE  = 20.73;     // cm per wheel rotation

// LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

volatile uint8_t lastA3 = 0;
volatile uint8_t lastA4 = 0;
int count;

// Timer variables
unsigned long startTime;

// PIN CHANGE INTERRUPT SETUP
void setupEncoders() {
  pinMode(LEFT_ENCODER, INPUT);
  pinMode(RIGHT_ENCODER, INPUT);

  // Enable pin change interrupt for Analog pins A0–A5
  PCICR  |= (1 << PCIE1);

  // Enable interrupts for A3 and A4 only
  PCMSK1 |= (1 << PCINT11);   // A3
  PCMSK1 |= (1 << PCINT12);   // A4

  lastA3 = digitalRead(A3);
  lastA4 = digitalRead(A4);
}


ISR(PCINT1_vect) {
  uint8_t newA3 = digitalRead(A3);
  uint8_t newA4 = digitalRead(A4);

  // Right encoder pulse
  if (newA3 != lastA3 && newA3 == HIGH) {
    rightTicks++;
  }

  // Left encoder pulse
  if (newA4 != lastA4 && newA4 == HIGH) {
    leftTicks++;
  }

  lastA3 = newA3;
  lastA4 = newA4;
}

// CALCULATE DISTANCE & TIME
float getDistanceCM() {
  float avgTicks = (leftTicks + rightTicks) / 2.0;
  return (avgTicks * WHEEL_CIRCUMFERENCE) / PULSES_PER_REV;
}


// MOTOR CONTROL FUNCTIONS
void forward() {
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  // Left wheel backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right wheel forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  // Left wheel forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right wheel backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
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

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // IR sensors
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  // Encoders
  setupEncoders();

  // LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  // Start timer
  startTime = millis();
}

// MAIN LOOP
void loop() {

  int leftVal  = digitalRead(LEFT_SENSOR);
  int rightVal = digitalRead(RIGHT_SENSOR);
  if (count > 5) {
     stopCar(); 
     while(1){

     } 
  }

  //=== LINE FOLLOWING ===
  if (leftVal == LOW && rightVal == HIGH) {
    turnLeft();
  }
  else if (leftVal == HIGH && rightVal == LOW) {
    turnRight();
  }
  else if (leftVal == HIGH && rightVal == HIGH) {
    forward();
  }

  if (leftVal == LOW && rightVal == LOW) {
    count++;
  }
  else{
    count=0;
  }

  // CALCULATE TIMER
  unsigned long currentTime = millis();
  unsigned long elapsedSeconds = (currentTime - startTime) / 1000;

  //=== DISPLAY DISTANCE ===
  float dist = getDistanceCM();

  lcd.setCursor(0, 0);
  lcd.print("Dist:");
  lcd.print(dist);
  lcd.print("cm ");

  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.print(elapsedSeconds);
  lcd.print("s");

 

}
