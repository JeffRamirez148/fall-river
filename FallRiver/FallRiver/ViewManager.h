#ifndef __ViewManager_h__
#define __ViewManager_h__

#include <Windows.h>
#include <vector>
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Animation.h"
#include "Light.h"

class Texture;
class Font;
class Kerning;
class Animation;
class AnimInfo;
class GamePlayState;
class GamePlayState;
class HighScoresMenuState;
class WinMenuState;
class DefeatMenuState;
class CreditsMenuState;
class LoadMenuState;
class PauseMenuState;
class MainMenuState;
class HowToPlayMenuState;
class HUD;
class CutScene;



class ViewManager
{
private: 
	vector<Animation> animations;
	vector<Texture> textures;
	vector<Font> fonts;
	vector<Kerning> kerns;
	vector<Light*> lights;

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


	ID3DXEffect					*postEffect;
	IDirect3DTexture9			*renderTarget;
	D3DSURFACE_DESC				backbuffer;
	IDirect3DSurface9			*current;
	IDirect3DSurface9			*output;
	IDirect3DVertexBuffer9		*wallbuff;
	IDirect3DVertexDeclaration9	*cubedecl;
	D3DXMATRIX					cam;
	D3DXMATRIX					proj;
	D3DXMATRIX					wall;
	float						ambientLight[3];
	float						lightDir[3];
	float						lightPos[3];
	float						spotLightPos[3];
	float						innerCone;
	float						outerCone;
	float						color[3];
	int							lightNum;
	struct VERTUV
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2	uv;
	};

	int QuestLog;

public: 
	Animation GetAnimation(int AnimID) {return animations[AnimID]; };

	static ViewManager* GetInstance();
	//Initializing the manager
	bool InitViewManager(HWND hWnd, int nScreenWidth, int nScreenHeight, bool bIsWindowed, bool bVsync);

	//Accessors
	LPDIRECT3D9					 GetDirect3DObject(void)	{ return m_lpDirect3DObject; }
	LPDIRECT3DDEVICE9			 GetDirect3DDevice(void)	{ return m_lpDirect3DDevice; }
	LPD3DXSPRITE				 GetSprite(void)			{ return m_lpSprite;		 }
	LPD3DXLINE					 GetLine(void)				{ return m_lpLine;			 }
	const D3DPRESENT_PARAMETERS* GetPresentParams(void)		{ return &m_PresentParams;	 }

	//Mutators
	void ChangeDisplayParam(int nWidth, int nHeight, bool bWindowed);

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
	void DrawRect(RECT rRt, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue, unsigned char uAlpha = 255);

	//Loading assets
	int RegisterTexture(char* aFilePath);
	int RegisterAnimation(char* aFilePath);
	int RegisterShader(char* aFilePath);
	int RegisterFont(char* filename );

	//For Drawing Animations
	bool DrawAnimation(AnimInfo* aAnimInfo, float nPosX, float nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, float fRotCenterX = 0, 
								float fRotCenterY = 0, float fRotation = 0, D3DCOLOR color = 0xFFFFFFFF);
 
	//For Drawing Fonts
	bool DrawFont(int nFontID, char* cString, float nPosX, float nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, float fRotCenterX = 0, 
								float fRotCenterY = 0, float fRotation = 0, D3DCOLOR color = 0xFFFFFFFF);

	//For Anything Else
	bool DrawStaticTexture(int nTextureID, float nPosX, float nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, RECT* sourceRect = nullptr, 
							float fRotCenterX = 0, float fRotCenterY = 0, float fRotation = 0, D3DCOLOR color = 0xFFFFFFFF);

	//
	void ShutdownDirect3D(void);

	// Lights
	int RegisterLight(Light light);
	void RemoveLight(int id);
	void RemoveLights(void);
	Light* GetLight(int id);

	
	void SetAmbientLight(float r, float g, float b)
	{
		ambientLight[0] = r;
		ambientLight[1] = g;
		ambientLight[2] = b;
	}

	void SetLightDir(float x, float y, float z)
	{
		lightDir[0] = x;
		lightDir[1] = y;
		lightDir[2] = z;
	}

	void SetLightPos(float x, float y, float z)
	{
		lightPos[0] = x;
		lightPos[1] = y;
		lightPos[2] = z;
	}

	void SetInnerCone(float cone) { innerCone = cone; }
	void SetOuterCone(float cone) { outerCone = cone; }

	void SetSpotLightPos(float x, float y, float z)
	{
		spotLightPos[0] = x;
		spotLightPos[1] = y;
		spotLightPos[2] = z;
	}

	void SetColor(float r, float g, float b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	float GetInnerCone(void) { return innerCone; }
	float GetOuterCone(void) { return outerCone; }

};

#endif
