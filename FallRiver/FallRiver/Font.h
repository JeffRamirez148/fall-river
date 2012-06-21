
#ifndef __Font_h__
#define __Font_h__

#include <Windows.h>
#include <vector>
using namespace std;
// #include "ViewManager.h"

class ViewManager;

class Kerning
{
public:
	int amount;
	int secondID;
	int firstID;


	Kerning();
	~Kerning();
};

class Font
{
public:
	int id;
	int yoffset;
	int xoffset;
	int height;
	int width;
	int x;
	int y;
	//RECT srcRect;
	//int nTextureID;

	Font();
	~Font();


};

#endif
