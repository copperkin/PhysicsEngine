#ifndef __SPRING_H__
#define __SPRING_H__

#include "Vector.h"

class Spring
{
public:
	Spring() : _rest_length(100), _stiffness(1.0f) {}
	Spring(Particle& p1, Particle& p2, float rest_length=100, float stiffness=1.0) :
	  _p1(p1), _p2(p2), _rest_length(rest_length), _stiffness(stiffness) {}

    void apply()
	{
       ///F = -kx
        _delta.copy(_p2.pos).sub(_p1.pos);

        float dist = _delta.mag() + 0.000001f;
        float force = (dist - _rest_length) / (dist * (_p1._massInv + _p2._massInv)) * _stiffness;

        if (!_p1.is_fixed())
            _p1.pos.add(_delta.clone().scale(force * _p1._massInv));

        if (!_p2.is_fixed())
            _p2.pos.add(_delta.scale(-force * _p2._massInv));
	}

private:
	Vector _delta;
	Particle _p1, _p2;
	float _rest_length, _stiffness;

};

#endif // __SPRING_H__