#include "stdafx.h"
#include "Animation.h"



//AddFrame adds frames to the m_vFrames vector
void Animation::AddFrame( Frame newFrame )
{
	m_vFrames.push_back( newFrame );
}