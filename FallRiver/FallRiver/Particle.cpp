#include "Particle.h"
#include "ViewManager.h"

Particle::Particle()
{
vel.x = 0;
vel.y = 0;
vel.z = 0;
lifeSpan = 0;
pos.x = 0;
pos.y = 0;
pos.z = 0;
color = 0;
imageID = -1;
scaleX = 1;
scaleY = 1;
mode = 0;
dir.x = 0;
dir.y = 0;
dir.z = 0;
rot = 0;
}

void Particle::Render() 
{
	// View Manager Calls
	ViewManager* view = ViewManager::GetInstance();
	if(imageID != -1)
	{
		view->DrawStaticTexture(imageID, int(pos.x), int(pos.y), scaleX, scaleY, nullptr, 
							0.0f, 0.0f, rot, color);
	}
}

