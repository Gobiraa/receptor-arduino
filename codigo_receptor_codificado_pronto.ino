#include <RCSwitch.h>

// Definição dos pinos
const int ledPin = 3;                // Pino do LED
const int receiverPin = 2;           // Pino do receptor
const int interruptReceiverPin = 0;  // Pino do receptor de interrupção

RCSwitch mySwitch = RCSwitch();

// Código do controle remoto específico que você deseja detectar
const unsigned long myCode = 160022629;  // Substitua com o código do seu controle remoto

unsigned long lastSignalTime = 0;    // Tempo do último sinal recebido
const unsigned long debounceTime = 500; // Tempo de espera entre sinais (1 segundo)

void setup() {
  pinMode(ledPin, OUTPUT);                      
  pinMode(receiverPin, INPUT);                  
  mySwitch.enableReceive(interruptReceiverPin); 
  Serial.begin(9600);                           
}

void loop() {
  // Lê o sinal do receptor
  if (mySwitch.available()) {
    unsigned long receivedCode = mySwitch.getReceivedValue();
    unsigned long currentTime = millis(); // Obtém o tempo atual

    // Verifica se o código recebido é o código do controle remoto específico
    if (receivedCode == myCode && (currentTime - lastSignalTime) > debounceTime) {
      Serial.print("Código recebido: ");
      Serial.println(receivedCode);
      
      // Liga o LED por um curto tempo quando o botão é pressionado
      Serial.println("Botão pressionado! Ligando o LED.");
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);

      lastSignalTime = currentTime;
    }

    mySwitch.resetAvailable();  // Reseta o status do receptor
  }
}
