#include "LoadingScreen.h"
#include "GamePlayState.h"

LoadingScreen::LoadingScreen(void)
{
	m_pVM = ViewManager::GetInstance();
	m_nBackLoad = ViewManager::GetInstance()->RegisterTexture("resource/graphics/Loading.png");
	m_nFontID	= m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");
	m_nProgress = 0;
	/*m_pVM->DeviceBegin();
	m_pVM->SpriteBegin();*/
}

LoadingScreen::~LoadingScreen()
{
	//m_pVM->SpriteEnd();
	//m_pVM->DeviceEnd();
	m_pVM = nullptr;
}

void LoadingScreen::Update()
{
	m_nProgress++;
}

void LoadingScreen::Render()
{
	// Clear the background
	m_pVM->Clear(0, 0, 0);

	//// Start D3D rendering
	m_pVM->DeviceBegin();
	m_pVM->SpriteBegin();

	m_pVM->GetSprite()->Flush();
	m_pVM->DrawStaticTexture(m_nBackLoad, 0, 0, 0.7f, 0.5f);
	m_pVM->DrawFont(m_nFontID, "Loading\nPlease Wait..", 10, 500);

	RECT progrect = {250, 525, progrect.left+(3*m_nProgress), 550};

	m_pVM->DrawRect(progrect, 255, 0, 0);

	m_pVM->SpriteEnd();
	m_pVM->DeviceEnd();

	// Render the buffer to the screen
	m_pVM->Present();
}
