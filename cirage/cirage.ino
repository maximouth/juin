#include "timers.h"

// registre pour mettre HIGH sur une broche
#define SENDLEDHIGH (*(( int32_t*)  0x400E1230) =  0x1<<25)
// registre pour mettre LOW sur une broche
#define SENDLEDLOW  (*(( int32_t*)  0x400E1234) =  0x1<<25)

#define ONESEC128 84000000/128

#define DELTA 11

int x = 0;
const int led = 5;
const int ifred = 6;
const int mt = 7;
int sens = 0;
volatile int flag = 0;

unsigned long time1;
unsigned long time2;
volatile int bruit = 0;

// nombre de tours 
volatile long cpt = 0;
//vitesse
volatile int y = 0;


void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(ifred, INPUT_PULLUP);
  pinMode(mt, OUTPUT);

  time1 = millis();

  attachInterrupt (ifred, compte, FALLING);

  analogWrite (mt,100);
}


void loop() {


  if(((millis() - time2) > DELTA) && (bruit == 1)) {
    bruit = 0;
  }


  if ((millis() - time1) > 500) {
    time1 = millis();
    Serial.println(cpt);

    if ((cpt < 5) && (flag == 0)) {
      Serial.println("arret");
      start_timer_TC1 (ONESEC128*2, 0);
      analogWrite (mt,60);
      flag = 1;
    }
    else if ((cpt < 12) && (flag == 0)) {
      Serial.println("fort");
      start_timer_TC1 (ONESEC128*4, 0);
      analogWrite (mt,250);
      SENDLEDHIGH;
      flag = 1;
    }

    cpt = 0;
  }     


}


void TC3_Handler() {
  analogWrite (mt,100);
  SENDLEDLOW;
  flag = 0;
  stop_timer_TC1 (0);
  TC_GetStatus (TC1,0);
}

   
void compte() {

  if (bruit == 0) {
    //Serial.println("compte");
    time2 = millis();
    cpt ++;
    bruit = 1;
  }

}
