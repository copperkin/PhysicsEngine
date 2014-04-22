#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Integrator.h"
#include "Spring.h"
#include <time.h>

class Physics
{
public:
	Physics(Integrator *integrator)
		:	_integrator(integrator),
			_timestep(1.0f / 60.0f),	// Fixed timestep.
			_viscosity(0.005f),		// Friction within the system.
			_time(0.0f),				// Time in seconds.
			_step(0.0f),				// Last step duration.
			_clock(0),				// Current time.
			_buffer(0.0f),			// Time buffer.
			_maxSteps(4)			// Max iterations per step.
	{}

    void integrate(float dt)
	{
        /*Performs a numerical integration step.*/

        // Drag is inversely proportional to viscosity.
        float drag = 1.0f - _viscosity;

        // Update particles / apply behaviours.
        for (int index = 0; index < particles.length(); index++)
		{
			Particle* particle = particles[index];
            for (int i = 0; i < behaviours.length(); i++)
			{
				behaviours[i]->apply(*particle, dt, index);
			}
            particle->update(dt, index);
		}

        // Integrate motion.
        _integrator->integrate(particles, dt, drag);

        // Compute all springs.
        for (int i = 0; i < springs.length(); i++)
            springs[i]->apply();
	}

    // Steps the system.
    void step()
	{
        // Initialise the clock on first step.
        if (_clock == 0)
            _clock = time(0);

        // Compute delta time since last step.
        time_t current_time = time(0);
        float delta = current_time - _clock;

        // Insufficient change.
        if (delta <= 0.0)
            return;

        // Update the clock.
        _clock = current_time;

        // Increment time buffer.
        _buffer += delta;

        // Integrate until the buffer is empty or until the
        // maximum amount of iterations per step is reached.
        int step = 0;
        while (_buffer >= _timestep && step < _maxSteps)
		{
            // Integrate motion by fixed timestep.
            integrate(_timestep);

            // Reduce buffer by one timestep.
            _buffer -= _timestep;

            // Increment running time.
            _time += _timestep;

            step += 1;
		}

        // Store step time for debugging.
        _step = time(0) - current_time;
	}

	List<Particle*, 20> particles;
	List<Behaviour*, 10> behaviours;
	List<Spring*, 5> springs;

private:
	Integrator *_integrator;
	float _timestep;
	float _viscosity;
	float _time;
	float _step;
	time_t _clock;
	float _buffer;
	int _maxSteps;
	
};

#endif //__PHYSICS_H__