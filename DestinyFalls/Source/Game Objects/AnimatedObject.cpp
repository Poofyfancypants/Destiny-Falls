#include "stdafx.h"
#include "AnimatedObject.h"


AnimatedObject::AnimatedObject()
{
	m_pTS = new AnimationTimeStamp;
}


AnimatedObject::~AnimatedObject()
{
	delete m_pTS;
}
