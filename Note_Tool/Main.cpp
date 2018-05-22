#include "AVDirector.h"

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	AVDirector::GetDiector()->RunApplication();

	return 0;
}