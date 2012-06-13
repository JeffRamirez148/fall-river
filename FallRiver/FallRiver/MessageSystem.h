#include "IMessage.h"
#include <queue>
using namespace std;

#ifndef __MessageSystem_h__
#define __MessageSystem_h__

typedef void (*MESSAGEPROC)(IMessage*);

class MessageSystem
{
	queue<IMessage*>			m_MsgQueue;				//	Stores my messages.
	MESSAGEPROC					m_pfnMsgProc;			//	Points to user defined function.

	MessageSystem() { m_pfnMsgProc = NULL;	}
	MessageSystem(const MessageSystem&);
	MessageSystem& operator=(const MessageSystem&);
	~MessageSystem() {}

public:
	static MessageSystem* GetInstance(void);
	inline int GetNumberOfMessages(void) { return (int)m_MsgQueue.size(); }
	void InitMessageSystem(MESSAGEPROC pfnMsgProc);
	void SendMsg(IMessage* pMsg);
	void ProcessMessages(void);
	void ClearMessages(void);
	void Shutdown(void);
};
#endif
