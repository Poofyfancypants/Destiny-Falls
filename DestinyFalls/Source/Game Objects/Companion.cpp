#include "stdafx.h"
#include "Companion.h"
#include "../Game States/CombatState.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"

Companion::Companion()
{
}

Companion::~Companion()
{
}

void Companion::Update(float elapsedTime)
{

	if (m_nHealth <= 0)
		m_nHealth = 0;

	if (m_nHealth > 0)
		Companion1HB.right = Companion1HB.left + m_nHealth;

	if (m_nHealth > 0)
		Companion2HB.right = Companion2HB.left + m_nHealth;

	if (m_nHealth >= 60)
		m_HealthColor = { 255, 0, 255, 0 };
	else if (m_nHealth < 60 && m_nHealth >= 30)
		m_HealthColor = { 255, 255, 255, 0 };
	else if (m_nHealth < 30 && m_nHealth >= 0)
		m_HealthColor = { 255, 255, 0, 0 };

	if (m_bUpdateAnimation)
	{
		m_pAnimator->GetInstance()->GetInstance()->Update(*this->GetTimeStamp(), elapsedTime);
	}
}

void Companion::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };
	pGraphics->DrawTexture(m_hImage, point);

}

void Companion::CombatRender(int _posIndex)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	switch (_posIndex)
	{
	case 1:
		pGraphics->DrawRectangle(Companion1HB, m_HealthColor);
		if (m_pAnimator->GetInstance()->CheckSize())
		{
			m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), Companion1rect.right, Companion1rect.bottom);
		}
		break;
	case 2:
		pGraphics->DrawRectangle(Companion2HB, m_HealthColor);
		if (m_pAnimator->GetInstance()->CheckSize())
		{
			m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), Companion2rect.right, Companion2rect.bottom);
		}
		break;

	default:
		break;
	}
}

bool Companion::TakeTurn(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	CombatState* pCombat = CombatState::GetInstance();

	float posX = 200.0f;

	SGD::Rectangle CompanionSelection{ posX, (float)(420 + 50 * m_nCursor), posX + 40, (float)(430 + 50 * m_nCursor) };

	if (m_nHealth < 0)
	{
		return false;
	}

	switch (GetCoType())
	{
#pragma region cleric
	case Cleric:
	{
				   if (selected == false) //Pick an action (melee magic or armor)
				   {
					   pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));
					   if (false) //cooldown
					   {
						   pGraphics->DrawString("Heal", SGD::Point{ 250, 470 }, SGD::Color(150, 255, 255, 255));
					   }
					   else
					   {
						   pGraphics->DrawString("Heal", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));
					   }
					   //pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
					   pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

					   pCombat->SetAction("Choose Action");
					   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
						   m_nCursor--;

					   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
						   m_nCursor++;

					   if (m_nCursor < 0)
						   m_nCursor = 0;
					   if (m_nCursor > 1)
						   m_nCursor = 1;

						   //First Selection >> Action
					   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					   {
						   //if
						   if (m_nCursor == 0)
						   {
							   ActionSelected = m_nCursor;
							   selected = true;
							   m_nCursor = 0;
						   }

						   if (m_nCursor == 1)
						   {
							   ActionSelected = CombatState::ActionType::Heal;
							   selected = true;
							   m_nCursor = 0;
						   }
					   }

				   }
				   else//Action selected, now pick target
				   {
					   pCombat->SetAction("Choose Target");
					   CompanionSelection = { ((Player*)pCombat->GetHeroes()[m_nCursor])->GetPosition().x, ((Player*)pCombat->GetHeroes()[m_nCursor])->GetPosition().y, ((Player*)pCombat->GetHeroes()[m_nCursor])->GetPosition().x + 40, ((Player*)pCombat->GetHeroes()[m_nCursor])->GetPosition().y + 40 };

					   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
					   {
						   m_nCursor--;
					   }
					   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
					   {
						   m_nCursor++;
					   }

					   if (ActionSelected == CombatState::ActionType::Heal)
					   {

						   if (((Player*)pCombat->GetHeroes()[m_nCursor])->GetHealth() <= 0)
							   m_nCursor++;

						   if (m_nCursor < 0)
							   m_nCursor = 0;
						   if (m_nCursor > pCombat->GetHeroes().size() - 1)
							   m_nCursor = pCombat->GetHeroes().size() - 1;

					   }
					   else
					   {
						   if (m_nCursor < 0)
							   m_nCursor = 0;
						   if (m_nCursor > pCombat->GetEnemies().size() - 1)
							   m_nCursor = pCombat->GetEnemies().size() - 1;

						   if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
							   m_nCursor++;

						   if (m_nCursor < 0)
							   m_nCursor = 0;
						   if (m_nCursor > pCombat->GetEnemies().size() - 1)
							   m_nCursor = pCombat->GetEnemies().size() - 1;

						   CompanionSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x + 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y + 40 };
					   }


						   //Second Selection >> Target
					   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					   {
						   selected = false;
						   SetAttacking(true);
						   pCombat->TakeAction(ActionSelected, this, m_nCursor);
						   m_nCursor = 0;
						   return true;
					   }
					   m_bUpdateAnimation = true;

					   this->GetTimeStamp()->SetCurrentFrame(0);
					   this->GetTimeStamp()->SetTimeOnFrame(0.0f);

					   if (CompanionSelection.left < CompanionSelection.right)
						   pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));
				   }


				   return false;
	}
		break;
#pragma endregion
	case Melee:
	{
				  if (selected == false) //Pick an action (melee magic or armor)
				  {
					  pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));
					  if (false)
					  {
						  pGraphics->DrawString("Fury", SGD::Point{ 250, 470 }, SGD::Color(150, 255, 255, 255)); //AOE attack
					  }
					  else
					  {
						  pGraphics->DrawString("Fury", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));
					  }
					  //pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
					  pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

					  pCombat->SetAction("Choose Action");
					  if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
						  m_nCursor--;

					  if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
						  m_nCursor++;

					  if (m_nCursor < 0)
						  m_nCursor = 0;
					  if (m_nCursor > 1)
						  m_nCursor = 1;

						  //First Selection >> Action
					  if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					  {
						  //if
						  if (m_nCursor == 0)
						  {
							  ActionSelected = m_nCursor;
							  selected = true;
							  m_nCursor = 0;
							  CombatState::GetInstance()->SetCooldown(false);
						  }

						  if (!CombatState::GetInstance()->GetCooldown() && m_nCursor == 1)
						  {
							  ActionSelected = m_nCursor;
							  selected = true;
							  m_nCursor = 0;
						  }
					  }

				  }
				  else //Action selected, now pick target
				  {
					  pCombat->SetAction("Choose Target");
					  if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
					  {
						  m_nCursor--;
					  }
					  if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
					  {
						  m_nCursor++;
					  }
					  if (m_nCursor < 0)
						  m_nCursor = 0;
					  if (m_nCursor > pCombat->GetEnemies().size() - 1)
						  m_nCursor = pCombat->GetEnemies().size() - 1;


						  //Second Selection >> Target
					  if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					  {
						  selected = false;
						  SetAttacking(true);
						  pCombat->TakeAction(ActionSelected, this, m_nCursor);
						  m_nCursor = 0;
						  return true;
					  }
					  m_bUpdateAnimation = true;

					  this->GetTimeStamp()->SetCurrentFrame(0);
					  this->GetTimeStamp()->SetTimeOnFrame(0.0f);
				  }


				  return false;
	}
		break;
	case Mage:
	{
				 pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));
				 if (CombatState::GetInstance()->GetCooldown())
				 {
					 pGraphics->DrawString("Magic", SGD::Point{ 250, 470 }, SGD::Color(150, 255, 255, 255));
				 }
				 else
				 {
					 pGraphics->DrawString("Magic", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));
				 }
				 //pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
				 pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));


				 if (selected == false) //Pick an action (melee magic or armor)
				 {
					 pCombat->SetAction("Choose Action");
					 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
						 m_nCursor--;

					 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
						 m_nCursor++;

					 if (m_nCursor < 0)
						 m_nCursor = 0;
					 if (m_nCursor > 1)
						 m_nCursor = 1;

						 //First Selection >> Action
					 if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					 {
						 //if
						 if (m_nCursor == 0)
						 {
							 ActionSelected = m_nCursor;
							 selected = true;
							 m_nCursor = 0;
							 CombatState::GetInstance()->SetCooldown(false);
						 }

						 if (!CombatState::GetInstance()->GetCooldown() && m_nCursor == 1)
						 {
							 ActionSelected = m_nCursor;
							 selected = true;
							 m_nCursor = 0;
						 }
					 }

				 }
				 else //Action selected, now pick target
				 {
					 pCombat->SetAction("Choose Target");
					 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
					 {
						 m_nCursor--;
					 }
					 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
					 {
						 m_nCursor++;
					 }
					 if (m_nCursor < 0)
						 m_nCursor = 0;
					 if (m_nCursor > pCombat->GetEnemies().size() - 1)
						 m_nCursor = pCombat->GetEnemies().size() - 1;


						 //Second Selection >> Target
					 if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					 {
						 selected = false;
						 SetAttacking(true);
						 pCombat->TakeAction(ActionSelected, this, m_nCursor);
						 m_nCursor = 0;
						 return true;
					 }
					 m_bUpdateAnimation = true;

					 this->GetTimeStamp()->SetCurrentFrame(0);
					 this->GetTimeStamp()->SetTimeOnFrame(0.0f);
				 }


				 return false;
	}
		break;
	case Tank:
	{
				 pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));

				 pGraphics->DrawString("Block", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));

				 //pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
				 pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

				 if (selected == false) //Pick an action (melee magic or armor)
				 {
					 pCombat->SetAction("Choose Action");
					 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
						 m_nCursor--;

					 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
						 m_nCursor++;

					 if (m_nCursor < 0)
						 m_nCursor = 0;
					 if (m_nCursor > 1)
						 m_nCursor = 1;

						 //First Selection >> Action
					 if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					 {
						 //if
						 if (m_nCursor == 0)
						 {
							 ActionSelected = m_nCursor;
							 selected = true;
							 m_nCursor = 0;
							 CombatState::GetInstance()->SetCooldown(false);
						 }

						 if (m_nCursor == 1)
						 {
							 ActionSelected = 2;
							 selected = true;
							 m_nCursor = 0;
						 }
					 }

				 }
				 else //Action selected, now pick target
				 {
					 if (ActionSelected == 2)
					 {
						 m_Block = true;
						 selected = false;
						 pCombat->TakeAction(ActionSelected, this, m_nCursor);
						 m_nCursor = 0;
						 return true;
					 }

					 pCombat->SetAction("Choose Target");
					 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
					 {
						 m_nCursor--;
					 }
					 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
					 {
						 m_nCursor++;
					 }
					 if (m_nCursor < 0)
						 m_nCursor = 0;
					 if (m_nCursor > pCombat->GetEnemies().size() - 1)
						 m_nCursor = pCombat->GetEnemies().size() - 1;


						 //Second Selection >> Target
					 if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 0))
					 {
						 selected = false;
						 SetAttacking(true);
						 pCombat->TakeAction(ActionSelected, this, m_nCursor);
						 m_nCursor = 0;
						 return true;
					 }
					 m_bUpdateAnimation = true;

					 this->GetTimeStamp()->SetCurrentFrame(0);
					 this->GetTimeStamp()->SetTimeOnFrame(0.0f);
				 }


				 return false;
	}
		break;
	default:
		break;
	}


	m_bUpdateAnimation = true;
	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);

	return true;
}

void Companion::SetCompanionAnimation(int companionType)
{
	m_pAnimator = m_pAnimator->GetInstance();

	switch (companionType)
	{
	case 1:
		this->GetTimeStamp()->SetCurrentAnimation("ClericAttack");
		break;
	case 2:
		this->GetTimeStamp()->SetCurrentAnimation("Companion1Attack");
		break;
	case 3:
		this->GetTimeStamp()->SetCurrentAnimation("RangerAttack");
		break;
	case 4:
		this->GetTimeStamp()->SetCurrentAnimation("GladiatorAttack");
		break;
	default:
		break;
	}

	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);

}

void Companion::ResetAnimation()
{
	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);
}