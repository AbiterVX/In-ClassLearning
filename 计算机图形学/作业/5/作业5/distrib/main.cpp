#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>
#include"RayTracer.h"

using namespace std;
float clampedDepth ( float depthInput, float depthMin , float depthMax);
#include "bitmap_image.hpp"
#include<iostream>



void drawPicture(SceneParser* scene_parser,int Width,int Height,char *output_file_name,int max_bounces) {
	int width = Width;											//屏幕宽度
	int height = Height;										//屏幕高度
	Vector3f ambient_light = scene_parser->getAmbientLight();	//环境光照
	
	Camera *camera = scene_parser->getCamera();					//透视投影相机
	float tmin = camera->getTMin();								//设置t的最小值
	tmin = 0.001;
	Image image(width, height);									//设置图片
	RayTracer tay_tracer(scene_parser, max_bounces);

	int high_width = width * 3;
	int high_height = height * 3;

	Vector3f** high_resolution = new Vector3f*[high_width];
	for (int i = 0; i < high_width;i++) {
		high_resolution[i] = new Vector3f[high_height];
	}

	
	for (int i = 0; i < high_width; i++) {																	//遍历每个像素点
		for (int j = 0; j < high_height; j++) {
			float ri = rand() / (float)(RAND_MAX) - 0.5;
			float rj = rand() / (float)(RAND_MAX) - 0.5;

			Vector2f position((float)(i+ ri) / (float)(high_width -1), (float)(j+ rj) / (float)(high_height -1));	//宽高分别所占比例
			Ray ray = camera->generateRay(position);													//初始光照
		
			Hit hit;
			Vector3f current_color = tay_tracer.traceRay(ray, tmin, 0, 1, hit);
			high_resolution[i][j] = current_color;
			//cout << i <<","<<j<< endl;
		}
		if (i % 100 == 0) {
			cout <<"抖动走样："<< i+100 << "/" << high_width << endl;
		}
	}
	float *nucleus_K = new float[5]{ 0.1201,0.2339,0.2931, 0.2339, 0.1201 };	//高斯模糊
	Vector3f** Gauss_horizontal = new Vector3f*[high_width];
	Vector3f** Gauss_vertical=new Vector3f*[high_width];
	for (int i = 0; i < high_width; i++) {
		Gauss_horizontal[i] = new Vector3f[high_height];
		Gauss_vertical[i]=new Vector3f[high_height];
	}

	cout << "gauss horizontal:" << endl;
	for (int i = 0; i < high_width; i++) {													
		for (int j = 0; j < high_height; j++) {
			Gauss_horizontal[i][j] = high_resolution[i][j] * nucleus_K[2];
			if (j==0) {
				Gauss_horizontal[i][j] += high_resolution[i][j+1] * nucleus_K[3]+
										  high_resolution[i][j+2] * nucleus_K[4];
			}
			else if (j==1) {
				Gauss_horizontal[i][j] += high_resolution[i][j - 1] * nucleus_K[1] +
										  high_resolution[i][j + 1] *nucleus_K[3] +
										  high_resolution[i][j + 2]*nucleus_K[4];
			}
			else if (j== high_height-1) {
				Gauss_horizontal[i][j] += high_resolution[i][j - 2] * nucleus_K[0] +
										  high_resolution[i][j - 1] * nucleus_K[1];
			}
			else if (j== high_height-2) {
				Gauss_horizontal[i][j] += high_resolution[i][j - 2] * nucleus_K[0] +
										  high_resolution[i][j - 1] * nucleus_K[1] +
										  high_resolution[i][j + 1] * nucleus_K[3];
			}
			else {
				Gauss_horizontal[i][j] += high_resolution[i][j - 2] * nucleus_K[0] +
										  high_resolution[i][j - 1] * nucleus_K[1] +
										  high_resolution[i][j + 1] * nucleus_K[3] +
										  high_resolution[i][j + 2] * nucleus_K[4];
			}
		}
	}

	cout << "gauss vertical:" << endl;
	for (int i = 0; i < high_width; i++) {
		for (int j = 0; j < high_height; j++) {
			Gauss_vertical[i][j] = Gauss_horizontal[i][j] * nucleus_K[2];
			if (i == 0) {
				Gauss_vertical[i][j] += Gauss_horizontal[i+1][j] * nucleus_K[3] +
										Gauss_horizontal[i+2][j] * nucleus_K[4];
			}
			else if (i == 1) {
				Gauss_vertical[i][j] += Gauss_horizontal[i-1][j] * nucleus_K[1] +
										Gauss_horizontal[i+1][j] * nucleus_K[3] +
										Gauss_horizontal[i+2][j] * nucleus_K[4];
			}
			else if (i == high_width - 1) {
				Gauss_vertical[i][j] += Gauss_horizontal[i-2][j] * nucleus_K[0] +
										Gauss_horizontal[i-1][j] * nucleus_K[1];
			}
			else if (i == high_width - 2) {
				Gauss_vertical[i][j] += Gauss_horizontal[i-2][j] * nucleus_K[0] +
										Gauss_horizontal[i-1][j] * nucleus_K[1] +
										Gauss_horizontal[i+1][j] * nucleus_K[3];
			}
			else {
				Gauss_vertical[i][j] += Gauss_horizontal[i-2][j] * nucleus_K[0] +
										Gauss_horizontal[i-1][j] * nucleus_K[1] +
										Gauss_horizontal[i+1][j] * nucleus_K[3] +
										Gauss_horizontal[i+2][j] * nucleus_K[4];
			}
		}
	}

	cout << "write:" << endl;
	for (int i = 0; i < width;i++) {
		for (int j = 0; j < height;j++) {
			Vector3f current_color=Vector3f::ZERO;			
			for (int u = -1; u < 2;u++) {
				for (int v = -1; v < 2;v++) {
					current_color += Gauss_vertical[1+(i) * 3 + u][1+(j) * 3 + v];
				}
			}
			image.SetPixel(i, j, current_color / 9);

			//image.SetPixel(i, j, Gauss_vertical[i*3][j*3]);
		}
		

	}

	

	string file_name = output_file_name;

	file_name = "Result_Picture/" + file_name;
	cout << file_name << endl;
	const char* const_file_name = file_name.c_str();
	image.SaveImage(const_file_name);
	cout << "Draw Picture finish!" << endl;
}


int main( int argc, char* argv[] )
{
	SceneParser* scene_parser;
	int width = 0;
	int height = 0;
	char *file_name;
	char *output_file_name;
	int max_bounces=3;
	for (int argNum = 1; argNum < argc; ++argNum)
	{
		std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
		if (!strcmp(argv[argNum], "-input") && argNum + 1 < argc) {
			scene_parser = new SceneParser(argv[argNum + 1]);
			file_name = argv[argNum + 1];
		}
		if (!strcmp(argv[argNum], "-size") && argNum + 2< argc) {
			width = atoi(argv[argNum + 1]);
			height = atoi(argv[argNum + 2]);
		}
		if (!strcmp(argv[argNum], "-output") && argNum + 1 < argc) {
			output_file_name= argv[argNum + 1];
		}
		if (!strcmp(argv[argNum],"-bounces" ) && argNum + 1 < argc) {
			max_bounces = atoi(argv[argNum + 1]);
			cout << "bounces" << max_bounces << endl;
		}
	}
	cout << endl<< "width: " << width <<","<<"height: " << height<<","<< "file name: " << file_name << endl<<endl;
	
	drawPicture(scene_parser, width, height, output_file_name, max_bounces);
	return 0;
}
