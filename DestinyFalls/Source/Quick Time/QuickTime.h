#pragma once

#include <vector>

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

	string m_sAlert = "Prepare for QuickTime!";
	unsigned int m_unlength = 0;
	unsigned int m_unNumCorrect = 0;
	unsigned int m_uncounter = 0;
	float m_fSeconds = 0.0f;
	float m_fAlertTimer = 2.0f;
	bool m_bqtOver = false;
	bool m_bShowAlert = true;

	

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

	void Update( float elapsedTime );
	void Render();

	SGD::Key m_kLastKeyPressed = SGD::Key::None;

};

