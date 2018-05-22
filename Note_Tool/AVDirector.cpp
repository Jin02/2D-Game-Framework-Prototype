#include "AVDirector.h"
#include "Scn_Test.h"

AVDirector::AVDirector(void)
{
	m_Scene = new Scn_Test;
}

AVDirector::~AVDirector(void)
{
}

AVDirector* AVDirector::GetDiector()
{
	if( _sharedDirector == NULL )
	{
		_sharedDirector = new AVDirector;
	}

	return _sharedDirector;
}

void AVDirector::deleteDirector()
{
	m_Scene->End();
	SAFE_DELETE(m_Application);

	if(_sharedDirector) delete _sharedDirector;
	_sharedDirector = NULL;

	PostQuitMessage(0);
}

void AVDirector::RunApplication()
{
	m_Application = new AVWinD3D((WNDPROC)AVDirector::WndProc);
	m_Application->InitWinD3D();

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			RunToInnerSystem();
			tickTime();
		}
	}
}

void AVDirector::RunToInnerSystem()
{
	m_Application->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

	if( SUCCEEDED( m_Application->GetD3DDevice()->BeginScene() ) )
	{
		m_Application->GetD3DSprite()->Begin(D3DXSPRITE_ALPHABLEND);

		if( m_state == AV_STATE_LOOP )
		{
			m_Scene->Loop();
			m_Scene->InnerUpdate();
		}
		else if ( m_state == AV_STATE_END )
		{
			m_Scene->End();
			m_state = AV_STATE_INIT;
		}
		else  // AV_STATE_INIT
		{ 
			m_Scene->Init(); 
			m_state = AV_STATE_LOOP; 
		}

		m_Application->GetD3DSprite()->End();
		m_Application->GetD3DDevice()->EndScene();
	}

	m_Application->GetD3DDevice()->Present(NULL,NULL,NULL,NULL);
}

void AVDirector::changeToState(const AVState state)
{
	m_state = state;
}

void AVDirector::tickTime()
{
	static float	lastTime;
	float			now;
	static DWORD	staticTime = GetTickCount();

	now = (double)(GetTickCount() - staticTime) / 1000;

	m_tickTime = now - lastTime;
	m_tickTime = MAX(0.f, m_tickTime);

	lastTime = now;
}

LRESULT WINAPI AVDirector::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Scene *scene = AVDirector::GetDiector()->GetScene();

	bool UpKey[256] = {false, }, DownKey[256] = {false, };
	int Mouse[2] = {0, };

	switch( msg )
	{
	case WM_KEYDOWN:
		DownKey[wParam] = true;
		scene->KeyBoard(DownKey, UpKey);
		break;

	case WM_KEYUP:
		UpKey[wParam]  = true;
		scene->KeyBoard(DownKey, UpKey);
		break;		

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		Mouse[LEFT] = msg - WM_LBUTTONDOWN + 1;
		break;

	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		Mouse[RIGHT] = msg - WM_RBUTTONDOWN + 1;
		break;

	case WM_DESTROY:
		AVDirector::GetDiector()->deleteDirector();
		return 0;
	}

	if( WM_LBUTTONDOWN <= msg && msg <= WM_RBUTTONUP )
	{
		scene->Mouse(D3DXVECTOR2(LOWORD(lParam), HIWORD(lParam)),
			Mouse[LEFT], Mouse[RIGHT]);
	}

	if( WM_MOUSEMOVE == msg )
		scene->MouseMove(D3DXVECTOR2(LOWORD(lParam), HIWORD(lParam)));

	return scene->Proc(hWnd, msg, wParam, lParam);
}

AVWinD3D* AVDirector::GetApplication()
{ 
	return m_Application;	
}

float AVDirector::GetTickTime()
{ 
	return m_tickTime;		
}

int	AVDirector::GetState()
{ 
	return m_state;		
}

Scene* AVDirector::GetScene()
{ 
	return m_Scene;		
}

void AVDirector::SetScene(Scene* scene)
{ 
	m_Scene = scene;		
}