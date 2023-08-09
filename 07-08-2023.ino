int sensorLuz = A0;
int acionador1 = 7;
int acionador2 = 8;
int luminosidade;
int defDia = 80;
int reles[2] = {acionador1, acionador2};

enum State {
  on = true,
  off = false
};

void setup() {
  
  pinMode(acionador1, OUTPUT);
  pinMode(acionador2, OUTPUT);
  
  Serial.begin(9600);

  setupInitialState();
  
}

void loop() {
  
  luminosidade = analogRead(sensorLuz);
  
  printFunction();
//  controleRele1();
//  controleRele2();
  controleTodosReles();
  
  delay(3000);
  
}

void setupInitialState() {
  
  digitalWrite(acionador1, HIGH);
  digitalWrite(acionador2, HIGH);
  
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

void controleRele2() {
  
  if(luminosidade < defDia) {
    digitalWrite(acionador2, LOW);
  } else {
    digitalWrite(acionador2, HIGH);
  }
  
}

void controleTodosReles() {
  
  if(luminosidade < defDia) {
    mudaEstadoReles(on);
  } else {
    mudaEstadoReles(off);
  }
  
}

void mudaEstadoReles(State estado) {
  for (const int &n : reles) {
    digitalWrite(n, !estado);
  }
}
