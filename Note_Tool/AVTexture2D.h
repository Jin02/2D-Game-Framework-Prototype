#pragma once

#include <d3dx9.h>
#include "AVBase.h"
#include "Information.h"

#pragma warning (disable:4927)

class AVTexture2D : public AVBase
{
protected:
	LPDIRECT3DTEXTURE9		m_Texture;
	D3DXIMAGE_INFO			m_Info;

	D3DXVECTOR2				m_vPosition;
	AVCOLOR					m_Color;

	RECT					m_Rect;

public:
	AVTexture2D(void);
	virtual ~AVTexture2D(void);

	void				CreateTexture(wchar_t *path);

	virtual void		Render();
	virtual void		Update();

	void				SetPosition(D3DXVECTOR2& vPosition)	;
	void				SetColor(AVCOLOR& color);

	void				SetRect(int x, int y, int w, int h);
	void				SetTexture(LPDIRECT3DTEXTURE9 Texture);

	D3DXVECTOR2&		GetPosition();
	AVCOLOR&			GetColor();

	LPDIRECT3DTEXTURE9* GetTexture();
	D3DXIMAGE_INFO&		GetTextureInfo();
	RECT&				GetRect();
};

