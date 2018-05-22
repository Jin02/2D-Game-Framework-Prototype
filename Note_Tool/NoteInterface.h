#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include "resource.h"
#include "Note_Info.h"

class Scn_Test;

class NoteInterface
{
	HDC			m_hdc;
	HWND		m_hWnd;

	wchar_t		m_noteType[7];
	wchar_t		m_soundName[30];

	int			m_NoteNum;
	int			m_maxNoteNum;

	Scn_Test	*m_Scene;

public:
	NoteInterface(void);
	~NoteInterface(void);

private:
	static bool CALLBACK Interface_Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

	void ComboBox(WPARAM &wParam);

	void DisableDlgItem();

	void  SetDlgItemFloat(HWND hDlg, int nIDDlgItem, float fValue);
	float GetDlgItemFloat(HWND hDlg, int nIDDlgItem);

public:
	void Interface_Create(int maxNoteNum);
	void Set_Interface_Position(D3DXVECTOR2& vPosition);

	void SetStartPosition(D3DXVECTOR2& vPosition);

	D3DXVECTOR2& GetStartPosition();
	float GetMovingTime();
	float GetArriveTime();

	void SetArriveTime(float time);

	void SetArrivePosition(D3DXVECTOR2& vPosition);
	D3DXVECTOR2 GetArrivePosition();

	int GetNoteNum();
	void BeforeNoteNum();
	void AfterNoteNum();

	void SetMoveTime(float time);
	void SetDuration(float time);

	float GetMoveTime();
	float GetDuration();

	void SetNoteType(int type);
	int  GetNoteType();

	void PlayButton();
};

