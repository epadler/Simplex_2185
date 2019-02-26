#ifndef __MYMESH_H_
#define __MYMESH_H_

#include "Definitions.h"

class MyMesh 
{
public:
	void Init();
	MyMesh();
	GLuint m_uShaderProgramID;
	GLuint m_uVAO;
	GLuint m_uVBO;

	std::vector<vector3> m_lVertex;

	void CompileOpenGL3X();
	~MyMesh();
	void AddVectorPos(vector3 a_v3Pos);
};

#endif // __MYMESH_H_