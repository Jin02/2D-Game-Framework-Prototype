#include "RotationMove.h"


RotationMove::RotationMove(void)
{
	id = AV_ACT_MOVE_ROTATION;
}


RotationMove::~RotationMove(void)
{
}

RotationMove::RotationMove(float duration, float vDeltaAngle, D3DXVECTOR2 &anchorPoint, ACTOPTION option)
{
	IntervalAction::Action(duration, option);
	id = AV_ACT_MOVE_ROTATION;
	m_vDeltaAngle = vDeltaAngle;
	
}

void RotationMove::system(float tick)
{
}

void RotationMove::Action(float duration, float vDeltaAngle, D3DXVECTOR2 &anchorPoint, ACTOPTION option)
{
	IntervalAction::Action(duration, option);
	m_vStartPos = (*m_vNowPos);
}

void RotationMove::Connect(void *p)
{
}

void RotationMove::SetData()
{
}