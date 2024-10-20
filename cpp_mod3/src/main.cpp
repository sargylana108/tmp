#include <Arduino.h>
#include <string>
#include <array> // Ипользуем std::array, так как по уловию знаем размер массива

#define LED_PIN 39
#define COMMAND_HISTORY_SIZE 4  // Количество последних команд для хранения

// мощность свечения
int power = 4096;

// буффер для приема сообщений
std::string message = "";

// Массив для хранения последних команд
std::array<std::string, COMMAND_HISTORY_SIZE> commandHistory = {"", "", "", ""};
unsigned long lastCommandPrintTime = 0;  // Время последнего вывода команд
const unsigned long commandPrintInterval = 20000;  // Интервал вывода команд в миллисекундах

bool light_on = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // читаем данные из серийного порта
  if (Serial.available() > 0) {
    message = "";

    while (Serial.available() > 0) {
      message += std::string(1, char(Serial.read()));
      delay(500);  // Пауза между чтением байтов
    }
    
    power = std::stoi(message);

    // Сохраняем команду в массиве последних команд
    for (int i = COMMAND_HISTORY_SIZE - 1; i > 0; --i) {
      commandHistory[i] = commandHistory[i - 1];  // Сдвигаем предыдущие команды
    }
    commandHistory[0] = message;  // Добавляем новую команду в начало

    Serial.print("Recieved: power = ");
    Serial.println(power);
  }

  // Проверяем, прошло ли 20 секунд с последнего вывода
  if (millis() - lastCommandPrintTime >= commandPrintInterval) {
    // Логика для вывода последних команд без отдельной функции
    Serial.println("Last 4 commands:");
    for (int i = 0; i < COMMAND_HISTORY_SIZE; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(commandHistory[i].c_str());
    }

    lastCommandPrintTime = millis();  // Обновляем время последнего вывода
  }

  if (digitalRead(18) == HIGH) {
    light_on = true;
  }

  if (light_on == true) {
    light_on = false;
    analogWrite(LED_PIN, power);
    delay(1000);
  } else {
    analogWrite(LED_PIN, 0);
  }
}