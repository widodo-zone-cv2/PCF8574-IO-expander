#ifndef LIBS_PCF8574_IO_EXPANDER_H
#define LIBS_PCF8574_IO_EXPANDER_H
#include <Wire.h>

class PCF8574_IO_EXPANDER
{
private:
    uint8_t _address;   // Alamat I2C dari PCF8574
    uint8_t _data;      // Variabel untuk menyimpan status dari 8 pin I/O
    uint8_t _readData;  // Variabel untuk menyimpan status pembacaan pin
    bool _inputMode[8]; // Array untuk menentukan apakah pin dalam mode input atau output

public:
    // Konstruktor untuk mengatur alamat I2C
    PCF8574_IO_EXPANDER(uint8_t address)
    {
        _address = address;
        _data = 0xFF; // Default semua pin HIGH (karena menggunakan pull-up pada mode input)
    }

    // Inisialisasi PCF8574
    void begin()
    {
        Wire.begin();
    }

    // Mengatur mode dari setiap pin (input atau output)
    void pinMode(uint8_t pin, uint8_t mode)
    {
        if (pin < 8)
        {
            if ((mode == INPUT) || (mode == INPUT_PULLUP))
            {
                _inputMode[pin] = 1;
                _data |= (1 << pin); // Set bit sebagai HIGH (default input mode)
            }
            else
            {
                _inputMode[pin] = 0;
                _data &= ~(1 << pin); // Set bit sebagai LOW (output mode)
            }
            writeData(); // Kirim data ke PCF8574
        }
    }

    // Menulis nilai ke pin (Hanya berlaku untuk pin output)
    void digitalWrite(uint8_t pin, bool value)
    {
        if (pin < 8 && !_inputMode[pin])
        {
            if (value)
            {
                _data |= (1 << pin); // Set pin ke HIGH
            }
            else
            {
                _data &= ~(1 << pin); // Set pin ke LOW
            }
            writeData(); // Kirim data ke PCF8574
        }
    }

    // Membaca nilai dari pin (Hanya berlaku untuk pin input)
    bool digitalRead(uint8_t pin)
    {
        if (pin < 8 && _inputMode[pin])
        {
            readData();                                   // Baca status dari semua pin
            return (_readData & (1 << pin)) ? HIGH : LOW; // Kembalikan status pin
        }
        return LOW; // Jika bukan input, kembalikan LOW
    }

private:
    // Mengirim data ke PCF8574
    void writeData()
    {
        Wire.beginTransmission(_address);
        Wire.write(_data); // Tulis byte ke PCF8574
        Wire.endTransmission();
    }

    // Membaca data dari PCF8574
    void readData()
    {
        Wire.requestFrom(_address, (uint8_t)1);
        if (Wire.available())
        {
            _readData = Wire.read(); // Simpan byte yang diterima
        }
    }
};

#endif
