/*
사용 부품
- 아두이노 나노
- 신호등 LED 모듈
- 버튼 3개
- 서보모터 3개
*/
#include <Servo.h>

// 각 모터별 핀번호
int rock_motor = 10;
int scissors_motor = 11;
int paper_motor = 12;

// 버튼 핀번호
int rock_btn = 2;
int scissors_btn = 3;
int paper_btn = 4;

// LED  핀번호
int red = 6;
int yellow = 7;
int green = 8;
int dly = 2000;  //결과 표시 유지 시간[ms]

Servo Rock, Scissors, Paper;  // servo 객체 지정
int down_degree = 0;          // 0도
int up_degree = 90;           // 90도
int state = 0;

int btnFlg1 = 0;
int btnChk1() {
  if (digitalRead(rock_btn) == 0) {
    btnFlg1 = 1;
    return 0;
  }
  if (btnFlg1 == 1) {
    btnFlg1 = 0;
    return 1;
  }
  return 0;
}

int btnFlg2 = 0;
int btnChk2() {
  if (digitalRead(scissors_btn) == 0) {
    btnFlg2 = 1;
    return 0;
  }
  if (btnFlg2 == 1) {
    btnFlg2 = 0;
    return 1;
  }
  return 0;
}

int btnFlg3 = 0;
int btnChk3() {
  if (digitalRead(paper_btn) == 0) {
    btnFlg3 = 1;
    return 0;
  }
  if (btnFlg3 == 1) {
    btnFlg3 = 0;
    return 1;
  }
  return 0;
}

int choiceRandom(int x) {
  randomSeed(millis());
  int val = random(0, x);
  return val;
}

void UpDown(int x, int y) {
  switch (x) {
    case 0:
      Rock.write(y);
      break;
    case 1:
      Scissors.write(y);
      break;
    case 2:
      Paper.write(y);
      break;
    case 3:
      Rock.write(y);
      Scissors.write(y);
      Paper.write(y);
      break;
    default:
      break;
  }
}

void winLoseLED(int x) {
  switch (x) {
    case 0:  //비긴 경우
      digitalWrite(yellow, HIGH);
      delay(dly);
      digitalWrite(yellow, LOW);
      break;
    case 1:  //이긴 경우
      digitalWrite(green, HIGH);
      delay(dly);
      digitalWrite(green, LOW);
      break;
    case 2:  //진 경우
      digitalWrite(red, HIGH);
      delay(dly);
      digitalWrite(red, LOW);
      break;
  }
}

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

void setup() {
  pinMode(rock_btn, INPUT_PULLUP);
  pinMode(scissors_btn, INPUT_PULLUP);
  pinMode(paper_btn, INPUT_PULLUP);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  attachServo(3);
  UpDown(3, down_degree);
  detachServo(3);

  Serial.begin(9600);
  Serial.println("Serial start");
}

void loop() {
  int com = choiceRandom(3);
  if (btnChk1() == 1) {  //바위 선택한 경우
    attachServo(com);
    Serial.println("rock btn clicked");
    UpDown(com, up_degree);
    switch (com) {
      case 0:  // 비긴 경우
        Serial.println("Draw");
        winLoseLED(0);
        break;
      case 1:  // 이긴 경우
        Serial.println("Win");
        winLoseLED(1);
        break;
      case 2:  // 진 경우
        Serial.println("Lose");
        winLoseLED(2);
        break;
    }
    UpDown(com, down_degree);
    detachServo(com);
  } else if (btnChk2() == 1) {
    attachServo(com);
    Serial.println("scissors btn clicked");
    UpDown(com, up_degree);
    switch (com) {
      case 0:  // 진 경우
        Serial.println("Lose");
        winLoseLED(2);
        break;
      case 1:  // 비긴 경우
        Serial.println("Draw");
        winLoseLED(0);
        break;
      case 2:  // 이긴 경우
        Serial.println("Win");
        winLoseLED(1);
        break;
    }
    UpDown(com, down_degree);
    detachServo(com);
  } else if (btnChk3() == 1) {
    attachServo(com);
    Serial.println("paper btn clicked");
    UpDown(com, up_degree);
    switch (com) {
      case 0:  // 이긴 경우
        Serial.println("Win");
        winLoseLED(1);
        break;
      case 1:  // 진 경우
        Serial.println("Lose");
        winLoseLED(2);
        break;
      case 2:  // 비긴 경우
        Serial.println("Draw");
        winLoseLED(0);
        break;
    }
    UpDown(com, down_degree);
    detachServo(com);
  }
}
