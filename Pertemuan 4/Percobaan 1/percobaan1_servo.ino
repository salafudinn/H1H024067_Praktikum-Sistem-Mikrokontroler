#include <Servo.h> // library untuk servo motor

Servo myservo; // membuat objek servo

// ===================== PIN SETUP =====================
// Berdasarkan gambar: Potensio ke A0, Servo ke Pin 9
const int potensioPin = A0;   // Pin analog input A0
const int servoPin = 9;      // Pin digital PWM 9

// ===================== VARIABEL =====================
int pos = 0; // Variabel sudut (0-180)
int val = 0; // Variabel pembacaan ADC (0-1023)

void setup() {
  // Hubungkan servo ke pin 9
  myservo.attach(servoPin); 

  // Aktifkan komunikasi serial untuk monitoring
  Serial.begin(9600); 
}

void loop() {
  // ===================== PEMBACAAN ADC =====================
  // Baca nilai dari potensiometer
  val = analogRead(potensioPin); 

  // ===================== KONVERSI DATA =====================
  // Mapping nilai ADC (0-1023) ke sudut servo (0-180)
  pos = map(val, 0, 1023, 0, 180);  

  // ===================== OUTPUT SERVO =====================
  // Gerakkan servo sesuai hasil mapping
  myservo.write(pos); 

  // ===================== MONITORING DATA =====================
  Serial.print("ADC Potensio: ");
  Serial.print(val); 

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos); 

  // ===================== STABILISASI =====================
  delay(10); // Delay standar untuk pergerakan servo yang halus
}