#include <Windows.h>
#include <string>
using namespace std;

#ifndef __HighScoresMenuState_h__
#define __HighScoresMenuState_h__

class ViewManager;
class AudioManager;
class DirectInput;
class HighScoresMenuState;

class HighScoresMenuState
{
private: 
	ViewManager* view;
	DirectInput* input;
	float fTime;
	int y;
	bool end;
	int scores[10];
	string player[10];
	AudioManager* audio;

public: 
	static HighScoresMenuState* GetInstance();

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	void SetEnd(bool end);

	void SetOldAttractMode(bool mode);
};

#endif
