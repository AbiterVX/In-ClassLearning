
#include "pendulumSystem.h"

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;
	
	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++) {		
		// for this system, we care about the position and the velocity
		Vector3f position(i*0.5, 0 , 1);
		Vector3f velocity(0 , 0 , 0);
		m_vVecState.push_back(position);
		m_vVecState.push_back(velocity);

		vector<Vector3f> connection;
		if (i != m_numParticles - 1) {
			Vector3f spring_attribute(i + 1,25 , 0.5);
			connection.push_back(spring_attribute);
		}
		if (i != 0) {
			Vector3f spring_attribute(i - 1, 25, 0.5);
			connection.push_back(spring_attribute);
		}
		spring_connect.push_back(connection);						
	}
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// YOUR CODE HERE
	Vector3f gravity(0, -9.8, 0);
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f sum_f(0,0,0);
		Vector3f velocity(0, 0, 0);
		if (i>0) {
			sum_f = sum_f + gravity;
			for (int j = 0; j < spring_connect[i].size(); j++) {
				Vector3f distance = state[i * 2] - state[spring_connect[i][j].x() * 2];
				float d = distance.abs();
				sum_f = sum_f + (-spring_connect[i][j].y()*(d - spring_connect[i][j].z()) * distance / d);
				sum_f = sum_f + 0.015*(-spring_connect[i][j].y()* state[i*2+1]);
			}
			velocity = state[i * 2 + 1];
		}				
		f.push_back(velocity);
		f.push_back(sum_f);
	}

	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos= m_vVecState[i*2];//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
