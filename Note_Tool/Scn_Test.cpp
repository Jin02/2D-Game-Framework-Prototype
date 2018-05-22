#include "Scn_Test.h"
#include "Scn_Test2.h"
#include "AVDirector.h"
#include "FileOpenManager.h"
#include "SharedTexture2D.h"

#define DEVICE_POSITION(x, y) D3DXVECTOR2(x-102, y-102)

float Distance2D(D3DXVECTOR2 &P1, D3DXVECTOR2 &P2)
{
	return sqrt( pow(P2.x - P1.x, 2) + pow(P2.y - P1.y, 2) );
}

Scn_Test::Scn_Test(void)
{
	m_Sound			 = NULL;
	m_isPlayStart	 = false;
	m_Interface		 = NULL;
	m_isTwoPhase	 = false;
	m_isShiftKeyDown = false;
	m_judNum		 = 0;
	m_isShiftClick	 = false;
	m_isTotalPlay	 = false;
}

Scn_Test::~Scn_Test(void)
{
	this->ChangeScene(new Scn_Test, true);
}

void Scn_Test::Init()
{
	m_screenArea = new Sprite;
	m_screenArea->CreateTexture(L"Resource/ScreenArea.png");
	m_screenArea->SetPosition(D3DXVECTOR2(100, 100));
	m_screenArea->SetanchorPoint(D3DXVECTOR2(0.f, 0.f));

	addObject(m_screenArea);

	m_Sound = new SoundPlayer;

	m_noteNum = new GraphicFont(16);
	m_noteNum->CreateTexture(L"Resource/Num.png");
	m_noteNum->SetValue(0);
	m_noteNum->SetPosition(D3DXVECTOR2(620,15));

	addObject(m_noteNum);

	m_whatNoteNum = new AVString;
	m_whatNoteNum->SetText(L"Note Total Number : ");
	m_whatNoteNum->SetRect(AVRECT(370,00,300,50));

	addObject(m_whatNoteNum);

	m_noteMax = 0;

	SharedTexture2D::GetsharedTexture2D()->addFile(L"Resource/Judgment_1_1.png", IMG_JUD_1_1);
	SharedTexture2D::GetsharedTexture2D()->addFile(L"Resource/Judgment_1_2.png", IMG_JUD_1_2);
	SharedTexture2D::GetsharedTexture2D()->addFile(L"Resource/Note.png", IMG_NOTE);
	SharedTexture2D::GetsharedTexture2D()->addFile(L"Resource/Num.png", IMG_GRAPHIC_NUM);

	for(int i=0; i<SCREEN_NOTE_MAX; i++)
	{
		m_Jud[i].Init();
		addObject(&m_Jud[i]);
	}

	for(int i=0; i<SCREEN_NOTE_MAX*2; i++)
	{
		m_Note[i].Create(SharedTexture2D::GetsharedTexture2D()->GetTexture2D(IMG_NOTE),
			SharedTexture2D::GetsharedTexture2D()->GetTexture2D(IMG_GRAPHIC_NUM));
		m_Note[i].SetisMod(true);
		addObject( &m_Note[i] );
	}

	m_Interface = new NoteInterface;

	m_countString = new AVString;
	m_countString->SetText(L"Play Count :");
	m_countString->SetRect(AVRECT(-20,0,200,50));

	addObject(m_countString);

	m_PlayCount = new GraphicFont(16);
	m_PlayCount->CreateTexture(L"Resource/Num.png");
	m_PlayCount->SetPosition(D3DXVECTOR2(145,15));
	m_PlayCount->SetValue(5);

	addObject(m_PlayCount);

	m_vStartPosition = D3DXVECTOR2(0,0);

	
	sprite.CreateTexture(L"Resource/Sun.png");
	sprite.SetanchorPoint(D3DXVECTOR2(0.5f, 0.5f));
	sprite.SetPosition(D3DXVECTOR2(0.f, 0.f));
//	sprite.Action(&RotateAction(30.f, AV_DI(360),AV_TO));
	sprite.Actions(OPTION(ACT_SEQUENCE,1),&RotateAction(30.f, AV_DI(360),AV_TO),NULL);
	addObject(&sprite);
}

void Scn_Test::Loop()
{
	static float time = 5.f;
	static bool isPlay = false;
	static bool isOne = false;

	if(m_Sound == NULL) return;

	if( m_isPlayStart == true )
	{
		if( time >= 0.f )			m_PlayCount->SetValue((int)(time -= AVDirector::GetDiector()->GetTickTime()));
		else{ if( !isPlay ) { isPlay = true; m_Sound->Play(true); }	}

		if( m_Sound->GetisSoundEnd() == true )
		{
			if(isOne) return;

			RECT rect;
			m_Interface->Interface_Create(m_noteMax);
			GetWindowRect( *AVDirector::GetDiector()->GetApplication()->GetHwnd(), &rect);
			m_Interface->Set_Interface_Position(D3DXVECTOR2(rect.right, rect.top));
			InterfaceDataSet(0);

			m_isPlayStart = false;
			m_isTwoPhase  = true;
			isOne		  = true;
		}

		return;
	}

	if( m_isTotalPlay )
	{
		if( m_total1 < m_noteMax && m_NoteData[m_total1].startTime <= (float)m_Sound->GetPosition() )
			m_Note[m_total1%(SCREEN_NOTE_MAX*2)].Action(&m_NoteData[m_total1++]);
	}
}

void Scn_Test::Mouse(D3DXVECTOR2 &vPosition, int Left, int Right)
{
	if(m_isPlayStart==false)
	{
		if(m_isTwoPhase == false)
			return;
		else
		{
			if(m_Sound->GetisPlay())
				return;
		}
	}
	
	vPosition = DEVICE_POSITION(vPosition.x, vPosition.y);

	if( Left != AV_MOUSE_DOWN ) return;

	if( m_isTwoPhase == false )
	{
		if( m_isShiftKeyDown && m_isShiftClick == false)
		{
			m_vShiftPos    = vPosition;
			m_isShiftClick = true;

			return;
		}

		m_NoteData[m_noteMax].vTargetPos = vPosition;
		m_NoteData[m_noteMax].arriveTime	= (float)m_Sound->GetPosition();

		if( m_noteMax != 0 )
			m_NoteData[m_noteMax].startTime	= m_NoteData[m_noteMax-1].arriveTime;

		m_NoteData[m_noteMax++].vStartPos = m_vStartPosition;
		m_noteNum->SetValue(m_noteMax);

		m_vStartPosition = vPosition;
	}
	else m_Interface->SetStartPosition(vPosition);

	m_Jud[m_judNum++%10].Action(0, D3DXVECTOR2(102,102) + vPosition);
}

void Scn_Test::MouseMove(D3DXVECTOR2 &vPosition)
{
	vPosition = DEVICE_POSITION(vPosition.x, vPosition.y);

	if( !m_isPlayStart ) return;

	if( Distance2D( m_vShiftPos, vPosition) >= 50 
		&& m_isShiftKeyDown && m_isShiftClick)
	{
		m_NoteData[m_noteMax++] = Note_Info(
			m_vShiftPos, 
			vPosition,
			(float)m_Sound->GetPosition() - 0.3f,
			(float)m_Sound->GetPosition(),
			NOTETYPE_SPECIAL);

		m_noteNum->SetValue(m_noteMax);
		m_vShiftPos = vPosition;

		m_Jud[m_judNum++%10].Action(NOTETYPE_SPECIAL, D3DXVECTOR2(102,102) + vPosition);
	}
}

void Scn_Test::KeyBoard(bool *push, bool *up)
{
#define PAUSE false
#define PLAY  true	

	static bool _switch = false;

	if( push[VK_SPACE] )
	{
		if( !_switch ){
			m_Sound->Pause();
			_switch = PLAY;
		}

		else{
			m_Sound->Play(true);
			_switch = PAUSE;
		}
	}

	if( push[VK_SHIFT] )
		m_isShiftKeyDown = true;

	if( up[VK_SHIFT] )
	{
		m_isShiftKeyDown = false;
		m_isShiftClick	 = false;
	}
}

LRESULT WINAPI Scn_Test::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND: 
		rc_Menu(wParam, hWnd);
		break;
	case WM_MOVE:
		if(m_Interface == NULL) break;

		RECT rect;
		GetWindowRect( *AVDirector::GetDiector()->GetApplication()->GetHwnd(), &rect);
		m_Interface->Set_Interface_Position(D3DXVECTOR2(rect.right, rect.top));
		break;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

void Scn_Test::End()
{
	deleteAllObject();

	SAFE_DELETE(m_whatNoteNum);
	SAFE_DELETE(m_screenArea);
	SAFE_DELETE(m_Sound);
	SAFE_DELETE(m_noteNum);
	SAFE_DELETE(m_Interface);
	SAFE_DELETE(m_PlayCount);
	SAFE_DELETE(m_countString);

}

void Scn_Test::rc_Menu(WPARAM &wParam, HWND &hWnd)
{
	static FileOpenManager *fom = FileOpenManager::GetFOM();

	switch(LOWORD(wParam))
	{
	case ID_SOUND_LOAD:
		fom->OpenToDialog(wParam, hWnd);
		m_Sound->Create(fom->GetPath());
		break;

	case ID_NOTE_LOAD:
		this->LoadNoteData();
		m_isTwoPhase = true;
		break;

	case ID_NOTE_SAVE:
		this->SaveNoteData();
		break;

	case ID_TOOLRESET:
		AVDirector::GetDiector()->changeToState(AV_STATE_END);
		break;

	case ID_SOUND_PLAY:
		if(m_isTwoPhase)
		{ 
			m_Sound->SetPosition(0);
			m_Sound->Play(true); 
			//			break; 
		}
		m_isPlayStart = true;
		break;

	case ID_SOUND_STOP:
		m_Sound->Stop();
		break;

	case ID_SOUND_PAUSE:
		m_Sound->Pause();
		break;
	}
}

void Scn_Test::NoteDataSet(int num)
{
	m_NoteData[num].arriveTime	= m_Interface->GetArriveTime();
	m_NoteData[num].startTime	= m_Interface->GetArriveTime() - m_Interface->GetMoveTime();
	m_NoteData[num].vStartPos	= m_Interface->GetStartPosition();
	m_NoteData[num].vTargetPos	= m_Interface->GetArrivePosition();
	m_NoteData[num].actionID	= m_Interface->GetNoteType();
	m_NoteData[num].time		= m_Interface->GetDuration();
}

void Scn_Test::InterfaceDataSet(int num)
{
	m_Interface->SetArriveTime(m_NoteData[num].arriveTime);
	m_Interface->SetArrivePosition(m_NoteData[num].vTargetPos);
	m_Interface->SetStartPosition(m_NoteData[num].vStartPos);
	m_Interface->SetMoveTime( m_NoteData[num].arriveTime - m_NoteData[num].startTime );

	m_Interface->SetNoteType(m_NoteData[num].actionID);
	m_Interface->SetDuration(m_NoteData[num].time);
}

void Scn_Test::NotePlay(int num)
{
	static int _num = 0;
	m_Note[_num++%(SCREEN_NOTE_MAX*2)].Action(&m_NoteData[num]);
//	m_pvJud[_num++%SCREEN_NOTE_MAX].Action;
	float deltaTime		 = m_NoteData[num].arriveTime - m_NoteData[num].startTime;
}

void Scn_Test::JudgmentPlay()
{
	static int _num = 0;
	int type;// = m_Interface->GetNoteType();
	D3DXVECTOR2 vTartget;// = m_Interface->GetArrivePosition() + D3DXVECTOR2(102, 102);
	float duration;// = m_Interface->GetDuration();

	if((m_Sound->GetisSoundEnd()==false) && m_isTwoPhase)
	{
		type = m_NoteData[m_total2].actionID;
		vTartget = m_NoteData[m_total2].vTargetPos + D3DXVECTOR2(102, 102);
		duration = m_NoteData[m_total2].arriveTime - m_NoteData[m_total2].startTime;
		m_total2++;
	}
	else
	{
		type = m_Interface->GetNoteType();
		vTartget = m_Interface->GetArrivePosition() + D3DXVECTOR2(102, 102);
		duration = m_Interface->GetDuration();
	}

	m_Jud[_num++%SCREEN_NOTE_MAX].Action(type,vTartget,duration);
}

void Scn_Test::SaveNoteData()
{
	if(FileOpenManager::GetFOM()->OpenToDialog(
		ID_NOTE_SAVE, 
		*(AVDirector::GetDiector()->GetApplication()->GetHwnd())) == 0)
		return;
	FILE *fp = _wfopen(FileOpenManager::GetFOM()->GetPath(),L"wb");

	fwrite(&m_noteMax,	sizeof(int), 1, fp);
	fwrite(&m_NoteData, sizeof(Note_Info), m_noteMax, fp);

	fclose(fp);
}

void Scn_Test::LoadNoteData()
{
	if(FileOpenManager::GetFOM()->OpenToDialog(ID_NOTE_LOAD, *AVDirector::GetDiector()->GetApplication()->GetHwnd()) == 0)
		return;
	FILE *fp = _wfopen(FileOpenManager::GetFOM()->GetPath(),L"rb");

	fread(&m_noteMax, sizeof(int), 1, fp);
	fread(&m_NoteData, sizeof(Note_Info), m_noteMax, fp);

	fclose(fp);

	m_noteNum->SetValue(m_noteMax);
}

void Scn_Test::TotalPlay()
{
	m_isTotalPlay = true;

	m_Sound->SetPosition(0);
	m_Sound->Play(true);

	m_total1 = 0;
	m_total2 = 0;
}