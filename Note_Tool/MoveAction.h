#pragma once

#include "IntervalAction.h"
#include <d3dx9.h>

class MoveAction : public IntervalAction
{
private:
	D3DXVECTOR2 m_vStartPos;
	D3DXVECTOR2 m_vDeltaPos;

protected:
	D3DXVECTOR2 *m_vNowPos;

public:
	MoveAction(void);
	MoveAction(float duration, D3DXVECTOR2 vDeltaPos, ACTOPTION option = AV_BY);

	MoveAction(MoveAction *pAction) : IntervalAction(pAction)
	{
		m_vStartPos		= pAction->m_vStartPos;
		m_vDeltaPos		= pAction->m_vDeltaPos;

//		IntervalAction::IntervalAction(pAction);
	}
	
	~MoveAction(void);

private:
	virtual void system(float tick);

public:
	void Action(float duration, D3DXVECTOR2 vDeltaPos, ACTOPTION option = AV_BY);
	virtual void Connect(void *p);
	virtual void SetData();
	//IntervalAction 의 Step함수를 호출하여 사용
};