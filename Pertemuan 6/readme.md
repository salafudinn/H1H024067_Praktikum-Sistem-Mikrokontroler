# Laporan Praktikum Sistem Mikrokontroler

# Modul 6: Interrupt dan Timer



Nama: MUHAMMAD IMAM SALAFUDIN  

NIM: H1H024067  



---

## pertanyaan Praktikum 6 Percobaan 1



1. Jelaskan proses bagaimana tombol dapat mengubah kondisi LED menggunakan

interrupt!!





Ketika mikrokontroler sedang mengeksekusi program utama di dalam fungsi `loop()`, 

tombol yang ditekan akan memicu perubahan sinyal digital pada pin eksternal (Pin 2). Perubahan sinyal ini terdeteksi oleh \*hardware\* interupsi, yang secara instan menghentikan sementara program utama. Mikrokontroler kemudian melompat untuk mengeksekusi fungsi khusus bernama \*Interrupt Service Routine\* (ISR).

Di dalam ISR tersebut, nilai variabel `ledState` dibalik (\*toggle\*). Setelah ISR selesai dieksekusi, mikrokontroler kembali melanjutkan program utama di titik terakhir ia ditinggalkan, lalu menerapkan status logika `ledState` terbaru ke LED melalui perintah `digitalWrite`.



2. Apa fungsi attachInterrupt() pada program tersebut?





Fungsi `attachInterrupt()` digunakan untuk mendaftarkan dan menghubungkan pin interrupt perangkat keras dengan fungsi ISR kustom yang telah dibuat. Fungsi ini memberitahu mikrokontroler mengenai tiga hal: pin mana yang harus diawasi (Pin 2), 

fungsi apa yang harus dijalankan saat pemicu terjadi (`tombolInterrupt`), dan mode transisi sinyal apa yang menjadi syarat pemicunya (misalnya `FALLING`).



&#x20;   

3. Mengapa pada ISR tidak disarankan menggunakan delay() dan Serial.print()?





Fungsi ISR dirancang untuk mengeksekusi perintah secepat dan sesingkat mungkin karena selama ISR berjalan, aliran program utama dibekukan (\*blocking\*). Fungsi `delay()` bergantung pada interupsi timer internal untuk bekerja. Namun, saat mikrokontroler berada di dalam fungsi ISR, 

semua interupsi lain akan dinonaktifkan sementara. Akibatnya, `delay()` tidak akan pernah tereksekusi dan menyebabkan sistem \*hang\* (berhenti total).

Hal yang sama berlaku untuk `Serial.print()` yang membutuhkan waktu komputasi panjang dan juga mengandalkan interupsi latar belakang.





4. Apa fungsi keyword volatile pada variabel ledState?





Keyword `volatile` berfungsi untuk memberi tahu \*compiler\* bahwa nilai dari variabel tersebut dapat berubah sewaktu-waktu oleh proses eksternal di luar alur normal program (yakni oleh fungsi ISR). Hal ini mencegah \*compiler\* melakukan optimasi pada saat membaca memori, 

sehingga mikrokontroler dipaksa untuk selalu mengambil dan membaca nilai terbaru variabel tersebut langsung dari RAM utama (bukan dari salinan \*cache\*).





5. Pada percobaan digunakan mode interrupt FALLING. Modifikasikan program

menggunakan mode interrupt lain (RISING, CHANGE, atau LOW) kemudian:

• Jelaskan perbedaan cara kerja masing-masing mode interrupt tersebut

• Analisis perubahan perilaku LED yang terjadi pada setiap mode

• Sertakan source code dan penjelasan program dalam bentuk README.md





```cpp

\#include <Arduino.h>



volatile bool ledState = false;



void tombolInterrupt() {

&#x20; ledState = !ledState;

}



void setup() {

&#x20; pinMode(13, OUTPUT);

&#x20; pinMode(2, INPUT\_PULLUP);

&#x20; 

&#x20; // Modifikasi dipicu oleh transisi CHANGE

&#x20; attachInterrupt(digitalPinToInterrupt(2), tombolInterrupt, CHANGE);

}



void loop() {

&#x20; digitalWrite(13, ledState);

}

```





\## pertanyaan Praktikum 6 Percobaan 2





1\. \*\*Jelaskan bagaimana fungsi millis() bekerja pada program tersebut!\*\*





Fungsi millis() menghitung dan mengembalikan waktu berjalan sistem (dalam satuan milidetik) yang dihitung sejak perangkat dinyalakan atau di-reset. Pada program ini, 

ia berfungsi sebagai stopwatch. Sistem secara terus-menerus mengambil waktu berjalan saat ini (currentMillis) dan membandingkannya dengan rekam jejak waktu terakhir (previousMillis). Jika selisih waktunya sudah mencapai nilai interval yang ditetapkan,

program akan mengubah logika lampu LED lalu memperbarui rekam jejak waktunya dengan waktu saat itu.





2\. \*\*Apa perbedaan utama antara delay() dan millis()?\*\*





delay() bersifat blocking. Perintah ini akan menghentikan seluruh aktivitas eksekusi CPU selama jeda yang ditentukan. Sistem menjadi buta terhadap instruksi lain, 

tidak bisa merespons sensor, maupun memproses logika lanjutan selama jeda berlangsung.





millis() bersifat non-blocking. Fungsi ini hanya bertugas mengukur pencatatan waktu. 

Mikrokontroler bebas terus melanjutkan pembacaan baris kode secara berulang-ulang tanpa harus membeku menunggu interval terpenuhi.





3\. \*\*Mengapa metode millis() disebut non-blocking?\*\*





Karena millis() tidak menghambat komputasi alur program di bawahnya. Mikrokontroler hanya akan mengeksekusi statement pengubah lampu apabila interval waktunya sudah melampaui kondisi if-nya.

Pada sisa milidetik lainnya, mikrokontroler akan mengabaikan blok if tersebut dan dapat melakukan pekerjaan instruksional lainnya (seperti membaca sensor atau mendengarkan input komunikasi),

&#x20;sehingga metode ini sangat penting untuk mendukung rutinitas multitasking.



&#x20;4. \*\*Modifikasi program agar:

• LED pertama berkedip setiap 1 detik

• LED kedua berkedip setiap 500 ms

• Tanpa menggunakan delay()

Berikan penjelasan setiap baris program dalam bentuk README.md\*\*





```cpp

\#include <Arduino.h>



// Deklarasi waktu terakhir LED berubah status

unsigned long previousMillis1 = 0; 

unsigned long previousMillis2 = 0;



// Konstanta interval kedip

const long interval1 = 1000; // LED 1 berkedip setiap 1000 ms (1 detik)

const long interval2 = 500;  // LED 2 berkedip setiap 500 ms (0.5 detik)



// Status logika LED saat ini

bool ledState1 = false;

bool ledState2 = false;



// Alokasi pin untuk LED 

const int pinLED1 = 13;

const int pinLED2 = 12;



void setup() {

&#x20; pinMode(pinLED1, OUTPUT);

&#x20; pinMode(pinLED2, OUTPUT);

}



void loop() {

&#x20; unsigned long currentMillis = millis();

&#x20; 

&#x20; // Kontrol interval LED 1 (1 detik)

&#x20; if(currentMillis - previousMillis1 >= interval1) {

&#x20;   previousMillis1 = currentMillis;   

&#x20;   ledState1 = !ledState1;            

&#x20;   digitalWrite(pinLED1, ledState1);  

&#x20; }



&#x20; // Kontrol interval LED 2 (500 ms)

&#x20; if(currentMillis - previousMillis2 >= interval2) {

&#x20;   previousMillis2 = currentMillis;   

&#x20;   ledState2 = !ledState2;            

&#x20;   digitalWrite(pinLED2, ledState2);  

&#x20; }

}

