#include <Arduino.h> // library dasar Arduino (tidak wajib diubah)

// ===================== PIN SETUP =====================
// Berdasarkan gambar: Potensio ke A0, LED ke Pin 9
const int potPin = A0;   // Pin analog A0 untuk potensiometer
const int ledPin = 9;    // Pin digital 9 (PWM) untuk LED

// ===================== VARIABEL =====================
int nilaiADC = 0;  // Variabel penyimpan nilai bacaan analog
int pwm = 0;       // Variabel penyimpan nilai hasil konversi PWM

void setup() {

  // ===================== OUTPUT SETUP =====================
  // Atur pin LED sebagai output
  pinMode(ledPin, OUTPUT);

  // ===================== SERIAL MONITOR =====================
  // Aktifkan komunikasi serial dengan baud rate standar
  Serial.begin(9600); 
}

void loop() {

  // ===================== PEMBACAAN SENSOR =====================
  // Baca nilai analog dari potensiometer (rentang 0–1023)
  nilaiADC = analogRead(potPin); 

  // ===================== PEMROSESAN DATA (SCALING) =====================
  // Ubah nilai ADC (0–1023) menjadi nilai PWM (0–255) agar LED bisa redup/terang
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // ===================== OUTPUT PWM =====================
  // Kirim sinyal PWM ke LED
  analogWrite(ledPin, pwm); 

  // ===================== MONITORING DATA =====================
  // Tampilkan data ke Serial Monitor untuk memantau perubahan
  Serial.print("ADC: ");
  Serial.print(nilaiADC); 

  Serial.print(" | PWM: ");
  Serial.println(pwm); 

  // ===================== STABILISASI SISTEM =====================
  // Delay agar pembacaan Serial Monitor tidak terlalu cepat
  delay(50); 
}