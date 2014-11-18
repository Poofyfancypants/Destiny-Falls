#pragma once

#include "../../SGD Wrappers/SGD_Handle.h"
#include "../../SGD Wrappers/SGD_Color.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

#include <string>
#include <vector>

using namespace std;

class BitmapFont
{
public:
	BitmapFont(void) = default;
	~BitmapFont(void) = default;

	void Initialize(string path);
	void Terminate(void);

	void Draw(const char* output, SGD::Point position,
		float scale, SGD::Color color) const;

	bool LoadFontFile(string path);

	struct CharAttributes
	{
		int id;
		int x, y;
		int width, height;
		int Xoffset, Yoffest;
		int Xadvance;
		int page;
		int chnl;
		
		
		CharAttributes() : x(0), y(0), width(0), height(0), Xoffset(0), Yoffest(0), Xadvance(0){}
	};
	
		vector<CharAttributes*> Letters;

private:
	// image
	SGD::HTexture	m_hImage = SGD::INVALID_HANDLE;

	// cell data
	int				m_nCharWidth = 0;
	int				m_nCharHeight = 0;
	int				m_nNumRows = 0;
	int				m_nNumCols = 0;

	vector<CharAttributes*> m_vCharAtt;

	// font info
	char			m_cFirstChar = '\0';
	bool			m_bOnlyUppercase = false;
	int				m_nCharOffest = 0;
};

