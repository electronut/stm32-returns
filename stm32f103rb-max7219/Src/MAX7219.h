/*
 * MAX7219.h
 *
 *  Created on: 29-Sep-2017
 *      Author: mahesh
 */

#ifndef MAX7219_H_
#define MAX7219_H_

#include "stm32f1xx_hal.h"

#include "BitBuf88.h"

// MAX7219 register addresses
typedef enum _MAX7129_REG
{
	eMAX7129_REG_Noop = 0x0,
	eMAX7129_REG_D0   = 0x1,
	eMAX7129_REG_D1   = 0x2,
	eMAX7129_REG_D2   = 0x3,
	eMAX7129_REG_D3   = 0x4,
	eMAX7129_REG_D4   = 0x5,
	eMAX7129_REG_D5   = 0x6,
	eMAX7129_REG_D6   = 0x7,
	eMAX7129_REG_D7   = 0x8,
	eMAX7129_REG_DecodeMode = 0x9,
	eMAX7129_REG_Intensity = 0xa,
	eMAX7129_REG_ScanLimit = 0xb,
	eMAX7129_REG_Shutdown = 0xc,
	eMAX7129_REG_DisplayTest = 0xf
} MAX7129_REG;

class MAX7219 {
public:
	MAX7219(SPI_HandleTypeDef* hSPI);
	virtual ~MAX7219();

	// send 16 bit data packet
	void sendPacket(MAX7129_REG reg, uint8_t data);

	// power on/off
	void power(bool on);

	// set intensity
	void setIntensity(uint8_t val);

	// set scan limit
	void setScanLimit(uint8_t dig);

	// clear all LEDs
	void clear();

	// set the whole display with an 8x8 buffer
	void setBuffer(const BitBuf88& buf);

private:

	const SPI_HandleTypeDef* _hSPI;
};

#endif /* MAX7219_H_ */
