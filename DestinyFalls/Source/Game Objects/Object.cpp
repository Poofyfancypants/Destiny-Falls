#include "stdafx.h"
#include "Object.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include <cassert>

Object::~Object(void)
{
	assert(m_unRefCount == 0 && "~Object - reference remains to destroyed object");
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hImage);
}

void Object::Update(float elapsedTime)
{
	
}

void Object::Render()
{
	assert(m_hImage != SGD::INVALID_HANDLE && "Object::Render - image was not set!");

	SGD::GraphicsManager::GetInstance()->DrawTexture(
		m_hImage, m_ptPosition,
		m_fRotation, m_szSize / 2);
}

SGD::Rectangle Object::GetRect() const
{
	return SGD::Rectangle{ m_ptPosition, m_szSize };
}

void Object::HandleCollision(const iObject* pOther)
{
	(void)pOther;
}

void Object::AddRef(void)
{
	assert(m_unRefCount != 0xFFFFFFFF && "Object::AddRef - maximum reference count has been exceeded");
	++m_unRefCount;
}

void Object::Release(void)
{
	--m_unRefCount;

	if (m_unRefCount == 0)
		delete this;
}