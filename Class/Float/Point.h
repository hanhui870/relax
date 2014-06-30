/**
 * Duomai.ADN Robot
 *
 * @author Bruce
 * @since 2014/06/30
 */
#ifndef POINT_H_
#define POINT_H_

class point{
public:
	point(float x) :
		_x(x) {
	}

	float x(){
		return _x;
	}

	protected:
	float _x;
};

#endif
