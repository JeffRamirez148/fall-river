#include <Windows.h>
#include <vector>
#include <assert.h>
#include <tchar.h>
using namespace std;

#include "ViewManager.h"
#include "Texture.h"
#include "Font.h"
#include "Animation.h"
#include "AnimInfo.h"

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(p)			if (p) { p->Release(); p = NULL; }
#endif

ViewManager::ViewManager()
{
	m_lpDirect3DObject	= NULL;
	m_lpDirect3DDevice	= NULL;
	m_lpSprite			= NULL;
	m_lpFont			= NULL;
	m_lpLine			= NULL;
	memset(&m_PresentParams, 0, sizeof(D3DPRESENT_PARAMETERS));
}
ViewManager* ViewManager::GetInstance() 
{
	static ViewManager s_Instance;

	return &s_Instance;
}

int ViewManager::RegisterTexture(char* aFilePath)
{
	if (!aFilePath)	return -1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (strcmp(aFilePath, textures[i].filename) == 0)
		{
			textures[i].ref++;
			return i;
		}
	}

	int nID = -1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].ref == 0)
		{
			nID = i;
			break;
		}
	}

	if (nID == -1)
	{
		Texture loaded;

		// Copy the filename of the loaded texture.
		strcpy_s(loaded.filename, _countof(loaded.filename), aFilePath);

		// Load the texture from the given file.
		HRESULT hr = 0;
		hr = D3DXCreateTextureFromFileA(m_lpDirect3DDevice, aFilePath, &loaded.texture);

		// AddRef.
		loaded.ref = 1;

		// Get surface description (to find Width/Height of the texture)
		D3DSURFACE_DESC d3dSurfDesc;
		ZeroMemory(&d3dSurfDesc, sizeof(d3dSurfDesc));

		loaded.texture->GetLevelDesc(0, &d3dSurfDesc);

		// Remember the Width and Height
		loaded.Width	= d3dSurfDesc.Width;
		loaded.Height	= d3dSurfDesc.Height;

		// Put the texture into the list.
		textures.push_back(loaded);

		// Return the nID of the texture.
		return (int)textures.size() - 1;
	}
	// we found an open spot
	else
	{
		// Make sure the texture has been released.
		SAFE_RELEASE(textures[nID].texture);

		// Copy the filename of the loaded texture.
		strcpy_s(textures[nID].filename, _countof(textures[nID].filename), aFilePath);

		// Load the texture from the given file.
		HRESULT hr = 0;
		hr = D3DXCreateTextureFromFileA(m_lpDirect3DDevice, aFilePath, &textures[nID].texture);

		// Get surface description (to find Width/Height of the texture)
		D3DSURFACE_DESC d3dSurfDesc;
		ZeroMemory(&d3dSurfDesc, sizeof(d3dSurfDesc));

		textures[nID].texture->GetLevelDesc(0, &d3dSurfDesc);

		// Remember the Width and Height
		textures[nID].Width	= d3dSurfDesc.Width;
		textures[nID].Height	= d3dSurfDesc.Height;

		// AddRef
		textures[nID].ref = 1;

		// Return the nID of the texture.
		return nID;
	}
}

int ViewManager::RegisterAnimation(char* aFilePath) 
{
	return -1;
}

int ViewManager::RegisterShader(char* aFilePath)
{
	return -1;
}

//For Drawing Animations
bool ViewManager::DrawAnimation(int nAnimID, AnimInfo* aAnimInfo, int nPosX, int nPosY, float fScaleX, float fScaleY, float fRotCenterX, 
							float fRotCenterY, float fRotation, D3DCOLOR color)
{
	return true;
}

 
//For Drawing Fonts
bool ViewManager::DrawFont(int nFontID, char* cString, int nPosX, int nPosY, float fScaleX, float fScaleY, float fRotCenterX, 
							float fRotCenterY, float fRotation, D3DCOLOR color)
{
		assert(nFontID > -1 && nFontID < (int)fonts.size() && "Font ID is out of range");

		int nX = nPosX;
		int nColStart = nX;
		int nY = nPosY;

		for(int i = 0; cString[i] != '\0'; i++)
		{
			char ch = cString[i];
			int id = ch -  ' ';

			if(ch == ' ')
			{
				//move the x over
				nX += int(fonts[nFontID].FontSourceRect[id].right - fonts[nFontID].FontSourceRect[id].left * fScaleX);
				continue;
			}
			else if(ch == '\n' )
			{
				// move the y down
				nY += int(fonts[nFontID].FontSourceRect[id].right - fonts[nFontID].FontSourceRect[id].left * fScaleY);
				nX = nColStart;
				continue;
			}

			//Draw!
			DrawStaticTexture(fonts[nFontID].nTextureID, nX, nY, 1.0f, 1.0f, &(fonts[nFontID].FontSourceRect[id]), 0, 0, 0, 0xFFFFFFFF);

			// Move position to next char
			nX += int(fonts[nFontID].FontSourceRect[id].right - fonts[nFontID].FontSourceRect[id].left * fScaleX);
		}

		return true;
}


//For Anything Else
bool ViewManager::DrawStaticTexture(int nTextureID, int nPosX, int nPosY, float fScaleX, float fScaleY, RECT* sourceRect, float fRotCenterX, 
							float fRotCenterY, float fRotation, D3DCOLOR color)
{
	// Make sure the nID is in range.
	assert(nTextureID > -1 && nTextureID < (int)textures.size() && "TextureID is out of range");

	// Make sure that the texture is valid
	assert(textures[nTextureID].texture != NULL && "Attempting to draw released texture id");

	// Make sure the sprite was created and we have a valid texture.
	if (!m_lpSprite)
		return false;

	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXMATRIX translate;
	D3DXMATRIX combined;

	// Initialize the Combined matrix.
	D3DXMatrixIdentity(&combined);

	// Scale the sprite.
	D3DXMatrixScaling(&scale, fScaleX, fScaleY, 1.0f);
	combined *= scale;

	// Rotate the sprite.
	D3DXMatrixTranslation(&translate, -fRotCenterX * fScaleX, -fRotCenterY * fScaleY, 0.0f);
	combined *= translate;
	D3DXMatrixRotationZ(&rotation, fRotation);
	combined *= rotation;
	D3DXMatrixTranslation(&translate, fRotCenterX * fScaleX, fRotCenterY * fScaleY, 0.0f);
	combined *= translate;

	// Translate the sprite
	D3DXMatrixTranslation(&translate, (float)nPosX, (float)nPosY, 0.0f);
	combined *= translate;

	// Apply the transform.
	m_lpSprite->SetTransform(&combined);

	// Draw the sprite.
	m_lpSprite->Draw(textures[nTextureID].texture, sourceRect, NULL, NULL, color);

	// Move the world back to identity.
	D3DXMatrixIdentity(&combined);
	m_lpSprite->SetTransform(&combined);

	// success.
	return true;
}



bool ViewManager::InitViewManager(HWND hWnd, int nScreenWidth, int nScreenHeight, bool bIsWindowed, bool bVsync)
{
	// Make sure the hWnd is valid.
	if (!hWnd) return false;

	// Set the handle to the window.
	m_hWnd = hWnd;

	// Create the Direct3D9 Object.
	m_lpDirect3DObject = Direct3DCreate9(D3D_SDK_VERSION);

	// Setup the parameters for using Direct3D.
	m_PresentParams.BackBufferWidth				= nScreenWidth;
	m_PresentParams.BackBufferHeight			= nScreenHeight;
	m_PresentParams.BackBufferFormat			= (bIsWindowed) ? D3DFMT_UNKNOWN : D3DFMT_R5G6B5;
	m_PresentParams.BackBufferCount				= 1;
	m_PresentParams.MultiSampleType				= D3DMULTISAMPLE_NONE;
	m_PresentParams.MultiSampleQuality			= 0;
	m_PresentParams.SwapEffect					= D3DSWAPEFFECT_COPY;
	m_PresentParams.hDeviceWindow				= hWnd;
	m_PresentParams.Windowed					= bIsWindowed;
	m_PresentParams.EnableAutoDepthStencil		= false;
	m_PresentParams.Flags						= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	m_PresentParams.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	m_PresentParams.PresentationInterval		= (bVsync) ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;

	// Create the Direct3D Device.
	m_lpDirect3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_PresentParams, &m_lpDirect3DDevice);

	// Create Sprite Object.
	D3DXCreateSprite(m_lpDirect3DDevice, &m_lpSprite);

	// Create the Line Object.
	D3DXCreateLine(m_lpDirect3DDevice, &m_lpLine);

	// Setup Line parameters.
	m_lpLine->SetAntialias(TRUE);
	m_lpLine->SetWidth(3.0f);

	//	Return success.
	return true;
}

bool ViewManager::DeviceBegin(void)
{
	m_lpDirect3DDevice->BeginScene();
	return true;
}

bool ViewManager::SpriteBegin(void)
{
	m_lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	return true;
}

bool ViewManager::LineBegin(void)
{
	m_lpLine->Begin();
	return true;
}

bool ViewManager::DeviceEnd(void)
{
	m_lpDirect3DDevice->EndScene();
	return true;
}

bool ViewManager::SpriteEnd(void)
{
	m_lpSprite->End();
	return true;
}

bool ViewManager::LineEnd(void)
{
	m_lpLine->End();
	return true;
}

void ViewManager::Present(void)
{
	m_lpDirect3DDevice->Present(0,0,0,0);
}

void ViewManager::DrawLine(int nX1, int nY1, int nX2, int nY2, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
{
	D3DXVECTOR2 verts[2];

	verts[0].x = (float)nX1;
	verts[0].y = (float)nY1;
	verts[1].x = (float)nX2;
	verts[1].y = (float)nY2;

	m_lpLine->Draw(verts, 2, D3DCOLOR_XRGB(ucRed, ucGreen, ucBlue));
}


void ViewManager::DrawUnfilledRect(RECT test, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
{
	D3DXVECTOR2 verts[5];

	verts[0].x = (float)test.left;

	verts[0].y = (float)test.top;

	verts[1].x = (float)test.right;

	verts[1].y = (float)test.top;

	verts[2].x = (float)test.right;

	verts[2].y = (float)test.bottom;

	verts[3].x = (float)test.left;

	verts[3].y = (float)test.bottom;

	verts[4].x = (float)test.left;

	verts[4].y = (float)test.top;


	m_lpLine->Draw(verts, 5, D3DCOLOR_XRGB(ucRed, ucGreen, ucBlue));
}


void ViewManager::DrawText(char *lpzText, int nX, int nY, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
{
	// Pointer to the Back Buffer.
	LPDIRECT3DSURFACE9 d3dBackBuffer = 0;

	// Get the Back Buffer from the Device.
	m_lpDirect3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &d3dBackBuffer);

	// Get a Device Context.
	HDC hdc = 0;
	d3dBackBuffer->GetDC(&hdc);

	// Print the string out to the screen.
	SetTextColor(hdc, RGB(ucRed, ucGreen, ucBlue));
	SetBkMode(hdc, TRANSPARENT);
	TextOutA(hdc, nX, nY, lpzText, (int)strlen(lpzText));

	// Release the Device Context.
	d3dBackBuffer->ReleaseDC(hdc);
	SAFE_RELEASE(d3dBackBuffer);
}

void ViewManager::Clear(unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
{
	m_lpDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(ucRed, ucGreen, ucBlue), 1.0f, 0);
}

void ViewManager::DrawRect(RECT rRt, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
{
	D3DRECT d3dRect;
	d3dRect.x1 = rRt.left;
	d3dRect.y1 = rRt.top;
	d3dRect.x2 = rRt.right;
	d3dRect.y2 = rRt.bottom;

	m_lpDirect3DDevice->Clear(1, &d3dRect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(ucRed, ucGreen, ucBlue), 1.0f, 0);
}