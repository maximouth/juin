#include "timers.h"

#define LED1 (53)
#define LED2 (49)
#define LED3 (45)
#define LED4 (40)
#define LED5 (37)
#define LED6 (33)

#define BT1 (30)
#define BT2 (26)

#define DELTA (200)

#define ONESEC128 (84000000/128)

volatile int cpt = 0;

unsigned long time1;
unsigned long time2;
unsigned long time3;

int bouton = 0;

int bruit = 0;
int bruit2 = 0;

void setup() {

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);

  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);

  attachInterrupt(BT1, lancement, CHANGE);
  attachInterrupt(BT2, compte, CHANGE);


  Serial.begin(9600);


  digitalWrite(LED1,LOW); 
  digitalWrite(LED2,LOW); 
  digitalWrite(LED3,LOW); 
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW); 
  digitalWrite(LED6,LOW); 


}


void loop() {

  if ((bouton == 1) && ((millis() - time3) > 8000)) {
    if (cpt > 32) {
      cpt = 32;
    }
    decompte (cpt);
    cpt = 0;
    bouton = 0;
  }



}


void compte() {


  if(((millis() - time2) > DELTA) && (bruit == 1)) {
    bruit = 0;
  }
  if (bruit == 0) {
    time2 = millis();
    cpt ++;
    bruit = 1;
    Serial.println("compte");
  }
}

 void lancement() {


  if(((millis() - time1) > DELTA) && (bruit2 == 1)) {
    bruit2 = 0;
  }
  if (bruit2 == 0) {
    cpt = 0;
    time1 = millis();
    bouton = 1;
    time3 = millis();
    Serial.println("lance");
    bruit2 = 1;
  }

 }
 





void decompte(int cpt) {
  Serial.println(cpt);
  if (cpt == 0 ) {
    digitalWrite(LED1, LOW);
    return;
  }

  int l1 = (cpt & 0b1);
  int l2 = (cpt & 0b10);
  int l3 = (cpt & 0b100);
  int l4 = (cpt & 0b1000);
  int l5 = (cpt & 0b10000);
  int l6 = (cpt & 0b100000);

  digitalWrite(LED1, l1);
  digitalWrite(LED2, l2);
  digitalWrite(LED3, l3);
  digitalWrite(LED4, l4);
  digitalWrite(LED5, l5);
  digitalWrite(LED6, l6);
    
  delay(750);

  decompte (cpt-1);

}
