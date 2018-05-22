#pragma once

#include "Scene.h"


class Scn_Test2 : public Scene
{
	

public:
	Scn_Test2(void);
	~Scn_Test2(void);

	virtual void Init();
	virtual void Loop();
	virtual	void End();
	virtual void Mouse(D3DXVECTOR2 &vPosition, int Left, int Right);
	virtual void MouseMove(D3DXVECTOR2 &vPosition);
	virtual void KeyBoard(bool *push, bool *up);
	virtual LRESULT WINAPI Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	
};

