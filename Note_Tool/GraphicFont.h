#pragma once

#include "Sprite.h"

class GraphicFont : public Sprite
{
	int		m_oneFontSize;
	int		m_distance;
	float	m_StartPosX;

	wchar_t m_content[15];

public:
	GraphicFont(void);
	GraphicFont(int one_Font_SizeW, int distance = 0);

	~GraphicFont(void);

public:
	virtual void Render();
	void SetFontSize(int one_Font_SizeW, int distance);
	void SetValue(int value);
	int GetValue();

	void SetPosition(D3DXVECTOR2& vPosition);
};

