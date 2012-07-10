#include "Light.h"
#include "Player.h"

Light::Light()
{
	lightDir[0] = 0;
	lightDir[1] = 0;
	lightDir[2] = 0;
	lightPos[0] = 0;
	lightPos[1] = 0;
	lightPos[2] = 0;
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	outerCone = .7f;
	innerCone = .9f;
}

Light::~Light()
{

}

void Light::Update(float fElapsedTime) 
{
}

