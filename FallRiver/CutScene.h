#include <Windows.h>
using namespace std;

#ifndef __CutScene_h__
#define __CutScene_h__

// #include "ViewManager.h"
// #include "AudioManager.h"

class ViewManager;
class AudioManager;
class CutScene;

class CutScene
{
public: 
	void Update(float fElapsedTime);

	void Render();
};

#endif
