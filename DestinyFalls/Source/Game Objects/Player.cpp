#include "stdafx.h"
#include "Player.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
#include "../Game States/PauseMenuState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"
#include "Chest.h"
#include "../Game States/GameplayState.h"
#include "../Bitmap Font/BitmapFont.h"
#include "../Quick Time/QuickTime.h"

Player::Player() : Listener(this)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	m_pAnimator = m_pAnimator->GetInstance();
	this->GetTimeStamp()->SetCurrentAnimation( "WalkingDown" );
	this->GetTimeStamp()->SetCurrentFrame( 0 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
}

Player::~Player()
{
	
}

void Player::Update(float elapsedTime)
{
	if (m_nHealth <= 0)
	{
		m_nHealth = 0;
		Game::GetInstance()->AddState(PauseMenuState::GetInstance());


		//m_ptPosition = GetCheckpoint();
		//m_nHealth = 100;
	}
	if (!m_bSliding)
		m_nDirection = 0;


	TakeInput();


	float speed = 500 * elapsedTime;

	switch (m_nDirection)
	{
	case 1:
		velocity = SGD::Vector(0, -speed);
		break;
	case 2:
		velocity = SGD::Vector(0, speed);
		break;
	case 3:
		velocity = SGD::Vector(-speed, 0);
		break;
	case 4:
		velocity = SGD::Vector(speed, 0);
		break;
	default:
		velocity = SGD::Vector();
		break;
	}

	SGD::Point futurePos = m_ptPosition + velocity;
	if (!GameplayState::GetInstance()->GetMap()->TileCollision(this, futurePos))
	{
		m_ptPosition = futurePos;

		if (m_bSliding && m_nDirection != 0)
			m_bMoving = true;
	}
	else if (m_bSliding)
	{
		m_bMoving = false;
	}

	m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp() , elapsedTime );


}

void Player::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	//SGD::Point point = { vec.x - ( m_szSize.width / 2 + GameplayState::GetInstance()->GetWorldCam().x ), vec.y - ( m_szSize.height / 2 + GameplayState::GetInstance()->GetWorldCam().y ) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };

	SGD::Rectangle rec = GetRect();
	rec.Offset(-GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y);

	//pGraphics->DrawRectangle( rec, SGD::Color( 0, 0, 255 ) );

	//pGraphics->DrawTextureSection(m_hImage, point, SGD::Rectangle{ 0, 0, 100, 100 });
	
	SGD::Point currentHealthHUD = { (Game::GetInstance()->GetScreenWidth() * 1 / 5) - 75, (Game::GetInstance()->GetScreenHeight() * 6 / 8) };
	
	currentHealthHUD = { (Game::GetInstance()->GetScreenWidth() * 1 / 5) - 75, (Game::GetInstance()->GetScreenHeight() * 11 / 13) };
	pGraphics->DrawLine(currentHealthHUD, SGD::Point{ currentHealthHUD.x + this->GetMaxHealth(), currentHealthHUD.y }, { 255, 0, 0 }, 17U);
	
	currentHealthHUD = { (Game::GetInstance()->GetScreenWidth() * 1 / 5) - 75, (Game::GetInstance()->GetScreenHeight() * 11 / 13) };
	pGraphics->DrawLine(currentHealthHUD, SGD::Point{ currentHealthHUD.x + this->GetHealth(), currentHealthHUD.y }, { 0, 255, 0 }, 17U);

	std::string potString = std::to_string(m_nPotions);
	potString += " P";
	pGraphics->DrawString(potString.c_str(), { (Game::GetInstance()->GetScreenWidth() - 100), (Game::GetInstance()->GetScreenHeight() - 100) }, SGD::Color(255, 255, 0, 0));

	if( m_pAnimator->GetInstance()->CheckSize() )
	{
		//AnimationTimeStamp ts = *this->GetTimeStamp();
		m_pAnimator->GetInstance()->Render( *this->GetTimeStamp() , point.x + ( m_szSize.width / 2 ) , point.y + ( m_szSize.height / 2 ) );
	}
}

void Player::TakeInput()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (m_bMoving)
	{
		return;
	}
	if (pInput->IsKeyDown(SGD::Key::Up) || pInput->IsKeyDown(SGD::Key::W))
	{
		m_nDirection = 1;

		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingUp" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingUp" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
		
		
		
	}
	if (pInput->IsKeyDown(SGD::Key::Down) || pInput->IsKeyDown(SGD::Key::S))
	{
		m_nDirection = 2;
		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingDown" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingDown" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}

	if (pInput->IsKeyDown(SGD::Key::Left) || pInput->IsKeyDown(SGD::Key::A))
	{
		m_nDirection = 3;

		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingLeft" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingLeft" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}
	if (pInput->IsKeyDown(SGD::Key::Right) || pInput->IsKeyDown(SGD::Key::D))
	{
		m_nDirection = 4;
		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingRight" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingRight" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}

	if (pInput->IsKeyPressed(SGD::Key::P) && m_nPotions > 0 && m_nHealth < 100)
	{
		m_nHealth += 30;
		if (m_nHealth > 100)
		{
			m_nCursor = 100;
		}
		m_nPotions--;
	}

}

SGD::Rectangle Player::GetRect(void) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}

void Player::HandleCollision(const iObject* pOther)
{
	if (pOther->GetType() == OBJ_ENEMY)
	{
		Game::GetInstance()->AddState(CombatState::GetInstance());
	}
	if (pOther->GetType() == OBJ_CHEST)
	{
		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Q))
		{
			if (((Chest*)pOther)->IsTrapped())
			{
				Game::GetInstance()->AddState(CombatState::GetInstance());
			}
			m_nPotions += ((Chest*)pOther)->GetNumPots();
			((Chest*)pOther)->RemoveItems();
		}
	}
}


bool Player::TakeTurn(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	CombatState* pCombat = CombatState::GetInstance();

	float posX = 200.0f;
	if (selected)
	{
		posX = 400.0f;
	}

	SGD::Rectangle PlayerSelection{ posX, (float)(420 + 50 * m_nCursor), posX + 40, (float)(430 + 50 * m_nCursor) };


	if (m_nHealth < 0)
	{
		return false;
	}

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
	pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

	if (selected == false) //Pick an action (melee magic or armor)
	{

		if (pInput->IsKeyPressed(SGD::Key::Up))
		{
			m_nCursor++;
		}
		if (pInput->IsKeyPressed(SGD::Key::Down))
		{
			m_nCursor--;
		}
		if (m_nCursor < 0)
			m_nCursor = 0;
		if (m_nCursor > 1)
			m_nCursor = 1;

		if (pInput->IsKeyPressed(SGD::Key::Enter)) //First Selection >> Action
		{
			if (m_nCursor == 0)
			{
				ActionSelected = m_nCursor;
				selected = true;
				m_nCursor = 0;
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
		if (pInput->IsKeyPressed(SGD::Key::Up))
		{
			m_nCursor++;
		}
		if (pInput->IsKeyPressed(SGD::Key::Down))
		{
			m_nCursor--;
		}
		if (m_nCursor < 0)
			m_nCursor = 0;
		if (m_nCursor > pCombat->GetNumEnemies() - 1)
			m_nCursor = pCombat->GetNumEnemies() - 1;

		int target;

		if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
		{
			target = m_nCursor + 1;
			selected = false;
			pCombat->DealDamage(ActionSelected, this, target);
			return true;
		}

	}


	return false;
}