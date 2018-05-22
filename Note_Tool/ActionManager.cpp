#include "ActionManager.h"
#include "AVDirector.h"

ActionManager::ActionManager()
{
	memset(&m_option,0,sizeof(OPTION));
	m_isAllEnd		= true;
}

ActionManager::ActionManager(
	D3DXVECTOR2 *vPosition, float *angle, 
	ScaleInfo *scale, float *opacity)
{
	this->Connect(vPosition, angle, scale, opacity);
	ActionManager();
}

ActionManager::~ActionManager(void)
{
}

void ActionManager::Connect(D3DXVECTOR2 *vPosition, float *angle, ScaleInfo *scale, float *opacity)
{
	m_vPosition = vPosition;
	m_angle		= angle;
	m_scale		= scale;
	m_opacity	= opacity;
}

void ActionManager::ActionUpdate()
{
	float tick = AVDirector::GetDiector()->GetTickTime();

	if( m_isAllEnd ) return;

	switch(m_option.method) {
	case ACT_SEQUENCE:	this->Sequence(tick);	return;
	case ACT_COINCIDE:	this->Coincide(tick);	return;
	case ACT_ALLOPTION:	this->TwoAction(tick);	return;
	case ACT_DEFAULT:	this->One(tick);			return;
	}
}

void ActionManager::Sequence(float tick)
{
	if( actionList[m_sequenceNum]->GetisAction() )		
	{
		if( (m_sequenceNum != actionList.size() - 1) )	
			actionList[++m_sequenceNum]->SetData();
		else{
			if( !(m_isAllEnd = RepeatisFull()) )
				ReStart();
			m_sequenceNum = 0;
		}
	}

	actionList[m_sequenceNum]->step(tick);
}

void ActionManager::Coincide(float tick)
{
	int cnt = 0;

	for( std::vector<IntervalAction*>::iterator iter = actionList.begin() ; iter != actionList.end(); iter++)
	{
		(*iter)->step(tick);			
		if( (*iter)->GetisAction() )		cnt++;
	}

	if(cnt == actionList.size())
		if( !(m_isAllEnd = RepeatisFull()) ) ReStart();
}

void ActionManager::One(float tick)
{
	actionList[0]->step(tick);
	if( actionList[0]->GetisAction() ){
		if( !(m_isAllEnd = RepeatisFull()) ) ReStart();
	}
}

void ActionManager::TwoAction(float tick)
{
	int cnt = 0;
	std::vector<IntervalAction*>::iterator iter;

	for( iter = two_ActionList[m_sequenceNum].begin();
		 iter != two_ActionList[m_sequenceNum].end(); iter++)
	{
		(*iter)->step(tick);			
		if( (*iter)->GetisAction() )		cnt++;
	}

	if(cnt == two_ActionList[m_sequenceNum].size())
	{
		if( m_sequenceNum != two_ActionList.size() - 1 )
		{
			m_sequenceNum++;
			for( std::vector<IntervalAction*>::iterator iter = two_ActionList[m_sequenceNum].begin(); iter != two_ActionList[m_sequenceNum].end(); iter++)	(*iter)->SetData();
		}

		else{ 
			if( !(m_isAllEnd = RepeatisFull()) ) ReStart();
			m_sequenceNum = 0;
		}
	}
}

void ActionManager::Action(IntervalAction *pAction, int playNum)
{
	Stop();
	actionList.push_back(Create(pAction));

	actionList[0]->SetData();

	m_option		= OPTION(ACT_DEFAULT, playNum);
	m_repeatNum		= 0;
	m_isAllEnd		= false;
}

void ActionManager::Actions(OPTION &option, IntervalAction *firstAction, ...)
{
	va_list				list;
	IntervalAction		*templateAction = firstAction;
	
	va_start( list, firstAction);
	Stop();

	while( templateAction != NULL )
	{
		actionList.push_back(Create(templateAction)); 
		templateAction = va_arg( list, IntervalAction* ); 
	}

	if(option.method == ACT_COINCIDE)
		for(std::vector<IntervalAction*>::iterator iter = actionList.begin() ; iter != actionList.end() ; iter++)		(*iter)->SetData();
	else
		actionList[0]->SetData();


	m_option		= option;
	m_isAllEnd		= false;
	m_sequenceNum	= 0;
	m_repeatNum		= 0;

	va_end(list);
}

void ActionManager::Two_OptionWithAction(int playNum, int Actionnum, std::vector<IntervalAction*> vector, ...)
{
	va_list				list;
	std::vector<IntervalAction*> _vector = vector;
	
	va_start( list, vector);
	Stop();

	two_ActionList.push_back(vector);

	for(int i=0; i<Actionnum-1; i++)
	{
		_vector = va_arg( list, std::vector<IntervalAction*> ); 
		two_ActionList.push_back(_vector); 
	}

	for(int i=0; i < two_ActionList[0].size(); i++)		
		two_ActionList[0][i]->SetData();

	m_option		= OPTION(ACT_ALLOPTION, playNum);
	m_isAllEnd		= false;
	m_sequenceNum	= 0;
	m_repeatNum		= 0;

	va_end(list);
}

IntervalAction* ActionManager::Create(IntervalAction *action)
{
	switch(action->id){
	case AV_ACT_MOVE:	return move_Create((MoveAction*)action);
	case AV_ACT_DEALY:	return Delay_Create((DelayAction*)action);
	case AV_ACT_FADE:	return fade_Create((FadeAction*)action);
	case AV_ACT_ROTAE:	return rotate_Create((RotateAction*)action);
	case AV_ACT_SCALE:	return scale_Create((ScaleAction*)action);
	}

	return NULL;
}

MoveAction* ActionManager::move_Create(MoveAction *action)
{
	MoveAction *tmpAction = new MoveAction(action);
	tmpAction->Connect((void*)m_vPosition);

	return tmpAction;
}

DelayAction* ActionManager::Delay_Create(DelayAction *action)
{
	return new DelayAction(action);
}

FadeAction* ActionManager::fade_Create(FadeAction *action)
{
	FadeAction *tmpAction = new FadeAction(action);
	tmpAction->Connect((void*)m_opacity);

	return tmpAction;
}

RotateAction* ActionManager::rotate_Create(RotateAction *action)	
{
	RotateAction *tmpAction = new RotateAction(action);
	tmpAction->Connect((void*)m_angle);

	return tmpAction;
}

ScaleAction* ActionManager::scale_Create(ScaleAction *action)
{
	ScaleAction *tmpAction = new ScaleAction(action);
	tmpAction->Connect((void*)m_scale);

	return tmpAction;
}

void ActionManager::Remove(std::vector<IntervalAction*> *vector)
{
	for(std::vector<IntervalAction*>::iterator iter = vector->begin() ; 	iter != vector->end() ; 	iter++)
	{
		if( (*iter) != NULL) delete (*iter);
	}

	vector->clear();
}

void ActionManager::Stop()
{
	if(m_option.method != ACT_ALLOPTION)	this->Remove(&actionList);

	else // ACT_ALLOPTION
	{
		for(int i=0; i < two_ActionList.size(); i++)		this->Remove(&two_ActionList[i]);		
		two_ActionList.clear();
	}
}

bool ActionManager::GetisRunning()
{
	return !m_isAllEnd;
}

bool ActionManager::RepeatisFull()
{
	if(++m_repeatNum == m_option.playNum )	
		return true;
	
	return false;
}

void ActionManager::ReStart()
{
	std::vector<IntervalAction*>::iterator iter;
	
	if( m_option.method != ACT_ALLOPTION )
	{
		actionList[0]->SetData();

		for(iter = actionList.begin(); iter != actionList.end(); iter++)
			(*iter)->ReStartAction();
	}
	else
	{
		for(int i = 0; i < two_ActionList.size(); i++)
		{
			for(iter = two_ActionList[i].begin(); iter != two_ActionList[i].end(); iter++)
			{
				(*iter)->SetData();
				(*iter)->ReStartAction();
			}
		}
	}

}

std::vector<IntervalAction*> ActionManager::TWO_COINCIDE(IntervalAction *Action, ...)
{
	va_list							list;
	IntervalAction					*templateAction = Action;
	std::vector<IntervalAction*>	vector;
	
	va_start( list, Action);

	while( templateAction != NULL )
	{
		vector.push_back(Create(templateAction)); 
		templateAction = va_arg( list, IntervalAction* ); 
	}

	va_end(list);

	return vector;
}
