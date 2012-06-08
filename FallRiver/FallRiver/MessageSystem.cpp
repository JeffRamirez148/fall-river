#include <Windows.h>
#include <queue>
using namespace std;

#include "MessageSystem.h"
#include "IMessage.h"
#include "GamePlayState.h"

MessageSystem* MessageSystem::GetInstance() {
	static MessageSystem s_Instance;

	return &s_Instance;
}

void MessageSystem::InitMessageSystem(MESSAGEPROC aMessageproc) 
{
}

void MessageSystem::SendMsg(IMessage* aMessage) 
{
}

void MessageSystem::ProcessMessages() 
{
}

void MessageSystem::ClearMessages() 
{
}

void MessageSystem::Shutdown() 
{
}

