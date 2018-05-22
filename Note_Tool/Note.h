#pragma once

#include "Sprite.h"
#include "GraphicFont.h"
#include "Note_Info.h"

class CNote : public AVBase
{
	Sprite					*m_Sprite;

	float					m_tick;
	bool					m_isUse;

	bool					m_isTool;

public:
	CNote(void);
	~CNote(void);

public:
	void Create(AVTexture2D *Notetex2D, AVTexture2D *GFontTex2D);
	void Action(Note_Info *noteData);

public:
	virtual void Update();
	virtual void Render();

	void SetisMod(bool isTool);
};

