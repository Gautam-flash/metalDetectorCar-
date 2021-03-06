#include <NewPing.h>
#include <SoftwareSerial.h>

#define RIGHT_FRONT_1 4
#define RIGHT_FRONT_2 5

#define RIGHT_BACK_1 A4
#define RIGHT_BACK_2 A3

#define LEFT_FRONT_1 6
#define LEFT_FRONT_2 7

#define LEFT_BACK_1 A2
#define LEFT_BACK_2 A1

#define RIGHT_TRIG 9
#define RIGHT_ECHO 10
#define RIGHT_SONAR_VCC 8

#define LEFT_TRIG 12
#define LEFT_ECHO 13
#define LEFT_SONAR_VCC 11

#define rx 3
#define tx 2

#define MAX_DISTANCE 200

#define metal_input A5

NewPing RIGHT_SONAR(RIGHT_TRIG, RIGHT_ECHO, MAX_DISTANCE);
NewPing LEFT_SONAR(LEFT_TRIG, LEFT_ECHO, MAX_DISTANCE);
SoftwareSerial BTserial(rx, tx);

String commands;
bool BTstop = false;
char current_command;
int rightSonarSumm;
int leftSonarSumm;

void setup(){
  pinMode(metal_input, INPUT);
  
  pinMode(RIGHT_FRONT_1, OUTPUT);
  pinMode(RIGHT_FRONT_2, OUTPUT);
   
  pinMode(RIGHT_BACK_1, OUTPUT);
  pinMode(RIGHT_BACK_2, OUTPUT);

  pinMode(LEFT_FRONT_1, OUTPUT);
  pinMode(LEFT_FRONT_2, OUTPUT);

  pinMode(LEFT_BACK_1, OUTPUT);
  pinMode(LEFT_BACK_2, OUTPUT);
  
  pinMode(LEFT_SONAR_VCC, OUTPUT);
  pinMode(RIGHT_SONAR_VCC, OUTPUT);
  
  digitalWrite(RIGHT_SONAR_VCC, HIGH);//power for right sonar
  digitalWrite(LEFT_SONAR_VCC, HIGH);//power for left sonar
  
  Serial.begin(9600);
  BTserial.begin(9600);

  while(!BTserial){};
  while(!Serial){};
}

void loop(){
  read_commands();
}

void mdFeedback(){
  while(BTserial){};
    BTserial.println(analogRead(metal_input));
  
}

byte getLeftUS(){
  leftSonarSumm = 0;
  for(byte i = 0; i < 10; i++){
    leftSonarSumm += LEFT_SONAR.ping_cm(); 
  }
  return leftSonarSumm / 10;
}

byte getRightUS(){
  rightSonarSumm = 0;
  for(byte i = 0; i < 10; i++){
    rightSonarSumm += RIGHT_SONAR.ping_cm(); 
  }
  return rightSonarSumm / 10;
}

void read_commands(){
  while (BTstop == false){
    while (BTserial.available() > 0){
      current_command = BTserial.read();
      if (current_command != 's')
        commands += current_command;
      else
        BTstop = true;
    }
  }
}

//needs a fix
void right(){
  digitalWrite(RIGHT_FRONT_1, HIGH); 
  digitalWrite(RIGHT_FRONT_2, LOW);

  digitalWrite(RIGHT_BACK_1, HIGH);
  digitalWrite(RIGHT_BACK_2, LOW);

  digitalWrite(LEFT_FRONT_1, LOW);
  digitalWrite(LEFT_FRONT_2, HIGH);

  digitalWrite(LEFT_BACK_1, LOW);
  digitalWrite(LEFT_BACK_2, HIGH);
}

void left(){
  digitalWrite(RIGHT_FRONT_1, HIGH); 
  digitalWrite(RIGHT_FRONT_2, LOW);

  digitalWrite(RIGHT_BACK_1, HIGH);
  digitalWrite(RIGHT_BACK_2, LOW);

  digitalWrite(LEFT_FRONT_1, LOW);
  digitalWrite(LEFT_FRONT_2, HIGH);

  digitalWrite(LEFT_BACK_1, LOW);
  digitalWrite(LEFT_BACK_2, HIGH);
}

void forward(){
  digitalWrite(RIGHT_FRONT_1, HIGH); 
  digitalWrite(RIGHT_FRONT_2, LOW);

  digitalWrite(RIGHT_BACK_1, HIGH);
  digitalWrite(RIGHT_BACK_2, LOW);

  digitalWrite(LEFT_FRONT_1, LOW);
  digitalWrite(LEFT_FRONT_2, HIGH);

  digitalWrite(LEFT_BACK_1, LOW);
  digitalWrite(LEFT_BACK_2, HIGH);
}

void back(){
  digitalWrite(RIGHT_FRONT_1, HIGH); 
  digitalWrite(RIGHT_FRONT_2, LOW);

  digitalWrite(RIGHT_BACK_1, HIGH);
  digitalWrite(RIGHT_BACK_2, LOW);

  digitalWrite(LEFT_FRONT_1, LOW);
  digitalWrite(LEFT_FRONT_2, HIGH);

  digitalWrite(LEFT_BACK_1, LOW);
  digitalWrite(LEFT_BACK_2, HIGH);
}

void stopCar(){

  digitalWrite(RIGHT_FRONT_1, LOW); 
  digitalWrite(RIGHT_FRONT_2, LOW);

  digitalWrite(RIGHT_BACK_1, LOW);
  digitalWrite(RIGHT_BACK_2, LOW);

  digitalWrite(LEFT_FRONT_1, LOW);
  digitalWrite(LEFT_FRONT_2, LOW);

  digitalWrite(LEFT_BACK_1, LOW);
  digitalWrite(LEFT_BACK_2, LOW);

}
