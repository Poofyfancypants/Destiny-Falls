#include "stdafx.h"
#include "CreditState.h"

CreditState* CreditState::GetInstance()
{
	static CreditState* s_Instance;
	return s_Instance;
}

void CreditState::Enter()
{

}

void CreditState::Exit()
{

}

bool CreditState::Input()
{
	return true;
}

void CreditState::Update(float elapsedTime)
{

}

void CreditState::Render()
{

}