#define SENDLEDHIGH (*(( int32_t*)  0x400E1230) =  0x1<<25)
#define SENDLEDLOW  (*(( int32_t*)  0x400E1234) =  0x1<<25)


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

}




void loop() {

  if ((millis() - time1) > 1000) {

  Serial.println (cpt);
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

  time1 = millis();
  }


}

void compte() {
  cpt ++;
}
