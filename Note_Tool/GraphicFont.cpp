#include "GraphicFont.h"


GraphicFont::GraphicFont(void)
{
}

GraphicFont::GraphicFont(int one_Font_SizeW, int distance)
{
	this->SetFontSize(one_Font_SizeW, distance);
}

GraphicFont::~GraphicFont(void)
{
}

void GraphicFont::SetFontSize(int one_Font_SizeW, int distance)
{
	m_oneFontSize = one_Font_SizeW;
	m_distance	  = distance;
}

void GraphicFont::SetValue(int value)
{
	wsprintf(m_content,L"%d",value);
}

void GraphicFont::Render()
{
	for(int i=0; m_content[i] != NULL; i++)
	{
		m_Rect.left  = (m_content[i] - '0') * m_oneFontSize;
		m_Rect.right = m_Rect.left + m_oneFontSize;
		AVTexture2D::m_vPosition.x = m_StartPosX + (i * m_oneFontSize) + (i*m_distance);
		Sprite::Render();
	}

	AVTexture2D::m_vPosition.x = m_StartPosX;
}

int GraphicFont::GetValue()
{
	return _wtoi(m_content);
}

void GraphicFont::SetPosition(D3DXVECTOR2& vPosition)
{
	AVTexture2D::SetPosition(vPosition);
	m_StartPosX = vPosition.x;
}