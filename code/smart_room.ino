#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4 // dht11 sensor
#define DHTTYPE DHT11
#define FAN_PIN 9
#define IR1 2 // entry trigger
#define IR2 3 // exit trigger

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // i2c address -> 0x27

int peopleCount = 0;

int state = 0;
// 0 = idle
// 1 = IR1 triggered first → ENTER
// 2 = IR2 triggered first → EXIT

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(FAN_PIN, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(1000);
}

void loop() {
  int ir1 = digitalRead(IR1);
  int ir2 = digitalRead(IR2);

  // ----------- PEOPLE COUNTING -----------
  if (state == 0) {
    if (ir1 == LOW) {
      state = 1;  // IR1 first → ENTER
      Serial.println("IR1 first");
    } else if (ir2 == LOW) {
      state = 2;  // IR2 first → EXIT
      Serial.println("IR2 first");
    }
  }

  // ENTER
  if (state == 1 && ir2 == LOW) {
    peopleCount++;
    Serial.print("ENTER → Count = ");
    Serial.println(peopleCount);
    state = 0;
    delay(500);
  }

  // EXIT
  if (state == 2 && ir1 == LOW) {
    peopleCount--;
    if (peopleCount < 0) peopleCount = 0;
    Serial.print("EXIT → Count = ");
    Serial.println(peopleCount);
    state = 0;
    delay(500);
  }

  // ----------- TEMPERATURE READING ----------
  float temp = dht.readTemperature();

  if (!isnan(temp)) {
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print("°C  | People: ");
    Serial.println(peopleCount);
  }

  // ----------- FAN CONTROL ----------
  int fanSpeed = 0;

  if (peopleCount > 0) {  // Only run fan if people are inside
    if (temp >= 25 && temp < 26) fanSpeed = 90;
    else if (temp >= 26 && temp < 27) fanSpeed = 130;
    else if (temp >= 27 && temp < 28) fanSpeed = 180;
    else if (temp >= 28) fanSpeed = 255;
    else fanSpeed = 0;  // below 25°C → OFF
  } else {
    fanSpeed = 0;  // no one in room → fan OFF
  }

  analogWrite(FAN_PIN, fanSpeed);


  // ----------- LCD DISPLAY ----------
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("People:");
  lcd.print(peopleCount);

  delay(300);
}