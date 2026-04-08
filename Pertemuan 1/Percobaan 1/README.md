1.5.4 Pertanyaan Praktikum:
1. Pada kondisi apa program masuk ke blok if?
   Program akan masuk dan mengeksekusi blok if Ketika nilai variable timeDelay kurang atau sama dengan          100       (timeDelay <=100), yaitu saat led berkedip sangat cepat.
2. Pada kondisi apa program masuk ke blok else?
   Program masuk ke blok else ketika kondisi program if tidak terpenuhi dan nilai variable melebihi 100, sehingga         nilai variable timeDelay akan dikurangi 100 dan membuat waktu delay dikurangi.
3. Apa fungsi dari perintah delay(timeDelay)?
   Fungsi dari perintah timeDelay adalah untuk memberikan jeda waktu (dalam milidetik) sebesar nilai yang tersimpan       dalam variabel timeDelay. Jeda ini menentukan durasi seberapa lama LED akan menyala atau mati sebelum melanjutkan      ke baris kode berikutnya
4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati),
ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang →
mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md

source code

```C++
const int ledPin = 6;           // Gunakan pin 6 untuk LED
int timeDelay = 1000;           // Set jeda awal 1000ms (1 detik)
int phase = 0;                  // Set fase awal ke 0 (fase cepat)

void setup() {                  // Fungsi inisialisasi awal
  pinMode(ledPin, OUTPUT);      // Atur pin 6 sebagai output
}                               // Tutup blok setup

void loop() {                   // Fungsi utama berulang
  if (phase == 0) {             // Jika program ada di fase 0
    digitalWrite(ledPin, HIGH); // Nyalakan LED
    delay(timeDelay);           // Jeda sesuai timeDelay
    digitalWrite(ledPin, LOW);  // Matikan LED
    delay(timeDelay);           // Jeda sesuai timeDelay
    timeDelay -= 100;           // Kurangi jeda 100ms agar makin cepat
    if (timeDelay <= 100) {     // Jika jeda sudah <= 100ms
      phase = 1;                // Ganti ke fase 1 (sedang)
      timeDelay = 500;          // Ubah jeda menjadi 500ms
    }                           // Tutup blok if kecepatan
  }                             // Tutup blok fase 0
  else if (phase == 1) {        // Jika program ada di fase 1
    for(int i = 0; i < 5; i++) {// Ulangi kedipan konstan 5 kali
      digitalWrite(ledPin, HIGH);// Nyalakan LED
      delay(timeDelay);         // Tahan selama 500ms
      digitalWrite(ledPin, LOW); // Matikan LED
      delay(timeDelay);         // Tahan selama 500ms
    }                           // Tutup blok for
    phase = 2;                  // Ganti ke fase 2 (mati)
  }                             // Tutup blok fase 1
  else if (phase == 2) {        // Jika program ada di fase 2
    digitalWrite(ledPin, LOW);  // Pastikan LED dimatikan
    delay(3000);                // Tahan mati selama 3 detik
    phase = 0;                  // Kembali ke fase 0 (awal)
    timeDelay = 1000;           // Kembalikan jeda ke 1 detik
  }                             // Tutup blok fase 2
}                               // Tutup blok loop
```
