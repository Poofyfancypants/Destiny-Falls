#pragma once
#include "iObject.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_Handle.h"

class Object :
	public iObject
{

public:
	Object() = default;
protected:
	virtual ~Object();

public:
	virtual void Update(float elapsedTime) override;
	virtual void Render() override;
	virtual int GetType() const override { return OBJ_BASE; }
	virtual SGD::Rectangle GetRect() const override;
	virtual void HandleCollision(const iObject* pOther) override;

	virtual void AddRef() final;
	virtual void Release() final;

	SGD::HTexture GetImage() const { return m_hImage; }
	SGD::Point GetPosition() const { return m_ptPosition; }
	SGD::Size GetSize() const {return m_szSize;}

	void SetImage		(SGD::HTexture img)	{ m_hImage = img; }
	void SetPosition	(SGD::Point	pos) 	{ m_ptPosition = pos; }
	void SetSize		(SGD::Size size) 	{ m_szSize = size; }
	void SetRotation	(float rad)			{ m_fRotation = rad; }

protected:
	SGD::HTexture m_hImage = SGD::INVALID_HANDLE;
	SGD::Point m_ptPosition = SGD::Point{ 0, 0 };
	SGD::Size m_szSize = SGD::Size{ 0, 0 };
	float				m_fRotation = 0.0f;

private:
	unsigned int m_unRefCount = 1;
};

