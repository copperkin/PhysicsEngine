#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "List.h"
#include "Vector.h"

class Particle;
typedef void (*callback)(Particle &p1, Particle &p2, float overlap);

class Behaviour
{
public:
	virtual void apply(Particle& p, float dt, int index) {}
};

class Collision : public Behaviour
{
public:
	Collision(bool useMass=true, callback callback=0);
    virtual void apply(Particle& p, float dt, int index);
	
	List<Particle*, 20> pool;

private:
	Vector _delta;
	
	callback _callback;
	bool _useMass;
};

class Attraction : public Behaviour
{
public:
	Attraction(float radius=100, float strength=100);
    virtual void apply(Particle& p, float dt, int index);
	
	void setStrength(float s) { _strength = s; }
	void setRadius(float r) { _radius = r; _radiusSq = r*r;}

	Vector target;
private:
	Vector _delta;
	float _radius, _radiusSq, _strength;
};

#endif // __BEHAVIOUR_H__