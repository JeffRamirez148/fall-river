#include <Windows.h>
#include <string>
using namespace std;

#ifndef __HighScoresMenuState_h__
#define __HighScoresMenuState_h__

#include "IMenuState.h"
#include "XMLManager.h"

class ViewManager;
class AudioManager;
class DirectInput;
class HighScoresMenuState;

class HighScoresMenuState : public IMenuState
{
private: 
	ViewManager*	m_pVM;
	DirectInput*	m_pDI;
	float			fTime;
	bool			end;
	int				scores[10];
	string			player[10];
	vector<tHighscore> m_vHighscore;
	AudioManager*	audio;
	int				fontID;
	int soundID2;
	int musicID;
	int musicID2;

	HighScoresMenuState();
	~HighScoresMenuState();
	HighScoresMenuState(const HighScoresMenuState&);
	HighScoresMenuState& operator=(const HighScoresMenuState&);

public: 
	static HighScoresMenuState* GetInstance();

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	void SetEnd(bool end);

	void SetOldAttractMode(bool mode);
	void ReEnter();
};

#endif
