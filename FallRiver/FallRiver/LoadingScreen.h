#pragma once

#include "ViewManager.h"

class LoadingScreen
{
private:
	ViewManager*		m_pVM;

	int m_nProgress;
	int m_nBackLoad;
	int m_nFontID;

	//LoadingScreen(void);
	//~LoadingScreen(void);
	//LoadingScreen(const LoadingScreen&);
	//LoadingScreen& operator=(const LoadingScreen&);

public:
	LoadingScreen(void);
	~LoadingScreen(void);
	//static LoadingScreen* GetInstance();

	void Update();
	void Render();
};

