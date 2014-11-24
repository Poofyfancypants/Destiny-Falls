#pragma once
#include "Object.h"
#include "../Engines/AnimationTimeStamp.h"
class AnimatedObject :
	public Object
{
	AnimationTimeStamp *m_pTS = nullptr;

public:
	AnimatedObject();
	~AnimatedObject();

	AnimationTimeStamp* GetTimeStamp() { return m_pTS; }
	void SetTimeStamp( AnimationTimeStamp *ts ){ m_pTS = ts; }
};

