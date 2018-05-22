#include "Judgment.h"
#include "SharedTexture2D.h"

#include "FadeAction.h"
#include "ScaleAction.h"

#include "AVDirector.h"

Judgment::Judgment(void)
{
	m_duration			= 0.f;
	m_longNoteTime		= 0.f;
	m_is_Long_ActionEnd	= true;
}

Judgment::~Judgment(void)
{
}

void Judgment::Init()
{
	m_Sprite[0].SetTexture( (*SharedTexture2D::GetsharedTexture2D()->GetTexture2D(0)->GetTexture()) );
	m_Sprite[1].SetTexture( (*SharedTexture2D::GetsharedTexture2D()->GetTexture2D(1)->GetTexture()) );

	for(int i=0; i<2; i++)
	{
		m_Sprite[i].SetScale(0.f);
		m_Sprite[i].SetanchorPoint(D3DXVECTOR2(0.5f, 0.5f));
		m_Sprite[i].SetColor(AVCOLOR(255,255,255,255));
	}
}

void Judgment::Action(int id, D3DXVECTOR2 &vPosition, float duration)
{
	AVCOLOR color;

	m_Sprite[0].SetRect(0,0,64,64);
	m_Sprite[1].SetRect(0,0,80,80);

	if( id == 0 )		color = AVCOLOR();
	else if( id == 1 )	color = AVCOLOR(255,255,128,0);
	else				color = AVCOLOR(255,rand()%255,rand()%255,rand()%255);

	for(int i=0; i<2; i++)
	{
		m_Sprite[i].SetScale(0.f);
		m_Sprite[i].SetPosition(vPosition);
		
		m_Sprite[i].SetColor(color);
	}

	m_duration = duration;

	if( id == 0 || id == 2)
		m_Sprite[0].Actions( OPTION(ACT_COINCIDE), &ScaleAction(0.6f, 1.0f, AV_TO), &FadeAction(0.7f, 0, AV_TO), NULL);
	
	else{
		m_Sprite[0].Actions( 
			OPTION(ACT_SEQUENCE, duration * 2 + 1 ),
		&ScaleAction(0.25f, 1.0f, AV_TO),
		&ScaleAction(0.25f, 0.8f, AV_TO), NULL);

		m_is_Long_ActionEnd = false;
	}
	m_Sprite[1].Actions( OPTION(ACT_COINCIDE), &ScaleAction(0.5f, 1.0f, AV_TO), &FadeAction(0.5f, 0, AV_TO), NULL);
}

void Judgment::Action(Note_Info* info)
{
	AVCOLOR color;

	m_Sprite[0].SetRect(0,0,64,64);
	m_Sprite[1].SetRect(0,0,80,80);

	if( info->actionID == 0 )		color = AVCOLOR();
	else if( info->actionID == 1 )	color = AVCOLOR(255,255,128,0);
	else				color = AVCOLOR(255,rand()%255,rand()%255,rand()%255);

	for(int i=0; i<2; i++)
	{
		m_Sprite[i].SetScale(0.f);
		m_Sprite[i].SetPosition(info->vTargetPos - 
			D3DXVECTOR2(m_Sprite[i].GetRect().right/2, 
			m_Sprite[i].GetRect().bottom/2) + D3DXVECTOR2(102,102));
		
		m_Sprite[i].SetColor(color);
	}

	m_duration = info->time;

	if( info->actionID == 0 || info->actionID == 2)
		m_Sprite[0].Actions( OPTION(ACT_COINCIDE), &ScaleAction(0.6f, 1.0f, AV_TO), &FadeAction(0.7f, 0, AV_TO), NULL);
	
	else{
		m_Sprite[0].Actions( 
			OPTION(ACT_SEQUENCE, m_duration * 2 + 1 ),
		&ScaleAction(0.25f, 1.0f, AV_TO),
		&ScaleAction(0.25f, 0.8f, AV_TO), NULL);

		m_is_Long_ActionEnd = false;
	}

	m_Sprite[1].Actions( OPTION(ACT_COINCIDE), &ScaleAction(0.5f, 1.0f, AV_TO), &FadeAction(0.5f, 0, AV_TO), NULL);
}

void Judgment::Update()
{
	static AVDirector *director = AVDirector::GetDiector();

	if( !m_is_Long_ActionEnd &&	m_duration && ( m_duration <= (m_longNoteTime += director->GetTickTime() ) ) )
	{
		m_Sprite[0].Stop();

		m_Sprite[0].Actions( OPTION(ACT_COINCIDE), 
			&ScaleAction(0.4f, 0.f, AV_TO), 
			&FadeAction(0.5f, 0, AV_TO), NULL );

		m_is_Long_ActionEnd = true;
		m_longNoteTime = 0.f;
	}

	for(int i=0; i<2; i++)
		m_Sprite[i].Update();
}

void Judgment::Render()
{
	for(int i=0; i<2; i++)
		m_Sprite[i].Render();
}