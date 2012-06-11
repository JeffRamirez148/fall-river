#include "MessageSystem.h"

MessageSystem* MessageSystem::GetInstance()
{
	static MessageSystem s_Instance;
	return &s_Instance;
}

void MessageSystem::InitMessageSystem(MESSAGEPROC aMessageproc) 
{
		if (!aMessageproc)
			return;
		m_pfnMsgProc = aMessageproc;
}

void MessageSystem::SendMsg(IMessage* aMessage) 
{
	if (!aMessage)
		return;

	m_MsgQueue.push(aMessage);
}

void MessageSystem::ProcessMessages() 
{
	if(!m_pfnMsgProc)
		return;

	while(!m_MsgQueue.empty())
	{
		m_pfnMsgProc(m_MsgQueue.front());
		delete m_MsgQueue.front();
		m_MsgQueue.pop();
	}
}

void MessageSystem::ClearMessages() 
{
	while(!m_MsgQueue.empty())
	{
		delete m_MsgQueue.front();
		m_MsgQueue.pop();
	}
}

void MessageSystem::Shutdown() 
{
	ClearMessages();
	m_pfnMsgProc = NULL;
}

