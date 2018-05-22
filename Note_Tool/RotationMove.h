#pragma once

#include "intervalaction.h"
#include <d3dx9.h>

class RotationMove :
	public IntervalAction
{
private:
	D3DXVECTOR2 m_vStartPos;
	float		m_vDeltaAngle;

protected:
	D3DXVECTOR2 *m_vNowPos;

public:
	RotationMove(void);
	RotationMove(float duration, float vDeltaAngle, D3DXVECTOR2 &anchorPoint, ACTOPTION option = AV_BY);

	RotationMove(RotationMove *pAction) : IntervalAction(pAction)
	{
		m_vStartPos   = pAction->m_vStartPos;
		m_vDeltaAngle = pAction->m_vDeltaAngle;
	}

	~RotationMove(void);

private:
	virtual void system(float tick);

public:
	void Action(float duration, float vDeltaAngle, D3DXVECTOR2 &anchorPoint, ACTOPTION option = AV_BY);
	virtual void Connect(void *p);
	virtual void SetData();

};

