#include "TimeStepper.hpp"
#include<iostream>

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> next_state;
	vector<Vector3f> current_state = particleSystem->getState();
	vector<Vector3f> current_F = particleSystem->evalF(current_state);
	for (int i = 0; i < particleSystem->m_numParticles; i++) {			
		Vector3f state(	current_state[i * 2] + stepSize * current_F[i * 2]);			
		Vector3f velocity(current_F[i*2]+current_F[i * 2 + 1] * stepSize);

		next_state.push_back(state);
		next_state.push_back(velocity);
	}
	particleSystem->setState(next_state);
}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> next_state;
	vector<Vector3f> current_state = particleSystem->getState();
	vector<Vector3f> current_F = particleSystem->evalF(current_state);

	vector<Vector3f> fictitious_next_state;
	vector<Vector3f> fictitious_next_F;

	for (int i = 0; i < particleSystem->m_numParticles; i++) {
		Vector3f state(	current_state[i * 2] + stepSize * current_F[i * 2]);
		Vector3f velocity(current_F[i * 2] + current_F[i * 2 + 1] * stepSize);

		fictitious_next_state.push_back(state);
		fictitious_next_state.push_back(velocity);
	}
	fictitious_next_F= particleSystem->evalF(fictitious_next_state);

	for (int i = 0; i < particleSystem->m_numParticles; i++) {
		Vector3f state( current_state[i * 2] + stepSize / 2 * (current_F[i * 2] + fictitious_next_F[i * 2 ] )   );
		Vector3f velocity( current_F[i * 2] + stepSize / 2 * (current_F[i * 2 + 1] + fictitious_next_F[i * 2 + 1])); //* stepSize


		next_state.push_back(state);
		next_state.push_back(velocity);
	}
	particleSystem->setState(next_state);
}








