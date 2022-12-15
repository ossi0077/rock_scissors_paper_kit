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
int dly = 2000; //결과 표시 유지 시간[ms]

Servo Rock, Scissors, Paper;  // servo 객체 지정
int degree0 = 0;              // 0도
int degree90 = 90;            // 90도
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

void Up(int x) {
  switch (x) {
    case 0:
      Rock.write(degree90);
      break;
    case 1:
      Scissors.write(degree90);
      break;
    case 2:
      Paper.write(degree90);
      break;
  }
}

void Down(int x) {
  switch (x) {
    case 0:
      Rock.write(degree0);
      break;
    case 1:
      Scissors.write(degree0);
      break;
    case 2:
      Paper.write(degree0);
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

  Rock.attach(rock_motor);
  Scissors.attach(scissors_motor);
  Paper.attach(paper_motor);
  Rock.write(degree0);
  Scissors.write(degree0);
  Paper.write(degree0);
  Serial.begin(9600);
  Serial.println("Serial start");
}

void loop() {
  int com = choiceRandom(3);
  if (btnChk1() == 1) {  //바위 선택한 경우
    Serial.println("rock btn clicked");
    Up(com);
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
    Down(com);
  } else if (btnChk2() == 1) {
    Serial.println("scissors btn clicked");
    Up(com);
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
    Down(com);
  } else if (btnChk3() == 1) {
    Serial.println("paper btn clicked");
    Up(com);
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
    Down(com);
  }
}
