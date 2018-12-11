 

#include <Wire.h>
#include "U8glib.h"
/* Create an instance for the SSD1306 OLED display in SPI mode 
 * connection scheme: 
 *   D0=sck=Pin 13 
 *   D1=mosi=Pin 11 
 *   CS=Pin 10 
 *   DC=A0=Pin 9
 *   Reset=Pin 8
 */
U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);
const int geigerPin=2;
const int buzzerPin=5;   // speaker output
const int ledPin=6;
long update=0;
long counts=0;
long previouscounts=0;
long previousUpdate=0;
long Interval=15000;


void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_6x10);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 10, "GEIGER COUNTER");
  u8g.drawStr( 0, 25, "uSv/h = ");
  u8g.setPrintPos(50, 25);
  u8g.print(update * 0.01998);
  u8g.drawStr( 0, 40, "CPM = ");
  u8g.setPrintPos(40, 40);
  u8g.print(update*3);
}

void setup(void) {
  u8g.setColorIndex(1);         // pixel on
  Serial.begin(9600);
  pinMode(geigerPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(geigerPin, HIGH);
  attachInterrupt(0, event, CHANGE);
}

void loop(void) {
  unsigned long currentMilis = millis();
  if (currentMilis - previousUpdate >= 20000) {
  previousUpdate = currentMilis, update = counts - previouscounts, previouscounts = counts;
  float ET = millis();
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  delay(50);
long update=0;
long counts=0;
long previouscounts=0;
long previousUpdate=0;
long Interval=15000;
  }
}

void event() {
  counts++;
  tone(buzzerPin, 4400, 5);
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW); 
}

