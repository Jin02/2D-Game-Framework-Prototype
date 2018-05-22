#pragma once

#include <d3dx9.h>
#include "AVBase.h"
#include "Information.h"

class AVString : public AVBase
{
protected:
	wchar_t					*m_Context;	

	RECT					m_rect;
	D3DCOLOR				m_Color;

public:
	AVString(void);
	~AVString(void);

	virtual void Update();
	virtual void Render();

	void SetRect(AVRECT &rect);
	void SetColor(D3DCOLOR color);

	AVRECT&		GetRect();
	D3DCOLOR	GetColor();

	void		SetText(wchar_t* str);
	wchar_t*	GetText();
};
