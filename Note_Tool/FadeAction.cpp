#include "FadeAction.h"


FadeAction::FadeAction(void)
{
	id = AV_ACT_FADE;
}

FadeAction::FadeAction(float duration, float opacity, ACTOPTION option)
{
	IntervalAction::Action(duration, option);
	id = AV_ACT_FADE;
	m_deltaOpacity  = opacity;
}

FadeAction::~FadeAction(void)
{
}

void FadeAction::Action(float duration, float opacity, ACTOPTION option)
{
	IntervalAction::Action(duration, option);

	m_startOpacity = (*m_nowOpacity);
	m_deltaOpacity = opacity - (option * m_startOpacity);
}

void FadeAction::system(float tick)
{
	(*m_nowOpacity) = m_startOpacity + (m_deltaOpacity * tick);
}

void FadeAction::Connect(void *p)
{
	m_nowOpacity = (float*)p;
}

void FadeAction::SetData()
{
	m_startOpacity = (*m_nowOpacity);
	m_deltaOpacity = m_deltaOpacity - (m_option * m_startOpacity);
}