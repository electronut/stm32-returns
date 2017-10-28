/*
 * Conway.cpp
 *
 * Conway's Game of Life on an 8x8 grid
 *
 * Author: Mahesh Venkitchalam
 * Website: electronut.in

 */


#include "Conway64.h"

// The Conway Task function
void conwayTaskFunc(void const * arg)
{
	// The Joy of C++
	Conway64* conway = const_cast<Conway64*>(static_cast<const Conway64*>(arg));

	// enable for testing only
	//conway->testInit();

	// add a glider object
	conway->addGlider(0, 0);
	// draw it
	conway->render();

	// task loop
	for(;;)
	{
		// wait for signal
		osSignalWait (0x0001, osWaitForever);
		// draw
		conway->update();
		// slight delay
		osDelay(1);
	}
}

Conway64::Conway64(SPI_HandleTypeDef* hSPI)
{
	// create MAX7129
	_max7219 = new MAX7219(hSPI);
}

Conway64::~Conway64() {
	delete _max7219;
}

// initialize
void Conway64::init()
{
	// set up display
	_max7219->power(true);
	_max7219->setIntensity(5);
	_max7219->setScanLimit(7);
	_max7219->clear();

	// create Conway task
	osThreadDef(conwayTask, conwayTaskFunc, osPriorityNormal, 0, 128);
	_conwayTaskHandle = osThreadCreate(osThread(conwayTask), this);
}

// test init SPI
void Conway64::testInit()
{
	_max7219->power(true);
	_max7219->setIntensity(5);
	_max7219->setScanLimit(7);
	_max7219->clear();

#if 0
	// diagonal line
	for (int8_t i = 0; i < 8; i++) {
		for (int8_t j = 0; j < 8; j++) {
			if(i*j % 2) {
				_grid.set(i, j);
			}
		}
	}
#endif
	//addGlider(0, 0);

	for (int8_t i = 0; i < 8; i++) {
		for (int8_t j = 0; j < 8; j++) {
			_grid.set(i, j);
		}
	}
	_max7219->setBuffer(_grid);

	osDelay(1000);

	for (int8_t i = 0; i < 8; i++) {
		for (int8_t j = 0; j < 8; j++) {
			if(_grid.get(i, j)) {
				_grid.clr(i, j);
			}
			else {
				_grid.set(i, j);
			}
		}
	}
	_max7219->setBuffer(_grid);

}

void Conway64::addGlider(int i, int j)
{
	_grid.clr(i+0, j+0);_grid.set(i+0, j+1);_grid.clr(i+0, j+2);
	_grid.clr(i+1, j+0);_grid.clr(i+1, j+1);_grid.set(i+1, j+2);
	_grid.set(i+2, j+0);_grid.set(i+2, j+1);_grid.set(i+2, j+2);
}

void Conway64::addBlinker(int i, int j)
{
	_grid.set(i, j-1);_grid.set(i, j);_grid.set(i, j+1);
}

void Conway64::update()
{
	// From my book Python Playground
	// https://www.nostarch.com/pythonplayground

	// copy grid since we require 8 neighbors for calculation
    // and we go line by line
	BitBuf88 _newGrid = _grid;
	uint8_t N = 8;
	// compute 8-neighbour sum
	// using toroidal boundary conditions - x and y wrap around
	// so that the simulaton takes place on a toroidal surface.
	for(int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int total = 0;
			// count
			if(_grid.get(i, (uint8_t)(j-1)%N))
				total++;
			if(_grid.get(i, (j+1)%N))
				total++;
			if(_grid.get((uint8_t)(i-1)%N, j))
				total++;
			if(_grid.get((i+1)%N, j))
				total++;
			if(_grid.get((uint8_t)(i-1)%N, (uint8_t)(j-1)%N))
				total++;
			if(_grid.get((uint8_t)(i-1)%N, (j+1)%N))
				total++;
			if(_grid.get((i+1)%N, (uint8_t)(j-1)%N))
				total++;
			if(_grid.get((i+1)%N, (j+1)%N))
				total++;

			// apply Conway's rules
			if (_grid.get(i, j)) {
				if ((total < 2) || (total > 3)) {
					_newGrid.clr(i, j);
				}
			}
			else {
				if (total == 3) {
					_newGrid.set(i, j);
				}
			}
		}
	}

	// render
	_max7219->setBuffer(_newGrid);

	// update data
	_grid = _newGrid;
}

// render current contents of buffer
void Conway64::render()
{
	_max7219->setBuffer(_grid);
}

void Conway64::signal()
{
	osSignalSet (_conwayTaskHandle, 0x0001);
}

// test SPI
void Conway64::test()
{
	_max7219->setBuffer(_grid);
	osDelay(500);
	_max7219->clear();
	osDelay(500);
}
