#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int adc = analogRead(pinPot);

  float volt = adc * (5.0 / 1023.0);
  int persen = map(adc, 0, 1023, 0, 100);

  Serial.print("Nilai ADC: ");
  Serial.print(adc);
  Serial.print(" ");
  Serial.print("Nilai Volt: ");
  Serial.print(volt);
  Serial.print(" ");
  Serial.print("Nilai %: ");
  Serial.print(persen);
  Serial.println("");

  // ===== LCD BARIS 1 (SEJAJAR) =====
  lcd.setCursor(0, 0);
  lcd.print("A:");
  lcd.print(adc);
  lcd.print("   "); // clear sisa

  lcd.setCursor(6, 0);
  lcd.print("V:");
  lcd.print(volt, 1); // 1 desimal biar muat
  lcd.print(" ");

  lcd.setCursor(12, 0);
  lcd.print(persen);
  lcd.print("% ");

  // ===== BARIS 2 (BAR) =====
  int panjangBar = map(adc, 0, 1023, 0, 16);

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}