# PCF8574-IO-expander Library
## Deskripsi
Library ini dirancang untuk memudahkan penggunaan ekspander GPIO PCF8574 yang berkomunikasi melalui protokol I2C. PCF8574 menyediakan 8 pin input/output yang dapat digunakan untuk memperluas kemampuan mikrokontroler seperti ESP32, Arduino, atau perangkat lainnya dengan antarmuka I2C.

Dengan menggunakan library ini, Anda dapat dengan mudah mengatur mode input dan output untuk setiap pin, serta membaca dan menulis data ke pin tersebut tanpa perlu menggunakan library pihak ketiga. Library ini dirancang untuk mengelola pengaturan input dengan pull-up bawaan dari PCF8574, serta mengendalikan pin output secara efektif.

## Fitur
Mengelola hingga 8 pin GPIO melalui bus I2C.
Dukungan untuk mode input, input dengan pull-up, dan output.
Pembacaan status pin dalam mode input.
Penulisan status pin dalam mode output.
Operasi menggunakan protokol I2C standar, sehingga dapat digunakan dengan berbagai platform mikrokontroler.
Spesifikasi PCF8574
Protokol I2C: Berkomunikasi dengan mikrokontroler melalui bus I2C.
8-bit I/O: Menyediakan 8 pin yang dapat dikonfigurasi sebagai input atau output.
Pull-up Internal: Pada mode input, PCF8574 memiliki resistor pull-up internal yang membuat pin secara default berada pada kondisi HIGH.
Tegangan Operasional: 2.5V hingga 6V.
Sink Current: Mampu menarik arus hingga 25mA pada pin output.
Alamat I2C: Dapat dikonfigurasi melalui 3 pin alamat, memungkinkan hingga 8 perangkat PCF8574 terhubung pada satu bus I2C.
Konfigurasi alamat I2C:
<table>
  <thead>
    <tr>
      <th>A0</th>
      <th>A1</th>
      <th>A2</th>
      <th>ADDR</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0x20</td>
    </tr>
     <tr>
      <td>0</td>
      <td>0</td>
      <td>1</td>
      <td>0x21</td>
    </tr>
     <tr>
      <td>0</td>
      <td>1</td>
      <td>0</td>
      <td>0x22</td>
    </tr>
     <tr>
      <td>0</td>
      <td>1</td>
      <td>1</td>
      <td>0x23</td>
    </tr>
     <tr>
      <td>1</td>
      <td>0</td>
      <td>0</td>
      <td>0x24</td>
    </tr>
     <tr>
      <td>1</td>
      <td>0</td>
      <td>1</td>
      <td>0x25</td>
    </tr>
     <tr>
      <td>1</td>
      <td>1</td>
      <td>0</td>
      <td>0x26</td>
    </tr>
     <tr>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>0x27</td>
    </tr>
  </tbody>
</table>

## Instalasi
Untuk menggunakan library ini, Anda dapat menyalin file header dan implementasi ke dalam proyek Anda, atau ikuti langkah-langkah di bawah ini untuk mengintegrasikannya ke dalam Arduino IDE:

Unduh file ZIP dari repository GitHub ini.
Buka Arduino IDE, dan pilih Sketch -> Include Library -> Add .ZIP Library.
Pilih file ZIP yang diunduh dan library akan ditambahkan ke Arduino IDE.
## Penggunaan
1. Inisialisasi
Pertama, inisialisasi objek PCF8574 dengan alamat I2C perangkat:
```
PCF8574 pcf(0x20);  // Ganti 0x20 dengan alamat I2C dari perangkat PCF8574 Anda
```
Pada setup(), panggil metode begin() untuk memulai komunikasi I2C:
```
void setup() {
  pcf.begin();
}
```
2. Mengatur Mode Pin
Gunakan fungsi pinMode() untuk mengatur apakah pin sebagai input atau output:
```
pcf.pinMode(0, OUTPUT);        // Mengatur pin 0 sebagai output
pcf.pinMode(1, INPUT);         // Mengatur pin 1 sebagai input
pcf.pinMode(2, INPUT_PULLUP);  // Mengatur pin 2 sebagai input dengan pull-up
```
3. Menulis Data ke Pin Output
Gunakan digitalWrite() untuk menulis status HIGH atau LOW ke pin output:
```
pcf.digitalWrite(0, HIGH);  // Mengatur pin 0 ke HIGH
pcf.digitalWrite(0, LOW);   // Mengatur pin 0 ke LOW
```
4. Membaca Data dari Pin Input
Gunakan digitalRead() untuk membaca status pin input:
```
bool state = pcf.digitalRead(1);  // Membaca status pin 1
```
5. Contoh Lengkap
```
#include "PCF8574.h"

PCF8574 pcf(0x20);

void setup() {
  pcf.begin();
  
  // Mengatur pin 0 sebagai output
  pcf.pinMode(0, OUTPUT);
  
  // Mengatur pin 1 sebagai input dengan pull-up
  pcf.pinMode(1, INPUT_PULLUP);
}

void loop() {
  // Jika tombol pada pin 1 ditekan (terhubung ke ground)
  if (pcf.digitalRead(1) == LOW) {
    // Nyalakan LED pada pin 0
    pcf.digitalWrite(0, HIGH);
  } else {
    // Matikan LED pada pin 0
    pcf.digitalWrite(0, LOW);
  }
}
```
## Lisensi
Library ini dirilis di bawah lisensi MIT, yang berarti Anda bebas untuk menggunakan, memodifikasi, dan mendistribusikan library ini dengan syarat atribusi yang tepat diberikan.
