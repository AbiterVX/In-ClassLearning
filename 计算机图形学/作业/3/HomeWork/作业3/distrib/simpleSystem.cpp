
#include "simpleSystem.h"

using namespace std;

SimpleSystem::SimpleSystem()
{
	m_numParticles = 1;
	Vector3f position(1,1,0);
	Vector3f velocity(0, 0, 0);
	m_vVecState.push_back(position);
	m_vVecState.push_back(velocity);
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
	// YOUR CODE HERE

	for (int i = 0; i < m_numParticles; i++) {
		Vector3f velocity(-state[i*2].y(), state[i*2].x(),0);
		Vector3f sum_f(0,0,0);
		f.push_back(velocity);
		f.push_back(sum_f);
	}
	
	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{
	Vector3f pos ;//YOUR PARTICLE POSITION
	pos = m_vVecState[0];
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2] );
	glutSolidSphere(0.075f,10.0f,10.0f);
	glPopMatrix();
}
