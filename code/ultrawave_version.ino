//초음파 센서 세로로 설치해야 보자기 낼때 인식이 잘됨
#include <Servo.h>

// 각 모터별 핀번호
int rock = 10;
int scissors = 11;
int paper = 12;

// 초음파 센서 핀번호
int trigPin = 3;
int echoPin = 4;

Servo Rock, Scissors, Paper;  // servo 객체 지정
double pulseTime;             // 초음파 센서 사용을 위한 변수
int degree0 = 0;              // 0도
int degree90 = 90;            // 90도
int detecting = 20;           // 감지거리[cm]
int state = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  Rock.attach(rock);
  Scissors.attach(scissors);
  Paper.attach(paper);
  Rock.write(degree0);
  Scissors.write(degree0);
  Paper.write(degree0);
  Serial.begin(9600);
  Serial.println("Serial start");
}

double distance_cm() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pulseTime = pulseIn(echoPin, HIGH);
  double distance_cm = pulseTime * 17 / 1000;
  return distance_cm;
}

void motorFunc(Servo test, int dly) {
  test.write(degree90);
  delay(dly);
  test.write(degree0);
}

int choiceRandom() {
  randomSeed(millis());
  int val = random(0, 3);
  return val;
}

void loop() {
  if (distance_cm() < detecting) {
    if (state == 0) {
      switch (choiceRandom()) {
        case 0:
          motorFunc(Rock, 2000);
          break;
        case 1:
          motorFunc(Scissors, 2000);
          break;
        case 2:
          motorFunc(Paper, 2000);
          break;
      }
      state = 1;
    } else if (state == 1) {
      return;
    }
  } else if (distance_cm() >= detecting) {
    if (state == 1) state = 0;
    else return;
  }
}