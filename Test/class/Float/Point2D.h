/**
 * Duomai.ADN Robot
 *
 * @author Bruce
 * @since 2014/06/30
 */
#ifndef POINT2D_H_
#define POINT2D_H_

#include "Point.h"

class point;
class point2d: public point {
public:
	point2d(float x, float y) :
		point(x), _y(y) {
	}

	float y() {
		return _y;
	}

protected:
	float _y;
};

#endif
