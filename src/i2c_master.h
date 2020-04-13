/**
 * @file i2c_master.h
 * @author Joel von Rotz (joel.vonrotz@maxonmotor.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Copyright (c) 2019, maxon motor ag, All Rights Reserved
 * 
 */
#ifndef _I2C_MASTER_H
#define _I2C_MASTER_H
#include "mbed.h"

class I2C_Master
{
public:
  /**
   * @brief Construct a new i2c master object
   * 
   * @param sda Pin-Designator of the SDA-Pin (ex. p10)
   * @param scl Pin-Designator of the SDA-Pin (ex. p9)
   * @param frequency I2C speed-frequency in Hz (defaults 400kHz)
   */
  I2C_Master(PinName sda, PinName scl, uint32_t frequency = 400000);

  /**
   * @brief Write a single byte to the specified register
   * 
   * @param slave_addr Slave address of the I2C Device (ex. 0x52)
   * @param register_addr Register address of the I2C Device
   * @param data Data that gets written into register address
   */
  void i2c_write(uint8_t slave_addr, uint8_t register_addr, const uint8_t data);

  /**
   * @brief Writes specific Bits
   * 
   * @param slave_addr Slave address of the I2C Device (ex. 0x52)
   * @param register_addr Register address of the I2C Device 
   * @param data Data that gets written into register address
   * @param mask Mask for writing data into register address
   */
  void i2c_writeBits(uint8_t slave_addr, uint8_t register_addr, const uint8_t data, uint8_t mask);

  /**
   * @brief Reads specific Bits
   * 
   * @param slave_addr Slave address of the I2C Device (ex. 0x52)
   * @param register_addr Register address of the I2C Device 
   * @param mask Mask to hide unwanted bits
   * @return uint8_t Read masked value
   */
  uint8_t i2c_readBits(uint8_t slave_addr, uint8_t register_addr, uint8_t mask);

  /**
   * @brief Reads a series of Bytes
   * 
   * @param slave_addr Slave address of the I2C Device (ex. 0x52)
   * @param register_addr Register address of the I2C Device 
   * @param data Pointer to array, so data can be saved onto it.
   * @param length Length of desired read bytes
   */
  void i2c_readSeries(uint8_t slave_addr, uint8_t register_addr, uint8_t *data, uint8_t length);

  /**
   * @brief Reads single Byte
   * 
   * @param slave_addr Slave address of the I2C Device (ex. 0x52)
   * @param register_addr Register address of the I2C Device 
   * @return uint8_t Read Byte
   */
  uint8_t i2c_read(uint8_t slave_addr, uint8_t register_addr);

private:
  I2C m_i2c_sensor;
  uint32_t m_i2c_frequency;
};

#endif