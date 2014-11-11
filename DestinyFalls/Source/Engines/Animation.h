#pragma once

#include "Frame.h"
#include "..\..\SGD Wrappers\SGD_Handle.h"

#include <vector>
#include <string>
using namespace std;

class Animation
{

	vector<Frame> m_vFrames;
	string m_szName;
	string m_szNextAnimation;

	bool m_bLooping;

	int m_nImageID;

	SGD::HTexture m_hImage = SGD::INVALID_HANDLE;

public:
	Animation();
	~Animation();

	///////////////////////////////////////////////////////
	//ACCESSORS

	//Returns m_vFrames
	//	--Gives you the entire vector
	vector<Frame> GetFrameVector() { return m_vFrames; }

	//Returns a single frame from the m_vFrames vector at the specified index
	Frame GetFrame( int index ) { return m_vFrames[ index ]; }

	//Return m_szName
	string GetName() { return m_szName; }

	//Return m_szNextAnimation
	string GetNextAnimation() { return m_szNextAnimation; }

	//Return m_bLooping
	bool GetLooping() { return m_bLooping; }

	//Return m_nImageID
	int GetImageID() { return m_nImageID; }

	//Return m_hImage
	SGD::HTexture GetImage() { return m_hImage; }

	///////////////////////////////////////////////////////
	//MUTATORS

	//Set m_vFrames
	//	--Set the entire vector
	void SetFramesVector( vector<Frame> frames ) { m_vFrames = frames; }

	//Set a specific frame in the frames vector
	void SetFrame( int index , Frame frame ) { m_vFrames[ index ] = frame; }

	//Set m_szName
	void SetName( string name ){ m_szName = name; }

	//Set m_szNextAnimation
	void SetNextAnimation( string nextAnimation ) { m_szNextAnimation = nextAnimation; }

	//Set m_bLooping
	void SetLooping( bool loop ) { m_bLooping = loop; }

	//Set m_nImageID
	void SetImageID( int id ) { m_nImageID = id; }

	//Set m_hImage
	void SetImage( SGD::HTexture image ) { m_hImage = image; }

	///////////////////////////////////////////////////////
	//FUNCTIONS

	void AddFrame( Frame newFrame );
};

