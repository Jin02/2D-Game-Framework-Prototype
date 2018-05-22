#pragma once

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "resource.h"
#include "Information.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")


template<typename T>
inline void SAFE_DELETE(T& p){if(p){delete p; p=NULL;}}

template<typename T>
inline void SAFE_ARRARY_DELETE(T& p){if(p){delete[] p; p=NULL;}}

template<typename T>
inline void SAFE_RELEASE(T& p){if(p){p->Release(); p=NULL;}}

template<typename T>
inline T MIN(T a, T b){ return a < b ? a : b;}

template<typename T>
inline T MAX(T a, T b){ return a > b ? a : b;}



const wchar_t * const cProgramName = L"Hello";

class AVWinD3D
{
private:
	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	LPD3DXSPRITE			m_Sprite;
	LPD3DXFONT				m_Font;

	HWND					m_hWnd;
	WNDCLASSEX				*m_window;
	D3DPRESENT_PARAMETERS	m_d3dpp;

	AVRECT					m_WindowSize;

public:
	AVWinD3D(WNDPROC wndProc);
	~AVWinD3D(void);

	void InitWinD3D();

public:
	inline const LPDIRECT3D9		GetD3D()		{ return m_pD3D;		}
	inline const LPDIRECT3DDEVICE9	GetD3DDevice()	{ return m_pd3dDevice;	}
	inline const LPD3DXSPRITE		GetD3DSprite()	{ return m_Sprite;		}
	inline const LPD3DXFONT			GetD3DFont()	{ return m_Font;		}
	inline const HWND*				GetHwnd()		{ return &m_hWnd;		}
	inline const AVRECT&			GetWindowSize() { return m_WindowSize;	}
	inline const HINSTANCE*			GetHInstance()	{ return &(m_window->hInstance); }
};