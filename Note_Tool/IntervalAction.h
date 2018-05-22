#pragma once

enum
{
	AV_BY,
	AV_TO
};

enum ACTION_ENUM
{
	AV_ACT_MOVE,
	AV_ACT_ROTAE,
	AV_ACT_SCALE,
	AV_ACT_DEALY,
	AV_ACT_FADE,
	AV_ACT_MOVE_ROTATION
};

#define ACTOPTION bool

class IntervalAction
{
public:
	int		id;

private:
	bool	m_isFirstTick;

protected:
	float		m_elapse;
	float		m_duration;

	ACTOPTION	m_option;

	bool		m_isActionsEnd;

public:
	IntervalAction();
	
	template <typename Action>
	IntervalAction(Action *pAction)
	{
		m_isFirstTick	= pAction->m_isFirstTick;
		m_duration		= pAction->m_duration;
		m_option		= pAction->m_option;
		m_isActionsEnd	= pAction->m_isActionsEnd;
	}

	virtual ~IntervalAction(void);

protected:
	virtual void system(float tick) = 0;

public:
	void Action(float duration, ACTOPTION option);
	void step(float p);

	virtual void	Connect(void *p) = 0;
	bool			GetisAction();// { return m_isActionsEnd; }
//	unsigned int	GetDirection();//{ return m_Direction;	   }
	virtual void	SetData()		 = 0;
	void			ReStartAction();// { m_isFirstTick = isRe; }
};

