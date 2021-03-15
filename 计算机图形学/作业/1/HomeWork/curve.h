#pragma once
#include <iostream>
#include<string>
#include <GL/glut.h> 
#include<math.h>
#include"arg_parser.h"
#include"matrix.h"
#include <vector>
using namespace std;


class Curve : public Spline
{
public:
	Curve() {
		Bezier_matrix = new float[16]{
			-1,3,-3,1,
			3,-6,3,0,
			-3,3,0,0,
			1,0,0,0
		};	
		BSpline_matrix = new  float[16]{
			-1,3,-3,1,
			3,-6,0,4,
			-3,3,3,1,
			1,0,0,0
		};
		for (int i = 0; i < 16; i++) {
			BSpline_matrix[i] /= 6;
		}
		Grow_type = 0;
	}
	Curve(int point_number) {
		Points = new Vec3f[point_number];
		Point_Number = point_number;
	}
	void Paint_Frame() {
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		int i = 0;
		glVertex3f(Points[i].x(), Points[i].y(), Points[i].z());
		for (; i < Point_Number - 1; i++) {
			glVertex3f(Points[i].x(), Points[i].y(), Points[i].z());
			glVertex3f(Points[i].x(), Points[i].y(), Points[i].z());
		}
		i = Point_Number - 1;
		glVertex3f(Points[i].x(), Points[i].y(), Points[i].z());
		glEnd();
		//------------------------------------------------------------------
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		for (int i = 0; i < Point_Number; i++) {
			glVertex3f(Points[i].x(), Points[i].y(), Points[i].z());
		}
		glEnd();		
	}
	void Paint_Curve(ArgParser* arg_parser) {
		/*int Paint_Point_Number = arg_parser->curve_tessellation;
		double Unit_Length = 1.0 / (double)(Paint_Point_Number);
		double Current_Position = 0;
		double X = Points[0].x();
		double Y = Points[0].y();
		double Z = Points[0].z();*/
		glLineWidth(5.0f);
		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		vector<Vec3f> All_Points = Get_All_Points(arg_parser);
		for (int i = 0; i < All_Points.size();i++) {
			glVertex3f(All_Points[i].x(), All_Points[i].y(), All_Points[i].z());
			//cout << "11" << endl;
		}
		/*for (int Paint_Begin = 0; Paint_Begin < Point_Number - 3; Paint_Begin += Grow_type) {
			Current_Position = 0;
			if (Paint_Point_Number>0) {
				for (int i = 0; i < Paint_Point_Number + 1; i++) {
					X = Caculate(Current_Position, 0, Paint_Begin);
					Y = Caculate(Current_Position, 1, Paint_Begin);
					Z = Caculate(Current_Position, 2, Paint_Begin);
					glVertex3f(X, Y, Z);
					if (i != 0 && i != Paint_Point_Number) {
						glVertex3f(X, Y, Z);
					}
					Current_Position += Unit_Length;
				}
			}
		}*/
		glEnd();
	}
	vector<Vec3f> Get_All_Points(ArgParser *arg_parser) {
		vector<Vec3f> All_Points;
		int Paint_Point_Number = arg_parser->curve_tessellation;
		double Unit_Length = 1.0 / (double)(Paint_Point_Number);
		double Current_Position = 0;
		double X = Points[0].x();
		double Y = Points[0].y();
		double Z = Points[0].z();
		for (int Paint_Begin = 0; Paint_Begin < Point_Number - 3; Paint_Begin += Grow_type) {
			Current_Position = 0;
			if (Paint_Point_Number>0) {
				for (int i = 0; i < Paint_Point_Number + 1; i++) {
					X = Caculate(Current_Position, 0, Paint_Begin);
					Y = Caculate(Current_Position, 1, Paint_Begin);
					Z = Caculate(Current_Position, 2, Paint_Begin);
					glVertex3f(X, Y, Z);
					Vec3f NewPoint(X, Y, Z);
					All_Points.push_back(NewPoint);
					if (i != 0 && i != Paint_Point_Number) {
						glVertex3f(X, Y, Z);
						Vec3f NewPoint(X, Y, Z);
						//All_Points.push_back(NewPoint);
					}
					Current_Position += Unit_Length;
				}
			}
		}
		return All_Points;
	}
	void Paint(ArgParser* arg_parser){
		Paint_Frame();
		//------------------------------------------------------------------
		Paint_Curve(arg_parser);
	}
	void set(int i, Vec3f v) {
		Points[i] = v;
		/*Control_Matrix->Set(0,i ,v.x());
		Control_Matrix->Set(1,i ,v.y());
		Control_Matrix->Set(2,i ,v.z());*/
	}
	double Get_Point_Value(int point,int type) {
		if (type==0) {
			return Points[point].x();
		}
		else if (type == 1) {
			return Points[point].y();
		}
		else if (type == 2) {
			return Points[point].z();
		}
	}
	double Caculate(double t, int type,int begin) {
		double result = 0;
		for (int i = 0; i < 4; i++) {
			result += (pow(t, 3)* Base_Matrix->Get(0, i) +
				pow(t, 2)* Base_Matrix->Get(1, i) +
				t * Base_Matrix->Get(2,i) +
				Base_Matrix->Get(3, i)
				) * Get_Point_Value(begin+i, type);
		}
		return result;
	};
	void Output(FILE *file) {
		Matrix *Anathor_Base=NULL;
		if (Current_OutPut == 0) {
			Anathor_Base = new Matrix(BSpline_matrix);
		}
		else if (Current_OutPut == 1) {
			Anathor_Base = new Matrix(Bezier_matrix);
		}
		Matrix *Inverse_BSpline_Base = new Matrix(*Base_Matrix);		
		Control_Matrix->Transpose();		
		Base_Matrix->Transpose();
		Base_Matrix->Inverse(*Inverse_BSpline_Base);
		Matrix *mutiply = new Matrix((*Control_Matrix)*(*Anathor_Base));
		Inverse_BSpline_Base->Transpose();
		Result_Control_Matrix = new Matrix((*mutiply)* (*Inverse_BSpline_Base));
		
		if (First==0) {
			if (Current_OutPut == 0) {
				fprintf(file, "bezier \n");
			}
			else if (Current_OutPut == 1) {
				fprintf(file, "bspline \n");
			}
			fprintf(file, "num_vertices %d\n", Point_Number);
			if (Current_OutPut == 0) {
				fprintf(file, "%f %f %f\n",
					Result_Control_Matrix->Get(0, 0),
					Result_Control_Matrix->Get(0, 1),
					Result_Control_Matrix->Get(0, 2));
			}
			else if (Current_OutPut == 1) {
				for (int i = 0; i < 3; i++) {
					fprintf(file, "%f %f %f\n",
						Result_Control_Matrix->Get(i, 0),
						Result_Control_Matrix->Get(i, 1),
						Result_Control_Matrix->Get(i, 2));
				}
			}
			First =1;
		}
		if (Current_OutPut == 0) {
			for (int i = 1; i < 4; i++) {
				fprintf(file, "%f %f %f\n",
					Result_Control_Matrix->Get(i, 0),
					Result_Control_Matrix->Get(i, 1),
					Result_Control_Matrix->Get(i, 2));
			}
		}
		else if (Current_OutPut == 1) {
			for (int i = 3; i < 4; i++) {
				fprintf(file, "%f %f %f\n",
					Result_Control_Matrix->Get(i, 0),
					Result_Control_Matrix->Get(i, 1),
					Result_Control_Matrix->Get(i, 2));
			}
		}
		
		
		//-----------------------------------------------
		cout << "Result_Control_Matrix" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << Result_Control_Matrix->Get(i, j) << ",";
			}
			cout << endl;
		}
		cout << endl;
	}

	int getNumVertices() { 
		return Point_Number;
	}
	Vec3f getVertex(int i)
	{	
		return Points[i];
	};
	void moveControlPoint(int selectedPoint, float x, float y) {
		Points[selectedPoint].Set(x,y,0);
	}
	void addControlPoint(int selectedPoint, float x, float y) {
		Vec3f * New_Points=new Vec3f[Point_Number];
		for (int i = 0; i < Point_Number; i++) {
			New_Points[i] = Points[i];
		}

		Point_Number += 1;
		Points=new Vec3f[Point_Number];

		for (int i = 0; i < selectedPoint; i++) {
			Points[i] = New_Points[i];
		}
		Vec3f New_Point(x,y,0);
		Points[selectedPoint] = New_Point;
		for (int i = selectedPoint+1; i < Point_Number; i++) {
			Points[i] = New_Points[i-1];
		}
		
	}
	void deleteControlPoint(int selectedPoint) {
		Vec3f * New_Points = new Vec3f[Point_Number];
		for (int i = 0; i < Point_Number; i++) {
			New_Points[i] = Points[i];
		}

		Point_Number -= 1;
		Points = new Vec3f[Point_Number];

		for (int i = 0; i < selectedPoint; i++) {
			Points[i] = New_Points[i];
		}

		for (int i = selectedPoint; i < Point_Number; i++) {
			Points[i] = New_Points[i + 1];
		}
	}
	
	int Get_Point_Number() {
		return Point_Number;
	}
	Vec3f *Get_Points() {
		return Points;
	}
	int GetType() {
		return Current_OutPut;
	}
protected:
	Vec3f * Points;
	int Point_Number;
	Matrix *Base_Matrix;
	Matrix *Control_Matrix;	
	Matrix *Result_Control_Matrix;

	float *Bezier_matrix;
	float *BSpline_matrix;

	int Grow_type;
	int Current_OutPut;
	int First;
};
class BezierCurve : public Curve
{
public:
	BezierCurve(int point_number){
		Curve::Curve();
		Curve::Points = new Vec3f[point_number];
		Curve::Point_Number = point_number;		
		Base_Matrix = new Matrix(Bezier_matrix);
		
		Grow_type = 3;
		Current_OutPut = 1;
	}
	void OutputBSpline(FILE *file) {
		/*Matrix *BSpline_Base = new Matrix(BSpline_matrix);
		Matrix *Inverse_BSpline_Base = new Matrix(*Base_Matrix);
		Control_Matrix->Transpose();
		//BSpline_Base->Transpose();
		Base_Matrix->Transpose();
		Base_Matrix->Inverse(*Inverse_BSpline_Base);
		Matrix *mutiply = new Matrix((*Control_Matrix)*(*BSpline_Base));
		Inverse_BSpline_Base->Transpose();
		Result_Control_Matrix = new Matrix((*mutiply)* (*Inverse_BSpline_Base));
		fprintf(file, "bezier \n");
		fprintf(file, "num_vertices %d\n", 4);
		for (int i = 0; i < 4; i++) {
		fprintf(file, "%f %f %f\n",
		Result_Control_Matrix->Get(i, 0),
		Result_Control_Matrix->Get(i, 1),
		Result_Control_Matrix->Get(i, 2));
		}
		//-----------------------------------------------
		cout << "Result_Control_Matrix" << endl;
		for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
		cout << Result_Control_Matrix->Get(i, j) << ",";
		}
		cout << endl;
		}
		cout << endl;
		}*/
		First = 0;
		for (int Begin = 0; Begin < Point_Number-3; Begin+=3) {
			Control_Matrix = new Matrix();
			for (int j = 0; j < 4; j++) {
				Control_Matrix->Set(0, j, Points[Begin + j].x());  //
				Control_Matrix->Set(1, j, Points[Begin + j].y());  //Points[Begin+j].y()
				Control_Matrix->Set(2, j, Points[Begin + j].z());  //Points[Begin+j].z()
				//cout << Points[Begin+j].x() << "," << Points[Begin+j].y() << "," << Points[Begin+j].z() << endl;
			}
			cout << endl;
			/*cout << "Control_Matrix" << endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cout << Control_Matrix->Get(j, i) << ",";
				}
				cout << endl;
			}*/

			Curve::Output(file);
		}		
	}
};

class BSplineCurve : public Curve
{
public:
	BSplineCurve(int point_number) {
		Curve::Curve();
		Curve::Points = new Vec3f[point_number];
		Curve::Point_Number = point_number;		
		Base_Matrix = new Matrix(BSpline_matrix);
		Control_Matrix = new Matrix();
		Grow_type = 1;
		Current_OutPut = 0;
	}
	void OutputBezier(FILE *file) {		
		/*Matrix *Bezier_Base = new Matrix(Bezier_matrix);
		Matrix *Inverse_BSpline_Base = new Matrix(*Base_Matrix);
		Control_Matrix->Transpose();
		Bezier_Base->Transpose();
		Base_Matrix->Transpose();
		Base_Matrix->Inverse(*Inverse_BSpline_Base);	
		Matrix *mutiply = new Matrix((*Control_Matrix)*(*Bezier_Base));		
		Inverse_BSpline_Base->Transpose();
		Result_Control_Matrix = new Matrix((*mutiply)* (*Inverse_BSpline_Base)  );
		fprintf(file,"bspline \n");
		fprintf(file, "num_vertices %d\n", 4);
		for (int i = 0; i < 4;i++) {
			fprintf(file,"%f %f %f\n", 
				Result_Control_Matrix->Get(i,0),
				Result_Control_Matrix->Get(i,1),
				Result_Control_Matrix->Get(i,2));			
		}
		//-----------------------------------------------
		cout << "Result_Control_Matrix" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << Result_Control_Matrix->Get(i, j) << ",";
			}
			cout << endl;
		}
		cout << endl;*/
		First = 0;
		for (int Begin = 0; Begin < Point_Number-3; Begin +=1) {
			for (int j = 0; j < 4; j++) {
				Control_Matrix->Set(0, j, Points[Begin + j].x());
				Control_Matrix->Set(1, j, Points[Begin + j].x());
				Control_Matrix->Set(2, j, Points[Begin + j].z());
			}
			Curve::Output(file);
		}
	}
};