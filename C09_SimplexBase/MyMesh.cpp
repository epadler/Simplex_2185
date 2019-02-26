#include "MyMesh.h";

void MyMesh::Init()
{
	m_uShaderProgramID = 0;
	m_uVAO = 0;
	m_uVBO = 0;
}

MyMesh::~MyMesh()
{

}

void MyMesh::AddVectorPos(vector3 a_v3Pos)
{
	m_lVertex.push_back(a_v3Pos);
}
