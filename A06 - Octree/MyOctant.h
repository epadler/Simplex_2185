#pragma once
#include "MyEntityManager.h"
namespace Simplex 
{
	class MyOctant
	{
	public:
		MyOctant();
		~MyOctant();

		typedef MyRigidBody* PRigidBody; //Entity Pointer


		vector3 origin;
		int length;

		vector3 m_v3CenterL = ZERO_V3; //center point in local space
		vector3 m_v3CenterG = ZERO_V3; //center point in global space

		vector3 m_v3MinL = ZERO_V3; //minimum coordinate in local space (for OBB)
		vector3 m_v3MaxL = ZERO_V3; //maximum coordinate in local space (for OBB)

		vector3 m_v3MinG = ZERO_V3; //minimum coordinate in global space (for ARBB)
		vector3 m_v3MaxG = ZERO_V3; //maximum coordinate in global space (for ARBB)

		vector3 m_v3HalfWidth = ZERO_V3; //half the size of the Oriented Bounding Box
		vector3 m_v3ARBBSize = ZERO_V3;// size of the Axis (Re)Alligned Bounding Box

		matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate

		uint m_nCollidingCount = 0; //size of the colliding set
		PRigidBody* m_CollidingArray = nullptr; //array of rigid bodies this one is colliding with
	};

	void Update();
}


