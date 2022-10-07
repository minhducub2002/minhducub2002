// include the library code:
#include <LiquidCrystal.h>

const unsigned int TRIG_PIN = 9;
const unsigned int ECHO_PIN = 8;
const unsigned int BAUD_RATE = 9600;

const unsigned int LED_RED = 6;
const unsigned int LED_GREEN = 7;

const unsigned int COI = 10;

unsigned long previousMillis = 0;
const long interval = 1000;
int ledStateRed = LOW;
int ledStateGreen = LOW;
int distance;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // set up cam bien
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(COI, OUTPUT);
}

void loop() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration / 29 / 2;

  //  int ghi = Serial.read();
  //  if (ghi == 'a' || ghi == 'b' || ghi == 'c') {
  //    distance = ghi;
  //  }

  Serial.println(distance);


  Serial.println(distance);
  if (distance < 30) {
    lcd.setCursor(0, 0);
    lcd.print(distance);
    delay(50);
  } else if (distance >= 30 && distance <= 150) {
    lcd.setCursor(0, 0);
    lcd.print(distance);
    delay(50);
  } else if (distance > 150) {
    lcd.setCursor(0, 0);
    lcd.print(distance);
    delay(50);
    lcd.clear();
  }

  unsigned long currentMillis;
  if (distance < 30) {
    ledStateGreen = LOW;
    digitalWrite(LED_GREEN, ledStateGreen);
    currentMillis = millis();
    if (currentMillis - previousMillis >= 200) {
      previousMillis = currentMillis;
      if (ledStateRed == LOW) {
        ledStateRed = HIGH;
      } else {
        ledStateRed = LOW;
      }
      digitalWrite(LED_RED, ledStateRed);
      digitalWrite(COI, ledStateRed);
    }
  } else if (distance >= 30 && distance <= 100) {
    ledStateGreen = LOW;
    digitalWrite(LED_GREEN, ledStateGreen);
    currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      if (ledStateRed == LOW) {
        ledStateRed = HIGH;
      } else {
        ledStateRed = LOW;
      }
      digitalWrite(LED_RED, ledStateRed);
      digitalWrite(COI, ledStateRed);
    }
  } else if (distance > 150) {
    ledStateRed = LOW;
    digitalWrite(LED_RED, ledStateRed);
    digitalWrite(COI, ledStateRed);
    currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      if (ledStateGreen == LOW) {
        ledStateGreen = HIGH;
      } else {
        ledStateGreen = LOW;
      }
      digitalWrite(LED_GREEN, ledStateGreen);
    }
  }

}
