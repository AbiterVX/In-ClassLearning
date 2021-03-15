#pragma once
#include <vector>

class Surface :public Spline 
{
public:	
	void set(int i, Vec3f v) {

		
	}
	
};


class SurfaceOfRevolution : public Surface
{
public:
	SurfaceOfRevolution(Curve * c) {
		Base_Curve = c;
	}
	void Paint(ArgParser *args) {
		Base_Curve->Paint(args);
		/*double PI = 3.14159265358979323;
		int Revolve_Segment = args->revolution_tessellation;
		double Unit_Degree = 360.0 / (double)Revolve_Segment ;
		int Point_Number = Base_Curve->Get_Point_Number();
		Vec3f *PointS = new Vec3f[Point_Number];
		Vec3f *Base_Points = Base_Curve->Get_Points();		
		Curve *Current_Curve=NULL;		
		double Current_Degree = 0;
		for (int i = 0; i < Revolve_Segment;i++) {		
			Current_Degree = i * Unit_Degree* PI / 180;
			if (Base_Curve->GetType() == 1) {
				Current_Curve = new BezierCurve(Point_Number);
			}
			else if (Base_Curve->GetType() == 0) {
				Current_Curve = new BSplineCurve(Point_Number);
			}
			for (int j = 0; j < Point_Number;j++) {				
				Vec3f NewPoint( ( Base_Points[j].x()*cos(Current_Degree)+ Base_Points[j].z()*sin(Current_Degree) ),
								( Base_Points[j].y() ),
								( -Base_Points[j].x()*sin(Current_Degree) + Base_Points[j].z()*cos(Current_Degree) )
								);
				//cout << NewPoint.x() << "," << NewPoint.y() << "," << NewPoint.z() << endl;
				Current_Curve->set(j, NewPoint);
			}			
			Current_Curve->Paint(args);
		}*/
	}	
	TriangleMesh *OutputTriangles(ArgParser *args) {
		//return Base_Curve->OutputTriangles(args);

		int V = args->revolution_tessellation;						//曲线个数 		
		vector<Vec3f> All_Points=Base_Curve->Get_All_Points(args);
		int U = All_Points.size();									//单曲线点数
		//---------------------------------------------------------------------
		int num_vertices = U*V;
		int num_triangles = 2*(U-1)*V;
		TriangleMesh* Current_Model = new TriangleMesh(num_vertices, num_triangles);

		double PI = 3.14159265358979323;
		int Revolve_Segment = args->revolution_tessellation;
		double Unit_Degree = 360.0 / (double)Revolve_Segment;
		int Point_Number = Base_Curve->Get_Point_Number();
		Vec3f *PointS = new Vec3f[Point_Number];
		Vec3f *Base_Points = Base_Curve->Get_Points();
		Curve *Current_Curve = NULL;
		double Current_Degree = 0;
		//------------------------PointS------------------------------------------
		for (int i = 0; i < V;i++) {
			Current_Degree = i * Unit_Degree* PI / 180;
			if (Base_Curve->GetType() == 1) {
				Current_Curve = new BezierCurve(Point_Number);
			}
			else if (Base_Curve->GetType() == 0) {
				Current_Curve = new BSplineCurve(Point_Number);
			}
			for (int j = 0; j < Point_Number; j++) {
				Vec3f NewPoint((Base_Points[j].x()*cos(Current_Degree) + Base_Points[j].z()*sin(Current_Degree)),
					(Base_Points[j].y()),
					(-Base_Points[j].x()*sin(Current_Degree) + Base_Points[j].z()*cos(Current_Degree))
				);
				Current_Curve->set(j, NewPoint);
			}
			All_Points = Current_Curve->Get_All_Points(args);
			for (int j = 0; j < U;j++) {
				Current_Model->SetVertex(i*U+j, All_Points[j]);
				//cout<< i * U + j<< All_Points[j].x()<<","<< All_Points[j].y()<<","<< All_Points[j].z() <<endl;
			}
		}
		//------------------------Triangles----------------------------------
		int Face_Number = 0;
		for (int i = 0; i < V;i++) {
			for (int j = 0; j < U-1;j++) {
				if (i==0 || i==V-1) {
					if (i==0) {
						Current_Model->SetTriangle(Face_Number++, i*U + j, i*U + j + 1, (i + 1)*U + j);
						Current_Model->SetTriangle(Face_Number++, i*U + j, (V - 1)*U + j + 1, i*U + j + 1 );
					}
					else if(i==V-1) {
						Current_Model->SetTriangle(Face_Number++, i*U + j, i*U + j + 1, 0 + j);
						Current_Model->SetTriangle(Face_Number++, i*U + j, (i - 1)*U + j + 1, i*U + j + 1 );
					}					
				}
				else {
					Current_Model->SetTriangle(Face_Number++, i*U + j, i*U + j + 1, (i + 1)*U + j);
					Current_Model->SetTriangle(Face_Number++, i*U + j,(i - 1)*U + j + 1 , i*U + j + 1 );
				}				
			}
		}
		return Current_Model;
	}
	void moveControlPoint(int selectedPoint, float x, float y) {
		Base_Curve->moveControlPoint(selectedPoint, x, y);
	}
	void addControlPoint(int selectedPoint, float x, float y) {
		Base_Curve->addControlPoint(selectedPoint, x, y);
	}
	void deleteControlPoint(int selectedPoint) {
		Base_Curve->deleteControlPoint(selectedPoint);
	}
	int getNumVertices() {
		return Base_Curve->getNumVertices();
	}
	Vec3f getVertex(int i)
	{
		return Base_Curve->getVertex(i);		 
	};
protected:
	Curve * Base_Curve;

};

class BezierPatch : public Surface
{
public:
	BezierPatch() {
		Base_PointS = new Vec3f[16];
		Base_Curve = new Curve[4];
		Row_Base_PointS = new vector<Vec3f>[4];
	}
	void set(int i, Vec3f v) {
		Base_PointS[i] = v;
		//cout << i <<","<< v.x() << "," << v.y() << "," << v.z() << endl;
	}
	void Paint(ArgParser *args) {	
		for (int i = 0; i < 4; i++) {
			BezierCurve NewCurve(4);			
			for (int j = 0; j < 4; j++) {
				NewCurve.set(j, Base_PointS[i * 4 + j]);
			}
			Base_Curve[i] = NewCurve;
			Row_Base_PointS[i] = Base_Curve[i].Get_All_Points(args);
			Base_Curve[i].Paint_Curve(args);
		}	
		int ColumnSize=Row_Base_PointS[1].size();
		cout << ColumnSize << endl;
		for (int i = 0; i < ColumnSize;i++) {
			BezierCurve Current_Column(4);
			for (int j = 0; j < 4;j++) {
				Current_Column.set(j, Row_Base_PointS[j][i]);
			}
			Current_Column.Paint_Curve(args);
		}
	}

	TriangleMesh *OutputTriangles(ArgParser *args) {
		for (int i = 0; i < 4; i++) {
			BezierCurve NewCurve(4);
			for (int j = 0; j < 4; j++) {
				NewCurve.set(j, Base_PointS[i * 4 + j]);
			}
			Base_Curve[i] = NewCurve;
			Row_Base_PointS[i] = Base_Curve[i].Get_All_Points(args);
			//Base_Curve[i].Paint_Curve(args);
		}
		int RowSize = args->curve_tessellation+1;
		int ColumnSize = Row_Base_PointS[1].size();
		int num_vertices = RowSize * ColumnSize;
		int num_triangles = 2*(RowSize - 1) * (ColumnSize - 1);
		TriangleMesh* Current_Model = new TriangleMesh(num_vertices, num_triangles);
		
		int CurrentFace = 0;
		for (int i = 0; i < ColumnSize; i++) {
			BezierCurve Current_Column(4);
			for (int j = 0; j < 4; j++) {
				Current_Column.set(j, Row_Base_PointS[j][i]);
			}
			vector<Vec3f> Column_Points=Current_Column.Get_All_Points(args);
			for (int j = 0; j < Column_Points.size();j++) {
				Current_Model->SetVertex(i*Column_Points.size()+j , Column_Points[j]);
			}	
			if (i>0) {
				for (int j = 0; j < Column_Points.size()-1;j++) {
					Current_Model->SetTriangle(CurrentFace++,
						i*(Column_Points.size() )+ j, (i - 1)*(Column_Points.size()) + j, i*(Column_Points.size() ) + j+1);
					Current_Model->SetTriangle(CurrentFace++,
						(i - 1)*(Column_Points.size() ) + j, (i - 1)*(Column_Points.size() ) + j+1, i*(Column_Points.size() ) + j + 1);
				}
				
			}
			Current_Column.Paint_Curve(args);
		}
		return Current_Model;
	}
private:
	Vec3f * Base_PointS;
	Curve * Base_Curve;
	vector<Vec3f> *Row_Base_PointS;
};