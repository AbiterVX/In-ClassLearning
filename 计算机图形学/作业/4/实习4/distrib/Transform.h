#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
public: 
	Transform(){}
	Transform( const Matrix4f& m, Object3D* obj ):o(obj){
		Transform::m = m;
		Transform::o = obj;
	}
	~Transform(){
	}
	
	
	
	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		Matrix4f m_inverse=m.inverse();
		Vector4f r_origin(r.getOrigin(),1);
		Vector4f r_direction(r.getDirection(), 0);

		Vector3f new_r_origin= (m_inverse*r_origin).xyz();
		Vector3f new_r_direction=(m_inverse*r_direction).xyz();
		//new_r_direction.normalize();

		Ray new_ray(new_r_origin, new_r_direction);

		bool state = o->intersect(new_ray, h, tmin);			//是否有交点
		if (state) {
			Vector4f hit_normal(h.getNormal(),0);
			h.set(h.getT(),h.getMaterial(), (m_inverse.transposed()*hit_normal).xyz().normalized());
			return true;
		}

		return false;
	}


protected:
	Object3D* o; //un-transformed object	
	Matrix4f m;

};

#endif //TRANSFORM_H
