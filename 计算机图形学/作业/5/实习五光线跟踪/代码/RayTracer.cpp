#include "RayTracer.h"
#include "Camera.h"
#include "Ray.h"
#include "Hit.h"
#include "Group.h"
#include "Material.h"
#include "Light.h"

#define EPSILON 0.001

//IMPLEMENT THESE FUNCTIONS
//These function definitions are mere suggestions. Change them as you like.
Vector3f mirrorDirection( const Vector3f& normal, const Vector3f& incoming)
{
	Vector3f Vision = incoming.normalized();
	Vector3f Normal = normal.normalized();
	return (Vision - 2 * (Vector3f::dot(Vision, Normal))*Normal);

}
bool transmittedDirection( const Vector3f& normal, const Vector3f& incoming, float index_n, float index_nt, Vector3f& transmitted){
	Vector3f L = -incoming.normalized();
	Vector3f N = normal.normalized();
	float index_nr = index_n / index_nt;
	float delta = 1 - pow(index_nr, 2)*(1 - pow((Vector3f::dot(N, L)), 2));
	if (delta<0) {
		transmitted = Vector3f::ZERO;
		return false;
	}
	else {
		delta = sqrt(delta);
		transmitted = (index_nr * Vector3f::dot(N, L)  - delta)*N-index_nr*L;
		transmitted.normalize();
		return true;
	}
}




RayTracer::RayTracer( SceneParser * scene, int max_bounces) :m_scene(scene){
	group =scene->getGroup();
	m_maxBounces = max_bounces;

	light_number = scene->getNumLights();						//光源个数
	lights = new Light*[light_number];							//光源
	for (int i = 0; i < light_number; i++) {					//设置光源
		lights[i] = scene->getLight(i);
	}
}

RayTracer::~RayTracer(){

}
Vector3f RayTracer::traceRay( Ray& ray, float tmin, int bounces,float refr_index, Hit& hit ) const{
	Vector3f color = Vector3f::ZERO;
	bool intersected = group->intersect(ray, hit, tmin);														//先求交
	if (intersected) {
		color += hit.getMaterial()->getDiffuseColor()*m_scene->getAmbientLight();
		Vector3f intersection = ray.pointAtParameter(hit.getT());												//交点
		
		for (int k = 0; k < light_number; k++) {																//求阴影光
			Vector3f direction_to_light;																		//指向光的方向
			Vector3f light_color;																				//光的颜色
			float distance_to_light_source;																		//到光的距离
			lights[k]->getIllumination(intersection, direction_to_light, light_color, distance_to_light_source);//

			Hit new_hit;																						//测试是否有交点！！！！！
			Ray to_light_ray(intersection, direction_to_light);													//指向光源的光线		
			bool hidden = group->intersect(to_light_ray, new_hit, tmin);										//光是否被遮挡，阴影光
			if (!hidden) {
				color += hit.getMaterial()->Shade(ray, hit, direction_to_light, light_color);					//当前光源作出贡献
			}
		}

		bounces++;																								//减少一次反射次数
		if (bounces <= m_maxBounces) {																			//在反射次数范围内
			Ray reflected_light(intersection, mirrorDirection(hit.getNormal(),ray.getDirection() ));			//反射光线

			Vector3f reflected_color;		//反射光颜色
			Vector3f transmitted_color;		//折射光颜色
			Vector3f sum_color;				//总颜色

			Hit new_hit;
			reflected_color = hit.getMaterial()->getSpecularColor()*traceRay(reflected_light, tmin, bounces, refr_index, new_hit);	//镜面反射
			//reflected_color = hit.getMaterial()->Shade(reflected_light, hit, reflected_light.getDirection(), color)*color;

			Vector3f ray_direction = ray.getDirection().normalized();		//光线方向,从源到当前交点
			Vector3f N = hit.getNormal().normalized();						//当前物体交点的法向量
			float d_dot_N = Vector3f::dot(ray_direction, N);					//d点乘N


			float n = refr_index;											//当前折射系数
			float nt = hit.getMaterial()->getRefractionIndex();				//将进入的物体折射系数

			if (d_dot_N > 0) {												//在当前物体内
				N = -N;
				nt = (float)1.0;
			}
			else {															//不在当前物体内
				nt = hit.getMaterial()->getRefractionIndex();
			}


			if (nt > 0) {																												//当前物体允许折射
				Vector3f transmitted_direction;
				bool iftransmitted = transmittedDirection(N, ray_direction, n, nt, transmitted_direction);	//折射
				
				if (iftransmitted) {																									//如果有折射
					Ray transmit_ray(intersection, transmitted_direction);	//生成折射光
					Hit new_hit;
					transmitted_color = hit.getMaterial()->getSpecularColor()*traceRay(transmit_ray, tmin, bounces, nt, new_hit);													//折射颜色

					
					float R0 = pow((nt - n) / (nt + n), 2);
					float C;
					if (n <= nt) {
						C = abs(Vector3f::dot(ray_direction, N));
					}
					else {
						C = abs(Vector3f::dot(transmitted_direction, N));
					}
					float R = R0 + (1.0 - R0)*pow((1.0 - C), 5);

					//cout << R << endl;
					sum_color = R * reflected_color + (1.0 - R)*transmitted_color;
					//sum_color = R * transmitted_color+ (1.0 - R)*reflected_color;
					//sum_color=(1.0 - R)*transmitted_color;
					//sum_color = reflected_color;
				}
				else {
					sum_color = reflected_color;															//全反射
				}
			}
			else {
				sum_color = reflected_color;																//全反射
			}
			
			color += sum_color;
		}	
	}
	else {
		color = m_scene->getBackgroundColor(ray.getDirection());
	}

	return color;
}
