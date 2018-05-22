#include "PVJudgment.h"
#include "SharedTexture2D.h"

PVJudgment::PVJudgment(void)
{
}


PVJudgment::~PVJudgment(void)
{
}

void PVJudgment::Init()
{
	m_Sprite[0].SetTexture( (*SharedTexture2D::GetsharedTexture2D()->GetTexture2D(0)->GetTexture()) );
	m_Sprite[1].SetTexture( (*SharedTexture2D::GetsharedTexture2D()->GetTexture2D(1)->GetTexture()) );

	for(int i=0; i<2; i++)
	{
		m_Sprite[i].SetScale(0.f);
		m_Sprite[i].SetanchorPoint(D3DXVECTOR2(0.5f, 0.5f));
		m_Sprite[i].SetColor(AVCOLOR(255,255,255,255));
	}

	m_Sprite[0].SetRect(0,0,64,64);
	m_Sprite[1].SetRect(0,0,80,80);
}

void PVJudgment::Action(D3DXVECTOR2 &vPosition, float duration)
{
	for(int i=0; i<2; i++)
	{
		m_Sprite[i].SetScale(0.f);
		m_Sprite[i].SetPosition(vPosition);		
		m_Sprite[i].SetOpacity(100);
	}

//	m_duration = duration;

	ScaleAction scale	= ScaleAction(duration, 1.0f, AV_TO);
	FadeAction  fadeOut = FadeAction(1.f, 0.f, AV_TO);

	for(int i=0; i<2; i++)
		m_Sprite[i].Actions(OPTION(ACT_SEQUENCE), &scale, &fadeOut, NULL);
}

void PVJudgment::Update()
{
	m_Sprite[0].Update();
	m_Sprite[1].Update();
}

void PVJudgment::Render()
{
	m_Sprite[0].Render();
	m_Sprite[1].Render();
}