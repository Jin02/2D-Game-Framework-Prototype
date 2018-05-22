#pragma once

#include "IntervalAction.h"
#include <d3dx9.h>

class FadeAction : public IntervalAction
{
private:
	float m_deltaOpacity;
	float m_startOpacity;

protected:
	float *m_nowOpacity;
	
public:
	FadeAction(void);
	FadeAction(float duration, float opacity, ACTOPTION option = AV_BY);

	FadeAction(FadeAction *pAction) : IntervalAction(pAction)
	{
		m_startOpacity = pAction->m_startOpacity;
		m_deltaOpacity = pAction->m_deltaOpacity;
	}

	~FadeAction(void);

private:
	virtual void system(float tick);

public:
	void Action(float duration, float opacity, ACTOPTION option = AV_BY);
	virtual void Connect(void *p);

	virtual void SetData();
};



