#include <string>
#include <vector>
using namespace std;

#ifndef __Animation_h__
#define __Animation_h__

#include "Frame.h"

class Animation
{
public:
	vector<vector<Frame>> frames;
	char filepath[260];
	int nTextureID;
	vector<bool> looping;
};

#endif
