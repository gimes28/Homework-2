
#include "wheel.h"

Wheel::Wheel() {
	lowBound = 1;
	upBound = 10;
}

void Wheel::spin() {
	spinVal = lowBound + (rand() % ((upBound - lowBound) + 1));
}

void Wheel::updateRange(int bound) {
	upBound = bound;
}
