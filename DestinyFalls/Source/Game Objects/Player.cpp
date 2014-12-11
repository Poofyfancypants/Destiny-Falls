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


Player::Player() : Listener(this)
{

	m_pAnimator = m_pAnimator->GetInstance();
	this->GetTimeStamp()->SetCurrentAnimation("WalkingDown");
	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);
	m_hPortrait = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/PlayerIcon.jpg");
	m_hDialogImg = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/PlayerIcon.jpg");
	m_hDialogImg2 = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/TestCompanionPortrait.png");
}
Player::~Player()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hPortrait);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hDialogImg);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hDialogImg2);

}

void Player::Update(float elapsedTime)
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	if (m_bPlayCombatAnimation)
	{
		m_pAnimator->GetInstance()->GetInstance()->Update(*this->GetTimeStamp(), elapsedTime);
		// - Why is this here!??
		if (m_nHealth <= 0)
		{
			pAudio->PlayAudio(Game::GetInstance()->deathSound, false);
			m_nHealth = 0;
			Game::GetInstance()->AddState(DeathState::GetInstance());

			m_ptPosition = GetCheckpoint();
			m_nHealth = 100;
		}
	}
	else
	{
		if (m_nHealth <= 0)
		{
			pAudio->PlayAudio(Game::GetInstance()->deathSound, false);
			m_nHealth = 0;
			Game::GetInstance()->AddState(DeathState::GetInstance());
			m_bSliding = false;

			m_ptPosition = GetCheckpoint();
			//m_nHealth = 100;
		}
		if (!m_bSliding)
			m_nDirection = 0;

		TakeInput();
		float speed;
		if (m_bSliding)
			speed = 500 * elapsedTime;
		else
			speed = 250 * elapsedTime;

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
		if (!GameplayState::GetInstance()->GetMap()->TileCollision(this, futurePos) && !m_bCollision)
		{
			m_ptPosition = futurePos;

			if (m_bSliding && m_nDirection != 0)
				m_bMoving = true;
		}
		else if (m_bSliding)
		{
			m_bMoving = false;
			m_nDirection = 0;
		}

		m_bCollision = false;
		if (m_bUpdateAnimation)
		{
			m_pAnimator->GetInstance()->GetInstance()->Update(*this->GetTimeStamp(), elapsedTime);

		}

		// Sub 25% health indicator

		m_fHealthFlash += elapsedTime;
		if (m_fHealthFlash > 2 && this->GetHealth() < 25)
		{
			m_bLowHealthWarning = true;
			m_fHealthFlash = 0;
		}
		else
			m_bLowHealthWarning = false;

		if (m_bPreventDialog)
		{
			PreventDialogFromRestarting(elapsedTime);
		}
	}

}

void Player::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	if (m_bPlayCombatAnimation)
	{
		m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), playerRect.right, playerRect.bottom);
	}
	else
	{
		SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
		SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };

		if (GameplayState::GetInstance()->GetDebugState())
		{
			SGD::Rectangle rec = GetRect();
			rec.Offset(-GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y);
			pGraphics->DrawRectangle(rec, SGD::Color(0, 0, 255));
		}


		SGD::Point currentHealthHUD = { 0, 0 };
		// Red Health Bar
		currentHealthHUD = { (Game::GetInstance()->GetScreenWidth() * 1 / 5) - 75, (Game::GetInstance()->GetScreenHeight() / 10) };
		pGraphics->DrawLine(currentHealthHUD, SGD::Point{ currentHealthHUD.x + this->GetMaxHealth(), currentHealthHUD.y }, { 255, 0, 0 }, 17U);
		// Green Health Bar
		currentHealthHUD = { (Game::GetInstance()->GetScreenWidth() * 1 / 5) - 75, (Game::GetInstance()->GetScreenHeight() / 10) };
		pGraphics->DrawLine(currentHealthHUD, SGD::Point{ currentHealthHUD.x + this->GetHealth(), currentHealthHUD.y }, { 0, 255, 0 }, 17U);
		pGraphics->DrawTexture(m_hPortrait, SGD::Point(currentHealthHUD.x - 70, currentHealthHUD.y - 30), {}, {}, {}, { .5f, .5f });

		if (m_pAnimator->GetInstance()->CheckSize())
		{
			m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), (int)(point.x + (m_szSize.width / 2.0f)), (int)(point.y + (m_szSize.height / 2.0f)));
		}
		// Low Health warning!

		if (m_bLowHealthWarning)
			pGraphics->DrawRectangle(SGD::Rectangle(0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight()), { 100, 255, 0, 0 });

		if (m_bRunDialog && !m_bPreventDialog)
		{
			RenderDialog();
		}
	}
}

void Player::TakeInput()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	if (currentQT != nullptr)
	{
		currentQT->m_kLastKeyPressed = pInput->GetAnyKeyPressed();
	}
	if (m_bMoving)
	{
		m_bUpdateAnimation = false;
		return;
	}
	if (pInput->IsKeyDown(SGD::Key::Up) || pInput->IsKeyDown(SGD::Key::W))
	{
		m_nDirection = 1;

		if (this->GetTimeStamp()->GetCurrentAnimation() != "WalkingUp")
		{
			this->GetTimeStamp()->SetCurrentAnimation("WalkingUp");
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}

	}
	if (pInput->IsKeyDown(SGD::Key::Down) || pInput->IsKeyDown(SGD::Key::S))
	{
		m_nDirection = 2;
		if (this->GetTimeStamp()->GetCurrentAnimation() != "WalkingDown")
		{
			this->GetTimeStamp()->SetCurrentAnimation("WalkingDown");
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
	}

	if (pInput->IsKeyDown(SGD::Key::Left) || pInput->IsKeyDown(SGD::Key::A))
	{
		m_nDirection = 3;

		if (this->GetTimeStamp()->GetCurrentAnimation() != "WalkingLeft")
		{
			this->GetTimeStamp()->SetCurrentAnimation("WalkingLeft");
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
	}
	if (pInput->IsKeyDown(SGD::Key::Right) || pInput->IsKeyDown(SGD::Key::D))
	{
		m_nDirection = 4;
		if (this->GetTimeStamp()->GetCurrentAnimation() != "WalkingRight")
		{
			this->GetTimeStamp()->SetCurrentAnimation("WalkingRight");
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
	}

	if (pInput->IsKeyPressed(SGD::Key::P) && m_nPotions > 0 && m_nHealth < 100)
	{
		m_nHealth += 30;
		pAudio->PlayAudio(Game::GetInstance()->potionSound, false);
		if (m_nHealth > 100)
		{
			m_nHealth = 100;
		}
		m_nPotions--;
	}
	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(GameplayState::GetInstance()->HealthPotionPosition))
		{
			m_nHealth += 30;
			pAudio->PlayAudio(Game::GetInstance()->potionSound, false);
			if (m_nHealth > 100)
			{
				m_nHealth = 100;
			}
			m_nPotions--;
		}
	}

	m_bUpdateAnimation = pInput->IsAnyKeyDown();

	if (m_bRunDialog && !m_bPreventDialog)
	{
		if (pInput->IsAnyKeyPressed())
		{
			UpdateDialog();
		}
	}


}

SGD::Rectangle Player::GetRect(void) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}



void Player::HandleCollision(const iObject* pOther)
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	if (pOther->GetType() == OBJ_ENEMY)
	{
		if (!m_bCombat)
		{
			CombatEnemyID = ((Enemy*)pOther)->GetEnemyType();
			pAudio->StopAudio(GameplayState::GetInstance()->bmusic);
			Game::GetInstance()->AddState(CombatState::GetInstance());
		}

	}
	if (pOther->GetType() == OBJ_CHEST)
	{
		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Q))
		{
			if (((Chest*)pOther)->IsTrapped())
			{
				CombatEnemyID = 1;
				Game::GetInstance()->AddState(CombatState::GetInstance());
				m_bCombat = true;
				((Chest*)pOther)->SetTrapped();
			}
			switch (((Chest*)pOther)->GetTier())
			{
			case 1:
				for (size_t i = 0; i < ((Chest*)pOther)->GetNumRunes(); i++)
				{
					Runes tempRune;
					tempRune.SetElement((Elements)(rand() % 4));
					tempRune.SetTier(1);
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld(tempRune);
				}
				break;
			case 2:
				for (size_t i = 0; i < ((Chest*)pOther)->GetNumRunes(); i++)
				{
					Runes tempRune;
					tempRune.SetElement((Elements)(rand() % 4));
					tempRune.SetTier(2);
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld(tempRune);
				}
				break;
			case 3:
				for (size_t i = 0; i < ((Chest*)pOther)->GetNumRunes(); i++)
				{
					Runes tempRune;
					tempRune.SetElement((Elements)(rand() % 4));
					tempRune.SetTier(3);
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld(tempRune);
				}
				break;
			default:
				break;
			}
			m_nPotions += ((Chest*)pOther)->GetNumPots();
			((Chest*)pOther)->RemoveItems();
		}
	}
	if (pOther->GetType() == OBJ_TRAP)
	{
		const Trap* trap = dynamic_cast<const Trap*>(pOther);

		m_nHealth -= trap->GetDamage();
		GameplayState::GetInstance()->SetScreenShake();

		//RunQuickTime( 3 );
	}
	if (pOther->GetType() == OBJ_BOULDER)
	{
		switch (m_nDirection)
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

	if (pOther->GetType() == OBJ_COMPANION)
	{
		m_bRunDialog = true;
	}
}

bool Player::TakeTurn(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	CombatState* pCombat = CombatState::GetInstance();
	SGD::Rectangle PlayerSelection{ 0, 0, 0, 0 };


	if (m_nHealth < 0)
	{
		return false;
	}

	if (!selected)
	{
		float posX = 200.0f;
		PlayerSelection = { posX, (float)(420 + 50 * m_nCursor), posX + 40, (float)(430 + 50 * m_nCursor) };

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

		pCombat->SetAction("Choose Action");
		if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
			m_nCursor--;

		if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
			m_nCursor++;

		if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
			m_nCursor--;

		if (m_nCursor < 0)
			m_nCursor = 0;
		if (m_nCursor > 1)
			m_nCursor = 1;

		if (pInput->IsKeyPressed(SGD::Key::Enter)) //First Selection >> Action
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
		if (PlayerSelection.left < PlayerSelection.right)
			pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));
	}
	else //Action selected, now pick target
	{
		if (ActionSelected == 0) //Melee
		{

			PlayerSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x + 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y + 40 };
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

			if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
				m_nCursor++;

			if (m_nCursor < 0)
				m_nCursor = 0;
			if (m_nCursor > pCombat->GetEnemies().size() - 1)
				m_nCursor = pCombat->GetEnemies().size() - 1;

			if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
			{
				selected = false;
				SetAttacking(true);
				pCombat->TakeAction(ActionSelected, this, m_nCursor);
				m_nCursor = 0;
				return true;
			}

			if (PlayerSelection.left < PlayerSelection.right)
				pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
		else if (ActionSelected == 1) //Magic
		{
			if (spellSelect == -1)
			{
				pCombat->SetAction("Choose Spell");

				float posX = 250.0f + (m_nCursor * 100);
				PlayerSelection = { posX, 500, posX + 60, 510 };

				if (pInput->IsKeyPressed(SGD::Key::Left) || pInput->IsKeyPressed(SGD::Key::W))
				{
					m_nCursor--;
				}
				if (pInput->IsKeyPressed(SGD::Key::Right) || pInput->IsKeyPressed(SGD::Key::S))
				{
					m_nCursor++;
				}

#pragma region spells
				InventoryState* pInventory = InventoryState::GetInstance();
				Runes temp1;
				temp1.SetElement(pInventory->m_vRing[0].GetElement());
				temp1.SetTier(pInventory->m_vRing[0].GetTier());

				Runes temp2;
				temp2.SetElement(pInventory->m_vRing[1].GetElement());
				temp2.SetTier(pInventory->m_vRing[1].GetTier());

				Runes temp3;
				temp3.SetElement(pInventory->m_vRing[2].GetElement());
				temp3.SetTier(pInventory->m_vRing[2].GetTier());

				string spell1;
				switch (temp1.GetElement())
				{
				case Fire:
				{
							 if (temp1.GetTier() == 1)
							 {
								 spell1 = "FireBolt1";
							 }
							 if (temp1.GetTier() == 2)
							 {
								 spell1 = "FireBolt2";
							 }
							 if (temp1.GetTier() == 3)
							 {
								 spell1 = "FireBolt3";
							 }
				}
					break;
				case Water:
				{
							  if (temp1.GetTier() == 1)
							  {
								  spell1 = "WaterBolt1";
							  }
							  if (temp1.GetTier() == 2)
							  {
								  spell1 = "WaterBolt2";
							  }
							  if (temp1.GetTier() == 3)
							  {
								  spell1 = "WaterBolt3";
							  }
				}
					break;
				case Air:
				{
							if (temp1.GetTier() == 1)
							{
								spell1 = "WindBolt1";
							}
							if (temp1.GetTier() == 2)
							{
								spell1 = "WindBolt2";
							}
							if (temp1.GetTier() == 3)
							{
								spell1 = "WindBolt3";
							}
				}
					break;
				case Earth:
				{
							  if (temp1.GetTier() == 1)
							  {
								  spell1 = "Rock Throw1";
							  }
							  if (temp1.GetTier() == 2)
							  {
								  spell1 = "Rock Throw2";
							  }
							  if (temp1.GetTier() == 3)
							  {
								  spell1 = "Rock Throw3";
							  }
				}
					break;
				case None:
					break;
				default:
					break;
				}
				string spell2;
				RuneManager rmanager;
				ComboElements firstCombo = rmanager.ElementCombination(temp1.GetElement(), temp2.GetElement());

				if (rmanager.ToString(firstCombo).length() > 0)
				{
					switch (firstCombo)
					{
					case Steam:
						spell2 = "Steam";
						break;
					case Ice:
						spell2 = "Ice";
						break;
					case Lightning:
						spell2 = "Lightning";
						break;
					case Magma:
						spell2 = "Magma";
						break;
					case Dust:
						spell2 = "Dust";
						break;
					case Mud:
						spell2 = "Mud";
						break;
					case Inferno:
						spell2 = "Inferno";
						break;
					case Wave:
						spell2 = "Wave";
						break;
					case Earthquake:
						spell2 = "Earthquake";
						break;
					case Whirlwind:
						spell2 = "Whirlwind";
						break;
					default:
						break;
					}

				}

				string spell3;

				ComboElements SecondCombo = rmanager.ElementCombination(temp2.GetElement(), temp3.GetElement());

				if (rmanager.ToString(firstCombo).length() > 0)
				{
					switch (SecondCombo)
					{
					case Steam:
						spell3 = "Steam";
						break;
					case Ice:
						spell3 = "Ice";
						break;
					case Lightning:
						spell3 = "Lightning";
						break;
					case Magma:
						spell3 = "Magma";
						break;
					case Dust:
						spell3 = "Dust";
						break;
					case Mud:
						spell3 = "Mud";
						break;
					case Inferno:
						spell3 = "Inferno";
						break;
					case Wave:
						spell3 = "Wave";
						break;
					case Earthquake:
						spell3 = "Earthquake";
						break;
					case Whirlwind:
						spell3 = "Whirlwind";
						break;
					default:
						break;
					}
				}


				for (size_t i = 0; i < pInventory->m_vRing.size(); i++)
				{
					switch (i)
					{
					case 0:
						if (m_bSpell1)
							pFont->Render("Bernardo", spell1.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 100, 255, 255, 255 });
						else
							pFont->Render("Bernardo", spell1.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 255, 255, 255, 255 });
						break;
					case 1:
						if (m_bSpell1)
							pFont->Render("Bernardo", spell2.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 100, 255, 255, 255 });
						else
							pFont->Render("Bernardo", spell2.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 255, 255, 255, 255 });
						break;
					case 2:
						if (m_bSpell1)
							pFont->Render("Bernardo", spell3.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 100, 255, 255, 255 });
						else
							pFont->Render("Bernardo", spell3.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 255, 255, 255, 255 });
						break;
					default:
						break;
					}
				}
#pragma endregion
				bool spellActive; //If no spell is active, selection needs to return as they cannot cast spells

				if (m_bSpell1)
					m_nCursor++;
				else
					spellActive = true;
				if (m_bSpell2)
					m_nCursor++;
				else
					spellActive = true;
				if (m_bSpell3)
					m_nCursor++;
				else
					spellActive = true;

				if (m_nCursor < 0)
					m_nCursor = 0;
				if (m_nCursor > pInventory->m_vRing.size() - 1)
					m_nCursor = pInventory->m_vRing.size() - 1;

				if (pInput->IsKeyPressed(SGD::Key::Enter))
				{
					spellSelect = m_nCursor;
					m_nCursor = 0;
				}
				if (PlayerSelection.left < PlayerSelection.right && pInventory->m_vRing.size() > 0)
					pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0)); //
			}
			else // spellSelect is set, choose target
			{
				PlayerSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x + 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y + 40 };
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

				if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
					m_nCursor++;

				if (m_nCursor < 0)
					m_nCursor = 0;
				if (m_nCursor > pCombat->GetEnemies().size() - 1)
					m_nCursor = pCombat->GetEnemies().size() - 1;

				if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
				{
					selected = false;
					SetAttacking(true);
					pCombat->TakeAction(ActionSelected, this, m_nCursor, spellSelect);
					spellSelect = -1;
					m_nCursor = 0;
					return true;
				}
				if (PlayerSelection.left < PlayerSelection.right)
					pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0)); //
			}
		}
	}
	return false;
}

void Player::RunQuickTime(int length)
{
	m_bDoQt = true;
	if (currentQT == nullptr)
	{
		currentQT = new QuickTime;
		currentQT->SetLength(length);
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
	this->GetTimeStamp()->SetCurrentAnimation("HeroSwordSwing");
	this->GetTimeStamp()->SetCurrentFrame(4);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);
}
void Player::StopCombat()
{
	m_bPlayCombatAnimation = false;
	this->GetTimeStamp()->SetCurrentAnimation(m_szLastAnimation);
	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);
}
void Player::ResetAnimation()
{
	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);
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

	pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));

	DialogManager* pDialog = pDialog->GetInstance();
	switch (m_nLineCounter)
	{
	case 1:
		pDialog->Render("Dialog", "Greeting", TextPositionOne, 1, SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hDialogImg2, portraitPosition);
		break;
	case 2:
		pDialog->Render("Dialog", "GreetingsResponse", TextPositionOne, 1, SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition, {}, {}, {}, { .3f, .3f });
		break;
	case 3:
		pDialog->Render("Dialog", "HowFares", TextPositionOne, 1, SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hDialogImg2, portraitPosition);
		break;
	case 4:
		pDialog->Render("Dialog", "HowFaresResponse", TextPositionOne, 1, SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition, {}, {}, {}, { .3f, .3f });
		break;
	case 5:
		pDialog->Render("Dialog", "RequestToJoin", TextPositionOne, 1, SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hDialogImg2, portraitPosition);
		break;
	case 6:
		pDialog->Render("Dialog", "Agree", TextPositionOne, 1, SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition, {}, {}, {}, { .3f, .3f });
		break;
	default:
		break;
	}
}

void Player::UpdateDialog()
{
	if (m_nLineCounter < 6)
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

void Player::PreventDialogFromRestarting(float elapsedTime)
{
	m_fDialogTimer -= elapsedTime;

	if (m_fDialogTimer <= 0.0f)
	{
		m_bPreventDialog = false;
		m_bRunDialog = false;
	}

}