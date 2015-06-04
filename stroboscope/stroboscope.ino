#include "timers.h"

#define ONESEC128 (84000000/128)
#define DELTA (11)

const int led = 5;
const int ifred = 6;
const int mt = 7;

volatile int cpt = 0;

volatile int sens = 0;

int bruit = 0;

unsigned long time1;
unsigned long time2;

int tour = 34;

int v =250;

void setup() {

  Serial.begin(9600);

  pinMode (led, OUTPUT);
  pinMode (ifred, INPUT_PULLUP);
  pinMode (mt, OUTPUT);

  digitalWrite(5,LOW);

  analogWrite (mt,v);

  start_timer_TC1 (ONESEC128/544,0);

  attachInterrupt (ifred, compte, FALLING);
}


void loop() {


  if ((millis() - time1) > 500) {
    time1 = millis();
    //   Serial.print(cpt);
    Serial.println(cpt);
    analogWrite (mt, v + (PID(cpt)));
    cpt = 0;
  }     


}


void TC3_Handler() {
  

  TC_GetStatus (TC1,0);

  if (sens == 0) {

    digitalWrite(5,HIGH);
    sens ++;
  }
  else {
    digitalWrite(5,LOW);
    sens = (sens +1) %16;
      }

}


void compte() {


  if(((millis() - time2) > DELTA) && (bruit == 1)) {
    bruit = 0;
  }
  if (bruit == 0) {
    //Serial.println("compte");
    time2 = millis();
    cpt ++;
    bruit = 1;
  }
}

float KE = 1/tour;
float KD = 0.05;
float KI = -0.7;
int prevErr = 0;
int somme = 0;

float PID(int cpt) {

  int err = (cpt-tour);
  somme += err;

  float pid = ( (err*KE) + ((KD/0.5)*(err-prevErr)) + (KI*0.5*(somme))); 

  prevErr = err;
  
  return pid;

}
