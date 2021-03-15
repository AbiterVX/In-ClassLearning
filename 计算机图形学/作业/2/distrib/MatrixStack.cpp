#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
	Matrix4f IdentityMatrix;
	IdentityMatrix=IdentityMatrix.identity();
	m_matrices.push_back(IdentityMatrix);
}
void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
	int length = m_matrices.size();
	while (length>0) {
		m_matrices.pop_back();
		length = m_matrices.size();
	}

	Matrix4f IdentityMatrix;
	IdentityMatrix=IdentityMatrix.identity();
	m_matrices.push_back(IdentityMatrix);
}
Matrix4f MatrixStack::top()
{
	// Return the top of the stack
	int length = m_matrices.size();
	return m_matrices[length - 1];
}
void MatrixStack::push( const Matrix4f& m )
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m
	m_matrices.push_back(m);
}
void MatrixStack::pop()
{
	// Remove the top element from the stack
	int length = m_matrices.size();
	if (length>0) {
		m_matrices.pop_back();
	}
}
