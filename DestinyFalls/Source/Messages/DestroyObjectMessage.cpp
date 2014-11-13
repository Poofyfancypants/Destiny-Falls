#include "stdafx.h"
#include "DestroyObjectMessage.h"
#include "MessageID.h"
#include <cassert>

DestroyObjectMessage::DestroyObjectMessage(iObject* pObject)
:Message(MessageID::MSG_DESTROY_OBJECT)
{
	assert(pObject != nullptr && "DestroyObjectMessage: Parameter cannot be null");

	m_pObject = pObject;
	m_pObject->AddRef();
}


DestroyObjectMessage::~DestroyObjectMessage()
{
	m_pObject->Release();
	m_pObject = nullptr;
}

iObject* DestroyObjectMessage::GetiObject() const
{
	return m_pObject;
}