#include <Arduino.h>

// Ajuste os pinos conforme a ligação no seu LED RGB
#define RED_PIN    7
#define GREEN_PIN  4
#define BLUE_PIN   5
#define BUTTON_PIN 8

#define MAX_CICLO 5

int ciclo = 0;
bool ultimoEstadoBotao = HIGH;

void apagarTodos() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

void acenderCor(bool r, bool g, bool b) {
  digitalWrite(RED_PIN, r ? HIGH : LOW);
  digitalWrite(GREEN_PIN, g ? HIGH : LOW);
  digitalWrite(BLUE_PIN, b ? HIGH : LOW);
}

void trocarLed() {
  apagarTodos();
  Serial.print("Ciclo: ");
  Serial.println(ciclo);

  switch (ciclo) {
    case 0: acenderCor(1, 0, 0); break; // Vermelho
    case 1: acenderCor(0, 1, 0); break; // Verde
    case 2: acenderCor(0, 0, 1); break; // Azul
    case 3: acenderCor(1, 1, 0); break; // Amarelo (vermelho + verde)
    case 4: acenderCor(1, 0, 1); break; // Magenta (vermelho + azul)
    case 5: acenderCor(0, 1, 1); break; // Ciano (verde + azul)
  }

  ciclo = (ciclo + 1) % (MAX_CICLO + 1);
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Botão entre pino e GND

  Serial.begin(9600);
  apagarTodos();
}

void loop() {
  bool estadoAtual = digitalRead(BUTTON_PIN);

  if (estadoAtual == LOW && ultimoEstadoBotao == HIGH) {
    delay(50); // debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      trocarLed();
    }
  }

  ultimoEstadoBotao = estadoAtual;
}