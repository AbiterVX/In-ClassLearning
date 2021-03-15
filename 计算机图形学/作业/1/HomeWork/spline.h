#include"triangle_mesh.h"
#include"vectors.h"

class Spline {
public:
	Spline() {}
	//--用于画图的FOR VISUALIZATION
	virtual void Paint(ArgParser *args) {}
	//--用于实现样条类型转换的FOR CONVERTING BETWEEN SPLINE TYPES
	virtual void OutputBezier(FILE *file) {}
	virtual void OutputBSpline(FILE *file) {}
	//--用于得到控制点的FOR CONTROL POINT PICKING
	virtual int getNumVertices() { return 0; }
	virtual Vec3f getVertex(int i)
	{
		Vec3f v;
		return v;
	};
	//--用于编辑操作的FOR EDITING OPERATIONS
	virtual void moveControlPoint(int selectedPoint, float x, float y) { cout << "moveControlPoint" << endl; }
	virtual void addControlPoint(int selectedPoint, float x, float y) { cout << "addControlPoint" << endl; }
	virtual void deleteControlPoint(int selectedPoint) { cout << "deleteControlPoint" << endl; }
	//--用于产生三角形的FOR GENERATING TRIANGLES
	virtual TriangleMesh* OutputTriangles(ArgParser *args) 
	{
		TriangleMesh *t=new TriangleMesh(1,1);
		return t;
	}
};
