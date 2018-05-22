#include "RotateAction.h"

RotateAction::RotateAction(void)
{
	id = AV_ACT_ROTAE;
}

RotateAction::RotateAction(float duration, float radian, ACTOPTION option)
{
	IntervalAction::Action(duration, option);
	id = AV_ACT_ROTAE;
	m_deltaAngle	= radian;
}

RotateAction::~RotateAction(void)
{
}

void RotateAction::Action(float duration, float radian, ACTOPTION option)
{
	IntervalAction::Action(duration, option);

	m_startAngle = (*m_nowAngle);
	m_deltaAngle = radian - (option * m_startAngle);
}

void RotateAction::system(float tick)
{
	(*m_nowAngle) = m_startAngle + (m_deltaAngle * tick);

	if( (*m_nowAngle) > AV_DI(360) )	(*m_nowAngle) -= AV_DI(360);
	if( (*m_nowAngle) < AV_DI(0) )		(*m_nowAngle) += AV_DI(360);
}

void RotateAction::Connect(void *p)
{
	m_nowAngle = (float*)p;
}

void RotateAction::SetData()
{
	m_startAngle = (*m_nowAngle);
	m_deltaAngle = m_deltaAngle - (m_option * m_startAngle);
}