// IN
int lightSensor = A0;
int button1 = A1;

// OUT
int relay1 = 7;
int relay2 = 8;

// CONST
const int defDay = 80;
const int defActivationLights = 3;
const int defDeactivationLights = 0;
const int relays[2] = {relay1, relay2};

// VAR
int counterOfCyclesForAction = 0;
int temporaryActivationCounter = 0;
int luminosity;

enum State {
  on = true,
  off = false
};

void setup() {
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(button1, INPUT);
  
  Serial.begin(9600);

  setupInitialState();
  
}

void loop() {
  
  luminosity = analogRead(lightSensor);
  
  printFunction();
  turnOnLightsTemporarily();
  twilightControl();
  
  delay(1000);
  
}

void setupInitialState() {
  
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  
}

void printFunction() {
  
  Serial.print("luminosity atual: ");
  Serial.println(luminosity);
  Serial.print(String("Contador para alteração de estado (") + defDeactivationLights + "-" + defActivationLights + "): ");
  Serial.println(counterOfCyclesForAction);
  Serial.print("Valor do button1: ");
  Serial.println(analogRead(button1));
  Serial.print("Acionamento temporário desliga em: ");
  Serial.println(temporaryActivationCounter);
  
}

void twilightControl() {
  
  if(luminosity < defDay && counterOfCyclesForAction < defActivationLights) {
   counterOfCyclesForAction ++;
  } else {
    if(temporaryActivationCounter > 0) {
        temporaryActivationCounter --;
    } else if(luminosity > defDay && counterOfCyclesForAction > defDeactivationLights) {
      counterOfCyclesForAction --;
    } else {
      decideAcionamento();
    }
  }

}

void decideAcionamento() {

  if(counterOfCyclesForAction == defActivationLights) {
    mudaEstadorelays(on);
  } else if(counterOfCyclesForAction == defDeactivationLights) {
    mudaEstadorelays(off);
  }

}

void mudaEstadorelays(State estado) {
  for (const int &n : relays) {
    digitalWrite(n, !estado);
  }
}

void turnOnLightsTemporarily() {

  if(checkAction(button1)) {
    // seria legal piscar um led aqui indicando ter recebido comando
    mudaEstadorelays(on);
    temporaryActivationCounter += 10;
  }

}

bool checkAction(int elemento) {

  if(analogRead(elemento) > 500) {
    return true;
  } else {
    return false;
  }

}