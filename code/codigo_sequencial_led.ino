int led_estado = 0;
const int pinoBotao = 6;  // Pino do botão alterado
bool ultimoEstadoBotao = HIGH;
bool atualEstadoBotao;

int entradas[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16}; // Pinos dos LEDs
const int numLeds = sizeof(entradas) / sizeof(entradas[0]); // Calcula a quantidade de LEDs de acordo com o vetor.

void setup() {
  Serial.begin(9600);
  
  //Todos os LEDs são saídas e se iniciam apagados.
  for (int i = 1; i < numLeds; i++) {
    pinMode(entradas[i], OUTPUT);
    digitalWrite(entradas[i], LOW);
  }

  pinMode(pinoBotao, INPUT_PULLUP);  // Configura o pino do botão como entrada com pull-up interno.

  Serial.println("Iniciando programa...");
}

void loop() {
  atualEstadoBotao = digitalRead(pinoBotao);
  Serial.print("Estado atual do botão: ");
  Serial.println(atualEstadoBotao);

  // Se o botão for apertado, troca o estado do LED
  if (atualEstadoBotao == LOW && ultimoEstadoBotao == HIGH) {
    Serial.println("Botão pressionado");

    digitalWrite(entradas[led_estado], LOW);
    led_estado++;

    // Após o último LED apagar, o primeiro é acendido.
    if (led_estado >= numLeds) {
      led_estado = 0;
    }
    digitalWrite(entradas[led_estado], HIGH);

    Serial.print("LED aceso: ");
    Serial.println(entradas[led_estado]);

    delay(100);  // Aumenta o debounce do botão
  }

  ultimoEstadoBotao = atualEstadoBotao; // Atualiza o estado do botão para a próxima iteração.
}
