#include "DestroyNPC.h"
#include "NPC.h"

DestroyNPC::DestroyNPC(NPC* aNPC) : Message(MSG_DESTROY_NPC)
{
	_m_pNPC = aNPC;
	_m_pNPC->AddRef();
}

DestroyNPC::~DestroyNPC() 
{
	_m_pNPC->Release();
}

