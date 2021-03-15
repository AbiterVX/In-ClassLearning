#include "Mesh.h"
#include<vector>
using namespace std;

void Mesh::load( const char* filename )
{
	// 2.1.1. load() should populate bindVertices, currentVertices, and faces
	// Add your code here.

	string data, type, x, y, z;
	ifstream file;
	file.open(filename);
	while (getline(file, data)) {
		istringstream in(data);
		in >> type >> x >> y >> z;
		if (type == "v") {
			Vector3f NewVertice(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));		
			bindVertices.push_back(NewVertice);
		}
		else if (type == "f") {
			Tuple3u NewFace(atoi(x.c_str()) - 1, atoi(y.c_str()) - 1, atoi(z.c_str()) - 1);
			faces.push_back(NewFace);
		}
	}
	file.close();

	// make a copy of the bind vertices as the current vertices
	currentVertices = bindVertices;
}

void Mesh::draw()
{
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".
	
	/*if (!glIsList((GLuint)1)) {
		glNewList(1, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		Vector3f **VetexS;
		VetexS = new Vector3f*[3];
		for (int i = 0; i < faces.size(); i++) {					
			for (int j = 0; j < 3; j++) {
				VetexS[j] = new Vector3f(currentVertices[faces[i][j]].x(),currentVertices[faces[i][j]].y(),currentVertices[faces[i][j]].z());			
			}

			Vector3f edge1 = *VetexS[1]- *VetexS[0];
			Vector3f edge2 = *VetexS[2]- *VetexS[0];
			edge1.normalize();
			edge2.normalize();
			Vector3f Normal(Vector3f::cross(edge1, edge2));
			glNormal3f(Normal.x(), Normal.y(), Normal.z());
			for (int j = 0; j < 3; j++) {
				glVertex3d(VetexS[j]->x(), VetexS[j]->y(), VetexS[j]->z());
			}
		}
		glEnd();
		glEndList();	
	}
	glCallList(1);*/
	glBegin(GL_TRIANGLES);
	Vector3f **VetexS;
	VetexS = new Vector3f*[3];
	for (int i = 0; i < faces.size(); i++) {
		for (int j = 0; j < 3; j++) {
			VetexS[j] = new Vector3f(currentVertices[faces[i][j]].x(), currentVertices[faces[i][j]].y(), currentVertices[faces[i][j]].z());
		}

		Vector3f edge1 = *VetexS[1] - *VetexS[0];
		Vector3f edge2 = *VetexS[2] - *VetexS[0];
		edge1.normalize();
		edge2.normalize();
		Vector3f Normal(Vector3f::cross(edge1, edge2));
		glNormal3f(Normal.x(), Normal.y(), Normal.z());
		for (int j = 0; j < 3; j++) {
			glVertex3d(VetexS[j]->x(), VetexS[j]->y(), VetexS[j]->z());
		}
	}
	glEnd();
}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 2.2. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments
	float* Weights = new float[numJoints];
	string data;
	ifstream file;
	file.open(filename);
	while (getline(file, data)) {
		istringstream in(data);
		vector<float> CurrentVertex;
		CurrentVertex.push_back(0);
		for (int i = 1; i < numJoints;i++) {
			in >> Weights[i];
			CurrentVertex.push_back(Weights[i]);
		}
		attachments.push_back(CurrentVertex);	
	}
	file.close();
}
