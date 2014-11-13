#pragma once
#include "MessageID.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../Game Objects/iObject.h"

class DestroyObjectMessage :
	public SGD::Message
{
public:
	DestroyObjectMessage(iObject* pObject);
	virtual ~DestroyObjectMessage();

	iObject* GetiObject() const;

private:
	iObject* m_pObject = nullptr;
};

