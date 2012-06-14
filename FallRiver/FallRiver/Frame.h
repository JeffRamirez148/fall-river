#include <Windows.h>
#include <string>
using namespace std;

#ifndef __Frame_h__
#define __Frame_h__

// #include "Animation.h"

class Animation;
class Frame;

class Frame
{
public:
	float duration;
	POINT anchor;
	RECT sourceRect;
	RECT activeRect;
	RECT colRect;
	string event;
};

#endif
