#include <Arduino_FreeRTOS.h>

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskPot(void *pvParameters);

// shared variable
int delayValue = 200; 

void setup() {
  Serial.begin(9600);

  xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL);
  xTaskCreate(TaskPot, "taskPot", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {}

// ================= TASK LED 1 =================
void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);

  while(1) {
    digitalWrite(8, HIGH);
    vTaskDelay(delayValue / portTICK_PERIOD_MS);

    digitalWrite(8, LOW);
    vTaskDelay(delayValue / portTICK_PERIOD_MS);
  }
}

// ================= TASK LED 2 =================
void TaskBlink2(void *pvParameters) {
  pinMode(7, OUTPUT);

  while(1) {
    digitalWrite(7, HIGH);
    vTaskDelay((delayValue + 100) / portTICK_PERIOD_MS);

    digitalWrite(7, LOW);
    vTaskDelay((delayValue + 100) / portTICK_PERIOD_MS);
  }
}

// ================= TASK POTENSIOMETER =================
void TaskPot(void *pvParameters) {
  while(1) {
    int potValue = analogRead(A0);

    // mapping 0–1023 jadi 100–1000 ms
    delayValue = map(potValue, 0, 1023, 100, 1000);

    Serial.print("Pot: ");
    Serial.print(potValue);
    Serial.print(" | Delay: ");
    Serial.println(delayValue);

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}