int sensorLuz = A0;
int acionador1 = 7;
int luminosidade;
int defDia = 80;

void setup() {
  
  pinMode(acionador1, OUTPUT);
  Serial.begin(9600);

  setupInitialState();
  
}

void loop() {
  
  luminosidade = analogRead(sensorLuz);
  
  printFunction();
  controleRele1();
  
  delay(3000);
  
}

void printFunction() {
  
  Serial.print(" Luminosidade atual: ");
  Serial.println(luminosidade);
  
}

void controleRele1() {
  
  if(luminosidade < defDia) {
    digitalWrite(acionador1, LOW);
  } else {
    digitalWrite(acionador1, HIGH);
  }
  
}

void setupInitialState() {
  
  digitalWrite(acionador1, HIGH);
  
}
