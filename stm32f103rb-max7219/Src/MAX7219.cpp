/*
 * MAX7219.cpp
 *
 *  Created on: 29-Sep-2017
 *      Author: mahesh
 */

#include "MAX7219.h"

MAX7219::MAX7219(SPI_HandleTypeDef* hSPI)
	:_hSPI(hSPI)
{
	// TODO Auto-generated constructor stub

}

MAX7219::~MAX7219() {
	// TODO Auto-generated destructor stub
}

// send 16 bit data packet
void MAX7219::sendPacket(MAX7129_REG reg, uint8_t data)
{
	// CS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

	//uint16_t packet = (reg << 8) | data;
	uint8_t packet[2];
	packet[0] = reg;
	packet[1] = data;

	HAL_SPI_Transmit(const_cast<SPI_HandleTypeDef*>(_hSPI), (uint8_t*)&packet, 2, 100);

	// CS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

}

void MAX7219::power(bool on)
{
	uint8_t val = on? 1 : 0;
	sendPacket(eMAX7129_REG_Shutdown, val);
}

void MAX7219::setIntensity(uint8_t val)
{
	sendPacket(eMAX7129_REG_Intensity, val & 0xf);
}

void MAX7219::setScanLimit(uint8_t dig)
{
	sendPacket(eMAX7129_REG_ScanLimit, dig & 0x7);
}

// turn all LEDs off
void MAX7219::clear()
{
	for (int j = 0 ; j < 8; j++) {
		sendPacket(static_cast<MAX7129_REG>(j+1), 0);
	}
}

// set the whole display with an 8x8 buffer
void MAX7219::setBuffer(const BitBuf88& buf)
{
	for (int j = 0 ; j < 8; j++) {
		sendPacket(static_cast<MAX7129_REG>(j+1), buf._vals[j]);
	}
}
