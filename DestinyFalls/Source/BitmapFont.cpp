#include "stdafx.h"
#include "BitmapFont.h"

#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <ctype.h>
#include <cassert>
#include <fstream>
#include "TinyXML\tinystr.h"
#include "TinyXML\tinyxml.h"

void BitmapFont::Initialize(string path)
{
	m_hImage = SGD::GraphicsManager::GetInstance()->LoadTexture(path.c_str());
}

void BitmapFont::Terminate(void)
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hImage);
}

void BitmapFont::Draw(const char* output, SGD::Point position, float scale, SGD::Color color) const
{
	// Validate the image
	assert(m_hImage != SGD::INVALID_HANDLE && "BitmapFont::Draw - image was not loaded");
	// Validate the parameter
	assert(output != nullptr && "BitmapFont::Draw - string cannot be null");

	// Is this string invisible?
	if (output[0] == '\0'			// string is empty?
		|| scale == 0.0f			// scale is invisible?
		|| color.alpha == 0)		// color is invisible?
		return;

	// Store the starting X position for newlines
	float colStart = position.x;

	// Iterate through the characters in the string
	for (int i = 0; output[i]; i++)
	{
		// Get the current character
		char ch = output[i];

		// Check for whitespace
		if (ch == ' ')
		{
			// Move to the next position
			position.x += m_nCharWidth * scale;
			continue;
		}

		if (m_bOnlyUppercase == true)
		{
			ch = toupper(ch);
		}

		// Calculate the tile ID for this character
		int id = ch - m_cFirstChar;

		// Calculate the source rect for that glyph
		SGD::Rectangle cell;
		cell.left = float((id % m_nNumCols) * m_nCharWidth);
		cell.top = float((id / m_nNumCols) * m_nCharHeight);
		cell.right = cell.left + m_nCharWidth;
		cell.bottom = cell.top + m_nCharHeight;

		// Draw the character
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(m_hImage, position, cell, 0.0f, {}, color, { scale, scale });

		// Move to the next position
		position.x += (int)(m_nCharWidth * scale);
	}
}

bool BitmapFont::LoadFontFile(string path)
{
	assert(path.c_str() != nullptr);

	TiXmlDocument doc;

	if (doc.LoadFile(path.c_str()) == false)
	{
		return false;
	}

	TiXmlElement* pFont = doc.RootElement();

	if (pFont == nullptr)
	{
		return false;
	}

	while (pFont != nullptr)
	{
		TiXmlElement* chars = pFont->FirstChildElement();

		if (chars == nullptr)
		{
			return false;
		}

		TiXmlElement* pChar = chars->FirstChildElement();

		while (pChar != nullptr)
		{
			CharAttributes* x = new CharAttributes;
			pChar->Attribute("id", &x->id);
			pChar->Attribute("x", &x->x);
			pChar->Attribute("y", &x->y);
			pChar->Attribute("width", &x->width);
			pChar->Attribute("height", &x->height);
			pChar->Attribute("xoffset", &x->Xoffset);
			pChar->Attribute("yoffset", &x->Yoffest);
			pChar->Attribute("xadvance", &x->Xadvance);
			pChar->Attribute("page", &x->page);
			pChar->Attribute("chnl", &x->chnl);

			Letters.push_back(x);

			pChar = pChar->NextSiblingElement();
		}




	}


}