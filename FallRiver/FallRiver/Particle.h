#include <Windows.h>
using namespace std;

#ifndef __Particle_h__
#define __Particle_h__
#include <D3DX9.h>
#pragma comment(lib, "D3DX9.lib")
class Particle
{

private: 
	int m_nFrameX;
	int m_nFrameY;
	DWORD m_dwDelay;
	D3DXVECTOR3 vel;
	float lifeSpan;
	D3DXVECTOR3 pos;
	int color;
	int imageID;
	float scale;
	int mode;

public: 
	void Render();

	void SetColor(int newColor) {color = newColor;}
	void SetScale(float newScale) {scale = newScale;}
	void SetMode(int newMode) { mode = newMode;}
	void SetImageID(int newID) { imageID = newID; }
	void SetPos( D3DXVECTOR3 newPos) { pos = newPos; }
	void SetVel( D3DXVECTOR3 newVel) { vel = newVel; }
	void SetLifeSpan(float newLifeSpan) { lifeSpan = newLifeSpan;}
	void SetDelay(DWORD newDelay) { m_dwDelay = newDelay; }
	void SetFrameX(int newFrame) { m_nFrameX = newFrame;}
	void SetFrameY(int newFrame) { m_nFrameY = newFrame;}

	int	GetColor(void) {return color;}
	float GetScale(void) {return scale;}
	int	GetMode(void) { return mode;}
	int	GetImageID(void) { return imageID; }
	D3DXVECTOR3 GetPos(void) { return pos; }
	D3DXVECTOR3 GetVel(void) { return vel; }
	float GetLifeSpan(void) { return lifeSpan;}
	DWORD GetDelay(void) { return m_dwDelay; }
	int	GetFrameX(void) { return m_nFrameX;}
	int	GetFrameY(void) { return m_nFrameY;}
};

#endif
