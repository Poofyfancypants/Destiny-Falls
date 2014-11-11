#include "stdafx.h"
#include "Frame.h"


//push a new collision rect back into the collisionRects vector
void Frame::AddCollisionRect( SGD::Rectangle collisionRect )
{
	m_vCollisionRects.push_back( collisionRect );
}