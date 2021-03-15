#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere : public Object3D
{
public:
	Sphere() {
		//unit ball at the center
		center = Vector3f::ZERO;
		radius = 0;
	}
	Sphere(Vector3f center, float radius, Material* material) :Object3D(material) {
		Sphere::center = center;
		Sphere::radius = radius;
	}
	~Sphere() {}


	virtual bool intersect(const Ray& r, Hit& h, float tmin) {			//求交

		float a = Vector3f::dot(r.getDirection(),r.getDirection());		// r.getDirection() *r.getDirection();										//系数a
		float b = 2 * Vector3f::dot(r.getDirection(), (r.getOrigin() - center));						//系数b，注意球心坐标不一定时原点
		float c = Vector3f::dot((r.getOrigin() - center), (r.getOrigin() - center)) - radius* radius;	//系数c
		float delta = b*b - 4 * a*c;																	//判别式
		
		if (delta<0) {								//判别式小于0，无交点
			return false;
		}
		else if (delta == 0) {						//判别式等于0，有一个交点
			float t = -b / (2 * a);					
			if (t >= tmin) {
				return set_hit_t(h, t, r);
				//return true;
			}
			else {
				return false;
			}
		}
		else {										//判别式大于0，有两个交点
			float d = sqrt(delta);					//
			float t_plus = (-b + d) / (2 * a);		//t1
			float t_minus = (-b - d) / (2 * a);		//t2

			if (t_minus >= tmin) {					//两个t都大于tmin
				return set_hit_t(h, t_minus, r);			//只取最小的t
				//return true;
			}
			else {									//tmin<较小的t
				if (t_plus >= tmin) {				//较大的t大于tmin
					return set_hit_t(h, t_plus, r);
					//return true;
				}
				else {								//较大的t小于tmin，无交点。
					return false;
				}
			}
		}
	}

	bool set_hit_t(Hit& h, float t, Ray r) {								//设置hit交点的t
		if (t < h.getT()) {													//如果当前hit内的t大于要更新的t
			Vector3f intersection = r.pointAtParameter(t);	//交点坐标，根据公式得出
			Vector3f normal = intersection - center;						//法向量
			normal.normalize();

			h.set(t, material, normal);
			return true;
		}
		return false;
	}

protected:
	Vector3f center;		//球心
	float radius;			//球半径

};


#endif
