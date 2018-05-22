#include "DelayAction.h"


DelayAction::DelayAction(void)
{
	id = AV_ACT_DEALY;
}


DelayAction::~DelayAction(void)
{
}

DelayAction::DelayAction(float duration)
{
	IntervalAction::Action(duration, NULL);
	id = AV_ACT_DEALY;
}