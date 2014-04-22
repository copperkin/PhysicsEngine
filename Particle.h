#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "vector.h"
#include "List.h"
#include "Behaviour.h"

class Particle
{
public:

	Particle(float mass = 1.0) 
	{
        // Set a unique id.
        _id = 0;//TODO

        // Set initial mass.
        setMass(mass);

        // Set initial radius.
        setRadius(1.0);

        // Apply forces.
        _fixed = false;
	}

    void moveTo(Vector &rpos)
	{
        /*Moves the particle to a given location vector.*/
        pos.copy(rpos);
        old_pos.copy(rpos);
	}

    void setMass(float mass=1.0)
	{
        /* Sets the mass of the particle. */
        _mass = mass;
        // The inverse mass.
        _massInv = 1.0f / _mass;
	}

    void setRadius(float radius=1.0)
	{
        /* Sets the radius of the particle. */
        _radius = radius;
        _radiusSq = _radius * _radius;
	}

    void update(float dt, int index)
	{
        /* Applies all behaviours to derive new force. */
        if (!_fixed)
		{
            for (int i = 0; i < behaviours.length(); i++)
			{
                behaviours[i]->apply(*this, dt, index);
			}
		}
	}

	bool operator ==(const Particle &rhs){ return _id == rhs._id; }
	bool operator !=(const Particle &rhs){ return _id != rhs._id; }

	bool is_fixed() { return _fixed; }

	Vector pos, vel, acc, old_pos, old_vel, old_acc;

	float _mass, _massInv;

	List<Behaviour*, 5> behaviours;

	float _radius, _radiusSq;

private:
	bool _fixed;
	int _id;
};

typedef List<Particle*, 20> ParticleList;

#endif //__PARTICLE_H__