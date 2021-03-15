#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"
///TODO:
///Implement Shade function that uses ambient, diffuse, specular and texture
class Material
{
public:	
	Material( const Vector3f& d_color ,const Vector3f& s_color=Vector3f::ZERO, float s=0):
	diffuseColor( d_color),specularColor(s_color), shininess(s){
        	
	}
	virtual ~Material(){

    }
	virtual Vector3f getDiffuseColor() const { 	
		return  diffuseColor;
	}   
	Vector3f Shade( const Ray& ray, const Hit& hit,const Vector3f& dirToLight, const Vector3f& lightColor ) {
		Vector3f color=Vector3f::ZERO;
		
		
		
		float n_dot_l = Vector3f::dot(hit.getNormal(), dirToLight);
		if (n_dot_l > 0) {
			if (t.valid()) {
				color += t(hit.texCoord.x(), hit.texCoord.y())* (n_dot_l)*lightColor;
			}
			else {
				color += diffuseColor * (n_dot_l)*lightColor;
			}
			
		}
		
			
		Vector3f ray_direction = -ray.getDirection();
		ray_direction.normalize();

		Vector3f ray_normal = hit.getNormal().normalized();

		float phong_dot =
			Vector3f::dot(ray_direction, 2 * Vector3f::dot(ray_normal, dirToLight)*ray_normal - dirToLight) ;
		if (phong_dot>0) {
			color += pow(phong_dot, shininess)*specularColor*lightColor;
		}

		return color;
	}
	void loadTexture(const char * filename){
		t.load(filename);
	}
protected:
	Vector3f diffuseColor;
	Vector3f specularColor;
	float shininess;
	Texture t;
};

#endif // MATERIAL_H
