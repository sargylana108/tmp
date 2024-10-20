#include <Arduino.h>
#include <string>
#include <array>  // Ипользуем std::array, так как по уловию знаем размер массива

#define LED_PIN 39

// мощность свечения
int power = 4096;

// буфер для приема сообщений
std::string message = "";

// Массив для хранения последних 4 команд
std::array<std::string, 4> commandHistory = {"", "", "", ""};
unsigned long lastCommandPrintTime = 0;  // Время последнего вывода команд
const unsigned long commandPrintInterval = 20000;  // Интервал вывода команд в миллисекундах (20 секунд)

bool light_on = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(18, INPUT);

  Serial.begin(115200);
}

void loop() {
  // читаем данные из серийного порта
  if (Serial.available() > 0) {
    message = "";

    while (Serial.available() > 0) {
      message += std::string(1, char(Serial.read()));
      delay(500);
    }

    power = std::stoi(message);

    // Сохраняем команду в массив последних команд
    for (int i = 3; i > 0; --i) {
      commandHistory[i] = commandHistory[i - 1];  // Сдвигаем предыдущие команды
    }
    commandHistory[0] = message;  // Добавляем новую команду в начало

    Serial.print("Recieved: power = ");
    Serial.println(power);
  }

  // Проверяем, прошло ли 20 секунд с последнего вывода команд
  if (millis() - lastCommandPrintTime >= commandPrintInterval) {
    // Выводим последние 4 команды
    Serial.println("Last 4 commands:");
    for (int i = 0; i < 4; ++i) {
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