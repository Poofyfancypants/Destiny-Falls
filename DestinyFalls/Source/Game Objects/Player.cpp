#include "stdafx.h"
#include "Player.h"
#include "../../SGD Wrappers/SGD_Event.h"


Player::Player() : Listener(this)
{
}


Player::~Player()
{
}

/*virtual*/ void Player::HandleEvent(const SGD::Event* pEvent) /*override*/
{

}