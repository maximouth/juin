#include "timers.h"

#define ONESEC128 (84000000/128)
#define DELTA (11)

// registre pour mettre HIGH sur une broche
#define SENDLEDHIGH (*(( int32_t*)  0x400E1230) =  0x1<<25)
// registre pour mettre LOW sur une broche
#define SENDLEDLOW  (*(( int32_t*)  0x400E1234) =  0x1<<25)

// les 3 broches
const int led = 5;
const int ifred = 6;
const int mt = 7;

// le nombre de tours secondes
volatile int cpt = 0;
//
volatile int etat = 0;
// pour empecher les rebonds
int bruit = 0;
// variables de temps
unsigned long time1;
unsigned long time2;
//consigne de vitesse
int tour = 28;
// variable
int vitesse = 0;
// commande à envoyer au moteur
int cmd2 =0;
//durée entre 2 flashs
int flash = ONESEC128/tour;
//temps d'alumage du stroboscope
int low = ONESEC128/(tour*16);

void setup() {

  Serial.begin(9600);
  //devlaration des broches
  pinMode (led, OUTPUT);
  pinMode (ifred, INPUT);
  pinMode (mt, OUTPUT);
  //stroboscope eteint
  SENDLEDLOW;
  //moteur à l'arret
  analogWrite (mt,0);
  //demarer les deux timers
  start_timer_TC1 (ONESEC128/tour,0);
  start_timer_TC1 (ONESEC128/2,1);
  //interruption pour compter les tours
  attachInterrupt (ifred, compte, FALLING);

}


//affichage de la commande envoyée au moteur toutes les 500 ms
void loop() {

  if ((millis() - time1) > 500) {
    time1 = millis();
    //  Serial.println(cpt);
    Serial.println(cmd2);
   } 

}

// regulation de la vitesse
void TC4_Handler() {
  //ré armer le timer
  TC_GetStatus (TC1,1);
  //appel au pid
  vitesse = (cpt*2)/2;
  cpt = 0;
  cmd2 += PID(vitesse);

  if (cmd2 > 255) {
    cmd2 = 255;
  }
  else if (cmd2 < 0) {
    cmd2 = 0;
  }

  analogWrite (mt, cmd2);

}

//commande le stroboscope
void TC3_Handler() {
  
  //re armer le timer
  TC_GetStatus (TC1,0);

  if (etat == 0) {
    //allume la led
    SENDLEDHIGH;
     //relance le timer pour eteindre la led 
    TC_SetRC (TC1, 0, low ) ;   /* Initialise count value. */
    TC_Start (TC1, 0) ;          /* Really start the timer. */
    etat = 1;
  }
  else {
    //eteint la led
    SENDLEDLOW;
    //relance le timer pour allumer la led
    TC_SetRC (TC1, 0, (flash - low ) ) ;   /* Initialise count value. */
    TC_Start (TC1, 0) ;    /* Really start the timer. */      
    etat = 0;
      }

}

// compte le nombre de tour
void compte() {

  //permet d'eviter les rebonds
  if(((millis() - time2) > DELTA) && (bruit == 1)) {
    bruit = 0;
  }
  if (bruit == 0) {
    //Serial.println("compte");
    //re initialiser le stamp
    time2 = millis();
    //compter un tour de plus
    cpt ++;
    bruit = 1;
  }
}


// variables pour le PID
// P
float KE = -2.5;
// D
float KD = 0;
// I
float KI = -0.02;
// contient l'erreur precedente
int prevErr = 0;
// la somme de toute les erreures depuis le lancement du programme
int somme = 0;

// calcul du PID
float PID(int cpt) {
  //calculer l'erreur
  int err = (cpt-tour);
  //rajouter l'erreur courante dans la somme
  somme += err;

  float pid = ( (err*KE) + (KD*(err-prevErr)) + (KI *(somme))); 

  prevErr = err;
  
  return pid;
}
