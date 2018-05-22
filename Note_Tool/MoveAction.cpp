#include "MoveAction.h"


MoveAction::MoveAction(void)
{
	id = AV_ACT_MOVE;
}

MoveAction::MoveAction(float duration, D3DXVECTOR2 vDeltaPos, ACTOPTION option)
{
	IntervalAction::Action(duration, option);

	id = AV_ACT_MOVE;
	m_vDeltaPos = vDeltaPos;
}

MoveAction::~MoveAction(void)
{
}

void MoveAction::Action(
	float duration, 
	D3DXVECTOR2 vDeltaPos, ACTOPTION option)
{
	IntervalAction::Action(duration, option);

	m_vStartPos = (*m_vNowPos);
	m_vDeltaPos = vDeltaPos - (option * m_vStartPos);
}

void MoveAction::system(float tick)
{
	*m_vNowPos = m_vStartPos + (m_vDeltaPos * tick);
}

void MoveAction::Connect(void *p)
{
	m_vNowPos = (D3DXVECTOR2*)p;
}

void MoveAction::SetData()
{
	m_vStartPos = (*m_vNowPos);
	m_vDeltaPos = m_vDeltaPos - (m_option * m_vStartPos);
}