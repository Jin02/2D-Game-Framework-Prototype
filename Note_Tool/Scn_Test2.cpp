#include "Scn_Test2.h"
#include "AVDirector.h"

Scn_Test2::Scn_Test2(void)
{
}

Scn_Test2::~Scn_Test2(void)
{
}

void Scn_Test2::Init()
{
}

void Scn_Test2::Loop()
{
}

void Scn_Test2::End()
{
	
}

void Scn_Test2::Mouse(D3DXVECTOR2 &vPosition, int Left, int Right)
{
}

void Scn_Test2::MouseMove(D3DXVECTOR2 &vPosition)
{

}

void Scn_Test2::KeyBoard(bool *push, bool *up)
{
}

LRESULT WINAPI Scn_Test2::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{

	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}