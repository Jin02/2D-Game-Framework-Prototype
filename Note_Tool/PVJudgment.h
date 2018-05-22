#pragma once

#include "Sprite.h"

class IntervalAction;

class PVJudgment : public AVBase
{
private:
	Sprite					m_Sprite[2];


public:
	PVJudgment(void);
	~PVJudgment(void);

	void Init();
	void Action(D3DXVECTOR2 &vPosition, float duration);

	virtual void Update();
	virtual void Render();
};

