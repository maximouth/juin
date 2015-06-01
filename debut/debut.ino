int x = 0;
const int led = 5;
const int ifred = 6;
const int mt = 7;

unsigned long time1;



void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(ifred, INPUT);
  pinMode(mt, OUTPUT);

  time1 = millis();

}

void loop() {

  delay(1000);

  Serial.println (digitalRead(ifred));

  if (x ==0) {
    digitalWrite (led, LOW);
    analogWrite (mt,200);
    x = 1;
  }
  else {
    digitalWrite (led, HIGH);
    analogWrite (mt,0);
    x = 0;
  }



}
