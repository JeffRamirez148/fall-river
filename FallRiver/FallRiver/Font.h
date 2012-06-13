
#ifndef __Font_h__
#define __Font_h__

#include <Windows.h>
#include <vector>
using namespace std;
// #include "ViewManager.h"

class ViewManager;

class Font
{
public:
	vector<RECT> FontSourceRect; //Uppercase/LowerCase/Numbers
	int nTextureID;
};

#endif
