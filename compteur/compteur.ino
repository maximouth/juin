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

    if (cpt < 1) {
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
 digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW); 
  digitalWrite(LED6,LOW); 

      return;
    }
    else {
      switch (cpt) {
      case 1 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(0);
	break;
      case 2 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(1);
	break;
      case 3 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(2);
	break;
      case 4 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return
	decompte(3);
	break;
      case 5 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(4);
	break;
      case 6 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(5);
	break;
      case 7 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(6);
	break;
 case 8 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(7);
	break;
 case 9 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(8);
	break;
 case 10 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(9);
	break;
 case 11 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(10);
	break;
 case 12 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(11);
	break;
 case 13 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(12);
	break;
 case 14 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(13);
	break;
 case 15 :
       digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(14);
	break;
 case 16 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,LOW); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(15);
	break;
 case 17 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(16);
	break;
 case 18 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(17);
	break;
 case 19 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(18);
	break;
 case 20 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(19);
	break;
 case 21 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(20);
	break;
 case 22 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(21);
	break;
 case 23 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(22);
	break;
 case 24 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,LOW);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(23);
	break;
 case 25 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(24);
	break;
 case 26 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(25);
	break;
 case 27 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4, HIGH);
	digitalWrite(LED5, HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(26);
	break;
 case 28 :
       digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(27);
	break;
 case 29 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(28);
	break;
 case 30 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(29);
	break;
 case 31 :
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,LOW); 
	delay(750);
	return decompte(30);
	break;
 case 32 :
	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4, HIGH);
	digitalWrite(LED5,HIGH); 
	digitalWrite(LED6,HIGH); 
	delay(750);
	return decompte(31);
	break;
      


default :
	decompte(32);
	break;
      
      }

    }
}
