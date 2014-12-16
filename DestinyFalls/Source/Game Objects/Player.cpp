#include "stdafx.h"
#include "Player.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"
#include "../Game States/CombatState.h"
#include "../Game States/PauseMenuState.h"
#include "../Game States/InventoryState.h"
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
	m_hDialogImg = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/PlayerIcon.jpg" );
	m_hDialogImg2 = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/TestCompanionPortrait.png" );
}
Player::~Player()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hPortrait );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hDialogImg );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hDialogImg2 );

}

void Player::Update( float elapsedTime )
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	if( m_nHealth <= 0 && m_fDeathAnimationTimer > 0.0f)
	{
		if( this->GetTimeStamp()->GetCurrentAnimation() != "DeathAnimation" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "DeathAnimation" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
		else
		{
			m_fDeathAnimationTimer -= elapsedTime;

			if( m_fDeathAnimationTimer < 0.0f )
			{
				m_fDeathAnimationTimer = 0.0f;
			}

			m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp() , elapsedTime );
		}
		return;
	}
	if( m_bPlayCombatAnimation )
	{
		m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp(), elapsedTime );
		// - Why is this here!??
		if( m_nHealth <= 0 )
		{
			pAudio->PlayAudio( Game::GetInstance()->deathSound, false );
			m_nHealth = 0;
			Game::GetInstance()->AddState( DeathState::GetInstance() );

			
			m_nHealth = 100;
		}
	}
	else
	{
		if( m_nHealth <= 0 )
		{
			pAudio->PlayAudio( Game::GetInstance()->deathSound, false );
			m_nHealth = 0;
			m_bSliding = false;
			Game::GetInstance()->AddState( DeathState::GetInstance() );

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

		if( m_bPreventDialog )
		{
			PreventDialogFromRestarting( elapsedTime );
		}
	}

	// - Scrolling Damage

	//// - Distance for the text to travel.
	//float dp = 500;

	//// - Starting position
	//if( !m_PrintDMG )
	//	p1 = m_ptPosition.y;
	//p2 = p1 + dp;
	//v1 = ( p2 - p1 ) * elapsedTime;
	//if( p1 > p2 )
	//	m_PrintDMG = false;
	//else
	//	p1 -= v1;

	if( m_PrintDMG )
	{
		m_fSecond += elapsedTime;
		if( m_fSecond >= .05f )
		{
			m_fScroll += 1.0f;
			m_fSecond = 0;
		}
	}
	if( m_fScroll > 10.0f )
	{
		m_fScroll = 0.0f;
		m_PrintDMG = false;
		m_nHealth -= m_ptTrapDmg;
		GameplayState::GetInstance()->SetScreenShake();
	}



}

void Player::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	if( m_bPlayCombatAnimation )
	{
		m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), (int)playerRect.right, (int)playerRect.bottom);
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

		if( m_pAnimator->GetInstance()->CheckSize() )
		{
			m_pAnimator->GetInstance()->Render( *this->GetTimeStamp(), (int)( point.x + ( m_szSize.width / 2.0f ) ), (int)( point.y + ( m_szSize.height / 2.0f ) ) );
		}
		// Low Health warning!

		if( m_PrintDMG )
		{
			BitmapFontManager::GetInstance()->Render( "Other",
				to_string( m_ptTrapDmg ).c_str(),
				SGD::Point( point.x, ( point.y - 30 ) - 5 * m_fScroll ),
				1, SGD::Color( 255, 0, 0 ) );
		}

		if( m_bLowHealthWarning )
			pGraphics->DrawRectangle( SGD::Rectangle( 0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() ), { 100, 255, 0, 0 } );

		if( m_bRunDialog && !m_bPreventDialog )
		{
			RenderDialog();
		}
	}
}

void Player::TakeInput()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	if( currentQT != nullptr )
	{
		currentQT->m_kLastKeyPressed = pInput->GetAnyKeyPressed();
	}
	if( m_bMoving )
	{
		m_bUpdateAnimation = false;
		return;
	}
	if (pInput->IsKeyDown(SGD::Key::Up) || pInput->IsKeyDown(SGD::Key::W) || pInput->IsDPadDown(0, SGD::DPad::Up))
	{
		m_nDirection = 1;

		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingUp" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingUp" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}

	}
	if (pInput->IsKeyDown(SGD::Key::Down) || pInput->IsKeyDown(SGD::Key::S) || pInput->IsDPadDown(0, SGD::DPad::Down))
	{
		m_nDirection = 2;
		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingDown" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingDown" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}

	if (pInput->IsKeyDown(SGD::Key::Left) || pInput->IsKeyDown(SGD::Key::A) || pInput->IsDPadDown(0, SGD::DPad::Left))
	{
		m_nDirection = 3;

		if( this->GetTimeStamp()->GetCurrentAnimation() != "WalkingLeft" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "WalkingLeft" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
	}
	if (pInput->IsKeyDown(SGD::Key::Right) || pInput->IsKeyDown(SGD::Key::D) || pInput->IsDPadDown(0, SGD::DPad::Right))
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

	if( m_bRunDialog && !m_bPreventDialog )
	{
		if( pInput->IsAnyKeyPressed() )
		{
			UpdateDialog();
		}
	}
}

SGD::Rectangle Player::GetRect( void ) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, ( m_ptPosition.x + m_szSize.width ), ( m_ptPosition.y + m_szSize.height ) };
	return sourceRect;
}



void Player::HandleCollision( const iObject* pOther )
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	SGD::InputManager * pInput = SGD::InputManager::GetInstance();
	if( pOther->GetType() == OBJ_ENEMY )
	{
		if( !m_bCombat )
		{
			CombatEnemyID = ( (Enemy*)pOther )->GetEnemyType();
			pAudio->StopAudio( GameplayState::GetInstance()->bmusic );
			Game::GetInstance()->AddState( CombatState::GetInstance() );
		}

	}
	if( pOther->GetType() == OBJ_CHEST )
	{
		if (pInput->IsKeyPressed(SGD::Key::Q) || pInput->IsButtonDown(0, 4))
		{
			if( ( (Chest*)pOther )->IsTrapped() )
			{
				CombatEnemyID = 1;
				Game::GetInstance()->AddState( CombatState::GetInstance() );
				m_bCombat = true;
				( (Chest*)pOther )->SetTrapped();
			}
			switch( ( (Chest*)pOther )->GetTier() )
			{
			case 1:
				for( int i = 0; i < ( (Chest*)pOther )->GetNumRunes(); i++ )
				{
					Runes tempRune;
					tempRune.SetElement( (Elements)( rand() % 4 ) );
					tempRune.SetTier( 1 );
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld( tempRune );
				}
				break;
			case 2:
				for( int i = 0; i < ( (Chest*)pOther )->GetNumRunes(); i++ )
				{
					Runes tempRune;
					tempRune.SetElement( (Elements)( rand() % 4 ) );
					tempRune.SetTier( 2 );
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld( tempRune );
				}
				break;
			case 3:
				for( int i = 0; i < ( (Chest*)pOther )->GetNumRunes(); i++ )
				{
					Runes tempRune;
					tempRune.SetElement( (Elements)( rand() % 4 ) );
					tempRune.SetTier( 3 );
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld( tempRune );
				}
				break;
			default:
				break;
			}
			m_nPotions += ( (Chest*)pOther )->GetNumPots();
			( (Chest*)pOther )->RemoveItems();
		}
	}
	if( pOther->GetType() == OBJ_TRAP )
	{
		BitmapFontManager* pFont = BitmapFontManager::GetInstance();

		const Trap* trap = dynamic_cast<const Trap*>( pOther );

		m_ptTrapDmg = trap->GetDamage();
		m_PrintDMG = true;

		//RunQuickTime( 3 );
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
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Point heroPosition;
	SGD::Point portraitPosition;
	// - Location of the Dialog Box at the bottom of the screen.
	SGD::Rectangle DialogBoxOne;
	DialogBoxOne.left = 25;
	DialogBoxOne.top = Game::GetInstance()->GetScreenHeight() - 125;
	DialogBoxOne.right = Game::GetInstance()->GetScreenWidth() - 25;
	DialogBoxOne.bottom = Game::GetInstance()->GetScreenHeight() - 25;

	// - Location to print the strings within the dialog Box
	SGD::Point TextPositionOne;
	SGD::Point TextPositionTwo;

	TextPositionOne.x = DialogBoxOne.left + 40;
	TextPositionOne.y = DialogBoxOne.top + 20;
	TextPositionTwo.x = DialogBoxOne.left + 20;
	TextPositionTwo.y = DialogBoxOne.top + 50;

	portraitPosition.x = DialogBoxOne.left - 10;
	portraitPosition.y = DialogBoxOne.top - 30;

	pGraphics->DrawRectangle( DialogBoxOne, SGD::Color( 220, 215, 143 ), SGD::Color( 0, 0, 0 ) );

	DialogManager* pDialog = pDialog->GetInstance();
	switch( m_nLineCounter )
	{
	case 1:
		pDialog->Render( "Dialog", "Greeting", TextPositionOne, 1, SGD::Color( 0, 0, 0 ) );
		pGraphics->DrawTexture( m_hDialogImg2, portraitPosition );
		break;
	case 2:
		pDialog->Render( "Dialog", "GreetingsResponse", TextPositionOne, 1, SGD::Color( 0, 0, 0 ) );
		pGraphics->DrawTexture( m_hDialogImg, portraitPosition, {}, {}, {}, { .3f, .3f } );
		break;
	case 3:
		pDialog->Render( "Dialog", "HowFares", TextPositionOne, 1, SGD::Color( 0, 0, 0 ) );
		pGraphics->DrawTexture( m_hDialogImg2, portraitPosition );
		break;
	case 4:
		pDialog->Render( "Dialog", "HowFaresResponse", TextPositionOne, 1, SGD::Color( 0, 0, 0 ) );
		pGraphics->DrawTexture( m_hDialogImg, portraitPosition, {}, {}, {}, { .3f, .3f } );
		break;
	case 5:
		pDialog->Render( "Dialog", "RequestToJoin", TextPositionOne, 1, SGD::Color( 0, 0, 0 ) );
		pGraphics->DrawTexture( m_hDialogImg2, portraitPosition );
		break;
	case 6:
		pDialog->Render( "Dialog", "Agree", TextPositionOne, 1, SGD::Color( 0, 0, 0 ) );
		pGraphics->DrawTexture( m_hDialogImg, portraitPosition, {}, {}, {}, { .3f, .3f } );
		break;
	default:
		break;
	}
}

void Player::UpdateDialog()
{
	if( m_nLineCounter < 6 )
	{
		m_nLineCounter++;
	}
	else
	{
		m_bRunDialog = false;
		m_bPreventDialog = true;
		m_nLineCounter = 1;
	}
}

void Player::PreventDialogFromRestarting( float elapsedTime )
{
	m_fDialogTimer -= elapsedTime;

	if( m_fDialogTimer <= 0.0f )
	{
		m_bPreventDialog = false;
		m_bRunDialog = false;
	}

}