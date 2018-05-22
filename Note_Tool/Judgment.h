#pragma once

#include "Sprite.h"
#include "Note_Info.h"

class IntervalAction;

enum Note
{
	NOTE_ID_NORMAL,
	NOTE_ID_LONG
};

class Judgment : public AVBase
{
	float					m_duration;
	Sprite				    m_Sprite[2];

	float					m_longNoteTime;
	bool					m_is_Long_ActionEnd;

public:
	Judgment(void);
	~Judgment(void);

	void Init();
	void Action(int id, D3DXVECTOR2 &vPosition, float duration = 0.f);
	void Action(Note_Info* info);

	virtual void Update();
	virtual void Render();
};
