#include<SoftwareSerial.h>
#define STOP_FRONT 12 // датчик остановки 1
#define MOTOR_1A 11   // Connect motor driver input 1 to pin 11
#define MOTOR_1B 10   // Connect motor driver input 2 to pin 10
#define MOTOR_2A 9     // Connect motor driver input 3 to pin 9
#define MOTOR_2B 6     // Connect motor driver input 4 to pin 6
#define TX 2                 // Connect Bluetooth module Tx to pin 2
#define RX 3                 // Connect Bluetooth module Rx to pin 3

SoftwareSerial BTmodule(TX, RX);
int speed = 45;   // основная скорость
int speedback = 45;   // скорость для разворота

void setup() {

  // Пины D3 и D11 - 8 кГц
 //TCCR2B = 0b00000010;  // x8
 //TCCR2A = 0b00000011;  // fast pwm

  Serial.begin(9600);
  BTmodule.begin(9600);
  BTmodule.setTimeout(10);
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, INPUT); 
  pinMode(MOTOR_2A, OUTPUT);
  pinMode(MOTOR_2B, INPUT);
  pinMode(STOP_FRONT, OUTPUT); 
}

void loop() {
  String readString;
  
  while(BTmodule.available()) {
    readString = BTmodule.readString();
    Serial.print("Received: ");
    Serial.println(readString);
  }

//Stop car when connection lost or bluetooth disconnected
   //if(digitalRead(BTState)==LOW)
   //{readString == "n";}
  
  
  // увеличиваем значение
 // if(ButtonA == pressed) 
 // counter++; 
//else if(ButtonB == pressed) 
//  counter--;

//if(readString == "A")//прибавляем скорость
//{speed++;}
//else if(readString == "B")//уменьшаем скорость
//{speed--;}

//int stopline = analogRead(STOP_FRONT); // датчик приближения 1
 //   if (stopline > 0){
 //     speed == 40;
 //   }
//int stopline2 = analogRead(STOP_BACK); // датчик приближения 2
//    if (stopline > 0){
 //     speedback == 40;
 //   }
  
  // FORWARD + SPEED
  if(readString == "a"){
    speed++;
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_2A, speed);
    pinMode(STOP_FRONT, INPUT);
  }
  // BACKWARD SPEED                                                                                    
  if(readString == "c"){
    speed--;
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_2A, speed);
    pinMode(STOP_FRONT, INPUT);
  }
     
  // BACKWARD 
                                                                                   
  if(readString == "k"){
    speed++;
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_1B, HIGH);
    analogWrite(MOTOR_2A, speed);
    analogWrite(MOTOR_2B, HIGH);
    pinMode(STOP_FRONT, INPUT);
    
  }
  
  // LEFT
  if(readString == "d"){
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_2A, (speed + (speed / 100) * 40));
  }
                                                                                       // RIGHT
  if(readString == "e"){
    analogWrite(MOTOR_1A, (speed + (speed / 100) * 40));
    analogWrite(MOTOR_2A, speed);
  }
// поворот по часовой  стрелке
  if(readString == "m"){
    speed++;
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_2A, speed);
    analogWrite(MOTOR_2B, HIGH);
    pinMode(STOP_FRONT, INPUT);
  }

  // поворот против часовой  стрелке
  if(readString == "l"){
    speed++;
    analogWrite(MOTOR_2A, speed);
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_1B, HIGH);
    pinMode(STOP_FRONT, INPUT);
  }
                                                                                       // STOP
  if(readString == "n"){
    speed = 45;
    speedback = 45;
    analogWrite(MOTOR_1A, 0);
    pinMode(MOTOR_1B, INPUT);
    analogWrite(MOTOR_2A, 0);
    pinMode(MOTOR_2B, INPUT);
    pinMode(STOP_FRONT, OUTPUT);
  }
                                                                                       

}
