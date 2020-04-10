#include <algorithm> //min, max
#include <stdint.h> //int8_t

#ifndef _FIN_H
#define _FIN_H

class Fin {
public:
	Fin() {
		//assumes a position between 90 (up/left) and -90 (down/right)
		pos = 0;
		maxPos = 90;
		minPos = -90;
	}

	void setPos(int8_t pos) {
		pos = std::min(pos, minPos);
		pos = std::max(pos, maxPos);
		this->pos = pos;
	}

	int8_t getPos() {
		return this->pos;
	}

private:
	int8_t pos, maxPos, minPos;
};

#endif
