#pragma once

#include "AVWinD3D.h"
#include "Scene.h"
#include "AVTexture2D.h"
#include <math.h>
#include "Information.h"

#pragma warning (disable:4244)
#pragma warning (disable:4018)
#pragma warning (disable:4927)

enum AVState{
	AV_STATE_INIT,
	AV_STATE_LOOP,
	AV_STATE_END
};


class AVDirector
{
private:

	int						m_state;
	float					m_tickTime;

	Scene					*m_Scene;
	AVWinD3D				*m_Application;

	AVTexture2D				*m_Sprite;

private:
	AVDirector(void);
	
	void tickTime();
	void RunToInnerSystem();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


public:
	~AVDirector(void);

	static AVDirector* GetDiector();

	void deleteDirector();
	void RunApplication();

	void changeToState(const AVState state);

	AVWinD3D*	GetApplication();
	float		GetTickTime();
	int			GetState();
	Scene*		GetScene();
	void		SetScene(Scene* scene);
};

static AVDirector *_sharedDirector = NULL;