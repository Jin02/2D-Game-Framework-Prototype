#include "AVWinD3D.h"

AVWinD3D::AVWinD3D(WNDPROC wndProc)
{	
	m_window				= new WNDCLASSEX;
	m_window->cbSize			= sizeof(WNDCLASSEX);
	m_window->style			= CS_CLASSDC;
	m_window->lpfnWndProc	= wndProc; //need to fix
	m_window->cbClsExtra		= 0L;
	m_window->cbWndExtra		= 0L;
	m_window->hInstance		= GetModuleHandle(NULL);
	m_window->hIcon			= NULL;
	m_window->hCursor		= NULL;
	m_window->hbrBackground	= NULL;
	m_window->lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);
	m_window->lpszClassName	= cProgramName;
	m_window->hIconSm		= NULL;

    ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

	m_d3dpp.Windowed				= TRUE;
    m_d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
    m_d3dpp.BackBufferFormat		= D3DFMT_UNKNOWN;
    m_d3dpp.EnableAutoDepthStencil	= TRUE;
    m_d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;

	m_WindowSize.x					= 100;
	m_WindowSize.y					= 100;
	m_WindowSize.w					= 700;
	m_WindowSize.h					= 600;
}

AVWinD3D::~AVWinD3D(void)
{
	UnregisterClass( cProgramName, m_window->hInstance );

	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_Sprite);
	SAFE_RELEASE(m_Font);
	SAFE_DELETE(m_window);
}

void AVWinD3D::InitWinD3D()
{
	RegisterClassEx( m_window );

   m_hWnd = CreateWindow( cProgramName, cProgramName,
	   WS_OVERLAPPEDWINDOW | WS_SYSMENU, (int)m_WindowSize.x, (int)m_WindowSize.y, (int)m_WindowSize.w, (int)m_WindowSize.h,
                           NULL, NULL, m_window->hInstance, NULL );

   /* D3D */
   m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

      m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
                          D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                          &m_d3dpp, &m_pd3dDevice);

	D3DXCreateSprite(m_pd3dDevice, &m_Sprite);

	D3DXCreateFont(m_pd3dDevice,20,10,
		FW_BOLD,1,false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		L"±¼¸²",&m_Font);

    m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,  TRUE );
	/* D3D */

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);
}