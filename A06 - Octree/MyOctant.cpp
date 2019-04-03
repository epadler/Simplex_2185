#include "MyOctant.h"
using namespace Simplex;
// MyOctant
uint MyOctant::m_uOctantCount = 0;
uint MyOctant::m_uMaxLevel = 3;
uint MyOctant::m_uIdealEntityCount = 5;
void Simplex::MyOctant::AssignIDtoEntity(void)
{
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		m_pChild[nChild]->AssignIDtoEntity();
	}
	if (m_uChildren == 0)
	{
		uint nEntities = m_pEntityMngr->GetEntityCount();
		for (uint nIndex = 0; nIndex < nEntities; nIndex++)
		{
			if (IsColliding(nIndex))
			{
				m_EntityList.push_back(nIndex);
				m_pEntityMngr->AddDimension(nIndex, m_uID);
			}
		}
	}
}
uint MyOctant::GetOctantCount(void) { return m_uOctantCount; }



	MyOctant::~MyOctant()
	{
		Release();
	}

	void Simplex::MyOctant::Release(void)
	{
		if (m_uLevel == 0)
		{
			KillBranches();
		}
		m_uChildren = 0;
		m_fSize = 0.0f;
		m_EntityList.clear();
		m_lChild.clear();
	}

	void Simplex::MyOctant::Init(void)
	{
		m_uChildren = 0;

		m_fSize = 0.0f;

		m_uID = m_uOctantCount;
		m_uLevel = 0;

		m_v3Center = vector3(0.0f);
		m_v3Min = vector3(0.0f);
		m_v3Max = vector3(0.0f);

		m_pMeshMngr = MeshManager::GetInstance();
		m_pEntityMngr = MyEntityManager::GetInstance();

		m_pRoot = nullptr;
		m_pParent = nullptr;
		for (uint n = 0; n < 8; n++)
		{
			m_pChild[n] = nullptr;
		}
	}

	void Simplex::MyOctant::ConstructList(void)
	{
	}

	void Update()
	{

	}

	Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
	{
		Init();

		m_uOctantCount = 0;
		m_uMaxLevel = a_nMaxLevel;
		m_uIdealEntityCount = a_nIdealEntityCount;
		m_uID = m_uOctantCount;

		m_pRoot = this;
		m_lChild.clear();

		std::vector<vector3> lMinMax;

		uint nObjects = m_pEntityMngr->GetEntityCount();
		for (uint i = 0; i < nObjects; i++)
		{
			MyEntity* pEntity = m_pEntityMngr->GetEntity(i);
			MyRigidBody* pRigideBody = pEntity->GetRigidBody();
			lMinMax.push_back(pRigideBody->GetMinGlobal());
			lMinMax.push_back(pRigideBody->GetMaxGlobal());
		}
		MyRigidBody* pRigidBody = new MyRigidBody(lMinMax);

		vector3 vHalfWidth = pRigidBody->GetHalfWidth();
		float fMax = vHalfWidth.x;
		for (int i = 1; i < 3; i++)
		{
			if (fMax < vHalfWidth[i])
				fMax = vHalfWidth[i];
		}
		vector3 v3Center = pRigidBody->GetCenterLocal();
		lMinMax.clear();
		SafeDelete(pRigidBody);

		m_fSize = fMax * 2.0f;
		m_v3Center = v3Center;
		m_v3Min = m_v3Center - (vector3(fMax));
		m_v3Max = m_v3Center + (vector3(fMax));

		m_uOctantCount++;

		ConstructTree(m_uMaxLevel);
	}

	MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
	{
		Init();
		m_v3Center = a_v3Center;
		m_fSize = a_fSize;

		m_v3Min = m_v3Center - (vector3(m_fSize) / 2.0f);
		m_v3Max = m_v3Center + (vector3(m_fSize) / 2.0f);
	}

	Simplex::MyOctant::MyOctant(MyOctant const & other)
	{
		m_uChildren = other.m_uChildren;
		m_v3Center = other.m_v3Center;
		m_v3Min = other.m_v3Min;
		m_v3Max = other.m_v3Max;

		m_fSize = other.m_fSize;
		m_uID = other.m_uID;
		m_uLevel = other.m_uLevel;
		m_pParent = other.m_pParent;

		m_pRoot = other.m_pRoot;
		m_lChild = other.m_lChild;

		m_pMeshMngr = MeshManager::GetInstance();
		m_pEntityMngr = MyEntityManager::GetInstance();

		for (uint i = 0; i < 8; i++)
		{
			m_pChild[i] = other.m_pChild[i];
		}
	}

	MyOctant & Simplex::MyOctant::operator=(MyOctant const & other)
	{
		if (this != &other)
		{
			Release();
			Init();
			MyOctant temp(other);
			Swap(temp);
		}
		return *this;
	}

	void Simplex::MyOctant::Swap(MyOctant & other)
	{
		std::swap(m_uChildren, other.m_uChildren);
		std::swap(m_uID, other.m_uID);
		std::swap(m_pRoot, other.m_pRoot);
		std::swap(m_lChild, other.m_lChild);

		std::swap(m_v3Center, other.m_v3Center);
		std::swap(m_v3Min, other.m_v3Min);
		std::swap(m_v3Max, other.m_v3Max);
		
		m_pMeshMngr = MeshManager::GetInstance();
		m_pEntityMngr = MyEntityManager::GetInstance();

		std::swap(m_uLevel, other.m_uLevel);
		std::swap(m_pParent, other.m_pParent);
		
		for (uint i = 0; i < 8; i++)
		{
			std::swap(m_pChild[i], other.m_pChild[i]);
		}
	}

	float Simplex::MyOctant::GetSize(void)
	{
		return m_fSize;
	}

	vector3 Simplex::MyOctant::GetCenterGlobal(void)
	{
		return m_v3Center;
	}

	vector3 Simplex::MyOctant::GetMinGlobal(void)
	{
		return m_v3Min;
	}

	vector3 Simplex::MyOctant::GetMaxGlobal(void)
	{
		return m_v3Max;
	}

	bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
	{
		uint nObjectCount = m_pEntityMngr->GetEntityCount();
		if (a_uRBIndex >= nObjectCount)
			return false;
		MyEntity* pEntity = m_pEntityMngr->GetEntity(a_uRBIndex);
		MyRigidBody* pRigidBody = pEntity->GetRigidBody();
		vector3 v3MinO = pRigidBody->GetMinGlobal();
		vector3 v3MaxO = pRigidBody->GetMaxGlobal();

		// check x
		if (m_v3Max.x < v3MinO.x)
			return false;
		if (m_v3Min.x > v3MaxO.x)
			return false;

		// check y
		if (m_v3Max.y < v3MinO.y)
			return false;
		if (m_v3Min.y > v3MaxO.y)
			return false;

		// check z
		if (m_v3Max.z < v3MinO.z)
			return false;
		if (m_v3Min.z > v3MaxO.z)
			return false;
		return true;
	}

	void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
	{
		if (m_uID == a_nIndex)
		{
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) + glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);

			return;
		}
		for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
		{
			m_pChild[nIndex]->Display(a_nIndex);
		}
	}

	void Simplex::MyOctant::Display(vector3 a_v3Color)
	{
		for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
		{
			m_pChild[nIndex]->Display(a_v3Color);
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
		}
	}

	void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
	{
		uint nLeafs = m_lChild.size();
		for (uint nChild = 0; nChild < nLeafs; nChild++)
		{
			m_lChild[nChild]->DisplayLeafs(a_v3Color);
		}
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
	}

	void Simplex::MyOctant::ClearEntityList(void)
	{
		for (uint nChild = 0; nChild < m_uChildren; nChild++)
		{
			m_pChild[nChild]->ClearEntityList();
		}
		m_EntityList.clear();
	}

	void Simplex::MyOctant::Subdivide(void)
	{
		if (m_uLevel >= m_uMaxLevel)
			return;
		if (m_uChildren != 0)
			return;
		m_uChildren = 8;

		float fSize = m_fSize / 4.0f;
		float fSizeD = fSize * 2.0f;
		vector3 v3Center;

		// #0 bot left back
		v3Center = m_v3Center;
		v3Center.x -= fSize;
		v3Center.y -= fSize;
		v3Center.z -= fSize;
		m_pChild[0] = new MyOctant(v3Center, fSizeD);

		// #1 bot right back
		v3Center.x += fSizeD;
		m_pChild[1] = new MyOctant(v3Center, fSizeD);

		// #2 bot right front
		v3Center.z += fSizeD;
		m_pChild[2] = new MyOctant(v3Center, fSizeD);

		// #3 bot left front
		v3Center.x -= fSizeD;
		m_pChild[3] = new MyOctant(v3Center, fSizeD);

		// #4 top left front
		v3Center.y += fSizeD;
		m_pChild[4] = new MyOctant(v3Center, fSizeD);

		// #5 top left back
		v3Center.z -= fSizeD;
		m_pChild[5] = new MyOctant(v3Center, fSizeD);

		// #6 top right back
		v3Center.x += fSizeD;
		m_pChild[6] = new MyOctant(v3Center, fSizeD);

		// #7 top right front
		v3Center.z += fSizeD;
		m_pChild[7] = new MyOctant(v3Center, fSizeD);

		for (uint nIndex = 0; nIndex < 8; nIndex++)
		{
			m_pChild[nIndex]->m_pRoot = m_pRoot;
			m_pChild[nIndex]->m_pParent = this;
			m_pChild[nIndex]->m_uLevel = m_uLevel + 1;
			if (m_pChild[nIndex]->ContainsMoreThan(m_uIdealEntityCount))
			{
				m_pChild[nIndex]->Subdivide();
			}
		}
	}

	MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
	{
		if (a_nChild > 7) return nullptr;
		return m_pChild[a_nChild];
	}

	MyOctant * Simplex::MyOctant::GetParent(void)
	{
		return m_pParent;
	}

	bool Simplex::MyOctant::IsLeaf(void)
	{
		return m_uChildren == 0;
	}

	bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
	{
		uint nCount = 0;
		uint nObjectCount = m_pEntityMngr->GetEntityCount();
		for (uint n = 0; n < nObjectCount; n++)
		{
			if (IsColliding(n))
				nCount++;
			if (nCount > a_nEntities)
				return true;
		}
		return false;
	}

	void Simplex::MyOctant::KillBranches(void)
	{
		for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
		{
			m_pChild[nIndex]->KillBranches();
			delete m_pChild[nIndex];
		}
	}

	void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
	{
		if (m_uLevel != 0)
			return;

		m_uMaxLevel = a_nMaxLevel;

		m_uOctantCount = 1;

		m_EntityList.clear();

		KillBranches();
		m_lChild.clear();

		if (ContainsMoreThan(m_uIdealEntityCount))
		{
			Subdivide();
		}

		AssignIDtoEntity();

		ConstructList();
	}
