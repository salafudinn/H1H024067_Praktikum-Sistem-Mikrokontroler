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
const int ledPin = 6;           // pin 6 untuk jalur LED
int timeDelay = 1000;           // set delay awal 1000ms 
int phase = 0;                  // set phase awal ke 0

void setup() {                  // fungsi setup atau inisiasi
  pinMode(ledPin, OUTPUT);      // pin 6 akan menjadi output
}                         

void loop() {                   // set Perulangan utama
  if (phase == 0) {             // ketika program ada di fase 0 langsung tereksekusi
    digitalWrite(ledPin, HIGH); // Led nyala
    delay(timeDelay);           // delay mengikuti deklarasi awal
    digitalWrite(ledPin, LOW);  // Led mati
    delay(timeDelay);           // delay mengikuti deklarasi awal
    timeDelay -= 100;           // mengurangi delay awal 100ms
    if (timeDelay <= 100) {     // ketika delay kurang dari 100ms
      phase = 1;                // akan ganti ke fase 1
      timeDelay = 500;          // ubah delay jadi 500ms
    }                           
  }                             
  else if (phase == 1) {        // ketika fase 1
    for(int i = 0; i < 5; i++) {// Akan mengulang kedipan 5 kali
      digitalWrite(ledPin, HIGH);// led nyala
      delay(timeDelay);         // delay 500ms
      digitalWrite(ledPin, LOW); // Led mati
      delay(timeDelay);         // delay 500ms
    }                           
    phase = 2;                  // masuk fase 2
  }                             
  else if (phase == 2) {        // ketika fase 2 program tereksekusi
    digitalWrite(ledPin, LOW);  // Memastikan led mati
    delay(3000);                // delay 3000ms
    phase = 0;                  // balik ke fase 0
    timeDelay = 1000;           // balikan juga delay awal ke 1000ms
  }                            
}                              
```
