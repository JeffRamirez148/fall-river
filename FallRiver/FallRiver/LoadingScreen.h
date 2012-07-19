#pragma once

#include "ViewManager.h"

class LoadingScreen
{
private:
	ViewManager*		m_pVM;

	int m_nProgress;
	int m_nBackLoad;
	int m_nFontID;
	DWORD m_dwFlashlight;

	LoadingScreen(void);
	~LoadingScreen(void);
	LoadingScreen(const LoadingScreen&);
	LoadingScreen& operator=(const LoadingScreen&);

public:
	static LoadingScreen* GetInstance();

	void Reset();
	int GetProgress() {return m_nProgress;}
	int GetFontID() {return m_nFontID;}

	void Update();
	void Render();
};

