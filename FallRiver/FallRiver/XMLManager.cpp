#include <Windows.h>
#include <string>
using namespace std;

#include "XMLManager.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "WinMenuState.h"
#include "DefeatMenuState.h"
#include "OptionsMenuState.h"
#include "GamePlayState.h"
#include "LoadMenuState.h"
#include "ViewManager.h"
#include "Level.h"
#include "Emitter.h"
XMLManager* XMLManager::GetInstance(void)
{
	static XMLManager s_Instance;
	return &s_Instance;
}

Level* XMLManager::Parse(string aFile) 
{
	return NULL;
}

float* XMLManager::ParseSound(string aFile) 
{
	return 0;
}

void XMLManager::ParseAnim(char* aFile, Animation& anim)
{

}

Emitter* XMLManager::ParseEmitter(string aFile)
{
	TiXmlDocument doc;
	if( doc.LoadFile( aFile.c_str() ) == false )
		return false;
	TiXmlElement* pRoot = doc.RootElement();
	if( pRoot == nullptr )
		return false;
	TiXmlElement* pEmitter = pRoot->FirstChildElement("emitter_info");
	int blendModeS;
	int blendModeD;
	int endColor;
	double endRot;
	double endScaleX;
	double endScaleY;
	D3DXVECTOR3 endVel;
	int imageID;
	double lifeSpan;
	double lifeTime;
	int loopin;
	int maxParticles;
	RECT rect;
	double spawnRate;
	int startColor;
	double startRot;
	double startScaleX;
	double startScaleY;
	D3DXVECTOR3 startVel;

	double x;
	double y;
	double z;
	double left;
	double right;
	double top;
	double bottom;

	const char* pText = pEmitter->GetText();
	char imageFilePath[100];
	if( pText != nullptr )
		strcpy_s( imageFilePath, 100, pText );
	imageID = ViewManager::GetInstance()->RegisterTexture(imageFilePath);

	pEmitter = pEmitter->NextSiblingElement("emitter_info");
	pEmitter->Attribute("blendModeS", &blendModeS);
	pEmitter->Attribute("blendModeD", &blendModeD);
	pEmitter->Attribute("endColor", &endColor);
	pEmitter->Attribute("endRot", &endRot);
	pEmitter->Attribute("endScaleX", &endScaleX);
	pEmitter->Attribute("endScaleY", &endScaleY);
	pEmitter->Attribute("endVelX", &x);
	pEmitter->Attribute("endVelY", &y);
	pEmitter->Attribute("endVelZ", &z);
	endVel.x = (float)x;
	endVel.y = (float)y;
	endVel.z = (float)z;
	pEmitter->Attribute("lifeSpan", &lifeSpan);
	pEmitter->Attribute("lifeTime", &lifeTime);
	pEmitter->Attribute("loopin", &loopin);
	pEmitter->Attribute("maxParticles", &maxParticles);
	pEmitter->Attribute("rectL", &left);
	pEmitter->Attribute("rectT", &top);
	pEmitter->Attribute("rectR", &right);
	pEmitter->Attribute("rectB", &bottom);
	rect.left = (LONG)left;
	rect.bottom = (LONG)bottom;
	rect.top = (LONG)top;
	rect.right = (LONG)right;
	pEmitter->Attribute("spawnRate", &spawnRate);
	pEmitter->Attribute("startColor", &startColor);
	pEmitter->Attribute("startRot", &startRot);
	pEmitter->Attribute("startScaleX", &startScaleX);
	pEmitter->Attribute("startScaleY", &startScaleY);
	pEmitter->Attribute("startVelX", &x);
	pEmitter->Attribute("startVelY", &y);
	pEmitter->Attribute("startVelZ", &z);
	startVel.x = (float)x;
	startVel.y = (float)y;
	startVel.z = (float)z;
	bool loop;
	if(loopin == 0)
		loop = false;
	else
		loop = true;

	Emitter* emitter = new Emitter( (float)spawnRate, loop, rect, maxParticles,startVel,endVel, (float)startScaleX, (float)startScaleY, (float)endScaleX, (float)endScaleY, blendModeS, blendModeD, imageID, (float)lifeSpan, (float)lifeTime, startColor, endColor, (float)startRot, (float)endRot);
	return emitter;
}
