#pragma once

#include <string>
using namespace std;

class AnimationTimeStamp
{

private:
	string m_szCurrentAnimation;
	int m_nCurrentFrame = 0;
	float m_fTimeOnFrame = 0.0f;


public:
	AnimationTimeStamp();
	~AnimationTimeStamp();

	///////////////////////////////////////////////////////
	//ACCESSORS

	//return m_szCurrentAnimation
	string GetCurrentAnimation() { return m_szCurrentAnimation; }
	//return m_nCurrentFrame
	int GetCurrentFrame() { return m_nCurrentFrame; }

	//return m_fTimeOnFrame
	float GetTimeOnFrame() { return m_fTimeOnFrame; }

	///////////////////////////////////////////////////////
	//MUTATORS

	//set m_szCurrentAnimation
	void SetCurrentAnimation( string currentAnimation ) { m_szCurrentAnimation = currentAnimation; }

	//set m_nCurrentFrame
	void SetCurrentFrame( int currentFrame ) { m_nCurrentFrame = currentFrame; }

	//set m_fTimeOnFrame
	void SetTimeOnFrame( float timeOnFrame ) { m_fTimeOnFrame = timeOnFrame; }

	///////////////////////////////////////////////////////
	//FUNCTIONS

};

