#include "stdafx.h"
#include "GameplayState.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../Messages/MessageID.h"


GameplayState* GameplayState::GetInstance()
{
	static GameplayState s_Instance;
	return &s_Instance;
}

void GameplayState::Enter()
{

}

void GameplayState::Exit()
{

}

bool GameplayState::Input()
{
	return true;
}

void GameplayState::Update(float elapsedTime)
{

}

void GameplayState::Render()
{

}

/*static*/ void GameplayState::MessageProc(const SGD::Message* pMsg)
{
	switch (pMsg->GetMessageID())
	{
	
	default:
	{
			   OutputDebugStringW(L"GameplayState::MessageProc - unknown message id\n");
	}
		break;
	}

}
