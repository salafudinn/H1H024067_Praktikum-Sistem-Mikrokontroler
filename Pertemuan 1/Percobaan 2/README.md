
1.6.4 Pertanyaan Praktikum
1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!

<img width="962" height="724" alt="schematic percobaan 2" src="https://github.com/user-attachments/assets/3cad99f9-e5e8-431a-9f8a-1da370b0b22f" />

2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
   Menggunakan perulangan for yang terus menambah nilai pin target (ledPin++) mulai dari Pin 2 perlahan naik hingga       Pin 7, lalu menyalakan dan mematikannya bergiliran.
3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
   Memberi jeda waktu penahanan eksekusi program (dalam satuan milidetik) sesuai dengan angka yang ada di dalam           variabel timeDelay.
4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian
dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

```c++
int timer = 300; // waktu delay untuk perpindahan nyala LED

void setup() {
  // inisialisasi pin 2 sampai 7 sebagai OUTPUT
  for (int ledPin = 2; ledPin <= 7; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
}

void loop() {
  // Nyalakan 3 Led kiri
  for (int ledPin = 2; ledPin <= 4; ledPin++) {
    digitalWrite(ledPin, HIGH); // nyalakan LED kiri
  }

  for (int ledPin = 5; ledPin <= 7; ledPin++) {
    digitalWrite(ledPin, LOW); // pastikan LED kanan mati
  }

  delay(timer); // tunggu beberapa saat

  // Matikan Led
  for (int ledPin = 2; ledPin <= 7; ledPin++) {
    digitalWrite(ledPin, LOW);
  }

  delay(200); // jeda kecil agar perpindahan terlihat jelas

  // Menyalakan 3 Led kanan
  for (int ledPin = 5; ledPin <= 7; ledPin++) {
    digitalWrite(ledPin, HIGH); // nyalakan LED kanan
  }

  for (int ledPin = 2; ledPin <= 4; ledPin++) {
    digitalWrite(ledPin, LOW); // pastikan LED kiri mati
  }

  delay(timer); // tunggu beberapa saat

  //Matikan Semua LED
  for (int ledPin = 2; ledPin <= 7; ledPin++) {
    digitalWrite(ledPin, LOW);
  }

  delay(200); // jeda sebelum mengulang loop
}
```
