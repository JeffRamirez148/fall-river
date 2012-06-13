
#ifndef __Texture_h__
#define __Texture_h__

#include <Windows.h>
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Texture
{
public:
	char				filename[260];	
	int					ref;					
	LPDIRECT3DTEXTURE9	texture;				
	int					Width;					
	int					Height;	
public:
	Texture();
};

#endif
