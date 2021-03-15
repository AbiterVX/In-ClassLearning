#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vecmath.h>
#include <vector>
#ifdef _WIN32
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"
#include<iostream>

class ClothSystem: public ParticleSystem
{
///ADD MORE FUNCTION AND FIELDS HERE
public:
	ClothSystem(int numParticles);
	vector<Vector3f> evalF(vector<Vector3f> state);
	void draw();


	//-------球体无摩擦碰撞-------
	void setState(const vector<Vector3f>  & newState) {
		Vector3f centre(-1, -2, 0);
		Vector3f Epsilon(0.03, 0.03, 0.03);
		Vector3f direction;
		for (int i = 0; i < number; i++) {
			for (int j = 0; j < number; j++) {
				int N = i * number + j;
				direction = newState[N * 2] - centre;
				if (direction.abs() < 1.03) {
					direction.normalize();
					direction += centre;
					m_vVecState[N * 2] = direction + Epsilon;	
					m_vVecState[N * 2 + 1] = newState[N * 2 + 1];
				}
				else {
					m_vVecState[N * 2] = newState[N * 2];
					m_vVecState[N * 2 + 1] = newState[N * 2 + 1];
				}	
				
			}
		}
	}

	//----绘画变换---
	int spring_type;
	void set_spring_type() {
		spring_type += 1;
		spring_type %= 5;
	};
	//----风力变换----
	bool wind;
	void set_wind() {
		wind = !wind;
	};

	//----鼠标拖拽-------
	void set_drag_point(int fixed_x, int fixed_y, Matrix4f m, Matrix4f rotate, Vector3f transform);  //设置拖拽点，投影，选取模式
	void move_drag_point(int x, int y, Matrix4f m, Matrix4f rotate);								 //移动并更新点坐标
	void release_drag_point() { current_point_index = -1; };										 //释放拖拽点
	Matrix4f m_m;			//look_at矩阵
	Matrix4f m_rotate;		//旋转矩阵
	Vector3f transform;		//平移矩阵
	int fixed_x;			//固定点坐标x
	int fixed_y;			//固定点坐标y
	int current_point_index;//当前选中的点
	vector<Vector3f> colors;//所有点颜色



private:
	int number;											//弹簧规模，点的个数为number*number。该变量主要为方便计算。
	vector<vector<Vector3f>> spring_connect;			//结构弹簧
	vector<vector<Vector3f>> spring_anti_shearing;		//抗剪弹簧
	vector<vector<Vector3f>> spring_anti_bending;		//抗弯弹簧
	//-----弹簧属性-------
	float gap_position;
	float gap_connect;
	float gap_anti_shear;
	float gap_anti_bend;
	float k_connect;
	float k_anti_shear;
	float k_anti_bend;
	float k_resistance;
	float gravity;
	//---绘画----
	void draw_connect();
	void draw_anti_shearing();
	void draw_anti_bending();
	void draw_faces();
	
	//-----点法向量计算---------
	Vector3f ***face_normal;									//存储面法向量
	Vector3f GetPointNormal(int i, int j);						//得到某位置面法向量
	Vector3f GetNormal(Vector3f v1, Vector3f v2, Vector3f v3);	//计算面法向量
	
	//------摇摆------
	float step;			 //摇摆计数
	float sum_velocity;  //摇摆力
	
};


#endif
