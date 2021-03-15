#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include <vecmath.h>

using namespace std;

class ParticleSystem
{
public:

	ParticleSystem(int numParticles=0);

	int m_numParticles;
	
	// for a given state, evaluate derivative f(X,t)
	virtual vector<Vector3f> evalF(vector<Vector3f> state) = 0;
	
	// getter method for the system's state
	vector<Vector3f> getState(){ return m_vVecState; };
	
	// setter method for the system's state
	virtual void setState(const vector<Vector3f>  & newState) { m_vVecState = newState; };
	
	virtual void draw() = 0;
	


	//-----------------布面需要的函数-----------------------------------------
	virtual void set_drag_point(int fixed_x, int fixed_y, Matrix4f m, Matrix4f rotate, Vector3f transform) {};
	virtual void move_drag_point(int x, int y, Matrix4f m, Matrix4f rotate) {};
	virtual void release_drag_point() {};
	virtual void set_spring_type() {};
	virtual void set_wind() {};
	bool swing;
protected:

	vector<Vector3f> m_vVecState;
	
};

#endif
