#define DIR_PIN 5
#define MAG_PIN 6
void setup() {
  pinMode(MAG_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN,HIGH);
  delay(10000);
  digitalWrite(DIR_PIN,LOW);

  

 
}

void loop() {
  // put your main code here, to run repeatedly:

}
