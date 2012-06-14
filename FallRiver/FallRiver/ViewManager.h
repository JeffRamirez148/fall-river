#ifndef __ViewManager_h__
#define __ViewManager_h__

#include <Windows.h>
#include <vector>
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// #include "GamePlayState.h"
// #include "HighScoresMenuState.h"
// #include "WinMenuState.h"
// #include "DefeatMenuState.h"
// #include "CreditsMenuState.h"
// #include "LoadMenuState.h"
// #include "PauseMenuState.h"
// #include "MainMenuState.h"
// #include "HowToPlayMenuState.h"
// #include "Texture.h"
// #include "Font.h"
// #include "Animation.h"
// #include "AnimInfo.h"
// #include "HUD.h"
// #include "CutScene.h"

class Texture;
class Font;
class Animation;
class AnimInfo;

class ViewManager
{
private: 
	vector<Animation> animations;
	vector<Texture> textures;
	vector<Font> fonts;

	ViewManager();
	ViewManager(const ViewManager&);
	ViewManager& operator=(const ViewManager&);

	LPDIRECT3D9					m_lpDirect3DObject;
	LPDIRECT3DDEVICE9			m_lpDirect3DDevice;
	LPD3DXSPRITE				m_lpSprite;
	LPD3DXFONT					m_lpFont;
	LPD3DXLINE					m_lpLine;
	D3DPRESENT_PARAMETERS		m_PresentParams;
	HWND						m_hWnd;

public: 
	static ViewManager* GetInstance();

	//Initializing the manager
	bool InitViewManager(HWND hWnd, int nScreenWidth, int nScreenHeight, bool bIsWindowed, bool bVsync);

	//All of these work exactly the same as from SGD
	void Clear(unsigned char ucRed = 0, unsigned char ucGreen = 0, unsigned char ucBlue = 0);
	bool DeviceBegin(void);
	bool SpriteBegin(void);
	bool LineBegin(void);
	bool DeviceEnd(void);
	bool SpriteEnd(void);
	bool LineEnd(void);
	void Present(void);
	void DrawLine(int nX1, int nY1, int nX2, int nY2, unsigned char ucRed = 255, unsigned char ucGreen = 255, unsigned char ucBlue = 255);
	void DrawUnfilledRect(RECT test, unsigned char ucRed = 255, unsigned char ucGreen = 255, unsigned char ucBlue = 255);
	void DrawText(char *lpzText, int nX, int nY, unsigned char ucRed = 255, unsigned char ucGreen = 255, unsigned char ucBlue = 255);
	void DrawRect(RECT rRt, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue);

	//Loading assets
	int RegisterTexture(char* aFilePath);
	int RegisterAnimation(char* aFilePath);
	int RegisterShader(char* aFilePath);

	//For Drawing Animations
	bool DrawAnimation(int nAnimID, AnimInfo* aAnimInfo, int nPosX, int nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, float fRotCenterX = 0, 
								float fRotCenterY = 0, float fRotation = 0, D3DCOLOR color = 0xFFFFFFFF);
 
	//For Drawing Fonts
	bool DrawFont(int nFontID, char* cString, int nPosX, int nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, float fRotCenterX = 0, 
								float fRotCenterY = 0, float fRotation = 0, D3DCOLOR color = 0xFFFFFFFF);

	//For Anything Else
	bool DrawStaticTexture(int nTextureID, int nPosX, int nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, RECT* sourceRect = nullptr, 
							float fRotCenterX = 0, float fRotCenterY = 0, float fRotation = 0, D3DCOLOR color = 0xFFFFFFFF);



};

#endif
