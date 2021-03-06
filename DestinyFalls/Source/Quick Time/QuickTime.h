#pragma once

#include <vector>

#include "../../SGD Wrappers/SGD_Handle.h"
#include "../../SGD Wrappers/SGD_Key.h"
#include <string>
using namespace std;

class QuickTime
{
private:
	std::vector<SGD::Key> m_vOutput;
	std::vector<SGD::Key> m_vInput;
	std::vector<SGD::Key> m_vKeys;

	string m_sInput = "";
	string m_sOutput = "";
	
	string m_sRenderInput = "";
	string m_sRenderOutput = "";

	string m_sAlert = "Prepare for QuickTime!";
	unsigned int m_unlength = 0;
	unsigned int m_unNumCorrect = 0;
	unsigned int m_uncounter = 0;
	float m_fSeconds = 0.0f;
	float m_fAlertTimer = 1.0f;
	float m_fLetterTimer = 2.0f;

	bool m_bqtOver = false;
	bool m_bShowAlert = true;

	unsigned int m_unLastPlayed = 0;	
	unsigned int m_unCurrentSet = 0;
	int m_nLastSet = 0;

	SGD::HTexture m_hScroll = SGD::INVALID_HANDLE;
	SGD::HTexture m_hArcadeButtons = SGD::INVALID_HANDLE;


public:
	QuickTime();
	~QuickTime();
	
	//accessors
	unsigned int GetLength(){ return m_unlength; }
	unsigned int GetNumCorrect( void ){ return m_unNumCorrect; }
	bool GetIsOver( void ){ return m_bqtOver; }
	

	//mutators
	void SetLength(unsigned int x);
	void SetNumCorrect( unsigned int numCorrect ){ m_unNumCorrect = numCorrect; }
	void SetIsOver( bool isOver ){ m_bqtOver = isOver; }

	void GenerateRandomLetter();
	void AddGuess(SGD::Key x);
	void ChangeRenderSet( int set );
	void Update( float elapsedTime );
	void Render();

	SGD::Key m_kLastKeyPressed = SGD::Key::None;

};

