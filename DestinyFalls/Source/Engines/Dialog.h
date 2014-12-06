#pragma once

#include <string>
using namespace std;

class Dialog
{
	string m_szMessageName;
	string m_szImageName;
	string m_szWords;

public:

	string GetName( void ){ return m_szMessageName; }
	string GetImageName( void ){ return m_szImageName; }
	string GetWords( void ){ return m_szWords; }

	void SetName( string messageName ){ m_szMessageName = messageName; }
	void SetImageName( string imageName ){ m_szImageName = imageName; }
	void SetWords( string messageWords ){ m_szWords = messageWords; }

	Dialog() = default;
	~Dialog() = default;
};

