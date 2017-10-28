/*
 * BitBuf88.h
 *
 * An 8x8 1-bit buffer for LED display
 *
 * Author: Mahesh Venkitchalam
 * Website: electronut.in
 */

#ifndef BITBUF88_H_
#define BITBUF88_H_

// 8x8 1-bit buffer for LED display
struct BitBuf88
{
	// constr
	BitBuf88() {
		clearAll();
	}
	// destr
	virtual ~BitBuf88() {}

	// set (i, j)
	void set(uint8_t i, uint8_t j) {
		_vals[i] |= (1 << j);
	}

	// clear (i, j)
	void clr(uint8_t i, uint8_t j) {
		_vals[i] &= ~(1 << j);
	}

	// get (i, j)
	bool get(uint8_t i, uint8_t j) {
		return _vals[i] & (1 << j) ? true : false;
	}

	// clear all bits
	void clearAll() {
		for(uint8_t i = 0; i < 8; i++) {
			_vals[i] = 0;
		}
	}

	// vals[i] represents digit (column) and bits vals[i][0:7] the rows
	uint8_t _vals[8];
};





#endif /* BITBUF88_H_ */
