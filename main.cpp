#include "Physics.h"

int main()
{
	Verlet v;
	Physics physics(&v);

    // Design some behaviours for particles
    Attraction avoidMouse;
    Attraction pullToCenter;

	pullToCenter.target._x = 50.0;
    pullToCenter.target._y = 50.0;
    pullToCenter.setStrength(120);

    avoidMouse.setRadius(60);
    avoidMouse.setStrength(-1000);

    // Allow particle collisions to make things interesting
    Collision collision;

    for (int i = 0; i < 20; i++)
	{
        //Create a particle
        Particle* particle = new Particle();
        Vector position(i, 2*i);
        particle->setRadius(particle->_mass * 10);
        particle->moveTo(position);
        
        // Make it collidable
        collision.pool.append(particle);

        // Apply behaviours
        particle->behaviours.append(&avoidMouse);
		particle->behaviours.append(&pullToCenter);
		particle->behaviours.append(&collision);

        // Add to the simulation
        physics.particles.append(particle);
	}
 
    while(1)
		physics.step();

	return 0;
}
