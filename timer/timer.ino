#include "timer1.h"

// registre pour mettre HIGH sur une broche
#define SENDLEDHIGH (*(( int32_t*)  0x400E1230) =  0x1<<25)
// registre pour mettre LOW sur une broche
#define SENDLEDLOW  (*(( int32_t*)  0x400E1234) =  0x1<<25)

#define ONESEC 84000000/128


int x = 0;
const int led = 5;
const int ifred = 6;
const int mt = 7;

unsigned long time1;

volatile long cpt = 0;


void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(ifred, INPUT);
  pinMode(mt, OUTPUT);

  time1 = millis();

  attachInterrupt (ifred, compte, FALLING);
  
  start_timer_TC1 (ONESEC);
}


void loop() {

}


void TC3_Handler() {

  cpt = 0;
  
  if (x ==0) {
    SENDLEDHIGH;
    analogWrite (mt,200);
    x = 1;
  }
  else {
    SENDLEDLOW;
    analogWrite (mt,0);
    x = 0;
  }
  TC_GetStatus (TC1,0);

}
  
   
void compte() {
  cpt ++;
}
