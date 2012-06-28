#ifndef __Light_h__
#define __Light_h__

struct Light
{
	float lightDir[3];
	float lightPos[3];
	float color[3];
	float outerCone;
	float innerCone;

	// Owner
	//Player* m_pOwner;

	Light();
	~Light();

	void Update(float fElapsedTime);
};

#endif
