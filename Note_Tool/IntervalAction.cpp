#include "IntervalAction.h"

#define MIN(a, b) a < b ? a : b

IntervalAction::IntervalAction()
{
	m_isFirstTick   = true;	
	m_isActionsEnd  = true;
	m_option		= AV_BY;
}

IntervalAction::~IntervalAction(void)
{
}

void IntervalAction::Action(float duration, ACTOPTION option)
{
	m_duration		= duration;
	m_isActionsEnd	= false;
	m_isFirstTick	= true;
	m_option		= option;
}

void IntervalAction::step(float p)
{
	if( m_isActionsEnd ) return;

	if( m_isFirstTick )
	{
		m_isFirstTick = false;
		m_elapse = 0;
	}
	else m_elapse += p;

	float tick;
	
	if( (tick = MIN(1, m_elapse/m_duration)) == 1.f )
		m_isActionsEnd = true;

	system( tick );
}

bool IntervalAction::GetisAction()
{ 
	return m_isActionsEnd; 
}

void IntervalAction::ReStartAction()
{ 
	m_isFirstTick  = true; 
	m_isActionsEnd = false;
	m_option = AV_BY;
}