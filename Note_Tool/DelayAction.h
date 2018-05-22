#pragma once

#include "IntervalAction.h"
#include <d3dx9.h>

class DelayAction : public IntervalAction
{
public:
	DelayAction(void);
	DelayAction(float duration);

	DelayAction(DelayAction *pAction) : IntervalAction(pAction)
	{
		//NULL
	}

	~DelayAction(void);

private:
	virtual void system(float tick)	{/*NULL*/}
	virtual void Connect(void *p)	{/*NULL*/}
	virtual void SetData()			{/*NULL*/}
};

