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
int down_degree = 0;          // 0도
int up_degree = 90;           // 90도
int detecting = 20;           // 감지거리[cm]
int state = 0;


void detachServo(int x) {
  delay(450);
  switch (x) {
    case 0:
      Rock.detach();
      break;
    case 1:
      Scissors.detach();
      break;
    case 2:
      Paper.detach();
      break;
    case 3:
      Rock.detach();
      Scissors.detach();
      Paper.detach();
      break;
    default:
      break;
  }
}

void attachServo(int x) {
  switch (x) {
    case 0:
      Rock.attach(rock_motor);
      break;
    case 1:
      Scissors.attach(scissors_motor);
      break;
    case 2:
      Paper.attach(paper_motor);
      break;
    case 3:
      Rock.attach(rock_motor);
      Scissors.attach(scissors_motor);
      Paper.attach(paper_motor);
      break;
    default:
      break;
  }
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
  test.write(up_degree);
  delay(dly);
  test.write(down_degree);
}

int choiceRandom() {
  randomSeed(millis());
  int val = random(0, 3);
  return val;
}

void UpDown(int rock_scissors_paper, int up_down_degree) {
  switch (rock_scissors_paper) {
    case 0:
      Rock.write(up_down_degree);
      break;
    case 1:
      Scissors.write(up_down_degree);
      break;
    case 2:
      Paper.write(up_down_degree);
      break;
    case 3:
      Rock.write(up_down_degree);
      Scissors.write(up_down_degree);
      Paper.write(up_down_degree);
      break;
    default:
      break;
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

  attachServo(3);
  UpDown(3, down_degree);
  detachServo(3);

  Serial.begin(9600);
  Serial.println("Serial start");
}

void loop() {
  if (distance_cm() < detecting) {
    if (state == 0) {
      switch (int nowRandom = choiceRandom()) {
        case 0:
          attachServo(nowRandom);
          UpDown(nowRandom, up_degree);
          delay(2000);
          UpDown(nowRandom, down_degree);
          detachServo(nowRandom);
          break;
        case 1:
          attachServo(nowRandom);
          UpDown(nowRandom, up_degree);
          delay(2000);
          UpDown(nowRandom, down_degree);
          detachServo(nowRandom);
          break;
        case 2:
          attachServo(nowRandom);
          UpDown(nowRandom, up_degree);
          delay(2000);
          UpDown(nowRandom, down_degree);
          detachServo(nowRandom);
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