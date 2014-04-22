#ifndef __INTEGRATOR_H__
#define __INTEGRATOR_H__

#include "List.h"
#include "Particle.h"

class Integrator
{
public:
    virtual void integrate(ParticleList &particles, float dt, float drag = 0.0f) = 0;
};

class Verlet : public Integrator
{
    // v = x - ox
    // x = x + (v + a * dt * dt)
public:
    virtual void integrate(ParticleList &particles, float dt, float drag)
	{
        Vector pos;

        float dtSq = dt * dt;

        for (int pi = 0; pi < particles.length(); pi++)
		{
			Particle* p = particles[pi];
            if (!p->is_fixed())
			{
                // Scale force to mass.;
                p->acc.scale(p->_massInv);

                // Derive velocity.
                p->vel.copy(p->pos).sub(p->old_pos);

                // Apply friction.
                if (drag > 0.0)
                    p->vel.scale(drag);

                // Apply forces to new position.
                pos.copy(p->pos).add(p->vel.add(p->acc.scale(dtSq)));

                // Store old position.
                p->old_pos.copy(p->pos);

                // update position.
                p->pos.copy(pos);

                // Reset forces.
                p->acc.clear();
			}
		}
	}
};
				
class Euler : public Integrator
{
public:
    // v += a * dt
    // x += v * dt

    virtual void integrate(ParticleList &particles, float dt, float drag)
	{
        Vector vel;
                
        for (int pi = 0; pi < particles.length(); pi++)
		{
			Particle* p = particles[pi];
            if (!p->is_fixed())
			{
                
                // Store previous location.
                p->old_pos.copy(p->pos);

                // Scale force to mass.
                p->acc.scale(p->_massInv);

                // Duplicate velocity to preserve momentum.
                vel.copy(p->vel);

                // Add force to velocity.
                p->vel.add(p->acc.scale(dt));

                // Add velocity to position.
                p->pos.add(vel.scale(dt));

                // Apply friction.
                if (drag > 0)
                    p->vel.scale(drag);

                // Reset forces.
                p->acc.clear();
			}
		}
	}
};

class ImprovedEuler : public Integrator
{
public:
    // x += (v * dt) + (a * 0.5 * dt * dt)
    // v += a * dt

    virtual void integrate(ParticleList &particles, float dt, float drag)
	{
		Vector acc, vel;

        float dtSq = dt * dt;

        for (int pi = 0; pi < particles.length(); pi++)
		{
			Particle* p = particles[pi];
            if (!p->is_fixed())
			{                
                // Store previous location.
                p->old_pos.copy(p->pos);

                // Scale force to mass.
				p->acc.scale(p->_massInv);

                // Duplicate velocity to preserve momentum.
                vel.copy(p->vel);

                // Duplicate force.
                acc.copy(p->acc);

                // Update position.
                p->pos.add(vel.scale(dt).add(acc.scale(0.5f * dtSq)));

                // Update velocity.
                p->vel.add(p->acc.scale(dt));

                // Apply friction.
                if (drag > 0.0)
                    p->vel.scale(drag);

                // Reset forces.
                p->acc.clear();
			}
		}
	}
};

#endif // __INTEGRATOR_H__