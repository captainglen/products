#include <Wire.h>
#include <SPI.h>
#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9, 8);

const int geigerPin=2;
const int buzzerPin=5;   // speaker output
const int ledPin=6;
long update=0;
long counts=0;
long previouscounts=0;
long previousUpdate=0;

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 10, "GEIGER COUNTER");
  u8g.drawStr( 0, 32, "uSv/h");
  u8g.setPrintPos(55, 32);
  u8g.print(update * 0.01998);
  u8g.drawStr( 0, 54, "CPM ");
  u8g.setPrintPos(55, 54);
  u8g.print(update * 6); //Decrease multiplication factor to 60000/update rate in miliseconds eg. 60000/15000=4 15 sec update.
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // assign default color value
  u8g.setColorIndex(1);
  pinMode(geigerPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(geigerPin, HIGH);
  attachInterrupt(0, event, CHANGE);
}

void loop() {
  unsigned long currentMilis = millis();
  if (currentMilis - previousUpdate >= 10000) { //increase update rate (10000) for more stable display for more accurate dose.
    previousUpdate = currentMilis, update = counts - previouscounts, previouscounts = counts;
    float ET = millis();	
u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(50);
  }
}
void event() {
  counts++;
  tone(buzzerPin, 4400, 5);
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);  
}
