#include <Arduino.h>

#define ledw 6   // LED branco
#define ledr 5   // LED vermelho
#define ledb 3   // LED azul
#define ledg 1   // LED verde
#define btn 8    // Botão
#define maximo 255
#define minimo 0

#define tempo_verde 5000
#define tempo_azul 2000
#define tempo_vermelho 3000

bool ultimoEstadoBotao = HIGH;
bool botaoPressionado = false;

void setup() {
  pinMode(ledw, OUTPUT);
  pinMode(ledr, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(btn, INPUT_PULLUP); // Usa pull-up interno, botão ligado ao GND
}

void piscar(int led, int tempo, int vezes) {
  for (int i = 0; i < vezes; i++) {
    digitalWrite(led, HIGH);
    delay(tempo);
    digitalWrite(led, LOW);
    delay(tempo);
  }
}

void acenderEApagar(int led, int tempo) {
  // Fade in
  for (int i = minimo; i <= maximo; i++) {
    analogWrite(led, i);
    delay(tempo);
  }
  // Fade out
  for (int i = maximo; i >= minimo; i--) {
    analogWrite(led, i);
    delay(tempo);
  }
}

void apagarTodos() {
  digitalWrite(ledg, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ledr, LOW);
  digitalWrite(ledw, LOW);
}

void sequencia() {
  // Verde
  digitalWrite(ledg, HIGH);
  delay(tempo_verde * 0.9);  // 90% do tempo
  piscar(ledw, 100, 5);      // Pisca branco
  digitalWrite(ledg, LOW);

  // Azul
  digitalWrite(ledb, HIGH);
  delay(tempo_azul * 0.9);
  piscar(ledw, 100, 5);
  digitalWrite(ledb, LOW);

  // Vermelho
  digitalWrite(ledr, HIGH);
  delay(tempo_vermelho * 0.9);  // 90% do tempo
  piscar(ledw, 100, 5);         // Pisca branco
  digitalWrite(ledr, LOW);

  acenderEApagar(ledw, 10);

  apagarTodos();  // Apaga tudo no final
}

void loop() {
  bool estadoAtualBotao = digitalRead(btn);

  if (estadoAtualBotao == LOW && ultimoEstadoBotao == HIGH) {
    // Botão foi pressionado
    delay(50); // debounce
    if (digitalRead(btn) == LOW) {
      sequencia();
    }
  }

  ultimoEstadoBotao = estadoAtualBotao;
}