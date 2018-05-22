#pragma once

#include "IntervalAction.h"
#include <d3dx9.h>
#include "Information.h"

class ScaleAction : public IntervalAction
{
private:
	ScaleInfo m_startScale;
	ScaleInfo m_deltaScale;

protected:
	ScaleInfo *m_nowScale;

public:
	ScaleAction(void);
	ScaleAction(float duration, float scale, ACTOPTION option);
	ScaleAction(float duration, float scaleX, float scaleY, ACTOPTION option);

	ScaleAction(ScaleAction *pAction) : IntervalAction(pAction)
	{
		m_startScale = pAction->m_startScale;
		m_deltaScale = pAction->m_deltaScale;
	}

	~ScaleAction(void);

private:
	virtual void system(float tick);

public:
	void Action(float duration, float scale, ACTOPTION option);
	void Action(float duration, float scaleX, float scaleY, ACTOPTION option);

	virtual void Connect(void *p);
	virtual void SetData();
};