#include "Particle.h"
#include "ViewManager.h"
#include "GamePlayState.h"

Particle::Particle()
{
vel.x = 0;
vel.y = 0;
vel.z = 0;
lifeSpan = 0;
pos.x = 0;
pos.y = 0;
pos.z = 0;
color = 0;
imageID = -1;
scaleX = 1;
scaleY = 1;
dir.x = 0;
dir.y = 0;
dir.z = 0;
rot = 0;
t = 0;
}

void Particle::Render() 
{
	// View Manager Calls
	ViewManager* view = ViewManager::GetInstance();
	DWORD tmpD;
	DWORD tmpS;
	view->GetDirect3DDevice()->GetRenderState( D3DRS_DESTBLEND, &tmpD);
	view->GetDirect3DDevice()->GetRenderState( D3DRS_SRCBLEND, &tmpS);
	DWORD tmp = DWORD(modeD);
	view->GetDirect3DDevice()->SetRenderState(D3DRS_DESTBLEND, tmp);
	tmp = DWORD(modeS);
	view->GetDirect3DDevice()->SetRenderState(D3DRS_SRCBLEND, tmp);

	view->GetSprite()->Flush();
	if(imageID != -1)
	{
		RECT tmpRect = {long(pos.x - scaleX * .5f), long(pos.y - scaleY * .5f), long(pos.x + scaleX * .5f), long(pos.y + scaleY * .5f)};
		tmpRect.left -= GamePlayState::GetInstance()->GetCamera().x;
		tmpRect.right -= GamePlayState::GetInstance()->GetCamera().x;
		tmpRect.top -= GamePlayState::GetInstance()->GetCamera().y;
		tmpRect.bottom -= GamePlayState::GetInstance()->GetCamera().y;
		view->DrawStaticTexture(imageID, pos.x, pos.y, scaleX, scaleY, nullptr,0.0f, 0.0f, rot, color);
	}
	else
	{
		RECT tmpRect = {long(pos.x - scaleX * .5f), long(pos.y - scaleY * .5f), long(pos.x + scaleX * .5f), long(pos.y + scaleY * .5f)};
		tmpRect.left -= GamePlayState::GetInstance()->GetCamera().x;
		tmpRect.right -= GamePlayState::GetInstance()->GetCamera().x;
		tmpRect.top -= GamePlayState::GetInstance()->GetCamera().y;
		tmpRect.bottom -= GamePlayState::GetInstance()->GetCamera().y;
		view->DrawRect( tmpRect, (color << 8) >> 24, (color << 16) >> 24, (color << 24) >> 24, color >> 24);

	}
	view->GetSprite()->Flush();
	view->GetDirect3DDevice()->SetRenderState(D3DRS_DESTBLEND, tmpD);
	view->GetDirect3DDevice()->SetRenderState(D3DRS_SRCBLEND, tmpS);
}

