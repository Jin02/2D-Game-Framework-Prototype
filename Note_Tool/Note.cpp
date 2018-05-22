#include "Note.h"
#include "SharedTexture2D.h"
#include "AVDirector.h"
#include "Scn_Test.h"

float Radian_Between_Two_Points(D3DXVECTOR2 &v1, D3DXVECTOR2 &v2){

	float a = atan2( v2.y - v1.y ,v2.x - v1.x );
	float b = a * 180.f / D3DX_PI;

	return a;
}

CNote::CNote(void)
{
	m_isUse = false;
}

CNote::~CNote(void)
{
	SAFE_DELETE(m_Sprite);
}

void CNote::Create(AVTexture2D *Notetex2D, AVTexture2D *GFontTex2D)
{
	m_Sprite = new Sprite;
	m_Sprite->SetTexture( *Notetex2D->GetTexture() );
	m_Sprite->SetRect(0,0,64,10);

}

void CNote::Action(Note_Info *noteData)
{
	float radian;
	AVCOLOR color;

	m_Sprite->SetanchorPoint(D3DXVECTOR2(0.f, 0.5f));
	m_Sprite->SetScale(1.f);

	if( noteData->actionID == 0 )		color = AVCOLOR();
	else if( noteData->actionID == 1 )	color = AVCOLOR(255,255,128,0);
	else								color = AVCOLOR(255,0,255,0);

	m_Sprite->SetColor(color);
	radian = Radian_Between_Two_Points( noteData->vStartPos 	 + D3DXVECTOR2(102, 102), noteData->vTargetPos + D3DXVECTOR2(102, 102)) + AV_DI(180);

	m_Sprite->SetAngle( radian );

	m_Sprite->SetPosition(noteData->vStartPos + D3DXVECTOR2(102, 102) - D3DXVECTOR2(64*cos(radian), 64*sin(radian)));
	m_Sprite->Actions( OPTION(ACT_COINCIDE), &MoveAction( noteData->arriveTime - noteData->startTime, noteData->vTargetPos + D3DXVECTOR2(102, 102), AV_TO),	&ScaleAction(noteData->arriveTime - noteData->startTime, 0.f,1.f,AV_TO), NULL);

	m_isUse = true;
	m_tick	= 0.f;
}

void CNote::Update()
{
	static Scn_Test *scn = (Scn_Test*)AVDirector::GetDiector()->GetScene();

	if(m_Sprite->GetisRunning() == false)
	{
		if(m_isUse == true)
		{ 
			m_isUse = false;
			if(m_isTool)
				scn->JudgmentPlay(); 
		}

		return;
	}

	if( m_tick <= 0.5f )
		m_tick += AVDirector::GetDiector()->GetTickTime();
	else{
		m_tick = 0.0f;
	}

	m_Sprite->Update();
}

void CNote::Render()
{
	if( m_isUse == false ) return;

	m_Sprite->Render();
}

void CNote::SetisMod(bool isTool)
{
	m_isTool = isTool;
}