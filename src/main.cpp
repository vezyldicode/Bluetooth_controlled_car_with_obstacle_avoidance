// Created by Tuan Viet Nguyen
// Date 14.08.2022




#include <Arduino.h>
#include <NewPing.h>

//L298N pins 
const int ENA = 5; // dieu khien toc do motor trai;
const int INA = 9; // chan am ben trai;
const int INB = 8; // chan duong ben trai;
const int INC = 7; // chan am ben phai;
const int IND = 6; // chan duong ben phai;
const int ENB = 10; // dieu khien toc do motor phai;

int val; // nhan gia tri tu dien thoai
int speed = 100; // toc do cua xe

int cm = 0;
int duration = 0; // khoang thoi gian thu phat tin hieu cua cam bien
int iterations = 2; // so lan do
int leftdis = 0; // khoang cach ben trai
int rightdis = 0; // khoang cach ben phai
int middis = 0; // khoang cach o giua
int mindis = 25; // gia tri khoang cach toi thieu

//sensor pins
#define trig1 A0 // analog 0 chan trig cam bien ben trai
#define echo1 A1 // analog 1 chan echo cam bien ben trai
#define trig2 A2 // analog 2 chan trig cam bien o giua
#define echo2 A3 // analog 3 chan echo cam bien o giua
#define trig3 A4 // analog 4 chan trig cam bien ben phai
#define echo3 A5 // analog 5 chan echo cam bien ben phai
#define maxDistance 400

boolean goForward = false;

NewPing sonar1(trig1, echo1, maxDistance); //chuc nang cam bien ben trai
NewPing sonar2(trig2, echo2, maxDistance); //chuc nang cam bien o giua
NewPing sonar3(trig3, echo3, maxDistance); //chuc nang cam bien ben phai

//ham doc cam bien ben trai
int readPingL()
{
  delay(10);
  duration = sonar1.ping_median(iterations);
  cm = (duration/2)*0.0343;
  if(cm>=400)
  {
    cm = 400;
  }
  if (cm<=2)
  {
    cm = 400;
  }
  return cm;
}

//ham doc cam bien ben phai
int readPingR()
{
  delay(10);
  duration = sonar3.ping_median(iterations);
  cm = (duration/2)*0.0343;
  if(cm>=400)
  {
    cm = 400;
  }
  if (cm<=2)
  {
    cm = 400;
  }
  return cm;
}

//ham doc cam bien o giua
int readPingM()
{
  delay(10);
  duration = sonar2.ping_median(iterations);
  cm = (duration/2)*0.0343;
  if(cm>=400)
  {
    cm = 400;
  }
  if (cm<=2)
  {
    cm = 400;
  }
  return cm;
}

void forward()                                                                                 // TIEN LEN
{
  if(!goForward)
  {
    goForward = true;
    Serial.println("Forward");
    Serial.println("");
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);  
    digitalWrite(INC, HIGH);
    digitalWrite(IND, LOW);
  }
}

void backward()                                                                                 // LUI LAI
{
  goForward = false;
  Serial.println("Backward");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);
}

void left()                                                                                     // RE TRAI
{
  goForward = false;
  Serial.println("TURN LEFT");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);
}

void right()                                                                                     // RE PHAI
{
  goForward = false;
  Serial.println("Forward");
  Serial.println("");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);
}

void forwardRight()                                                                              // TIEN LEN BEN PHAI
{
  goForward = false;
  Serial.println("Forward Right");
  Serial.println("");
  analogWrite(ENA,speed-20);
  analogWrite(ENB,speed-20);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);
}

void forwardLeft()                                                                               // TIEN LEN BEN TRAI
{
  goForward = false;
  Serial.println("forward Left");
  Serial.println("");
  analogWrite(ENA, speed-20);
  analogWrite(ENB, speed-20);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);
}

void backwardRight()                                                                            // LUI LAI BEN PHAI
{
  goForward = false;
  Serial.println("Backward Right");
  Serial.println("");
  analogWrite(ENA,speed-20);
  analogWrite(ENB,speed-20);
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);
}

void backwardLeft()                                                                            // LUI LAI BEN TRAI
{
  goForward = false;
  Serial.println("Backward Left");
  Serial.println("");
  analogWrite(ENA,speed-20);
  analogWrite(ENB,speed-20);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);
}

void stop()                                                                                    //DUNG XE
{
  goForward = false;
  Serial.println("Stop");
  Serial.println("");
  analogWrite(ENA,LOW);
  analogWrite(ENB,LOW);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);  
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);
}


void setup()
{
  Serial.begin(9600);
  //khai bao sensor
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  //khai bao L298N
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INC, OUTPUT);
  pinMode(IND, OUTPUT);
  stop();
  delay(100);
}


void loop()
{
  // do khoang cach 3 huong
  leftdis = readPingL();
  rightdis = readPingR();
  middis = readPingM();
  Serial.print("Khoang cach ben trai la: ");
  Serial.print(leftdis);
  Serial.print("Khoang cach ben phai la: ");
  Serial.print(rightdis);
  Serial.print("Khoang cach o giua la: ");
  Serial.print(middis);

  if ((leftdis <= mindis) || (rightdis <= mindis) || (middis <= mindis))
  {
    goForward = false;
    stop();
    delay(100);
  }
  while (Serial.available() > 0)
  {
    val = Serial.read(); // in gia tri dien thoai len serial
    Serial.println(val);
    Serial.println("");
    switch (val) // kiem tra cac gia tri tu dien thoai
    {
      case 'F': if ((leftdis >= mindis) && (middis >= mindis) && (rightdis >= mindis)) {forward();}; break;
      case 'B':backward(); break;
      case 'L':left(); break;
      case 'R':right(); break;
      case 'I':forwardRight(); break;
      case 'G':forwardLeft(); break;
      case 'J':backwardRight(); break;
      case 'H':backwardLeft(); break;
      case 'S':stop(); break;
      case '0': speed = 0; break;
      case '1': speed = 25.5; break;
      case '2': speed = 51; break;
      case '3': speed = 76.5; break;
      case '4': speed = 102; break;
      case '5': speed = 127.5; break;
      case '6': speed = 153; break;
      case '7': speed = 178.5; break;
      case '8': speed = 204; break;
      case '9': speed = 229.5; break;
      case 'q': speed = 255; break;   
    }
  }
}


