#include "DestroyPickUp.h"
#include "PickUp.h"
#include "Message.h"

DestroyPickUp::DestroyPickUp(PickUp* aPickUp) : Message(MSG_1)
{
}

DestroyPickUp::~DestroyPickUp()
{
}

