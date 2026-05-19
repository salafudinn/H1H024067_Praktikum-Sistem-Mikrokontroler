# Laporan Praktikum Sistem Mikrokontroler
# Modul 5:RTOS

*Nama:* Muhammad Imam Salafudin  
*NIM:* H1H024067  

---
## pertanyaan Praktikum 5 Percobaan 1

1. **Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!**


Ketiga task berjalan secara bersamaan 
Namun, secara teknis pada perangkat keras (Arduino Uno dengan arsitektur mikrokontroler single-core), instruksi dieksekusi secara bergantian. 
Mekanisme ini sepenuhnya dikendalikan oleh Kernel Scheduler dari FreeRTOS yang melakukan context switching. 
Penjadwal membagi waktu pemrosesan dan mengalihkan penanganan dari satu task ke task lainnya dengan kecepatan sangat tinggi dalam orde milidetik, menciptakan ilusi bahwa semua task berjalan paralel secara serempak.


2. **Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!**


Berikut adalah langkah-langkah untuk menambahkan task keempat pada FreeRTOS:


a.  **Deklarasi Fungsi Task:** Buat prototipe dan definisi fungsi baru, misalnya `void TaskBlink3(void *pvParameters);`.


b.  **Tulis Logika Program:** Di dalam blok fungsi tersebut, atur konfigurasi awal (seperti `pinMode`) dan buat siklus perulangan `while(1)` yang memuat instruksi (misal menyalakan LED) beserta jeda waktu menggunakan `vTaskDelay()`.


c.  **Registrasi Task:** Panggil fungsi `xTaskCreate()` di dalam `setup()` sebelum perintah `vTaskStartScheduler();`. Contoh sintaksnya: 
    `xTaskCreate(TaskBlink3, "task4", 128, NULL, 1, NULL);`

    
3. **Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalugunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya? Jelaskanprogram pada file README.md.**


```cpp
#include <Arduino_FreeRTOS.h>

// Deklarasi fungsi Task
void TaskBlinkPot(void *pvParameters);
void TaskPrint(void *pvParameters);

void setup() {
  Serial.begin(9600);
  
  // Membuat Task untuk Blink LED dengan kontrol Potensiometer
  xTaskCreate(TaskBlinkPot, "BlinkPot", 128, NULL, 1, NULL);
  
  // Membuat Task untuk memantau nilai di Serial Monitor
  xTaskCreate(TaskPrint, "Print", 128, NULL, 1, NULL);
  
  vTaskStartScheduler();
}

void loop() {}

void TaskBlinkPot(void *pvParameters) {
  pinMode(8, OUTPUT); // Mengatur pin 8 sebagai output LED
  
  while(1) {
    int potValue = analogRead(A0); // Membaca nilai analog dari potensiometer (0-1023)
    // Memetakan nilai 0-1023 menjadi jeda waktu 100ms - 1000ms
    int delayTime = map(potValue, 0, 1023, 100, 1000); 

    digitalWrite(8, HIGH); // Menyalakan LED
    vTaskDelay(delayTime / portTICK_PERIOD_MS); // Jeda sesuai nilai potensiometer
    
    digitalWrite(8, LOW); // Mematikan LED
    vTaskDelay(delayTime / portTICK_PERIOD_MS); // Jeda sesuai nilai potensiometer
  }
}

void TaskPrint(void *pvParameters) {
  while(1) {
    Serial.println("Task Multitasking Berjalan.");
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Print setiap 1 detik
  }
}
```

## pertanyaan Praktikum 5 Percobaan 2


1. **Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!**


Sama halnya dengan Percobaan 5A, kedua task (`read_data` dan `display`) dieksekusi secara bergantian secara fisik oleh prosesor melalui mekanisme context switching yang dikelola oleh Kernel Scheduler, meskipun secara fungsional keduanya bertindak saling melengkapi dalam waktu yang terkesan bersamaan.


2. **Apakah program ini berpotensi mengalami race condition? Jelaskan!**


idak berpotensi**. Program ini dirancang bebas dari insiden race condition karena mengadopsi mekanisme komunikasi data berbasis Queue (Antrean). Struktur `xQueueSend()` dan `xQueueReceive()` beroperasi dengan prinsip thread-safe. Saat task pertama (`read_data`) menyisipkan data,
antarmuka Queue akan mengatur dan memproteksi aliran memori tersebut hingga task kedua (`display`) siap mengekstraknya secara sekuensial,
sehingga tumpang tindih manipulasi memori pada waktu yang sama dapat dihindari.


3. **Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya? Jelaskan program pada file README.md.**


```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "DHT.h"

#define DHTPIN 2     // Pin sensor DHT terhubung ke pin 2
#define DHTTYPE DHT11 // Tipe sensor DHT 11

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float humidity;
};

QueueHandle_t my_queue;

void setup() {
  Serial.begin(9600);
  dht.begin(); // Inisialisasi sensor DHT
  
  // Membuat Queue untuk menampung 1 paket data bertipe struct readings
  my_queue = xQueueCreate(1, sizeof(struct readings));
  
  // Membuat Task Pembaca Sensor dan Task Penampil Data
  xTaskCreate(read_sensor_task, "ReadDHT", 128, NULL, 1, NULL);
  xTaskCreate(display_task, "Display", 128, NULL, 1, NULL);
}

void loop() {}

void read_sensor_task(void *pvParameters) {
  struct readings data_dikirim;
  
  while(1) {
    data_dikirim.temp = dht.readTemperature(); // Membaca suhu asli
    data_dikirim.humidity = dht.readHumidity(); // Membaca kelembaban asli
    
    // Mengirim data ke antrean (Queue)
    xQueueSend(my_queue, &data_dikirim, portMAX_DELAY);
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Baca setiap 2 detik
  }
}

void display_task(void *pvParameters) {
  struct readings data_diterima;
  
  while(1) {
    // Menunggu dan mengambil data dari antrean (Queue)
    if (xQueueReceive(my_queue, &data_diterima, portMAX_DELAY) == pdPASS) {
      Serial.print("Suhu: ");
      Serial.print(data_diterima.temp);
      Serial.print(" C | Kelembaban: ");
      Serial.print(data_diterima.humidity);
      Serial.println(" %");
    }
  }
}
