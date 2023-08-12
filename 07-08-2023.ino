int sensorLuz = A0;
int botao1 = A1;
int acionador1 = 7;
int acionador2 = 8;
int luminosidade;
int defDia = 80;
int contadorDeCiclosParaAcionamento = 0;
int defAcionaLuzes = 3;
int defApagaLuzes = 0;
int reles[2] = {acionador1, acionador2};
int acionamentoTemporario = 0;

enum State {
  on = true,
  off = false
};

void setup() {
  
  pinMode(acionador1, OUTPUT);
  pinMode(acionador2, OUTPUT);
  pinMode(botao1, INPUT);
  
  Serial.begin(9600);

  setupInitialState();
  
}

void loop() {
  
  luminosidade = analogRead(sensorLuz);
  
  printFunction();
//  controleRele1();
//  controleRele2();
  acionaLuzesTemporariamente();
  controleCrepuscular();
  
  delay(1000);
  
}

void setupInitialState() {
  
  digitalWrite(acionador1, HIGH);
  digitalWrite(acionador2, HIGH);
  
}

void printFunction() {
  
  Serial.print("Luminosidade atual: ");
  Serial.println(luminosidade);
  Serial.print(String("Contador para alteração de estado (") + defApagaLuzes + "-" + defAcionaLuzes + "): ");
  Serial.println(contadorDeCiclosParaAcionamento);
  Serial.print("Valor do Botao1: ");
  Serial.println(analogRead(botao1));
  Serial.print("Acionamento temporário desliga em: ");
  Serial.println(acionamentoTemporario);
  
}

// Ter apenas um controle para acionamento, passando rele por parâmetro, eliminando boilerplate
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

void controleCrepuscular() {
  
  if(luminosidade < defDia && contadorDeCiclosParaAcionamento < defAcionaLuzes) {
   contadorDeCiclosParaAcionamento ++;
  } else {
    if(acionamentoTemporario > 0) {
        acionamentoTemporario --;
    } else if(luminosidade > defDia && contadorDeCiclosParaAcionamento > defApagaLuzes) {
      contadorDeCiclosParaAcionamento --;
    } else {
      decideAcionamento();
    }
  }

}

void decideAcionamento() {

  if(contadorDeCiclosParaAcionamento == defAcionaLuzes) {
    mudaEstadoReles(on);
  } else if(contadorDeCiclosParaAcionamento == defApagaLuzes) {
    mudaEstadoReles(off);
  }

}

void mudaEstadoReles(State estado) {
  for (const int &n : reles) {
    digitalWrite(n, !estado);
  }
}

void acionaLuzesTemporariamente() {

  if(checkAction(botao1)) {
    // seria legal piscar um led aqui indicando ter recebido comando
    mudaEstadoReles(on);
    acionamentoTemporario += 10;
  }

}

bool checkAction(int elemento) {

  if(analogRead(elemento) > 500) {
    return true;
  } else {
    return false;
  }

}