#include "mbed.h"
#include "i2c_master.h"

I2C_Master::I2C_Master(PinName sda, PinName scl, uint32_t frequency) : m_i2c_sensor(sda, scl)
{
  m_i2c_sensor.frequency(frequency);
}

void I2C_Master::i2c_write(uint8_t slave_addr, uint8_t register_addr, const uint8_t data)
{
  char writeArray[2] = {register_addr, data};
  m_i2c_sensor.write(slave_addr, writeArray, 2, false);
}

void I2C_Master::i2c_writeBits(uint8_t slave_addr, uint8_t register_addr, const uint8_t data, uint8_t mask)
{
  char current_value;
  char writeArray[2] = {register_addr, data};

  //Get current value of desired register and mask it with mask-value
  current_value = i2c_read(slave_addr, register_addr);
  current_value &= ~mask;

  //Combine Data with the new data (additionaly masking the data) and send it to the Sensor
  writeArray[1] = current_value | (data & mask);

  m_i2c_sensor.write(slave_addr, writeArray, 2, false);
}

void I2C_Master::i2c_readSeries(uint8_t slave_addr, uint8_t register_addr, uint8_t *data, uint8_t length)
{
  char *data_array;
  data_array = reinterpret_cast<char *>(data);

  const char temp_address = register_addr;

  m_i2c_sensor.write(slave_addr, &temp_address, 1, true);
  m_i2c_sensor.read(slave_addr, data_array, length, false);
}

uint8_t I2C_Master::i2c_read(uint8_t slave_addr, uint8_t register_addr)
{
  char data;
  const char temp_address = register_addr;
  m_i2c_sensor.write(slave_addr, &temp_address, 1, true);
  m_i2c_sensor.read(slave_addr, &data, 1, false);
  return data;
}

uint8_t I2C_Master::i2c_readBits(uint8_t slave_addr, uint8_t register_addr, uint8_t mask)
{
  char data;
  const char temp_address = register_addr;
  m_i2c_sensor.write(slave_addr, &temp_address, 1, true);
  m_i2c_sensor.read(slave_addr, &data, 1, false);
  return data & mask;
}