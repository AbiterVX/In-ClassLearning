#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include <vecmath.h>
#include <vector>
#ifdef _WIN32
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"

class PendulumSystem: public ParticleSystem
{
public:
	PendulumSystem(int numParticles);	
	vector<Vector3f> evalF(vector<Vector3f> state);
	void draw();
	
	vector<vector<Vector3f>> spring_connect;  // n 粒子下标,k 弹性系数 ,r 弹簧原长
};

#endif
