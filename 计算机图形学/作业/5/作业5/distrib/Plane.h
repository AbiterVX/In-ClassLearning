#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane: public Object3D
{
public:
	Plane(){}
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m){
		Plane::normal = normal.normalized();
		Plane::d = -d;
	}
	~Plane(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		//Vector3f intersection = r.pointAtParameter();
		//float t= -(d+Vecto normal)/
		float n_dot_Rd = Vector3f::dot(normal,r.getDirection());
		if (n_dot_Rd!=0) {
			float t = -(d+ Vector3f::dot(normal,r.getOrigin())) / n_dot_Rd;
			if (t>=tmin) {
				if (t<h.getT()) {
					h.set(t,material,normal);
				}
				return true;
			}			
		}
		return false;
	}

protected:
	Vector3f normal;
	float d;

};
#endif //PLANE_H
		

