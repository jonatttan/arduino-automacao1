// IN
int lightSensor = A0;
int button1 = A1;

// OUT
int relay1 = 7;
int relay2 = 8;
int indicatorLight1 = 2;
int indicatorLight2 = 3;

// CONST
const int defDay = 80;
const int defActivationLights = 3;
const int defDeactivationLights = 0;
const int relays[2] = {relay1, relay2};
const int defaultDelay = 1000;

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
  pinMode(indicatorLight1, OUTPUT);
  pinMode(indicatorLight2, OUTPUT);
  pinMode(button1, INPUT);
  
  Serial.begin(9600);

  setupInitialState();
  
}

void loop() {
  
  luminosity = analogRead(lightSensor);
  
  printFunction();
  turnOnLightsTemporarily();
  twilightControl();
  
  delay(defaultDelay);
  
}

void setupInitialState() {
  
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(indicatorLight1, LOW);
  digitalWrite(indicatorLight2, LOW);
  
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
      decideToTrigger();
    }
  }

}

void decideToTrigger() {
  State state = (counterOfCyclesForAction == defActivationLights) ? on : off;
  changeRalaysState(state);
  digitalWrite(indicatorLight1, state);

}

void changeRalaysState(State estado) {
  for (const int &n : relays) {
    digitalWrite(n, !estado);
  }
}

void turnOnLightsTemporarily() {

  if(checkAction(button1)) {
    changeRalaysState(on);
    temporaryActivationCounter += 300; // With default dalay == 1000, this is five minutes
    flashigLight(indicatorLight2);
  }

}

bool checkAction(int elemento) {

  if(analogRead(elemento) > 500) {
    return true;
  } else {
    return false;
  }

}

void flashigLight(int element) {

  digitalWrite(element, HIGH);
  delay(100);
  digitalWrite(element, LOW);

}