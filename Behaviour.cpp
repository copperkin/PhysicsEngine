#include "Behaviour.h"
#include "Particle.h"


Collision::Collision(bool useMass, callback callback) : _useMass(useMass), _callback(callback)
{
}


void Collision::apply(Particle& p, float dt, int index)
{
    // Check pool for collisions.
    for (int i = index; i < pool.length(); i++)
	{
		Particle *o = pool[i];
        if (*o != p)
		{
            // Delta between particles positions.
            _delta.copy(o->pos).sub(p.pos);

            // Squared distance between particles.
            float distSq = _delta.mag_squared();

            // Sum of both radii.
            float radii = p._radius + o->_radius;

            // Check if particles collide.
            if (distSq <= radii*radii)
			{
                // Compute real distance.
                float dist = sqrt(distSq);

                // Determine overlap.
                float overlap = radii - dist;
                overlap += 0.5;

                // Total mass.
                float mt = p._mass + o->_mass;

                // Distribute collision responses.
				float r1 = _useMass ? o->_mass / mt : 0.5;
				float r2 = _useMass ? p._mass / mt : 0.5;

                // Move particles so they no longer overlap.
                p.pos.add(_delta.clone().norm().scale(overlap * -r1));
                o->pos.add(_delta.norm().scale(overlap * r2));

                // Fire callback if defined.
                if (_callback)
                    _callback(p, *o, overlap);
			}
		}
	}
}


Attraction::Attraction(float radius, float strength) : _strength(strength)
{
	setRadius(radius);
}

void Attraction::apply(Particle& p, float dt, int index)
{
	_delta.copy(target).sub(p.pos);

    // Squared distance to target.
    float distSq = _delta.mag_squared();

    // Limit force to behaviour radius.
    if (0.000001 < distSq && distSq < _radiusSq)
	{
        // Calculate force vector.
        _delta.norm().scale(1.0 - distSq / _radiusSq);
        // Apply force.
        p.acc.add(_delta.scale(_strength));
	}
}