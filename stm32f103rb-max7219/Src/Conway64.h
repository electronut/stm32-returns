/*
 * Conway.h
 *
 * Conway's Game of Life on an 8x8 grid
 *
 * Author: Mahesh Venkitchalam
 * Website: electronut.in
 *
 */

#ifndef CONWAY64_H_
#define CONWAY64_H_

#include <stdint.h>
#include "cmsis_os.h"

#include "MAX7219.h"

class Conway64 {
public:
	Conway64(SPI_HandleTypeDef* hSPI);
	virtual ~Conway64();

	// initialize
	void init();

	// add glider with top left cell at (i, j)
	void addGlider(int i, int j);

	void addBlinker(int i, int j);

	// update simulation
	void update();

	// render to LED grid
	void render();

	// signal to thread
	void signal();

	// test init SPI
	void testInit();

	// test SPI
	void test();

private:


	BitBuf88 _grid;

	MAX7219* _max7219;

	osThreadId _conwayTaskHandle;
};

#endif /* CONWAY64_H_ */
