#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_MOSI  11   //D1
#define OLED_CLK   13   //D0
#define OLED_DC    9
#define OLED_CS    10
#define OLED_RESET 8
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
const int geigerPin=2;
const int buzzerPin=5;   // speaker output
const int ledPin=6;
long update=0;
long counts=0;
long previouscounts=0;
long previousUpdate=0;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  pinMode(geigerPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(geigerPin, HIGH);
  attachInterrupt(0, event, CHANGE);
  display.clearDisplay();
  display.setCursor(10,8);
  display.println("uSv/h = ");
  display.setCursor(10,18);	
  display.println("CPM = ");
}

void loop() {
  unsigned long currentMilis = millis();
  if (currentMilis - previousUpdate >= 10000) {
    previousUpdate = currentMilis, update = counts - previouscounts, previouscounts = counts;
    float ET = millis();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.setCursor(10,8);
    display.println("uSv/h = ");
    display.setCursor(58,8);
    display.println(update * 0.01998);
    display.setCursor(10,18);	
    display.println("CPM = ");
    display.setCursor(50,18);	
    display.println(update * 6);
    display.display();
  }
}

void event() {
  counts++;
  tone(buzzerPin, 4400, 5);
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);  
}

