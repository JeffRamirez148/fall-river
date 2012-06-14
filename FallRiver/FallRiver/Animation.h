#include <string>
#include <vector>
using namespace std;

#ifndef __Animation_h__
#define __Animation_h__

#include "Frame.h"

class Animation
{
public:
	vector<Frame> frames;
	string _name;
	int nTextureID;
	bool looping;
};

#endif
