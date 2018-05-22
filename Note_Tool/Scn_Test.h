#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "GraphicFont.h"
#include "Animation.h"
#include "SoundPlayer.h"
#include "AVString.h"
#include "FileOpenManager.h"
#include "Note_Info.h"
#include "Judgment.h"
#include "NoteInterface.h"
#include "Note.h"
#include "PVJudgment.h"

enum IMAGE_ID{
	IMG_JUD_1_1,
	IMG_JUD_1_2,
	IMG_NOTE,
	IMG_GRAPHIC_NUM
};

#define SCREEN_NOTE_MAX		15
#define EFFECT_SOUND_MAX	15

class Scn_Test : public Scene
{
	Sprite sprite;

	Sprite					*m_screenArea;
	SoundPlayer				*m_Sound;

	GraphicFont				*m_noteNum;
	GraphicFont				*m_PlayCount;

	AVString				*m_whatNoteNum;
	AVString				*m_countString;

	int						m_noteMax;
	Note_Info				m_NoteData[1000];

	int						m_state;

	Judgment				m_Jud[SCREEN_NOTE_MAX];
	CNote					m_Note[SCREEN_NOTE_MAX*2];

	NoteInterface			*m_Interface;

	bool					m_isPlayStart;
	bool					m_isTwoPhase;

	bool					m_isShiftKeyDown;
	bool					m_isShiftClick;
	D3DXVECTOR2				m_vShiftPos;
	D3DXVECTOR2				m_vStartPosition;

	int						m_judNum;


	bool					m_isTotalPlay;

	int						m_total1;
	int						m_total2;

private:
	void rc_Menu(WPARAM &wParam, HWND &hWnd);
	

public:
	Scn_Test(void);
	~Scn_Test(void);

	virtual void Init();
	virtual void Loop();
	virtual	void End();
	virtual void Mouse(D3DXVECTOR2 &vPosition, int Left, int Right);
	virtual void MouseMove(D3DXVECTOR2 &vPosition);
	virtual void KeyBoard(bool *push, bool *up);
	virtual LRESULT WINAPI Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	NoteInterface* GetInterface() { return m_Interface; }

	void InterfaceDataSet(int num);
	void NoteDataSet(int num);

	void NotePlay(int num);
	void JudgmentPlay();

	void TotalPlay();
	
private:
	void SaveNoteData();
	void LoadNoteData();
};

