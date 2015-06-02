

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
int sens = 0;

unsigned long time1;

// nombre de tours 
volatile long cpt = 0;
//vitesse
volatile int y = 0;


void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(ifred, INPUT);
  pinMode(mt, OUTPUT);

  time1 = millis();

  attachInterrupt (ifred, compte, FALLING);
  
  start_timer_TC1 (ONESEC);

  analogWrite (mt,0);
}


void loop() {

 if ((millis() - time1) > 500) {
    time1 = millis();
    Serial.println(cpt);
    cpt = 0;
  }

 if (y >249) {
   Serial.println("max");
   sens = 1;
 }
 if (y < 11) {
   Serial.println("min");
   sens = 0;
 }

}


void TC3_Handler() {

  TC_GetStatus (TC1,0);


  if (x ==0) {
    SENDLEDHIGH;
    analogWrite (mt,y);
    x = 1;
  }
  else {
    SENDLEDLOW;
    x = 0;
  }

  if (sens == 0) {
    y = (y + 10);
  }
  else {
    y = (y - 10);
  }
  
  

}
  
   
void compte() {
  cpt ++;
}
