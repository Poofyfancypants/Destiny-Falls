#include "stdafx.h"
#include "Player.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"
#include "../Game States/CombatState.h"
#include "../Game States/PauseMenuState.h"
#include "../Game States/DeathState.h"
#include "../Game States/GameplayState.h"
#include "../Game States/MainMenuState.h"
#include "../Managers/ParticleManager.h"
#include "../Bitmap Font/BitmapFont.h"
#include "../Managers/TileManager.h"
#include "../Game Core/Game.h"
#include "Chest.h"
#include "../Managers/DialogManager.h"
//#include "../Quick Time/QuickTime.h"

#include "../Game Objects/Trap.h"


Player::Player() : Listener( this )
{

	m_pAnimator = m_pAnimator->GetInstance();
	this->GetTimeStamp()->SetCurrentAnimation( "WalkingDown" );
	this->GetTimeStamp()->SetCurrentFrame( 0 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
	m_hPortrait = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/PlayerIcon.jpg" );

}
Player::~Player()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hPortrait );

}

void Player::Update( float elapsedTime )
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	if( m_bPlayCombatAnimation )
	{
		m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp(), elapsedTime );
		if( m_nHealth <= 0 )
		{
			pAudio->PlayAudio( Game::GetInstance()->deathSound, false );
			m_nHealth = 0;
			Game::GetInstance()->AddState( DeathState::GetInstance() );

			m_ptPosition = GetCheckpoint();
			m_nHealth = 100;
		}
	}
	else
	{
		if( m_nHealth <= 0 )
		{
			pAudio->PlayAudio( Game::GetInstance()->deathSound, false );
			m_nHealth = 0;
			Game::GetInstance()->AddState( PauseMenuState::GetInstance() );

			m_ptPosition = GetCheckpoint();
			//m_nHealth = 100;
		}
		if( !m_bSliding )
			m_nDirection = 0;

		TakeInput();
		float speed;
		if( m_bSliding )
			speed = 500 * elapsedTime;
		else
			speed = 250 * elapsedTime;

		switch( m_nDirection )
		{
		case 1:
			velocity = SGD::Vector( 0, -speed );
			break;
		case 2:
			velocity = SGD::Vector( 0, speed );
			break;
		case 3:
			velocity = SGD::Vector( -speed, 0 );
			break;
		case 4:
			velocity = SGD::Vector( speed, 0 );
			break;
		default:
			velocity = SGD::Vector();
			break;
		}

		SGD::Point futurePos = m_ptPosition + velocity;
		if( !GameplayState::GetInstance()->GetMap()->TileCollision( this, futurePos ) && !m_bCollision )
		{
			m_ptPosition = futurePos;

			if( m_bSliding && m_nDirection != 0 )
				m_bMoving = true;
		}
		else if( m_bSliding )
		{
			m_bMoving = false;
			m_nDirection = 0;
		}

		m_bCollision = false;
		if( m_bUpdateAnimation )
		{
			m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp(), elapsedTime );

		}

		// Sub 25% health indicator

		m_fHealthFlash += elapsedTime;
		if( m_fHealthFlash > 2 && this->GetHealth() < 25 )
		{
			m_bLowHealthWarning = true;
			m_fHealthFlash = 0;
		}
		else
			m_bLowHealthWarning = false;
	}


}

void Player::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	if( m_bPlayCombatAnimation )
	{
		m_pAnimator->GetInstance()->Render( *this->GetTimeStamp(), 289, 264 );
	}
	else
	{
		SGD::Vector vec = { ( m_ptPosition.x ), ( m_ptPosition.y ) };
		SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };
		if( GameplayState::GetInstance()->GetDebugState() )
		{
			SGD::Rectangle rec = GetRect();
			rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
			pGraphics->DrawRectangle( rec, SGD::Color( 0, 0, 255 ) );
		}


		SGD::Point currentHealthHUD = { 0, 0 };
		// Red Health Bar
		currentHealthHUD = { ( Game::GetInstance()->GetScreenWidth() * 1 / 5 ) - 75, ( Game::GetInstance()->GetScreenHeight() / 10 ) };
		pGraphics->DrawLine( currentHealthHUD, SGD::Point{ currentHealthHUD.x + this->GetMaxHealth(), currentHealthHUD.y }, { 255, 0, 0 }, 17U );
		// Green Health Bar
		currentHealthHUD = { ( Game::GetInstance()->GetScreenWidth() * 1 / 5 ) - 75, ( Game::GetInstance()->GetScreenHeight() / 10 ) };
		pGraphics->DrawLine( currentHealthHUD, SGD::Point{ currentHealthHUD.x + this->GetHealth(), currentHealthHUD.y }, { 0, 255, 0 }, 17U );
		pGraphics->DrawTexture( m_hPortrait, SGD::Point( currentHealthHUD.x - 70, currentHealthHUD.y - 30 ), {}, {}, {}, { .5f, .5f } );

		std::string potString = std::to_string( m_nPotions );
		potString += " Potions";
		pGraphics->DrawString( potString.c_str(), { ( Game::GetInstance()->GetScreenWidth() - 100 ), ( Game::GetInstance()->GetScreenHeight() - 80 ) }, SGD::Color( 255, 255, 0, 0 ) );

		if( m_pAnimator->GetInstance()->CheckSize() )
		{
			m_pAnimator->GetInstance()->Render( *this->GetTimeStamp(), (int)( point.x + ( m_szSize.width / 2.0f ) ), (int)( point.y + ( m_szSize.height / 2.0f ) ) );
		}
		// Low Health warning!

		if( m_bLowHealthWarning )
			pGraphics->DrawRectangle( SGD::Rectangle( 0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() ), { 100, 255, 0, 0 } );

	}
}

void Player::TakeInput()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	if( m_bMoving )
	{
		m_bUpdateAnimation = false;
		return;
	}
	if( pInput->IsKeyDown( SGD::Key::Up ) || pInput->IsKeyDown( SGD::Key::W ) )
	{
		m_nDirection = 1;

		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingUp" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingUp" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}

	}
	if( pInput->IsKeyDown( SGD::Key::Down ) || pInput->IsKeyDown( SGD::Key::S ) )
	{
		m_nDirection = 2;
		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingDown" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingDown" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}

	if( pInput->IsKeyDown( SGD::Key::Left ) || pInput->IsKeyDown( SGD::Key::A ) )
	{
		m_nDirection = 3;

		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingLeft" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingLeft" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}
	if( pInput->IsKeyDown( SGD::Key::Right ) || pInput->IsKeyDown( SGD::Key::D ) )
	{
		m_nDirection = 4;
		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingRight" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingRight" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}

	if( pInput->IsKeyPressed( SGD::Key::P ) && m_nPotions > 0 && m_nHealth < 100 )
	{
		m_nHealth += 30;
		pAudio->PlayAudio( Game::GetInstance()->potionSound, false );
		if( m_nHealth > 100 )
		{
			m_nHealth = 100;
		}
		m_nPotions--;
	}
	if( pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
	{
		if( pInput->GetCursorPosition().IsPointInRectangle( GameplayState::GetInstance()->HealthPotionPosition ) )
		{
			m_nHealth += 30;
			pAudio->PlayAudio( Game::GetInstance()->potionSound, false );
			if( m_nHealth > 100 )
			{
				m_nHealth = 100;
			}
			m_nPotions--;
		}
	}

	m_bUpdateAnimation = pInput->IsAnyKeyDown();


}

SGD::Rectangle Player::GetRect( void ) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, ( m_ptPosition.x + m_szSize.width ), ( m_ptPosition.y + m_szSize.height ) };
	return sourceRect;
}

void Player::HandleCollision( const iObject* pOther )
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	if( pOther->GetType() == OBJ_ENEMY )
	{
		if( !m_bCombat )
		{
			pAudio->StopAudio( GameplayState::GetInstance()->bmusic );
			Game::GetInstance()->AddState( CombatState::GetInstance() );
		}

	}
	if( pOther->GetType() == OBJ_CHEST )
	{
		if( SGD::InputManager::GetInstance()->IsKeyPressed( SGD::Key::Q ) )
		{
			if( ( (Chest*)pOther )->IsTrapped() )
			{
				Game::GetInstance()->AddState( CombatState::GetInstance() );
				m_bCombat = true;
				( (Chest*)pOther )->SetTrapped();
			}
			m_nPotions += ( (Chest*)pOther )->GetNumPots();
			( (Chest*)pOther )->RemoveItems();
		}
	}
	if( pOther->GetType() == OBJ_TRAP )
	{
		const Trap* trap = dynamic_cast<const Trap*>( pOther );

		m_nHealth -= trap->GetDamage();
	}
	if( pOther->GetType() == OBJ_BOULDER )
	{
		switch( m_nDirection )
		{
		case 1: // - Up
			m_ptPosition.y = pOther->GetRect().bottom + 3;
			break;
		case 2: // - Down
			m_ptPosition.y = pOther->GetRect().top - m_szSize.height - 3;
			break;
		case 3: // - Left
			m_ptPosition.x = pOther->GetRect().right + 3;
			break;
		case 4: // - Right
			m_ptPosition.x = pOther->GetRect().left - m_szSize.width - 3;
			break;
		default:
			velocity = SGD::Vector();
			break;
		}
		//	m_ptPosition -= velocity;
		m_bCollision = true;
	}
	
	if( pOther->GetType() == OBJ_COMPANION )
	{
		m_bRunDialog = true;
	}
}


bool Player::TakeTurn( float elapsedTime )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	CombatState* pCombat = CombatState::GetInstance();

	float posX = 200.0f;
	if( selected )
	{
		posX = 400.0f;
	}

	SGD::Rectangle PlayerSelection{ posX, (float)( 420 + 50 * m_nCursor ), posX + 40, (float)( 430 + 50 * m_nCursor ) };

	if( m_nHealth < 0 )
	{
		return false;
	}


	pGraphics->DrawString( "Melee", SGD::Point{ 250, 420 }, SGD::Color( 255, 255, 255, 255 ) );
	if( CombatState::GetInstance()->GetCooldown() )
	{
		pGraphics->DrawString( "Magic", SGD::Point{ 250, 470 }, SGD::Color( 150, 255, 255, 255 ) );
	}
	else
	{
		pGraphics->DrawString( "Magic", SGD::Point{ 250, 470 }, SGD::Color( 255, 255, 255, 255 ) );
	}
	//pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
	pGraphics->DrawRectangle( PlayerSelection, SGD::Color( 255, 0, 255, 0 ), SGD::Color( 255, 0, 255, 0 ) );


	if( selected == false ) //Pick an action (melee magic or armor)
	{
		pCombat->SetAction( "Choose Action" );
		if( pInput->IsKeyPressed( SGD::Key::Up ) || pInput->IsKeyPressed( SGD::Key::W ) )
			m_nCursor--;

		if( pInput->IsKeyPressed( SGD::Key::Down ) || pInput->IsKeyPressed( SGD::Key::S ) )
			m_nCursor++;

		if( m_nCursor < 0 )
			m_nCursor = 0;
		if( m_nCursor > 1 )
			m_nCursor = 1;

		if( pInput->IsKeyPressed( SGD::Key::Enter ) ) //First Selection >> Action
		{
			//if
			if( m_nCursor == 0 )
			{
				ActionSelected = m_nCursor;
				selected = true;
				m_nCursor = 0;
				CombatState::GetInstance()->SetCooldown( false );
			}

			if( !CombatState::GetInstance()->GetCooldown() && m_nCursor == 1 )
			{
				ActionSelected = m_nCursor;
				selected = true;
				m_nCursor = 0;
			}
		}

	}
	else //Action selected, now pick target
	{
		pCombat->SetAction( "Choose Target" );
		if( pInput->IsKeyPressed( SGD::Key::Up ) || pInput->IsKeyPressed( SGD::Key::W ) )
		{
			m_nCursor--;
		}
		if( pInput->IsKeyPressed( SGD::Key::Down ) || pInput->IsKeyPressed( SGD::Key::S ) )
		{
			m_nCursor++;
		}
		if( m_nCursor < 0 )
			m_nCursor = 0;
		if( m_nCursor > pCombat->GetEnemies().size() - 1 )
			m_nCursor = pCombat->GetEnemies().size() - 1;


		if( pInput->IsKeyPressed( SGD::Key::Enter ) ) //Second Selection >> Target
		{
			selected = false;
			SetAttacking( true );
			pCombat->TakeAction( ActionSelected, this, m_nCursor );
			m_nCursor = 0;
			return true;
		}
		this->GetTimeStamp()->SetCurrentFrame( 0 );
		this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
	}


	return false;
}

void Player::RunQuickTime( int length )
{
	m_bDoQt = true;
	if( currentQT == nullptr )
	{
		currentQT = new QuickTime;
		currentQT->SetLength( length );
	}
}
void Player::StopQuickTime()
{
	m_bDoQt = false;
	delete currentQT;
	currentQT = nullptr;
}

void Player::StartCombat()
{
	m_bPlayCombatAnimation = true;

	m_szLastAnimation = this->GetTimeStamp()->GetCurrentAnimation();
	this->GetTimeStamp()->SetCurrentAnimation( "HeroSwordSwing" );
	this->GetTimeStamp()->SetCurrentFrame( 4 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
}

void Player::StopCombat()
{
	m_bPlayCombatAnimation = false;
	this->GetTimeStamp()->SetCurrentAnimation( m_szLastAnimation );
	this->GetTimeStamp()->SetCurrentFrame( 0 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
}
void Player::ResetAnimation()
{
	this->GetTimeStamp()->SetCurrentFrame( 0 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
}

void Player::RenderDialog()
{
	DialogManager* pDialog = pDialog->GetInstance();
	switch( m_nLineCounter )
	{
		case 1:
			break;
		case 2:
			//pDialog->Render("")
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
	}
}

void Player::UpdateDialog( float elapsedTime )
{

}