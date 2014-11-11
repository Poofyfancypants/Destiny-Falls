#pragma once
#include "../../SGD Wrappers/SGD_Declarations.h"

class iObject
{

protected:

	iObject() = default;
	virtual ~iObject() = default;

public:
	enum ObjectType { OBJ_BASE, OBJ_PLAYER, };

	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual int GetType() const = 0;
	virtual SGD::Rectangle GetRect() const = 0;
	virtual void HandleCollision(const iObject* pOther)	= 0;

	virtual void AddRef() = 0;
	virtual void Release() = 0;
};

