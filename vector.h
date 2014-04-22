#ifndef __vector_h__
#define __vector_h__

#include <math.h>

class Vector
{
public:

	static Vector add(Vector &v1, Vector &v2)
	{
        /*Adds two vectors and returns the product. */
        return Vector(v1._x + v2._x, v1._y + v2._y);
	}

    static Vector sub(Vector &v1, Vector &v2)
	{
        /*Subtracts v2 from v1 and returns the product.*/
        return Vector(v1._x - v2._x, v1._y - v2._y);
	}

    static Vector project(Vector &v1, Vector &v2)
	{
        /*Projects one vector (v1) onto another (v2)*/
        return v1.clone().scale(v1.dot(v2) / v1.mag_squared());
	}

	/*Creates a new Vector instance.*/
	Vector(float x = 0.0, float y = 0.0) : _x(x), _y(y) {}
	
	Vector& set(float x, float y)
	{
        /*Sets the components of this vector.*/
        _x, _y = x, y;
		return *this;
	}

    Vector& add(Vector &v)
	{
        /*Add a vector to this one.*/
        _x += v._x;
        _y += v._y;
        return *this;
	}

    Vector& sub(Vector &v)
	{
        /*Subtracts a vector from this one.*/
        _x -= v._x;
        _y -= v._y;
        return *this;
	}

    Vector& scale(float f)
	{
        /*Scales this vector by a value.*/
        _x *= f;
        _y *= f;
        return *this;
	}

    float dot(Vector &v)
	{
        /*Computes the dot product between vectors.*/
        return _x * v._x + _y * v._y;
	}

    float cross(Vector &v)
	{
        /*# Computes the cross product between vectors.*/
        return (_x * v._y) - (_y * v._x);
	}

    float mag()
	{
        /*Computes the magnitude (length).*/
        return sqrt(mag_squared());
	}

    float mag_squared()
	{
        /*Computes the squared magnitude (length).*/
        return _x * _x + _y * _y;
	}

    float dist(Vector &v)
	{
        /*Computes the distance to another vector.*/
        float dx = v._x - _x;
        float dy = v._y - _y;
        return sqrt(dx * dx + dy * dy);
	}

    float dist_squared(Vector &v)
	{
        /*# Computes the squared distance to another vector.*/
        float dx = v._x - _x;
        float dy = v._y - _y;
        return dx * dx + dy * dy;
	}

    Vector& norm()
	{
        /*# Normalises the vector, making it a unit vector (of length 1).*/
        float m = sqrt(_x * _x + _y * _y);
        _x /= m;
        _y /= m;
        return *this;
	}

    Vector& limit(float limit)
	{
        /*# Limits the vector length to a given amount.*/
        float m_sq = _x * _x + _y * _y;
        if (m_sq > (limit*limit))
		{
            float m = sqrt(m_sq);
            _x /= m;
            _y /= m;
            _x *= limit;
            _y *= limit;
		}
	}

    Vector& copy(Vector &v)
	{
        /*# Copies components from another vector.*/
        _x = v._x;
        _y = v._y;
        return *this;
	}

    Vector clone()
	{
        /*# Clones this vector to a new identical one.*/
        return Vector(_x, _y);
	}

    Vector& clear()
	{
        /*# Resets the vector to zero.*/
        _x = 0.0;
        _y = 0.0;
		return *this;
	}

	float _x, _y;
};

#endif  // __vector_h__
