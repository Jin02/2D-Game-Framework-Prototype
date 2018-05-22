#pragma once

#include "FadeAction.h"
#include "MoveAction.h"
#include "RotateAction.h"
#include "ScaleAction.h"
#include "DelayAction.h"

#include <stdarg.h>
#include <vector>

#define INFINITY -1

enum ACT_METHOD
{
	ACT_DEFAULT,
	ACT_SEQUENCE,
	ACT_COINCIDE,
	ACT_ALLOPTION
};


typedef struct OPTION
{
	ACT_METHOD method;
	int playNum;

	OPTION(const ACT_METHOD _method=ACT_DEFAULT, const unsigned int _playNum=1)
	{
		method = _method;
		playNum = _playNum;
	}

}OPTION;

class ActionManager
{
	D3DXVECTOR2		*m_vPosition;
	float			*m_angle;
	ScaleInfo		*m_scale;
	float	*m_opacity;

	OPTION			m_option;
	bool			m_isAllEnd;
	
	int				m_sequenceNum;
	int				m_repeatNum;

	std::vector<IntervalAction*>				actionList;
	std::vector<std::vector<IntervalAction*>>	two_ActionList;

protected:
	void ActionUpdate();
	void Connect(D3DXVECTOR2 *vPosition, float *angle, ScaleInfo *scale, float *opacity);

public:
	ActionManager();
	ActionManager(D3DXVECTOR2 *vPosition, float *angle, ScaleInfo *scale, float *opacity);
	~ActionManager(void);

private:
	void Sequence(float tick);
	void Coincide(float tick);
	void One(float tick);
	void TwoAction(float tick);

	void Remove(std::vector<IntervalAction*> *vector);

	bool RepeatisFull();

private:
	MoveAction*		move_Create(MoveAction *action);
	DelayAction*	Delay_Create(DelayAction *action);
	FadeAction*		fade_Create(FadeAction *action);
	RotateAction*	rotate_Create(RotateAction *action);
	ScaleAction*	scale_Create(ScaleAction *action);

public:
	IntervalAction*	Create(IntervalAction *action);
	void Action(IntervalAction *pAction, int playNum = 1);
	void Actions(OPTION &option, IntervalAction *firstAction, ...);

	void Two_OptionWithAction(int playNum, int Actionnum, std::vector<IntervalAction*> vector, ...);	
	std::vector<IntervalAction*> TWO_COINCIDE(IntervalAction *Action, ...);						

	bool GetisRunning();
	void Stop();
	void ReStart();
};
