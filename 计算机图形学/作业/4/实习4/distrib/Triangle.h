#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
        ///@param a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m){
		Triangle::a = a;
		Triangle::b = b;
		Triangle::c = c;
		//normal = Vector3f::cross((b-a),(c-a));
		//normal.normalize();

		hasTex = false;
	}

	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin){
		Matrix3f A( a.x()-b.x(), a.x()-c.x(), ray.getDirection().x(),
					a.y()-b.y(), a.y()-c.y(), ray.getDirection().y(),
					a.z()-b.z(), a.z()-c.z(), ray.getDirection().z()	);
		Matrix3f matrix_beta(a.x() - ray.getOrigin().x(), a.x() - c.x(), ray.getDirection().x(),
							 a.y() - ray.getOrigin().y(), a.y() - c.y(), ray.getDirection().y(),
							 a.z() - ray.getOrigin().z(), a.z() - c.z(), ray.getDirection().z()   );
		Matrix3f matrix_gama(a.x() - b.x(), a.x() - ray.getOrigin().x(), ray.getDirection().x(),
							 a.y() - b.y(), a.y() - ray.getOrigin().y(), ray.getDirection().y(),
							 a.z() - b.z(), a.z() - ray.getOrigin().z(), ray.getDirection().z()   );
		Matrix3f matrix_t(a.x() - b.x(), a.x() - c.x(), a.x() - ray.getOrigin().x(),
						  a.y() - b.y(), a.y() - c.y(), a.y() - ray.getOrigin().y(),
						  a.z() - b.z(), a.z() - c.z(), a.z() - ray.getOrigin().z()    );
		float beta= matrix_beta.determinant()/A.determinant();
		float gama= matrix_gama.determinant()/A.determinant();
		float t= matrix_t.determinant()/A.determinant();

		if (beta+ gama<1 && beta>0 && gama>0) {
			if (t>=tmin) {
				if (t<hit.getT()) {
					Vector3f normal=(1- beta - gama)*normals[0]+ beta*normals[1]+ gama*normals[2];

					hit.setTexCoord((1 - beta - gama)*texCoords[0] + beta * texCoords[1] + gama * texCoords[2]);
					

					hit.set(t, material, normal);
				}
				return true;
			}
		}
		return false;
	}


	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:
	Vector3f a;
	Vector3f b;
	Vector3f c;
	//Vector3f normal;
};

#endif //TRIANGLE_H
