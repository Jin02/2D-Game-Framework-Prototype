#include "NoteInterface.h"
#include "AVDirector.h"
#include "Scn_Test.h"
#include "FileOpenManager.h"

NoteInterface::NoteInterface(void)
{
	m_NoteNum		= 0;
	m_Scene			= (Scn_Test*)AVDirector::GetDiector()->GetScene();
}

NoteInterface::~NoteInterface(void)
{
	DestroyWindow(m_hWnd);
}

void NoteInterface::Interface_Create(int maxNoteNum)
{
	m_hWnd = CreateDialog(
		*AVDirector::GetDiector()->GetApplication()->GetHInstance(),
		MAKEINTRESOURCE(ID_DIALOG),
		*AVDirector::GetDiector()->GetApplication()->GetHwnd(),
		(DLGPROC)NoteInterface::Interface_Proc);

	ShowWindow(m_hWnd, SW_SHOW);

	HWND hCB = GetDlgItem(m_hWnd, IDC_NOTE_SELECT);

	SendMessage(hCB, CB_ADDSTRING, 0, (LPARAM)L"Normal"); 
	SendMessage(hCB, CB_ADDSTRING, 0, (LPARAM)L"Long");
	SendMessage(hCB, CB_ADDSTRING, 0, (LPARAM)L"Special");
	SendMessage(hCB, CB_ADDSTRING, 0, (LPARAM)L"Create");

	m_maxNoteNum = maxNoteNum;

	SetDlgItemInt(m_hWnd, IDC_EDT_NOTE_NUM, 1, false);

	EnableWindow( GetDlgItem(m_hWnd, IDC_EDT_DURATION), false);
}

void NoteInterface::Set_Interface_Position(D3DXVECTOR2& vPosition)
{
	SetWindowPos(m_hWnd, NULL, vPosition.x, vPosition.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

bool CALLBACK NoteInterface::Interface_Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static NoteInterface *_interface = ((Scn_Test*)AVDirector::GetDiector()->GetScene())->GetInterface();

	switch(iMessage)
	{
	case WM_INITDIALOG:
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_COMBO1:
			_interface->ComboBox(wParam);
			_interface->DisableDlgItem();
			break;

		case IDC_BUT_BEFORE:
			_interface->BeforeNoteNum();
			break;

		case IDC_BUT_AFTER:
			_interface->AfterNoteNum();
			break;

		case IDC_BUT_PLAY:
			_interface->PlayButton();
			break;

		case IDC_BUT_TOTAL_PLAY:
			_interface->m_Scene->TotalPlay();
			break;
		}

		return false;
	}

	return false;
}

void NoteInterface::DisableDlgItem()
{
	HWND hEdt;
	hEdt = GetDlgItem(m_hWnd, IDC_EDT_DURATION);

	if( wcscmp(m_noteType, L"Long") == 0)
	{
		EnableWindow( hEdt, true);
		return;
	}

	EnableWindow( hEdt, false);
}

void NoteInterface::ComboBox(WPARAM &wParam)
{
	switch(HIWORD(wParam))
	{
	case CBN_SELCHANGE:
		GetWindowText( GetDlgItem(m_hWnd, IDC_NOTE_SELECT), m_noteType, 7);
		break;
	}
}

void NoteInterface::SetStartPosition(D3DXVECTOR2& vPosition)
{
	SetDlgItemInt( m_hWnd, IDC_EDT_START_POS_X, (int)vPosition.x, true);
	SetDlgItemInt( m_hWnd, IDC_EDT_START_POS_Y, (int)vPosition.y, true);
}

D3DXVECTOR2& NoteInterface::GetStartPosition()
{
	int x = GetDlgItemInt( m_hWnd, IDC_EDT_START_POS_X, NULL, true);
	int y = GetDlgItemInt( m_hWnd, IDC_EDT_START_POS_Y, NULL, true);

	return D3DXVECTOR2(x, y);
}

int NoteInterface::GetNoteNum()
{
	return GetDlgItemInt( m_hWnd, IDC_EDT_NOTE_NUM, NULL, true);
}

float NoteInterface::GetArriveTime()
{
	return GetDlgItemFloat(m_hWnd, IDC_EDT_ARRIVE_TIME);
}

void NoteInterface::SetDlgItemFloat(HWND hDlg, int nIDDlgItem, float fValue)
{
	wchar_t uni_value[32];
	char value[32];
	sprintf(value, "%f", fValue);
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, value, 32, uni_value, 32); 
	
	SetDlgItemText(m_hWnd, nIDDlgItem, uni_value);
}

float NoteInterface::GetDlgItemFloat(HWND hDlg, int nIDDlgItem)
{
	wchar_t value[32];
	int interger;
	float result = 0;

	GetDlgItemText(m_hWnd, nIDDlgItem, value, 32);
	for(interger = 0; value[interger] != '.'; interger++);

	for(int i=0; i < wcslen(value); i++)
	{
		if( value[i] == '.' )
			continue;

		result += (value[i] - '0') * pow(10.f, interger - i -(1 - (i >= interger) ));
	}

	return result;
}

void NoteInterface::SetArriveTime(float time)
{
	SetDlgItemFloat(m_hWnd, IDC_EDT_ARRIVE_TIME, time);
}

float NoteInterface::GetMovingTime()
{
	return GetDlgItemFloat(m_hWnd, IDC_EDT_MOVE_TIME);
}

void NoteInterface::SetArrivePosition(D3DXVECTOR2& vPosition)
{
	SetDlgItemInt( m_hWnd, IDC_EDT_ARRIVE_POS_X, (int)vPosition.x, true);
	SetDlgItemInt( m_hWnd, IDC_EDT_ARRIVE_POS_Y, (int)vPosition.y, true);
}

D3DXVECTOR2 NoteInterface::GetArrivePosition()
{
	return D3DXVECTOR2(
		(float)GetDlgItemInt( m_hWnd, IDC_EDT_ARRIVE_POS_X, NULL, true),
		(float)GetDlgItemInt( m_hWnd, IDC_EDT_ARRIVE_POS_Y, NULL, true) );
}

void NoteInterface::SetMoveTime(float time)
{
	if( GetArriveTime() - 0.0001 <= time && time <= GetArriveTime() + 0.0001 )
		time = 0.f;

	SetDlgItemFloat(m_hWnd, IDC_EDT_MOVE_TIME, time);
}

void NoteInterface::SetDuration(float time)
{
	if(this->GetNoteType() != NOTETYPE_LONG){
		EnableWindow( GetDlgItem(m_hWnd, IDC_EDT_DURATION), false);
		return;
	}

	SetDlgItemFloat(m_hWnd, IDC_EDT_DURATION, time);
}

float NoteInterface::GetMoveTime()
{
	return GetDlgItemFloat(m_hWnd, IDC_EDT_MOVE_TIME);
}

float NoteInterface::GetDuration()
{
	return GetDlgItemFloat(m_hWnd, IDC_EDT_DURATION);
}

void NoteInterface::SetNoteType(int type)
{
	wchar_t *text;

	if( type == NOTETYPE_NOMAL )	text = L"Normal";
	else if( type == NOTETYPE_LONG) text = L"Long";
	else if( type == NOTETYPE_SPECIAL) text = L"Special";
	else text = L"Create";

	SendMessage( GetDlgItem(m_hWnd, IDC_NOTE_SELECT), CB_SELECTSTRING, 0, (LPARAM)text);
}

int NoteInterface::GetNoteType()
{
	GetWindowText( GetDlgItem(m_hWnd, IDC_NOTE_SELECT), m_noteType, 7);

	if( wcscmp(L"Normal", m_noteType) == 0 )
		return NOTETYPE_NOMAL;

	if( wcscmp(L"Long", m_noteType) == 0 )
		return NOTETYPE_LONG;

	if( wcscmp(L"Special", m_noteType) == 0)
		return NOTETYPE_SPECIAL;
	
	return NOTETYPE_CREATE;
}

void NoteInterface::BeforeNoteNum()
{
	m_Scene->NoteDataSet(m_NoteNum);

	if(m_NoteNum > 0) m_NoteNum--;
	m_Scene->InterfaceDataSet(m_NoteNum);
	SetDlgItemInt(m_hWnd, IDC_EDT_NOTE_NUM, m_NoteNum+1, false);
}

void NoteInterface::AfterNoteNum()
{
	m_Scene->NoteDataSet(m_NoteNum);

	if(m_NoteNum < m_maxNoteNum-1) m_NoteNum++;

	m_Scene->InterfaceDataSet(m_NoteNum);
	SetDlgItemInt(m_hWnd, IDC_EDT_NOTE_NUM, m_NoteNum+1, false);
}

void NoteInterface::PlayButton()
{
	m_Scene->NoteDataSet(m_NoteNum);
	m_Scene->NotePlay(m_NoteNum);
}