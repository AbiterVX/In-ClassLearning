#include "SkeletalModel.h"

#include <FL/Fl.H>
#include<math.h>
using namespace std;

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
	loadSkeleton(skeletonFile);

	m_mesh.load(meshFile);
	m_mesh.loadAttachments(attachmentsFile, m_joints.size());

	computeBindWorldToJointTransforms();
	updateCurrentJointToWorldTransforms();
}

void SkeletalModel::draw(Matrix4f cameraMatrix, bool skeletonVisible)
{
	// draw() gets called whenever a redraw is required
	// (after an update() occurs, when the camera moves, the window is resized, etc)

	m_matrixStack.clear();
	m_matrixStack.push(cameraMatrix);

	if( skeletonVisible )
	{
		drawJoints();

		drawSkeleton();
	}
	else
	{
		// Clear out any weird matrix we may have been using for drawing the bones and revert to the camera matrix.
		glLoadMatrixf(m_matrixStack.top());

		// Tell the mesh to draw itself.
		m_mesh.draw();
	}
}

void SkeletalModel::loadSkeleton( const char* filename )
{
	// Load the skeleton from file here.
	FILE *file;
	file = fopen(filename, "r");
	float x,y,z;
	int number;
	m_rootJoint = new Joint();
	m_rootJoint->currentJointToWorldTransform=m_rootJoint->currentJointToWorldTransform.identity();
	m_rootJoint->bindWorldToJointTransform=m_rootJoint->bindWorldToJointTransform.identity();
	m_rootJoint->transform=m_rootJoint->transform.identity();

	while (fscanf(file, "%f %f %f %d", &x, &y, &z, &number)!=EOF) {
		Joint *NewJoint=new Joint();
		NewJoint->transform=NewJoint->transform.translation(x,y,z);
		NewJoint->bindWorldToJointTransform=NewJoint->bindWorldToJointTransform.identity();
		NewJoint->currentJointToWorldTransform=NewJoint->currentJointToWorldTransform.identity();
		if (number!=-1) {
			m_joints[number]->children.push_back(NewJoint);
		}
		else {		
			m_rootJoint->children.push_back(NewJoint);
		}			
		m_joints.push_back(NewJoint);
	}	
	fclose(file);


	for (int i = 0; i < m_joints.size(); i++)
	{
		m_joints[i]->bindWorldToJointTransform = m_joints[i]->transform;
	}
}


//画关节
void SkeletalModel::drawJoints( )
{
	// Draw a sphere at each joint. You will need to add a recursive helper function to traverse the joint hierarchy.
	//
	// We recommend using glutSolidSphere( 0.025f, 12, 12 )
	// to draw a sphere of reasonable size.
	//
	// You are *not* permitted to use the OpenGL matrix stack commands
	// (glPushMatrix, glPopMatrix, glMultMatrix).
	// You should use your MatrixStack class
	// and use glLoadMatrix() before your drawing call.
	JointsTraverse(m_rootJoint);
	glLoadMatrixf(m_matrixStack.top().identity());
}
void SkeletalModel::JointsTraverse2(Joint *CurrentJoint)
{
	if (CurrentJoint != m_rootJoint) {	
		Vector4f CurrentPoint(CurrentJoint->transform * CurrentJoint->bindWorldToJointTransform.getCol(3));
		CurrentJoint->currentJointToWorldTransform.setCol(3,CurrentPoint);
	
		//cout << CurrentPoint.x() << "," << CurrentPoint.y() << "," << CurrentPoint.z() << endl;

		CurrentJoint->currentJointToWorldTransform.print();
		cout << endl;
		glTranslatef(CurrentPoint.x(), CurrentPoint.y(), CurrentPoint.z());
		glutSolidSphere(0.025f, 12, 12);
		glTranslatef(-CurrentPoint.x(),-CurrentPoint.y(),-CurrentPoint.z());
	}
	int length = CurrentJoint->children.size();
	if (length!=0) {
		for (int i = 0; i < length;i++) {
			CurrentJoint->children[i]->bindWorldToJointTransform = CurrentJoint->currentJointToWorldTransform;
			JointsTraverse2(CurrentJoint->children[i]);
		}
	}	
}
void SkeletalModel::JointsTraverse(Joint *CurrentJoint)
{
	int length = CurrentJoint->children.size();
	if (length != 0) {
		m_matrixStack.push( m_matrixStack.top()*CurrentJoint->transform );  //!!!!!!!!!!!!!!!相反
		for (int i = 0; i < length; i++) {
			JointsTraverse(CurrentJoint->children[i]);
		}
		m_matrixStack.pop();	
	}
	if (CurrentJoint != m_rootJoint) {
		glLoadMatrixf(m_matrixStack.top()*CurrentJoint->transform );
		glutSolidSphere(0.025f, 12, 12);
	}
}

//画骨骼
void SkeletalModel::drawSkeleton( )  //绘制骨骼
{
	// Draw boxes between the joints. You will need to add a recursive helper function to traverse the joint hierarchy.
	SkeletonTraverse(m_rootJoint);
}
void SkeletalModel::SkeletonTraverse(Joint *CurrentJoint) {
	int length = CurrentJoint->children.size();
	if (length != 0) {
		m_matrixStack.push(m_matrixStack.top()*CurrentJoint->transform);  
		for (int i = 0; i < length; i++) {	
			Matrix4f *CurrentMatrix = new Matrix4f(CurrentJoint->transform);
			SkeletonTraverse(CurrentJoint->children[i]);
		}
		m_matrixStack.pop();
	}

	if (CurrentJoint != m_rootJoint) {
		if (LastJoint!=NULL) {					
			for (int i = 0; i < length; i++) {
				Matrix4f CurrentMatrix = m_matrixStack.top()*CurrentJoint->transform;
				Matrix4f TransformMatrix = CurrentJoint->transform.identity();
				Vector3f Z_Axis(0, 0, 1);

				Matrix4f NextMatrix = CurrentJoint->children[i]->transform;
				Vector3f Direction(NextMatrix.getCol(3).x(), NextMatrix.getCol(3).y(), NextMatrix.getCol(3).z());
				float Length = Direction.abs();
				Direction = Direction.normalized();
				float radians = acos(abs(Direction.z()));
				int Sympol = 1;															//叉乘的先后位置，
				if (Direction.z() >= 0) {
					Direction = Direction.cross(Z_Axis, Direction);
				}
				else {
					Sympol = -1;
					Direction = Direction.cross(Direction, Z_Axis);
				}
				//Direction = Direction.normalized();
				TransformMatrix = TransformMatrix.rotation(Direction, radians);
				//cout << radians <<","<< Direction.x() << "," << Direction.y() << "," << Direction.z() << endl;			
				CurrentMatrix = CurrentMatrix * TransformMatrix;
				Matrix4f transform;
				Vector3f transformvector(0, 0, Sympol*Length / 2);			//叉乘方向。 
				transform = transform.translation(transformvector);
				glLoadMatrixf(CurrentMatrix*transform);
				
				glScalef(0.025, 0.025, Length);
				glutSolidCube(1.0f);						
			}
		}		
	}
}


//关节转动
void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
	// Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.

	Matrix4f Transform = Matrix4f::rotateX(rX)*Matrix4f::rotateY(rY)* Matrix4f::rotateZ(rZ);
	Transform.setCol(3, m_joints[jointIndex]->transform.getCol(3));
	m_joints[jointIndex]->transform = Transform;


	//m_joints[jointIndex]->transform = m_joints[jointIndex]->bindWorldToJointTransform*Transform;
	//JointTransformTraverse(m_joints[jointIndex],Transform);						//!!!!!!!!!
	/*
	for (int i = 0; i < m_joints[jointIndex]->children.size();i++) {
		m_joints[jointIndex]->children[i]->transform = Transform* m_joints[jointIndex]->children[i]->transform ;
	}*/
}

//初始绑定
void SkeletalModel::computeBindWorldToJointTransforms()
{
	// 2.3.1. Implement this method to compute a per-joint transform from
	// world-space to joint space in the BIND POSE.
	//
	// Note that this needs to be computed only once since there is only
	// a single bind pose.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy. 
	m_rootJoint->bindWorldToJointTransform = Matrix4f::identity();
	BindWorld_Recursive(m_rootJoint);
}
void SkeletalModel::BindWorld_Recursive(Joint *CurrentJoint) {
	CurrentJoint->bindWorldToJointTransform = CurrentJoint->bindWorldToJointTransform*CurrentJoint->transform;
	int length = CurrentJoint->children.size();
	for (int i = 0; i < length; i++) {
		CurrentJoint->children[i]->bindWorldToJointTransform = CurrentJoint->bindWorldToJointTransform;
		BindWorld_Recursive(CurrentJoint->children[i]);
	}	
}


//更新
void SkeletalModel::updateCurrentJointToWorldTransforms()
{
	// 2.3.2. Implement this method to compute a per-joint transform from
	// joint space to world space in the CURRENT POSE.
	//
	// The current pose is defined by the rotations you've applied to the
	// joints and hence needs to be *updated* every time the joint angles change.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.
	m_rootJoint->currentJointToWorldTransform = Matrix4f::identity();
	CurrentWorld_Recursive(m_rootJoint);
}
void SkeletalModel::CurrentWorld_Recursive(Joint *CurrentJoint) {
	CurrentJoint->currentJointToWorldTransform = CurrentJoint->currentJointToWorldTransform*CurrentJoint->transform;
	int length = CurrentJoint->children.size();
	for (int i = 0; i < length; i++) {
		CurrentJoint->children[i]->currentJointToWorldTransform = CurrentJoint->currentJointToWorldTransform;
		CurrentWorld_Recursive(CurrentJoint->children[i]);
	}
}


void SkeletalModel::updateMesh()
{
	// 2.3.2. This is the core of SSD.
	// Implement this method to update the vertices of the mesh
	// given the current state of the skeleton.
	// You will need both the bind pose world --> joint transforms.
	// and the current joint --> world transforms.

	int verteices_number=m_mesh.currentVertices.size();
	int joint_number = m_mesh.attachments[0].size();

	for (int i = 0; i < verteices_number;i++) {
		m_mesh.currentVertices[i]=Vector3f::ZERO;

		Vector4f bind_vertices(m_mesh.bindVertices[i], 1);
		for (int j = 0; j < joint_number;j++) {
			// m_joints[j]->transform*
			Vector4f Position = m_joints[j]->currentJointToWorldTransform *m_joints[j]->bindWorldToJointTransform.inverse() *  bind_vertices;
			m_mesh.currentVertices[i] += m_mesh.attachments[i][j] * Position.xyz();
		}
	}
}


void SkeletalModel::SelectMode() {
	GLuint selectBuffer[18] = { 0 };
	
	glSelectBuffer(18, selectBuffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//-------
	glLoadName(1);


	//-------
	glPopMatrix();   //对应glPushMatrix
	glFlush();


	GLuint hits = glRenderMode(GL_RENDER);
	GLuint *ptr = selectBuffer;


}
