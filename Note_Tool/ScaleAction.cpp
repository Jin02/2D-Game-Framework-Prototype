#include "ScaleAction.h"


ScaleAction::ScaleAction(void)
{
	id = AV_ACT_SCALE;
}

ScaleAction::ScaleAction(float duration, float scale, ACTOPTION option)
{
	IntervalAction::Action(duration, option);
	id = AV_ACT_SCALE;
	m_deltaScale.x = scale;
	m_deltaScale.y = scale;
}

ScaleAction::ScaleAction(float duration, float scaleX, float scaleY, ACTOPTION option = AV_BY)
{
	IntervalAction::Action(duration, option);

	id = AV_ACT_SCALE;
	m_deltaScale.x = scaleX;
	m_deltaScale.y = scaleY;
}

ScaleAction::~ScaleAction(void)
{
}

void ScaleAction::Action(float duration, float scale, ACTOPTION option)
{
	IntervalAction::Action(duration, option);

	m_startScale = (*m_nowScale);

	m_deltaScale.x = scale - (option * m_startScale.x);
	m_deltaScale.y = scale - (option * m_startScale.y);
}

void ScaleAction::Action(float duration, float scaleX, float scaleY, ACTOPTION option = AV_BY)
{
	IntervalAction::Action(duration, option);

	m_startScale = (*m_nowScale);

	m_deltaScale.x = scaleX - (option * m_startScale.x);
	m_deltaScale.y = scaleY - (option * m_startScale.y);
}

void ScaleAction::system(float tick)
{
	m_nowScale->x = m_startScale.x + (m_deltaScale.x * tick);
	m_nowScale->y = m_startScale.y + (m_deltaScale.y * tick);
}

void ScaleAction::Connect(void *p)
{
	m_nowScale = (ScaleInfo*)p;
}

void ScaleAction::SetData()
{
	m_startScale = (*m_nowScale);

	m_deltaScale.x = m_deltaScale.x - (m_option * m_startScale.x);
	m_deltaScale.y = m_deltaScale.y - (m_option * m_startScale.y);
}