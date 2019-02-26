#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	// m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);
	m_pMesh->GenerateCube(1.0f, C_BLACK);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f,2.0f,2.0f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 2.0f, 3.0f));
	value += 0.01f;

	//matrix4 m4Model = m4Translate * m4Scale;
	for (int i = 0; i < 11; i++)
	{
		matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value+i, 1.0f, 1.0f));
		matrix4 m4Model = m4Scale * m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);

	}
	m4Translate = glm::translate(IDENTITY_M4, vector3(value+1, 2.0f, 1.0f));
	matrix4 m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value, 0.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	for (int i = 2; i < 9; i++)
	{
		matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value + i, 0.0f, 1.0f));
		matrix4 m4Model = m4Scale * m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}

	m4Translate = glm::translate(IDENTITY_M4, vector3(value, -1.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value+2, 2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 4, 2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 5, 2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 6, 2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 8, 2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 9, 2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	for (int i = 2; i < 9; i++)
	{
		matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value + i, 3.0f, 1.0f));
		matrix4 m4Model = m4Scale * m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 3, 4.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 2, 5.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 7, 4.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 8, 5.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 10, 0.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 10, -1.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value+2, -1.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 8, -1.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 3, -2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 4, -2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 6, -2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(value + 7, -2.0f, 1.0f));
	m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);
	// matrix4 m4Model = m4Scale * m4Translate;
	// m_pMesh->Render(m4Projection, m4View, m4Model);

	// m4Translate = glm::translate(IDENTITY_M4, vector3(value+1, 2.0f, 3.0f));
	// m4Model = m4Scale * m4Translate;
	// m_pMesh->Render(m4Projection, m4View, m4Model);

	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}