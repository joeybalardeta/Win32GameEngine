#include "Utils.h"
#include <assert.h>

unsigned int Utils::RGBtoHex(unsigned int r, unsigned int g, unsigned int b) {
	assert(r <= 255 && r >= 0);
	assert(g <= 255 && g >= 0);
	assert(b <= 255 && b >= 0);

	return (0x010000 * r) + (0x000100 * g) + (0x000001 * b);
}
