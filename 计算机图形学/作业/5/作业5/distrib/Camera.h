#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
//#include <float.h>
#include <cmath>

#define M_PI 3.1415926	
class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay(const Vector2f& point) = 0;
	virtual float getTMin() const = 0;
	virtual ~Camera() {}
protected:
	Vector3f center;
	Vector3f direction;
	Vector3f up;
	Vector3f horizontal;

};


///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, float angle) {
		Camera::center = center;
		Camera::direction = direction;
		Camera::up = up;
		PerspectiveCamera::angle = angle;

		w = direction;								//W
		u = Vector3f::cross(w, up);					//U
		v = Vector3f::cross(u, w);					//V
		u.normalize();						
		v.normalize();
		w.normalize();
		screen_width = 2 * distance*tan(angle / 2);	//图片宽度
	}
	virtual Ray generateRay(const Vector2f& point) {
		float x = point.x()*screen_width - screen_width / 2;	//二维的x坐标
		float y = point.y()*screen_width - screen_width / 2;	//二维的y坐标

		Vector3f ray_direction = u*x + v*y;						//三维的点坐标
		ray_direction += distance * w;							//得到方向向量
		ray_direction.normalize();
		return Ray(center, ray_direction);
	}
	virtual float getTMin() const {
		return 0.0f;
	}
	void print(Vector3f v) {
		cout << "V:" << v.x() << "," << v.y() << "," << v.z() << endl;
	}
private:
	float angle;

private:
	Vector3f w;
	Vector3f u;
	Vector3f v;
	float distance = 10;
	float screen_width;
};

#endif //CAMERA_H
