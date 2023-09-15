void setup() {
  // put your setup code here, to run once:
  pinMode(D10,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D10,HIGH);
  delay(1000);
  digitalWrite(D10,LOW);
  delay(1000);

}
