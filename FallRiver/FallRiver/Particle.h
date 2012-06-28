#ifndef __Particle_h__
#define __Particle_h__

#include <Windows.h>
using namespace std;
#include <D3DX9.h>
#pragma comment(lib, "D3DX9.lib")
class Particle
{

private: 
	D3DXVECTOR3 vel;
	float lifeSpan;
	D3DXVECTOR3 pos;
	int color;
	int imageID;
	float scaleX;
	float scaleY;
	float rot;
	D3DXVECTOR3 dir;
	float t;
	int modeS;
	int modeD;

public: 
	Particle();
	void Render();

	void SetColor(int newColor) {color = newColor;}
	void SetScaleX(float newScale) {scaleX = newScale;}
	void SetScaleY(float newScale) {scaleY = newScale;}
	void SetImageID(int newID) { imageID = newID; }
	void SetPos( D3DXVECTOR3 newPos) { pos = newPos; }
	void SetVel( D3DXVECTOR3 newVel) { vel = newVel; }
	void SetDir( D3DXVECTOR3 newDir) { dir = newDir; }
	void SetLifeSpan(float newLifeSpan) { lifeSpan = newLifeSpan;}
	void SetRotation(float newRot) { rot = newRot;}
	void SetTime(float time) { t = time;}
	void SetModeS(int mode){ modeS = mode; }
	void SetModeD(int mode){ modeD = mode; }

	int	GetColor(void) {return color;}
	float GetScaleX(void) {return scaleX;}
	float GetScaleY(void) {return scaleY;}
	int	GetImageID(void) { return imageID; }
	D3DXVECTOR3 GetPos(void) { return pos; }
	D3DXVECTOR3 GetVel(void) { return vel; }
	D3DXVECTOR3 GetDir(void) { return dir; }
	float GetLifeSpan(void) { return lifeSpan;}
	float GetRotation(void) { return rot;}
	float GetTime() { return t; }
};

#endif
