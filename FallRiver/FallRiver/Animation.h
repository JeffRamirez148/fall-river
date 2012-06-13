#include <string>
#include <vector>
using namespace std;

#ifndef __Animation_h__
#define __Animation_h__

// #include "ViewManager.h"
// #include "Frame.h"

class Frame;

class Animation
{
public:
	vector<Frame*> frames;
	string _name;
	int animationID;
	bool looping;
};

#endif
