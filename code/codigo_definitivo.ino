#include <RCSwitch.h>

// Definição dos pinos dos LEDs e do receptor
const int ledPins[] = { 4, 5, 6, 7};  // Pinos dos LEDs ativados pelo controle remoto
const int receiverPin = 2;              // Pino do receptor (D2)
const int interruptReceiverPin = 0;     // Pino do receptor de interrupção
const int pinoBotao = 13;               // Pino do botão para controle sequencial

int led_estado = 3;  // Controle do LED sequencial

RCSwitch mySwitch = RCSwitch();
const unsigned long myCode = 160022629;  // Código do controle remoto
unsigned long lastSignalTime = 0;        // Tempo do último sinal recebido

int remoteLedIndex = 0;  // Índice do LED a ser aceso pelo controle remoto

// Função para apagar todos os LEDs antes de acender o próximo
void apagarTodosOsLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);  // Apaga todos os LEDs
  }
}

void setup() {
  Serial.begin(9600);

  // Configura LEDs para controle remoto
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);  // Inicia todos os LEDs desligados
  }

  // Configuração do receptor RF
  pinMode(receiverPin, INPUT);                   // Configura o receptor no pino D2
  mySwitch.enableReceive(interruptReceiverPin);  // Inicia o receptor RF

  apagarTodosOsLeds();

  Serial.println("Sistema inicializado...");
}

void loop() {
  // Controle do LED via controle remoto RF
  if (mySwitch.available()) {
    unsigned long receivedCode = mySwitch.getReceivedValue();

    // Verifica se o código recebido é do controle remoto e aplica debounce
    if (receivedCode == myCode) {
      Serial.print("Código recebido: ");
      Serial.println(receivedCode);

      // Desliga o LED atual
      Serial.print("Apaga LED ");
      Serial.println(ledPins[remoteLedIndex]);
      digitalWrite(ledPins[remoteLedIndex], LOW);

      // Avança para o próximo LED
      remoteLedIndex++;
      if (remoteLedIndex >= 4) {
        remoteLedIndex = 0;  // Volta para o primeiro LED se ultrapassar o limite
      }

      // Liga o próximo LED
      digitalWrite(ledPins[remoteLedIndex], HIGH);
      Serial.print("Acende LED ");
      Serial.println(ledPins[remoteLedIndex]);

      delay(500);
    }

    mySwitch.resetAvailable();  // Reseta o status do receptor
  }
}
