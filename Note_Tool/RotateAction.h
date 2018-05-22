#pragma once

#include "IntervalAction.h"
#include <d3dx9.h>

#define AV_DI(degree) degree * (D3DX_PI/180)

class RotateAction : public IntervalAction
{
private:
	float m_startAngle;
	float m_deltaAngle;

protected:
	float *m_nowAngle;

public:
	RotateAction(void);
	RotateAction(float duration, float radian, ACTOPTION option = AV_BY);

	RotateAction(RotateAction *pAction) : IntervalAction(pAction)
	{
		m_startAngle = pAction->m_startAngle;
		m_deltaAngle = pAction->m_deltaAngle;
	}

	~RotateAction(void);

private:
	virtual void system(float tick);

public:
	void Action(float duration, float radian, ACTOPTION option = AV_BY);
	virtual void Connect(void *p);

	virtual void SetData();
};

