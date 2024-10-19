#include <Arduino.h>

const int led_pin = 39;
// Глобальная переменная для количества нажатий
const int button_push_number = 3;

int press_count = 0; // Счётчик нажатий

void setup() {
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if(digitalRead(18) == HIGH) {
    press_count++;  // Инкремент счётчика нажатий
    delay(200);     // Небольшая задержка, чтобы кнопка не загоралась преждевременно
  }else{

  }
  // Если количество нажатий достигло заданного значения
  if (press_count >= button_push_number) {
    digitalWrite(led_pin, HIGH);   // Включаем светодиод
    delay(1000);                   // Задержка 1 секунда
    press_count = 0;               // Сброс счётчика
    digitalWrite(led_pin, LOW);
  }
}