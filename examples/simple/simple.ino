#include <Wire.h>
#include "PCF8574-IO-EXPANDER.h"

PCF8574_IO_EXPANDER pcf(0x20);  // Inisialisasi dengan alamat I2C 0x20

void setup() {
  pcf.begin();
  
  // Atur P0 sebagai output untuk mengontrol LED
  pcf.pinMode(0, OUTPUT);

  // Atur P1 sebagai input untuk membaca tombol
  pcf.pinMode(1, INPUT);
}

void loop() {
  // Membaca status tombol
  bool buttonState = pcf.digitalRead(1);
  
  // Nyalakan LED jika tombol ditekan
  if (buttonState == LOW) {  // Mengasumsikan tombol terhubung ke ground (aktif LOW)
    pcf.digitalWrite(0, HIGH); // Nyalakan LED
  } else {
    pcf.digitalWrite(0, LOW);  // Matikan LED
  }
}
