#include "Wolf.h"

Wolf::Wolf(int x, int y) : Animal('#', 1, x, y, 9, 5) {
}

Wolf* Wolf::Child() {
	return new Wolf(*this);
}