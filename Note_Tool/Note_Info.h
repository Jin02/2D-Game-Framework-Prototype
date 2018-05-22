#pragma once

#include <d3dx9.h>

enum LONGNOTE{
	LONG_DEALY,
	LONG_MOVE,
	LONG_ROTATION
};

enum NOTETYPE{
	NOTETYPE_NOMAL,
	NOTETYPE_LONG,
	NOTETYPE_SPECIAL,
	NOTETYPE_CREATE
};

	

typedef struct Note_Info
{
	D3DXVECTOR2 vStartPos;
	D3DXVECTOR2 vTargetPos;
	float		startTime;
	float		arriveTime;

	int			actionID;
	float		time;

	wchar_t		Sound[30];

	Note_Info()
	{
		vTargetPos = vStartPos = D3DXVECTOR2(0,0);
		arriveTime = startTime = 0;

		actionID = NOTETYPE_NOMAL;
		time = 0.5f;
		wcscpy(Sound,L"None");
	}

	Note_Info(D3DXVECTOR2 &_vStartPos, D3DXVECTOR2 &_vTargetPos, 
		float _startTime, float _arriveTime, int _actionID = NOTETYPE_NOMAL, float _time = 0.f, wchar_t *SoundName = L"None")
	{
		vStartPos = _vStartPos;
		vTargetPos = _vTargetPos;
		startTime = _startTime;
		arriveTime = _arriveTime;

		actionID = _actionID;
		time = _time;
		wcscpy(Sound,SoundName);
	}

}Note_Info;

