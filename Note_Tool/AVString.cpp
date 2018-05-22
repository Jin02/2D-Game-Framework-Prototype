#include "AVString.h"
#include "AVDirector.h"

AVString::AVString(void)
{
	m_Context = NULL;
	m_Color   = D3DCOLOR_ARGB(255,255,255,255);

	RECT rect = {0, 0, -1, -1};
	m_rect = rect;
}

AVString::~AVString(void)
{
}

void AVString::Update()
{
	//NULL
}

void AVString::Render()
{
	static LPD3DXFONT	font	= AVDirector::GetDiector()->GetApplication()->GetD3DFont();
	static LPD3DXSPRITE sprite	= AVDirector::GetDiector()->GetApplication()->GetD3DSprite();

	font->DrawText( sprite, 	m_Context, -1, &m_rect, D3DFMT_A8R8G8B8, m_Color);
}

void AVString::SetRect(AVRECT &rect)
{
	m_rect.left		= (long)(rect.x);
	m_rect.top		= (long)(rect.y);
	m_rect.right	= (long)(rect.x + rect.w);
	m_rect.bottom	= (long)(rect.y + rect.h);
}

void AVString::SetColor(D3DCOLOR color)
{
	m_Color = color;
}

AVRECT& AVString::GetRect()
{ 
	return AVRECT( m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}

D3DCOLOR AVString::GetColor()
{ 
	return m_Color;		
}

void AVString::SetText(wchar_t* str)
{	
	m_Context = str;	
}

wchar_t* AVString::GetText()
{ 
	return m_Context;		
}