#include "DestroyPickUp.h"
#include "PickUp.h"

DestroyPickUp::DestroyPickUp(PickUp* aPickUp) : Message(MSG_DESTROY_PICKUP)
{
	_m_pPickup = aPickUp;
	_m_pPickup->AddRef();
}

DestroyPickUp::~DestroyPickUp()
{
	_m_pPickup->Release();
}

