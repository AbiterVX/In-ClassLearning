#include "stdafx.h"
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<math.h>
#include <GL/glut.h> 
using namespace std;

/*--------------------全局变量--------------------------*/
//----渐变颜色相关变量
GLfloat mat[4]{ 1.0,1.0,1.0,0 };
GLfloat mat1[4]{ 1.0,1.0,1.0,0 };
GLfloat mat2[4]{ 1.0,1.0,1.0,0 };
int ColorCount = 1;
bool ChangeColor = 0;
int Count = 0;
//----光照位置
GLfloat position[] = { 1.0, 1.0, 5.0, 1.0 };
//----光照追踪
bool track = 0;
//----键盘按键旋转
int angle = 0;
bool Rotate = 0;
//----模型信息存储数组
vector<double*> Vertices;
vector<double*> Faces;
string file_path;
bool TeaPot = 0;
//----鼠标移动相机的相关变量
int Begin_x = 0;
int Begin_y = 0;
double radius = 1.5;
double c = 3.1415926 / 180.0;
double degree = 90;
double height = 0;
//----缩放倍数
double Scale = 3;
bool Scaled = 0;

/*-----------------读文件，导入模型--------------------*/
void Read_Obj() {  //分析源文件
	string data, type, x, y, z;
	ifstream file;
	file.open(file_path);
	while (getline(file, data)) {
		istringstream in(data);
		in >> type >> x >> y >> z;
		if (type == "v") {
			double *NewVertice = new double[3]{ atof(x.c_str()),atof(y.c_str()),atof(z.c_str()) };
			Vertices.push_back(NewVertice);
		}
		else if (type == "f") {
			double *NewFace = new double[3]{ atof(x.c_str()) - 1,atof(y.c_str()) - 1,atof(z.c_str()) - 1 };
			Faces.push_back(NewFace);
		}
	}
	file.close();
}
void Build_Model() {  //建立模型
	if (!glIsList((GLuint)1) || Scaled) {
		glNewList(1, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < Faces.size(); i++) {
			for (int j = 0; j < 3; j++) {
				glVertex3d(Vertices[Faces[i][j]][0] * Scale, Vertices[Faces[i][j]][1] * Scale, Vertices[Faces[i][j]][2] * Scale);
			}
		}
		glEnd();
		glEndList();
		Scaled = 0;
		//cout << "NewLIst" << endl;
	}
	else {
		//cout << "CALLLIST" << endl;
	}
	glCallList(1);
}
/*----------------------初始化-------------------------*/
void Init(void) //初始化光源
{
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat local_view[] = { 0.0 };
	//-------
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	//-------
	glFrontFace(GL_CW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}
void ReshapeFunc(int w, int h) //窗口，坐标Reshape
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(0.0, 20.0, 0.0, 20.0*(GLfloat)h / (GLfloat)w,-10.0, 10.0);
	else
		glOrtho(0.0, 20.0*(GLfloat)w / (GLfloat)h, 0.0, 20.0,-10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
/*----------------------显示函数-----------------------*/
void DisplayFunc(void)   //显示模型
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(10, 10, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	/*----------------添加功能-----------------*/
	//----旋转
	glRotatef(angle, 0, 1, 0);
	//----相机
	gluLookAt(radius*cos(c*degree), height, radius*sin(c*degree), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (track) {
		position[0] = 10 + radius * cos(c*degree);
		position[1] = height;
		position[2] = 10 + radius * sin(c*degree);
	}
	
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//----只显示网格
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	//----导入模型
	if (!TeaPot) {
		Build_Model();
	}
	else {
		glutWireTeapot(3.0);
	}	
	glPopMatrix();
	glFlush();
}
/*----------------------改变颜色，旋转,缩放-----------------*/
void KeyboardFunc(unsigned char key, int x, int y)  //键盘响应，改变颜色，旋转，缩放
{
	if (key == 27) {
		cout << "escape !" << endl;
		exit(0);
	}
	else if (key == 'c') {
		if (!ChangeColor) {
			if (Count % 4 == 0) {
				mat1[0] = 0.5; mat1[1] = 0.5; mat1[2] = 0.9;
			}
			else if (Count % 4 == 1) {
				mat1[0] = 1.0; mat1[1] = 0.0; mat1[2] = 0.0;
			}
			else if (Count % 4 == 2) {
				mat1[0] = 0.0; mat1[1] = 1.0; mat1[2] = 0.0;
			}
			else if (Count % 4 == 3) {
				mat1[0] = 0.0; mat1[1] = 0.0; mat1[2] = 1.0;
			}
			Count++;
			ChangeColor = 1;
			mat2[0] = (mat1[0] - mat[0]) / 20;
			mat2[1] = (mat1[1] - mat[1]) / 20;
			mat2[2] = (mat1[2] - mat[2]) / 20;
			ColorCount = 1;
		}
	}
	else if (key == 'r') {
		if (!Rotate) {
			Rotate = true;
			cout << "Rotate On" << endl;
		}
		else {
			Rotate = false;
			cout << "Rotate Off" << endl;
		}
	}
	else if (key == 'a') {
		Scale += 0.2;
		Scaled = 1;
		cout << "Scale:"<< Scale << endl;
	}
	else if (key == 's') {
		Scale -= 0.2;
		if (Scale < 1) {
			Scale = 1;
		}
		else {
			Scaled = 1;
		}
		cout << "Scale:" << Scale << endl;
	}
	else if (key == 't') {
		if (!track) {
			track = 1;
			cout <<"Track On"<< endl;
		}
		else{
			track = 0;
			cout << "Track Off" << endl;
		}
	}
	glutPostRedisplay();
}
void TimerFunc(int val) {  //定时器响应，改变颜色，旋转
	if (Rotate) {
		angle += 5;
		glutPostRedisplay();
	}
	if (ChangeColor) {
		mat[0] += mat2[0];
		mat[1] += mat2[1];
		mat[2] += mat2[2];
		if (ColorCount == 20) {
			ChangeColor = 0;
			cout << "Color Change Successful!" << endl;
		}
		ColorCount += 1;
		glutPostRedisplay();	
	}
	glutTimerFunc(50, TimerFunc, 0);
}
/*----------------------方向键调整光源-----------------*/
void KeyboardFunc_direction(int key, int x, int y)  //键盘响应，方向键调整光源
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		position[0] -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
		position[0] += 0.5;
		break;
	case GLUT_KEY_UP:
		position[1] += 0.5;
		break;
	case GLUT_KEY_DOWN:
		position[1] -= 0.5;
		break;
	}
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glutPostRedisplay();
}
/*----------------------鼠标拖拽移动相机---------------*/
void MouseFunc(int button, int state, int x, int y) {  //鼠标点击响应，鼠标拖拽移动相机
	if (button== GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Begin_x = x;
		Begin_y = y;
	}
}
void MouseMotionFunc(int x, int y) {  //鼠标移动响应，鼠标拖拽移动相机
	degree += 0.03*(x - Begin_x);
	if (degree >= 360) {
		degree -= 360;
	}
	height += 0.002*(y - Begin_y);
	if (height > 1.5) {
		height = 1.5;
	}
	if (height<-1.0) {
		height = -1.0;
	}
}
/*-----------------------程序初始化提示----------------*/
void Begin(bool hasfile) {
	if (!hasfile) {
		cout << "请选择导入模型(输入数字)" << endl;
		cout << " -数字0 :glut茶壶" << endl;
		cout << " -数字1 :cube" << endl;
		cout << " -数字2 :bunny_200" << endl;
		cout << " -数字3 :bunny_1k" << endl;
		cout << ">>输入数字：";
		int type;
		cin >> type;
		if (type == 0) {
			TeaPot = 1;
		}
		else if (type == 1) {
			file_path = "./cube.obj";
		}
		else if (type == 2) {
			file_path = "./bunny_200.obj";
			Scale = 20;
		}
		else if (type == 3) {
			file_path = "./bunny_1k.obj";
			Scale = 20;
		}
	}	
	if (file_path!="") {
		Read_Obj();
	}
	cout << endl;
	cout << "功能：" << endl;
	cout << " 1.按r键可自动旋转，再次按即暂停。" << endl;
	cout << " 2.按c键可渐变改变颜色。" << endl;
	cout << " 3.按上下左右方向键可改变光源位置。" << endl;
	cout << " 4.按a键放大，按s键缩小。" << endl;
	cout << " 5.鼠标可拖拽相机位置。" << endl;
	cout << " 6.按t使光源跟随旋转。关闭时才能用方向键改变位置" << endl;
	cout << endl;
}

int main(int argc, char **argv)
{
	if (argc==1) {
		Begin(0);
	}
	else {
		file_path = argv[argc - 1];
		Begin(1);
	}
		
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("GLUT Model!");

	Init();
	glutReshapeFunc(ReshapeFunc);

	glutDisplayFunc(DisplayFunc);
	glutIdleFunc(DisplayFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(KeyboardFunc_direction);
	glutTimerFunc(50, TimerFunc, 0);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotionFunc);
	glutMainLoop();
	return 0;
}