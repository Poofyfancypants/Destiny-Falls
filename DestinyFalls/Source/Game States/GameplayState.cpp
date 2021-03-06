#include "stdafx.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "InventoryState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "CombatState.h"
#include "WinState.h"
#include "ForgeState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Boulder.h"
#include "../Game Objects/Enemy.h"
#include "../Game Objects/Chest.h"
#include "../Game Objects/SpikeTrap.h"
#include "../Game Objects/FireTrap.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Companion.h"
#include "../Messages/MessageID.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_String.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_EventManager.h"


GameplayState* GameplayState::GetInstance()
{
	static GameplayState s_Instance;
	return &s_Instance;
}

void GameplayState::Enter()
{
	SGD::AudioManager*	  pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	m_pObjects = new ObjectManager;
	m_pMap = new TileManager;

	//Set up Animation Manager
	m_pAnimator = m_pAnimator->GetInstance();

	//Load Animations
	m_pAnimator->Load("resource/XML/HeroWalking2XML.xml");
	m_pAnimator->Load("resource/XML/ChestXML.xml");
	m_pAnimator->Load("resource/XML/HeroSwordSwingXML.xml");
	m_pAnimator->Load("resource/XML/AirBossAttackXML.xml");
	m_pAnimator->Load("resource/XML/AirElementalAttackXML.xml");
	m_pAnimator->Load("resource/XML/AirMiniBossAttackXML.xml");  // Air level boss
	m_pAnimator->Load("resource/XML/BaronAttackXML.xml"); // Water mini boss
	m_pAnimator->Load("resource/XML/BehemothAttackXML.xml");
	m_pAnimator->Load("resource/XML/BombAttackXML.xml");
	m_pAnimator->Load("resource/XML/EarthEnemyAttackXML.xml");
	m_pAnimator->Load("resource/XML/EarthMiniBossAttackXML.xml");	// Earth mini boss
	m_pAnimator->Load("resource/XML/EarthBossAttackXML.xml");		// Earth level boss
	m_pAnimator->Load("resource/XML/GenieAttackXML.xml");
	m_pAnimator->Load("resource/XML/GolemAttackXML.xml");
	m_pAnimator->Load("resource/XML/GreenGoblinAttackXML.xml");
	m_pAnimator->Load("resource/XML/IceBossAttackXML.xml");	// Water level boss
	m_pAnimator->Load("resource/XML/IceElementalAttackXML.xml");
	m_pAnimator->Load("resource/XML/NagaAttackXML.xml");  // fire level boss
	m_pAnimator->Load("resource/XML/OrcAttackXML.xml");
	m_pAnimator->Load("resource/XML/OrcElementalAttackXML.xml");
	m_pAnimator->Load("resource/XML/OrcSkeletonAttackXML.xml"); // fire mini boss
	m_pAnimator->Load("resource/XML/PlantAttackXML.xml");
	m_pAnimator->Load("resource/XML/RockElementalAttackXML.xml");
	m_pAnimator->Load("resource/XML/TitanAttackXML.xml");  // final boss
	m_pAnimator->Load("resource/XML/WaterElementalAttackXML.xml");
	m_pAnimator->Load("resource/XML/WaterEnemyAttackXML.xml");

	m_pAnimator->Load("resource/XML/ClericAttackXML.xml");
	m_pAnimator->Load("resource/XML/RangerAttackXML.xml");
	m_pAnimator->Load("resource/XML/Companion1AttackXML.xml");
	m_pAnimator->Load("resource/XML/GladiatorAttackXML.xml");

	m_pAnimator->Load("resource/XML/DeathAnimationXML.xml");

	m_pAnimator->Load("resource/XML/OverWorldEnemiesXML.xml");



	m_hTutorialRune = pGraphics->LoadTexture(L"resource/graphics/Firet2.png");
	m_hminiboss = pGraphics->LoadTexture(L"resource/graphics/testMB1.png");
	m_hlevelboss = pGraphics->LoadTexture(L"resource/graphics/testLB1.png");
	m_hFinalboss = pGraphics->LoadTexture(L"resource/graphics/testLB5.png");
	m_hRanger = pGraphics->LoadTexture(L"resource/graphics/testc.png");
	m_hCleric = pGraphics->LoadTexture(L"resource/graphics/testc2.png");
	//m_hForge = pGraphics->LoadTexture( L"resource/graphics/Anvil1.png" );
	m_hHealthPot = pGraphics->LoadTexture(L"resource/graphics/healthpot.png");
	m_hDialogImg = pGraphics->LoadTexture(L"resource/graphics/heroPortrait.png");
	m_hplayer = pGraphics->LoadTexture(L"resource/graphics/testhero.png");
	m_henemy = pGraphics->LoadTexture(L"resource/graphics/enemy1.png");
	m_hChest = pGraphics->LoadTexture(L"resource/graphics/chest.png");
	m_hBoulder = pGraphics->LoadTexture(L"resource/graphics/boulder.png");
	m_hInvButton = pGraphics->LoadTexture(L"resource/graphics/NewInventory.png");
	m_hHero = pGraphics->LoadTexture(L"resource/graphics/testhero.png");
	bmusic = pAudio->LoadAudio(L"resource/audio/backgroundMusic.wav");
	bLevel1Music = pAudio->LoadAudio(L"resource/audio/Level1Music.xwm");
	bLevel2Music = pAudio->LoadAudio(L"resource/audio/Level2Music.xwm");
	bLevel3Music = pAudio->LoadAudio(L"resource/audio/Level3Music.xwm");
	bLevel4Music = pAudio->LoadAudio(L"resource/audio/Level4Music.xwm");


	m_hSpikeTrap = pGraphics->LoadTexture(L"resource/graphics/spikeTrap.png");
	m_hFireTrap = pGraphics->LoadTexture(L"resource/graphics/fireTrap.png");

	m_htutorialFrame = pGraphics->LoadTexture(L"resource/graphics/tutorialFrame.png");
	m_hearthFrame = pGraphics->LoadTexture(L"resource/graphics/earthFrame.png");
	m_hwaterFrame = pGraphics->LoadTexture(L"resource/graphics/waterFrame.png");
	m_hairFrame = pGraphics->LoadTexture(L"resource/graphics/airFrame.png");
	m_fireFrame = pGraphics->LoadTexture(L"resource/graphics/fireFrame.png");
	m_hfinalFrame = pGraphics->LoadTexture(L"resource/graphics/finalFrame.png");

	pAudio->PlayAudio(bmusic, true);

	m_bSetSidePosition = false;
	m_bSetLevelPosition = false;
	m_bFirstDialog = false;
	m_bPuzzleDialog = false;
	m_bBoulderDialog = false;
	m_bTrapDialog = false;
	m_bMainDialog = false;
	m_bChestDialog = false;
	m_bSigmundDialog = false;

	// Invisible inventory selection button behind inventory image.
	InventoryButton = SGD::Rectangle(SGD::Point{ (Game::GetInstance()->GetScreenWidth() - 60), (Game::GetInstance()->GetScreenHeight() - 60) }, SGD::Size{ 120, 120 });
	ForgeButton = SGD::Rectangle(SGD::Point{ (Game::GetInstance()->GetScreenWidth() - 120), (Game::GetInstance()->GetScreenHeight() - 60) }, SGD::Point{ (Game::GetInstance()->GetScreenWidth() - 59), (Game::GetInstance()->GetScreenHeight()) });
	HealthPotionPosition = SGD::Rectangle(SGD::Point{ 10, (Game::GetInstance()->GetScreenHeight() - 60) }, SGD::Size{ 60, 60 });


	m_ptWorldCam = { 0, 0 };
	m_fWorldWidth = 800;
	m_fWorldHeight = 600;

	// - Manage The map
	m_nCurrentLevel = 0;
	m_nCurrentSideLevel = -1;
	LoadNewLevel();



}

void GameplayState::Exit()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager*	  pAudio = SGD::AudioManager::GetInstance();

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}
	pAudio->StopAudio( GameplayState::GetInstance()->bmusic );
	pAudio->UnloadAudio(bmusic);
	pAudio->UnloadAudio(bLevel1Music);
	pAudio->UnloadAudio(bLevel2Music);
	pAudio->UnloadAudio(bLevel3Music);
	pAudio->UnloadAudio(bLevel4Music);

	//unload images
	pGraphics->UnloadTexture(m_hminiboss);
	pGraphics->UnloadTexture(m_hlevelboss);
	pGraphics->UnloadTexture(m_hFinalboss);
	//pGraphics->UnloadTexture( m_hForge );
	pGraphics->UnloadTexture(m_hplayer);
	pGraphics->UnloadTexture(m_henemy);
	pGraphics->UnloadTexture(m_hChest);
	pGraphics->UnloadTexture(m_hBoulder);
	pGraphics->UnloadTexture(m_hInvButton);
	pGraphics->UnloadTexture(m_hHero);
	pGraphics->UnloadTexture(m_hDialogImg);
	pGraphics->UnloadTexture(m_hHealthPot);
	pGraphics->UnloadTexture(m_hRanger);
	pGraphics->UnloadTexture(m_hCleric);
	pGraphics->UnloadTexture(m_hSpikeTrap);
	pGraphics->UnloadTexture(m_hFireTrap);
	pGraphics->UnloadTexture(m_hTutorialRune);
	pGraphics->UnloadTexture(m_hearthFrame);

	pGraphics->UnloadTexture(m_htutorialFrame);
	pGraphics->UnloadTexture(m_hearthFrame);
	pGraphics->UnloadTexture(m_hwaterFrame);
	pGraphics->UnloadTexture(m_hairFrame);
	pGraphics->UnloadTexture(m_fireFrame);
	pGraphics->UnloadTexture(m_hfinalFrame);

	InventoryState::GetInstance()->ClearInventory();

	m_pObjects->RemoveAll();
	delete m_pObjects;
	m_pObjects = nullptr;

	delete m_pMap;
	m_pMap = nullptr;
	m_pAnimator->DeleteInstance();
	//m_particle.Exit();
}

bool GameplayState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	//if( pInput->IsKeyPressed( SGD::Key::F1 ) )
	//{
	//	Game::GetInstance()->RemoveState(); //Make this Pause
	//	Game::GetInstance()->AddState( MainMenuState::GetInstance() );
	//}
	if (m_fArcadeTimer >= 0.5f)
	{
	if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonPressed(0, 6))
	{
		m_bPaused = !m_bPaused;
		m_fArcadeTimer = 0.0f;
		Game::GetInstance()->AddState(PauseMenuState::GetInstance());
	}

	
		if (pInput->IsKeyPressed(SGD::Key::E) || pInput->IsButtonPressed(0, 4) || pInput->IsKeyPressed(SGD::Key::MouseRight))
		{
			m_fArcadeTimer = 0.0f;
			Game::GetInstance()->AddState(InventoryState::GetInstance());
		}
	}

	//if( pInput->IsKeyPressed( SGD::Key::F ) )
	//{
	//	Game::GetInstance()->AddState( ForgeState::GetInstance() );
	//}

	// - Toggle DebugMode with F2
	if (pInput->IsKeyPressed(SGD::Key::F1))
		m_bDebug = !m_bDebug;
	if (m_nCurrentLevel == 0 && pInput->IsKeyPressed(SGD::Key::Tab))
	{
		m_pPlayer->SetPosition(SGD::Point(17 * 32, 21 * 32));
	}
	if (pInput->IsKeyPressed(SGD::Key::F6))
	{
		NextLevel();
		m_bChangeLevels = true;
	}

	// Toggle Inventory
	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(InventoryButton))
		{
			Game::GetInstance()->AddState(InventoryState::GetInstance());
		}
	}

	if (pInput->IsKeyPressed(SGD::Key::T))
	{
		m_fAlpha = 0;
		m_bIn = true;
	}

	m_bIcelandic = Game::GetInstance()->GetIcelandic();

	return true;
}

void GameplayState::Update(float elapsedTime)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();


	// - Update Name
	if (m_bIn)
	{
		if (m_fAlpha >= 200)
			m_fAlpha += .5f;
		else
			m_fAlpha += 2;
		if (m_fAlpha >= 255)
		{
			m_bIn = false;
			m_bOut = true;
		}
	}
	else if (m_bOut)
	{
		m_fAlpha -= 2;
		if (m_fAlpha <= 0)
			m_bOut = false;
	}

	m_fFPSTime += elapsedTime;
	m_nFrames++;
	if (m_fFPSTime >= 1.0f)
	{
		m_nFPS = m_nFrames;
		m_nFrames = 0;
		m_fFPSTime = 0.0f;
	}
	if (m_fShakeTimer > 0)
	{
		m_fShakeTimer -= elapsedTime;
	}

	m_pObjects->UpdateAll(elapsedTime);
	m_pObjects->CheckCollisions(BOULDER_BUCKET, BOULDER_BUCKET);
	m_pObjects->CheckCollisions(PLAYER_BUCKET, BOULDER_BUCKET);
	m_pObjects->CheckCollisions(PLAYER_BUCKET, ENEMY_BUCKET);
	m_pObjects->CheckCollisions(PLAYER_BUCKET, CHEST_BUCKET);
	m_pObjects->CheckCollisions(PLAYER_BUCKET, TRAP_BUCKET);
	m_pObjects->CheckCollisions(PLAYER_BUCKET, COMPANION_BUCKET);

	if (m_bScreenShake)
	{
		float randY = 0;
		float randX = 0;

		randX = (float)(rand() % 6 - 3);
		randY = (float)(rand() % 6 - 3);

		if (m_fShakeTimer <= 0.0f)
		{
			m_bScreenShake = false;
		}
		m_ptWorldCam = { m_pPlayer->GetPosition().x - Game::GetInstance()->GetScreenWidth() / 2.0f + randX, m_pPlayer->GetPosition().y - Game::GetInstance()->GetScreenHeight() / 2.0f + randY };

	}
	else
	{
		m_ptWorldCam = { m_pPlayer->GetPosition().x - Game::GetInstance()->GetScreenWidth() / 2.0f, m_pPlayer->GetPosition().y - Game::GetInstance()->GetScreenHeight() / 2.0f };
	}

	if (m_nCurrentLevel == 0 && m_bUpdateTutorial)
		HandleTutorial();

	// - Next Level?
	if (m_bChangeLevels)
		LoadNewLevel();
	else if (m_bChangeSideLevels)
		LoadNewSideLevel();

	m_fArcadeTimer += elapsedTime;

}

void GameplayState::Render()
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	m_pMap->DrawLevel(m_ptWorldCam, m_pPlayer->GetPosition());

	pGraphics->SetClearColor();
	m_pObjects->RenderAll();

	if (m_bDebug)
	{
		SGD::OStringStream numEnt;
		numEnt << "Objects: " << GameplayState::GetInstance()->GetObjManager()->GetNumObjects();
		SGD::GraphicsManager::GetInstance()->DrawString(numEnt.str().c_str(), SGD::Point(10, 30), { 0, 255, 0 });

		SGD::OStringStream fps;
		fps << "FPS: " << Game::GetInstance()->GetFrames();
		pGraphics->DrawString(fps.str().c_str(), SGD::Point(10, 10), SGD::Color(0, 255, 0));
	}

	//pGraphics->DrawTexture( m_hForge, SGD::Point( ( Game::GetInstance()->GetScreenWidth() - 120 ), ( Game::GetInstance()->GetScreenHeight() - 60 ) ), {}, {}, {}, { 0.4f, 0.35f } );

	if (m_nCurrentLevel == 0)
	{
		RenderDialog();
	}

	// Inventory Image/Scaling
	//pGraphics->DrawRectangle( InventoryButton, SGD::Color{ 0, 0, 255, 0 } );
	pGraphics->DrawTexture(m_hInvButton, SGD::Point((Game::GetInstance()->GetScreenWidth() - 60), (Game::GetInstance()->GetScreenHeight() - 60)), {}, {}, {}, { 0.5f, 0.5f });

	pGraphics->DrawRectangle(SGD::Rectangle(
		HealthPotionPosition.left - 3,
		HealthPotionPosition.top - 3,
		HealthPotionPosition.right + 20,
		HealthPotionPosition.top + 50),
		SGD::Color(100, 50, 50, 50));


	pGraphics->DrawTexture(m_hHealthPot, SGD::Point(HealthPotionPosition.left, HealthPotionPosition.top), {}, {}, {}, { 0.7f, 0.7f });
	pFont->Render("Bernardo",
		to_string(((Player*)(m_pPlayer))->GetNumPotions()).c_str(),
		SGD::Point(HealthPotionPosition.right - 7, HealthPotionPosition.top - 15),
		2, SGD::Color(255, 0, 0));

	if (m_nCurrentLevel == 0)
	{
		RenderDialog();
	}

	// - Render Name
	if (m_bIn || m_bOut)
	{
		switch (m_nCurrentLevel)
		{
		case GameplayState::TUTORIAL_LEVEL:
			pGraphics->DrawTexture(m_htutorialFrame, SGD::Point(100, 100), {}, {}, { (unsigned char)m_fAlpha, 255, 255, 255 }, { 1.3f, .7f });
			break;
		case GameplayState::EARTH_LEVEL:
			pGraphics->DrawTexture(m_hearthFrame, SGD::Point(100, 100), {}, {}, { (unsigned char)m_fAlpha, 255, 255, 255 }, { 1.3f, .7f });
			break;
		case GameplayState::WATER_LEVEL:
			pGraphics->DrawTexture(m_hwaterFrame, SGD::Point(100, 100), {}, {}, { (unsigned char)m_fAlpha, 255, 255, 255 }, { 1.3f, .7f });
			break;
		case GameplayState::AIR_LEVEL:
			pGraphics->DrawTexture(m_hairFrame, SGD::Point(100, 100), {}, {}, { (unsigned char)m_fAlpha, 255, 255, 255 }, { 1.3f, .7f });
			break;
		case GameplayState::FIRE_LEVEL:
			pGraphics->DrawTexture(m_fireFrame, SGD::Point(100, 100), {}, {}, { (unsigned char)m_fAlpha, 255, 255, 255 }, { 1.3f, .7f });
			break;
		case GameplayState::BOSS_LEVEL:
			pGraphics->DrawTexture(m_hfinalFrame, SGD::Point(100, 100), {}, {}, { (unsigned char)m_fAlpha, 255, 255, 255 }, { 1.3f, .7f });
			break;
		}
		//pFont->Render("Other", m_sName.c_str(), SGD::Point(100,100), 3, SGD::Color(m_fAlpha, 0,255,0));
	}




	/*if (LevelList::TUTORIAL_LEVEL == m_nCurrentLevel)
	{
	m_particle.ReadXML("resource/XML/Test3.xml");
	}
	else if (LevelList::EARTH_LEVEL == m_nCurrentLevel)
	{
	m_particle.ReadXML("resource/XML/Test2.xml");
	}
	else if (LevelList::WATER_LEVEL == m_nCurrentLevel)
	{
	m_particle.ReadXML("resource/XML/Test3.xml");
	}
	else if (LevelList::AIR_LEVEL == m_nCurrentLevel)
	{
	m_particle.ReadXML("resource/XML/Test4.xml");
	}
	else if (LevelList::FIRE_LEVEL == m_nCurrentLevel)
	{
	m_particle.ReadXML("resource/XML/Test5.xml");
	}
	else if (LevelList::BOSS_LEVEL == m_nCurrentLevel)
	{
	m_particle.ReadXML("resource/XML/Test6.xml");
	}
	m_particle.Render();*/


}

Object* GameplayState::CreatePlayer(SGD::Point _pos)
{
	Player* temp = new Player;
	temp->SetImage(m_hplayer);
	temp->SetSize({ 16, 16 });
	temp->SetPosition(_pos);
	temp->SetRotation(0);
	return temp;
}

Object* GameplayState::CreateEnemy(SGD::Point _pos, int _id)
{
	Enemy* temp = new Enemy;
	temp->SetPosition(_pos);
	temp->SetEnemyType(_id);
	temp->SetSize(SGD::Size(32, 32));
	m_pMap->NextWaypoint(temp);
	temp->SetWaypointID(1);
	switch (_id)
	{
	case 0:
		//temp->SetImage( m_henemy );
		temp->SetAnimation(0);
		break;
	case 1:
		//temp->SetImage( m_henemy );
		temp->SetAnimation(1);
		break;
	case 2:
		//temp->SetImage( m_hminiboss );
		temp->SetAnimation(2);
		break;
	case 3:
		//temp->SetImage( m_hlevelboss );
		temp->SetAnimation(3);
		break;
	case 4:
		//temp->SetImage( m_hFinalboss );
		temp->SetAnimation(4);
		break;
	default:
		break;
	}
	return temp;
}

// - ID == Chest Tier
Object* GameplayState::CreateChest(SGD::Point _pos, int _id)
{
	// - Chest tier 1
	Chest* temp = new Chest;
	temp->SetImage(m_hChest);
	temp->SetSize({ 32, 32 });
	temp->SetTier(_id);

	if (_id == 1) // - Set the loot of Tier 1 chests
	{
		int numPots = rand() % 2;
		int numRunes = rand() % 2;
	}
	else if (_id == 2) // - Set the loot of Tier 2 chests
	{
		int numPots = rand() % 2 + 1;
		int numRunes = rand() % 3;
	}
	else if (_id == 3) // - Set the loot of Tier 3 chests
	{
		int numPots = rand() % 2 + 2;
		int numRunes = rand() % 3 + 1;
	}
	temp->SetPosition(_pos);
	return temp;
}

Object* GameplayState::CreateTrap(SGD::Point _pos, int _id){
	// 1 == fire trap || 2 == spike trap
	if (_id == 1)
	{
		FireTrap* temp = new FireTrap;
		temp->SetPosition(_pos);
		temp->SetImage(m_hFireTrap);
		temp->SetSize(SGD::Size(32, 32));
		return temp;
	}
	else if (_id == 2)
	{
		SpikeTrap* temp = new SpikeTrap;
		temp->SetPosition(_pos);
		temp->SetImage(m_hSpikeTrap);
		temp->SetSize(SGD::Size(32, 32));
		return temp;
	}
	return 0;
}

Object* GameplayState::CreateBoulder(SGD::Point _pos)
{
	Boulder* temp = new Boulder;
	temp->SetImage(m_hBoulder);
	temp->SetPosition(_pos);
	temp->SetSize(SGD::Size(28, 28));
	return temp;


}

Object* GameplayState::CreateCompanion(SGD::Point _pos, int _ID)
{
	Companion* temp = new Companion;
	if (_ID == 1)
		temp->SetImage(m_hRanger);
	else
		temp->SetImage(m_hCleric);
	temp->SetPosition(_pos);
	temp->SetSize(SGD::Size(30, 30));
	return temp;
}

// - Helper
void GameplayState::UnloadAndCreate()
{

	int playerHealth, numPotions;
	SGD::Point checkpoint;
	SGD::Point prevPos = m_pMap->GetPrevPosition();
	SGD::Point prevLevelPos = m_pMap->GetPrevLevelPosition();
	if (m_pPlayer != nullptr)
	{
		checkpoint = ((Player*)(m_pPlayer))->GetCheckpoint();;
		playerHealth = (int)((Player*)(m_pPlayer))->GetHealth();
		numPotions = ((Player*)(m_pPlayer))->GetNumPotions();
	}
	else
	{
		playerHealth = 100;
		numPotions = 0;
	}


	m_pObjects->RemoveAll();
	delete m_pObjects;
	m_pObjects = new ObjectManager;

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	m_pPlayer = CreatePlayer(SGD::Point(150, 150));
	((Player*)m_pPlayer)->SetHealth((float)playerHealth);
	((Player*)m_pPlayer)->SetPotions(numPotions);

	m_pObjects->AddObject(m_pPlayer, PLAYER_BUCKET);


	delete m_pMap;
	m_pMap = new TileManager;
	((Player*)(m_pPlayer))->SetCheckPoint(checkpoint);
	m_pMap->SetPrevPosition(prevPos);
	m_pMap->SetPrevLevelPosition(prevLevelPos);

	if (m_nCurrentLevel == 0)
	{
		SGD::Point dest = { (float)((3 * 32) - m_ptWorldCam.x), (float)((8 * 32) - m_ptWorldCam.y) };

		Object* temp = new Object;
		temp->SetPosition(dest);
		temp->SetImage(m_hHero);
		m_pObjects->AddObject(temp, TUTORIAL_HERO_BUCKET);
		temp->Release();
	}
}
void GameplayState::LoadNewLevel()
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();



	if (MainMenuState::GetInstance()->GetTutorial() && m_nCurrentLevel != 0)
	{
		Game::GetInstance()->ClearStates();
		Game::GetInstance()->AddState(MainMenuState::GetInstance());
	}
	else
	{
		m_bUpdateTutorial = true;
		switch (m_nCurrentLevel)
		{
		case GameplayState::TUTORIAL_LEVEL:
			UnloadAndCreate();
			m_pMap->LoadLevel("resource/XML/TutorialStage.xml");
			//m_pMap->LoadLevel( "resource/XML/Balencingtestmap.xml" );
			/*Balencingtestmap.xml*/
			if (m_bSetSidePosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevPosition());
			else  if (m_bSetLevelPosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevLevelPosition());

			break;
		case GameplayState::EARTH_LEVEL:
			UnloadAndCreate();
			m_pMap->LoadLevel("resource/XML/earthLevel.xml");
			if (m_bSetSidePosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevPosition());
			else  if (m_bSetLevelPosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevLevelPosition());
			if (pAudio->IsAudioPlaying(bmusic))
				pAudio->StopAudio(bmusic);
			if (pAudio->IsAudioPlaying(bLevel2Music))
				pAudio->StopAudio(bLevel2Music);

			pAudio->PlayAudio(bLevel1Music);
			break;
		case GameplayState::WATER_LEVEL:
			UnloadAndCreate();
			m_pMap->LoadLevel("resource/XML/waterLevel.xml");
			if (m_bSetSidePosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevPosition());
			else  if (m_bSetLevelPosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevLevelPosition());
			if (pAudio->IsAudioPlaying(bLevel1Music))
				pAudio->StopAudio(bLevel1Music);

			if (pAudio->IsAudioPlaying(bLevel3Music))
				pAudio->StopAudio(bLevel3Music);


			pAudio->PlayAudio(bLevel2Music);

			break;
		case GameplayState::AIR_LEVEL:
			UnloadAndCreate();
			m_pMap->LoadLevel("resource/XML/airLevel2.xml");
			if (m_bSetSidePosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevPosition());
			else  if (m_bSetLevelPosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevLevelPosition());
			if (pAudio->IsAudioPlaying(bLevel2Music))
				pAudio->StopAudio(bLevel2Music);
			if (pAudio->IsAudioPlaying(bLevel4Music))
				pAudio->StopAudio(bLevel4Music);


			pAudio->PlayAudio(bLevel3Music);
			break;
		case GameplayState::FIRE_LEVEL:
			UnloadAndCreate();
			m_pMap->LoadLevel("resource/XML/FireLevelT1.xml");
			if (m_bSetSidePosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevPosition());
			else  if (m_bSetLevelPosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevLevelPosition());
			if (pAudio->IsAudioPlaying(bLevel3Music))
				pAudio->StopAudio(bLevel3Music);


			pAudio->PlayAudio(bLevel4Music);

			break;
		case GameplayState::BOSS_LEVEL:
			UnloadAndCreate();
			m_pMap->LoadLevel("resource/XML/FinalLevel.xml");
			if (m_bSetSidePosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevPosition());
			else  if (m_bSetLevelPosition)
				m_pPlayer->SetPosition(m_pMap->GetPrevLevelPosition());

			break;
		case GameplayState::WIN_LEVEL:
			Game::GetInstance()->RemoveState();
			Game::GetInstance()->AddState( WinState::GetInstance() );
			m_nCurrentLevel = 1;

			break;
		default:
			break;
		}

	}
	m_fAlpha = 0;
	m_bIn = true;
	m_bChangeLevels = false;
}
void GameplayState::LoadNewSideLevel()
{
	if (m_nCurrentLevel == 0)
	{
		m_bFirstDialog = false;
		m_bPuzzleDialog = false;
		m_bBoulderDialog = false;
		m_bTrapDialog = false;
		m_bMainDialog = false;
		m_bChestDialog = false;
		m_bSigmundDialog = false;
		m_bUpdateTutorial = false;
	}

	// - Needs to be filled in. 9 levels
	switch (m_nCurrentSideLevel)
	{
	case GameplayState::TUTORIAL_SIDE:
		UnloadAndCreate();
		m_pMap->LoadLevel("resource/XML/CastleBlevel.xml");
		break;
	case GameplayState::EARTH_SIDE:
		UnloadAndCreate();
		m_pMap->LoadLevel("resource/XML/FarmHouseBLevel.xml");
		break;
	case GameplayState::WATER_SIDE:
		UnloadAndCreate();
		m_pMap->LoadLevel("resource/XML/IceForestBLevel.xml");
		break;
	case GameplayState::AIR_SIDE:
		UnloadAndCreate();
		m_pMap->LoadLevel("resource/XML/AirBLevel.xml");
		break;
	case GameplayState::FIRE_SIDE:
		break;
	case GameplayState::BOSS_SIDE:
		break;
	default:
		break;
	}

	m_bChangeSideLevels = false;
}

void GameplayState::HandleTutorial()
{

	// - Tutorial Update
	if (m_nCurrentLevel == 0)
	{
		SGD::Rectangle heroTooltipRange;
		heroTooltipRange.left = 0;
		heroTooltipRange.top = 5 * 32;
		heroTooltipRange.right = 8 * 32;
		heroTooltipRange.bottom = 9 * 32;

		SGD::Rectangle puzzleTooltipRange;
		puzzleTooltipRange.left = 0;
		puzzleTooltipRange.top = 14 * 32;
		puzzleTooltipRange.right = 15 * 32;
		puzzleTooltipRange.bottom = 18 * 32;

		SGD::Rectangle boulderTooltipRange;
		boulderTooltipRange.left = 10 * 32;
		boulderTooltipRange.top = 0;
		boulderTooltipRange.right = 17 * 32;
		boulderTooltipRange.bottom = 8 * 32;

		SGD::Rectangle trapTooltipRange;
		trapTooltipRange.left = 23 * 32;
		trapTooltipRange.top = 0;
		trapTooltipRange.right = 30 * 32;
		trapTooltipRange.bottom = 6 * 32;
		// - 4 3 
		SGD::Rectangle mainTooltipRange;
		mainTooltipRange.left = 25 * 32;
		mainTooltipRange.top = 16 * 32;
		mainTooltipRange.right = 30 * 32;
		mainTooltipRange.bottom = 19 * 32;

		SGD::Rectangle chestTooltipRange;
		chestTooltipRange.left = 20 * 32;
		chestTooltipRange.top = 4 * 32;
		chestTooltipRange.right = 24 * 32;
		chestTooltipRange.bottom = 7 * 32;

		SGD::Rectangle sigmundTooltipRange;
		sigmundTooltipRange.left = 17 * 32;
		sigmundTooltipRange.top = 16 * 32;
		sigmundTooltipRange.right = 21 * 32;
		sigmundTooltipRange.bottom = 21 * 32;

		// - If Player is within range of the Hero, start the dialog.
		if (heroTooltipRange.IsPointInRectangle(m_pPlayer->GetPosition()))
			m_bFirstDialog = true;
		else if (puzzleTooltipRange.IsPointInRectangle(m_pPlayer->GetPosition()))
			m_bPuzzleDialog = true;
		else if (boulderTooltipRange.IsPointInRectangle(m_pPlayer->GetPosition()))
			m_bBoulderDialog = true;
		else if (trapTooltipRange.IsPointInRectangle(m_pPlayer->GetPosition()))
			m_bTrapDialog = true;
		else if (mainTooltipRange.IsPointInRectangle(m_pPlayer->GetPosition()))
			m_bMainDialog = true;
		else if (chestTooltipRange.IsPointInRectangle(m_pPlayer->GetPosition()))
			m_bChestDialog = true;
		else if (sigmundTooltipRange.IsPointInRectangle(m_pPlayer->GetPosition()))
			m_bSigmundDialog = true;
		else
			m_bSigmundDialog = m_bChestDialog = m_bMainDialog = m_bFirstDialog = m_bTrapDialog = m_bPuzzleDialog = m_bBoulderDialog = false;
	}
}

void GameplayState::RenderDialog()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager *pFont = BitmapFontManager::GetInstance();



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

	if (m_bFirstDialog)
	{
		if (m_bIcelandic)
		{
			TextPositionOne.x = DialogBoxOne.left + 150;
			TextPositionTwo.x = DialogBoxOne.left + 170;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 50;
			TextPositionTwo.x = DialogBoxOne.left + 200;
		}

		heroPosition = { (float)((3 * 32) - m_ptWorldCam.x), (float)((8 * 32) - m_ptWorldCam.y) };

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition);
		pGraphics->DrawTexture(m_hHero, heroPosition);
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 1).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 2).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));
	}

	else if (m_bPuzzleDialog)
	{
		if (m_bIcelandic)
		{
			TextPositionOne.x = DialogBoxOne.left + 115;
			TextPositionTwo.x = DialogBoxOne.left + 140;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 160;
			TextPositionTwo.x = DialogBoxOne.left + 100;
		}
		heroPosition = { (float)((7 * 32) - m_ptWorldCam.x), (float)((14 * 32) - m_ptWorldCam.y) };

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hHero, heroPosition);
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition);
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 3).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 4).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));
	}

	else if (m_bBoulderDialog)
	{
		if (m_bIcelandic)
		{
			TextPositionOne.x = DialogBoxOne.left + 115;
			TextPositionTwo.x = DialogBoxOne.left + 140;
		}
		else
		{
			TextPositionTwo.x = DialogBoxOne.left + 115;
		}
		heroPosition = { (float)((12 * 32) - m_ptWorldCam.x), (float)((0 * 32) - m_ptWorldCam.y) };

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hHero, heroPosition);
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition);
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 5).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(8, 6).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));

	}

	else if (m_bTrapDialog)
	{
		heroPosition = { (float)((26 * 32) - m_ptWorldCam.x), (float)((2 * 32) - m_ptWorldCam.y) };
		if (m_bIcelandic)
		{
			TextPositionOne.x = DialogBoxOne.left + 130;
			TextPositionTwo.x = DialogBoxOne.left + 110;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 90;
			TextPositionTwo.x = DialogBoxOne.left + 110;
		}
		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));		// - Draw string One.
		pGraphics->DrawTexture(m_hHero, heroPosition);
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition);
		pGraphics->DrawTexture(m_hSpikeTrap, SGD::Point(DialogBoxOne.left + 50, DialogBoxOne.top + 30));
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 6).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 7).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));

	}

	else if (m_bMainDialog)
	{
		heroPosition = { (float)((24 * 32) - m_ptWorldCam.x), (float)((16 * 32) - m_ptWorldCam.y) };
		if (m_bIcelandic)
		{
			TextPositionOne.x = DialogBoxOne.left + 180;
			TextPositionTwo.x = DialogBoxOne.left + 120;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 150;
			TextPositionTwo.x = DialogBoxOne.left + 120;
		}
		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hHero, heroPosition);
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition);
		pGraphics->DrawTexture(m_hFireTrap, SGD::Point(DialogBoxOne.left + 50, DialogBoxOne.top + 30));
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 8).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(7, 9).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));
	}

	else if (m_bChestDialog)
	{
		heroPosition = { (float)((20 * 32) - m_ptWorldCam.x), (float)((7 * 32) - m_ptWorldCam.y) };
		if (m_bIcelandic)
		{
			TextPositionOne.x = DialogBoxOne.left + 150;
			TextPositionTwo.x = DialogBoxOne.left + 120;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 110;
			TextPositionTwo.x = DialogBoxOne.left + 120;
		}
		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hHero, heroPosition);
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition);
		pGraphics->DrawTexture(m_hTutorialRune, SGD::Point(DialogBoxOne.left + 40, DialogBoxOne.top + 5), {}, {}, {}, { 0.2f, 0.18f });
		pFont->Render("Dialog", Game::GetInstance()->GetString(8, 1).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(8, 2).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));
	}

	else if (m_bSigmundDialog)
	{
		heroPosition = { (float)((16 * 32) - m_ptWorldCam.x), (float)((19 * 32) - m_ptWorldCam.y) };
		if (m_bIcelandic)
		{
			TextPositionOne.x = DialogBoxOne.left + 220;
		}
		else
			TextPositionOne.x = DialogBoxOne.left + 220;

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(m_hHero, heroPosition);
		pGraphics->DrawTexture(m_hDialogImg, portraitPosition);
		pFont->Render("Dialog", Game::GetInstance()->GetString(8, 3).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));

	}
}
