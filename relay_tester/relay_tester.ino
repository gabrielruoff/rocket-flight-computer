#define r1 3
#define r2 2

void setup() {
  // put your setup code here, to run once:
pinMode(r1, OUTPUT);
pinMode(r2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(r1, HIGH);
digitalWrite(r2, HIGH);
delay(1000);
digitalWrite(r1, LOW);
digitalWrite(r2, LOW);
delay(1000);
}
