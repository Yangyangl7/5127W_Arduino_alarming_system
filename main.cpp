#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//defines pins numbers
const int servoPin = 8;
const int trigPin = 9;
const int echoPin = 10;
//defines variables
int pos = 0;
//defines servo
Servo myservo;

void setup() {
  //Sets the trigPin as an Output
  pinMode(trigPin, OUTPUT);
  //Sets the echoPin as an Input
  pinMode(echoPin, INPUT); 
  //Sets digital pin lED_BUTLINT as an output
  pinMode(LED_BUILTIN, OUTPUT); 
  //Attache pin number to servo
  myservo.attach(servoPin);
  
  lcd.begin(16, 2 );
  //Set LCD cursor to upper left corner, column 0, row 0
  lcd.setCursor(0,0);  
  //Print Message on First Row
  lcd.print("Target Distance:");  
}

void loop() {
  //Servo scan range from 15 to 165 angle
  for (pos = 15; pos <= 165; pos += 15) {
    myservo.write(pos);               
    delay(200);                      
    printOut();
  }
  for (pos = 165; pos >= 15; pos -= 15) { 
    myservo.write(pos);               
    delay(200);                       
    printOut();
  }
}

int distance() {
   long duration, distance;
   
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;

  return distance;  
}

void printOut() {
  long dis = distance();
  if (dis < 10) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (dis >= 10) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  lcd.setCursor(0, 1);
  //Print blanks to clear the row
  lcd.print("                ");
  //Set Cursor again to first column of second row
  lcd.setCursor(0,1);
  //Print measured distance
  lcd.print(dis); 
  //Print your units.
  lcd.print(" cm");
  //pause to let things settle  
  delay(250);
}
