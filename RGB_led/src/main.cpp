#include <Arduino.h>

// troca entre r g b quando aperta botao

#define ledR 7
#define ledB 5
#define ledG 4
#define btn 8

int ciclo = 0;

bool ultimoEstadoBotao = HIGH;
bool botaoPressionado = false;

void apagarTodos() {
  digitalWrite(ledR, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, LOW);
}

void trocarLed()
{
  if (ciclo == 0)
  {
    digitalWrite(ledB, 0);
    digitalWrite(ledR, 1);
  }
  else if (ciclo == 1)
  {
    digitalWrite(ledR, 0);
    digitalWrite(ledG, 1);
  }
  else if (ciclo == 2)
  {
    digitalWrite(ledG, 0);
    digitalWrite(ledB, 1);
  }
  ciclo++;
  if (ciclo > 2)
  {
    ciclo = 0;
  }
}

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(btn, INPUT);
  // put your setup code here, to run once:
}

void loop() {
  bool estadoAtualBotao = digitalRead(btn);

  if (estadoAtualBotao == LOW && ultimoEstadoBotao == HIGH)
  {
    delay(50); //debounce
    if (!digitalRead(btn))
    {
      trocarLed();
    }
  }

  ultimoEstadoBotao = estadoAtualBotao;
  // put your main code here, to run repeatedly:
}
