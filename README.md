# mbed I2C-Master

## 🦮 How to Use

As it is with all other C/C++-libraries, add following line to your main program to include the library.

```cpp
#include "i2c_master.h"
```

After you did this, you can declare & initialize an `I2C-Master`-object

```cpp
#include "mbed.h"
#include "i2c_master.h"

//declare I2C-Master object with pins 9 & 10 + frequency of 400kHz
I2C_Master i2c_device(p9, p10);
```

## 📚 Functions

### Class-Constructor

```cpp
I2C_Master(PinName sda, PinName scl, uint32_t frequency = 400000)

//Example
I2C_Master i2c_device(p9, p10, 100000);
```

### `i2c_write` Write Single Byte

```cpp
void i2c_write(uint8_t slave_addr, uint8_t register_addr, const uint8_t data);

//Example
i2c_device.i2c_write(0x23, 0x55, 0x12);
```

### `i2c_read` Read single Byte

```cpp
uint8_t i2c_read(uint8_t slave_addr, uint8_t register_addr);

//Example
uint8_t mostlyBits = i2c_device.i2c_read(0x23, 0x12);
```

### `i2c_writeBits` Write specific Bits

This function does following things chronologically:

1. Read out byte from the register address
2. Apply mask onto read byte
3. `XOR` data onto the masked byte
4. Write the data back onto the register address

Doing this way allows the other unspecified bits to be ignored (they keep their value).

```cpp
void i2c_writeBits(uint8_t slave_addr, uint8_t register_addr, const uint8_t data, uint8_t mask);

//Example
i2c_device.i2c_writeBits(0x23, 0x55, 0x12, 0x1);
```

### `i2c_readBits` Read Bits

Reads a single byte from an register, applies the defined mask onto it and returns it.

```cpp
uint8_t i2c_readBits(uint8_t slave_addr, uint8_t register_addr, uint8_t mask);

//Example
uint8_t mostlyBits = i2c_device.i2c_readBits(0x23, 0x25, 0x10);
```

### `i2c_readSeries` Read a Series of Bytes

Read bytes will be saved onto the referenced `data`-array.

```cpp
void i2c_readSeries(uint8_t slave_addr, uint8_t register_addr, uint8_t *data, uint8_t length);

//Example
uint8_t dataLicious[8];

i2c_device.i2c_readSeries(0x23, 0x55, dataLicious, 8);
```
