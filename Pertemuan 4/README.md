# Laporan Praktikum Sistem Mikrokontroler
## Modul 4: Analog to Digital Converter (ADC) dan Pulse Width Modulation (PWM) 

---
## pertanyaan Praktikum 4 Percobaan 1

1. **Apa fungsi perintah analogRead() pada rangkaian praktikum ini?**

Pada rangkaian praktikum ini, analogRead() berfungsi untuk membaca nilai tegangan analog yang dikirimkan oleh potensiometer (sebagai pembagi tegangan) ke pin analog Arduino (misalnya A0).
Perintah ini menggunakan fitur Analog-to-Digital Converter (ADC) di dalam mikrokontroler untuk mengubah tegangan kontinu (biasanya 0–5V) menjadi nilai digital diskrit.
Pada Arduino standar yang memiliki resolusi ADC 10-bit, nilai yang dihasilkan berada dalam rentang 0 hingga 1023


2. **Mengapa diperlukan fungsi map() dalam program tersebut?**

Fungsi map() mutlak diperlukan untuk menyesuaikan (scaling) resolusi data masukan dengan kapasitas data keluaran
Pada program awal (kontrol LED), nilai masukan dari potensiometer memiliki rentang 0–1023 (10-bit), sedangkan fungsi analogWrite() untuk menghasilkan sinyal PWM pada LED hanya menerima nilai dalam rentang 0–255 (8-bit) 
Tanpa map(), pembacaan akan tidak proporsional dan terjadi overflow. Fungsi ini memetakan kedua rentang tersebut secara linear sehingga putaran potensiometer berbanding lurus dengan perubahan kecerahan LED (atau pergerakan sudut motor servo pada kasus lain)


3. **Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md**


```cpp
#include <Arduino.h>
#include <Servo.h> // Library wajib untuk mengontrol motor servo

Servo myServo;           // Membuat objek servo untuk mengontrol motor
const int potPin = A0;   // Pin analog untuk membaca potensiometer
const int servoPin = 9;  // Pin digital PWM yang terhubung ke kabel sinyal servo

int nilaiADC = 0;        // Menyimpan hasil pembacaan potensiometer (0-1023)
int sudutServo = 0;      // Menyimpan hasil konversi sudut (30-150)

void setup() {
  myServo.attach(servoPin); // Menghubungkan pin 9 ke objek myServo

  Serial.begin(9600);       // Mengaktifkan komunikasi serial dengan baud rate 9600
}

void loop() {
  // Baca nilai analog dari potensiometer (rentang 0–1023)
  nilaiADC = analogRead(potPin); 

  // Ubah nilai ADC (0–1023) menjadi batasan sudut servo (30–150 derajat)
  sudutServo = map(nilaiADC, 0, 1023, 30, 150); 

  // Perintahkan motor servo untuk bergerak ke sudut yang telah dipetakan
  myServo.write(sudutServo); 

  // Tampilkan data ADC dan Sudut ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | Sudut Servo: ");
  Serial.print(sudutServo);
  Serial.println("°");

  // Delay untuk memberi waktu servo mencapai posisi dan menstabilkan serial
  delay(50); 
}
```

## pertanyaan Praktikum 4 Percobaan 2


1. **Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!**


Fungsi analogWrite() sebenarnya tidak mengeluarkan tegangan analog murni yang naik-turun secara halus. Alih-alih, fungsi ini menggunakan teknik PWM (Pulse Width Modulation).

Pada teknik PWM, pin digital mikrokontroler dihidupkan (HIGH / 5V) dan dimatikan (LOW / 0V) dengan sangat cepat. Kecerahan LED ditentukan oleh duty cycle, yaitu perbandingan durasi pin berada dalam keadaan HIGH dibandingkan dengan total waktu satu siklus.  Semakin lama durasi HIGH (nilai PWM mendekati 255), rata-rata tegangan yang diterima LED akan semakin besar, sehingga mata manusia menangkapnya sebagai cahaya yang lebih terang. Sebaliknya, jika durasi HIGH singkat, LED akan meredup.

2. **Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?**
Hubungannya terletak pada perbedaan resolusi data antara sensor pembaca dan pin output:


-ADC (Analog-to-Digital Converter): Pada Arduino standar, ADC memiliki resolusi 10-bit. Artinya, variasi tegangan analog (0-5V) dari potensiometer dipetakan menjadi $2^{10}$ atau 1024 tingkat nilai diskrit, yaitu dari 0 hingga 1023.


-PWM (Pulse Width Modulation): Fungsi analogWrite() menggunakan timer mikrokontroler beresolusi 8-bit. Ini berarti output sinyal hanya bisa dibagi menjadi $2^8$ atau 256 tingkat nilai, yaitu dari 0 hingga 255.


3. **Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.**


```cpp
#include <Arduino.h> // library dasar Arduino

const int potPin = A0;   // Pin analog untuk membaca potensiometer
const int ledPin = 9;    // Pin digital PWM untuk LED

int nilaiADC = 0; 
int pwm = 0;      

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  nilaiADC = analogRead(potPin); 
  pwm = map(nilaiADC, 0, 1023, 0, 255); 
  // LED hanya menyala jika nilai PWM berada di rentang 50 sampai 200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm); 
  } else {
    analogWrite(ledPin, 0); // Matikan LED (PWM 0) jika di luar rentang
  }
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50); 
}
