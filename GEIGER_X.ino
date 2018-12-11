#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);

const int geigerPin=2;
const int buzzerPin=5;   // speaker output
const int ledPin=9;
long update=0;
long counts=0;
long previouscounts=0;
long previousUpdate=0;
long Interval=15000;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  pinMode(geigerPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
 
  digitalWrite(geigerPin, HIGH);
  attachInterrupt(0, event, CHANGE);
}

void loop() {
  unsigned long currentMilis = millis();
  if (currentMilis - previousUpdate >= 20000) { //change for desired screen update rate in milliseconds
    previousUpdate = currentMilis, update = counts - previouscounts, previouscounts = counts;
    float ET = millis();	
    lcd.clear();
    lcd.print("uSv/h");
    lcd.setCursor(8,0);
    lcd.print(update * 0.01998);
    lcd.setCursor(0,1);
    lcd.print("CPM ");
    lcd.setCursor(8,1);
    lcd.print(update * 3); //change to 60,000/ desired update rate in milliseconds
  }
}

void event() {
  counts++;
  tone(buzzerPin, 4400, 5);
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);  
}

