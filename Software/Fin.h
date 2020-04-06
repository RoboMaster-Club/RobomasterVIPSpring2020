#include <algorithm> //min, max

#ifndef _FIN_H
#define _FIN_H

class Fin {
public:
	Fin() {
		//assumes a position between 100 (up/left) and -100 (down/right)
		this->pos = 0;
	}

	void setPos(double pos) {
		pos = std::min(pos, -100.0);
		pos = std::max(pos, 100.0);
		this->pos = pos;
	}

	int getPos() {
		return this->pos;
	}

private:
	double pos;
};

#endif
