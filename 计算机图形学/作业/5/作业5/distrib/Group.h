#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group :public Object3D
{
public:
	Group() {

	}
	Group(int num_objects) {
		object_number = num_objects;
		objects = new Object3D*[num_objects];
	}
	~Group() {

	}

	virtual bool intersect(const Ray& r, Hit& h, float tmin) {		//求交
		bool intersected = false;
		for (int i = 0; i < object_number; i++) {
			bool state = objects[i]->intersect(r, h, tmin);			//是否有交点
			if (!intersected &&state) {
				intersected = true;
			}
		}
		return intersected;
	}
	void addObject(int index, Object3D* obj) {
		objects[index] = obj;
	}
	int getGroupSize() {
		return object_number;
	}

private:
	Object3D **objects;
	int object_number;

};

#endif

