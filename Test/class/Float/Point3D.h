/**
 * Duomai.ADN Robot
 *
 * @author Bruce
 * @since 2014/06/30
 */
#ifndef POINT3D_H_
#define POINT3D_H_

#include "Point2d.h"

class point3d: public point2d{
public:
	point3d(float x, float y, float z):
		point2d(x, y), _z(z){
	}

	float z() {
		return _z;
	}

protected:
	float _z;
};

#endif
