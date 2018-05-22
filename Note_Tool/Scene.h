#pragma once

#include <stdarg.h>
#include <vector>
#include "AVBase.h"
#include "AVWinD3D.h"

class Scene
{
private:
	std::vector<AVBase*> m_vector;

public:
	Scene(void);
	~Scene(void);

	virtual void Init()		= 0;
	virtual void Loop()		= 0;
	virtual	void End()		= 0;
	virtual void Mouse(D3DXVECTOR2 &vPosition, int Left, int Right)	= 0;
	virtual void MouseMove(D3DXVECTOR2 &vPosition) = 0;
	virtual void KeyBoard(bool *push, bool *up) = 0;

	void InnerUpdate();

	virtual LRESULT WINAPI Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

protected:
	void addObject(AVBase* object);
	void deleteObject(AVBase* object);
	void deleteAllObject();

	void ChangeScene(Scene* scene, bool isDelete);
};