#include "AVTexture2D.h"
#include "AVDirector.h"

AVTexture2D::AVTexture2D(void)
{
	m_Texture	= NULL;
	m_vPosition = D3DXVECTOR2(0,0);
	m_Color		= AVCOLOR();

	memset(&m_Rect,0,sizeof(RECT));
	memset(&m_Info,0,sizeof(D3DXIMAGE_INFO));

	

//	ActionManager::ActionManager(NULL,NULL,NULL,NULL);
}

AVTexture2D::~AVTexture2D(void)
{
	if(m_Texture)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}

void AVTexture2D::CreateTexture(wchar_t *path)
{
	D3DXCreateTextureFromFileEx(
		AVDirector::GetDiector()->GetApplication()->GetD3DDevice(),
		path,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(0,0,0,255),
		&m_Info,NULL,
		&m_Texture);

	m_Rect.right  = m_Info.Width;
	m_Rect.bottom = m_Info.Height;
}

void AVTexture2D::Update()
{

}

void AVTexture2D::Render()
{
	static LPD3DXSPRITE sprite = AVDirector::GetDiector()->GetApplication()->GetD3DSprite();
		
	D3DCOLOR color = D3DCOLOR_ARGB((int)m_Color.a, (int)m_Color.r, (int)m_Color.g, (int)m_Color.b);
	sprite->Draw(m_Texture, &m_Rect, NULL, &D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 0), color);
}

void AVTexture2D::SetRect(int x, int y, int w, int h)
{
	m_Rect.left		= x;
	m_Rect.top		= y;
	m_Rect.right	= x+w;
	m_Rect.bottom	= y+h;
}

void AVTexture2D::SetTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_Texture = Texture;
}

void AVTexture2D::SetPosition(D3DXVECTOR2& vPosition)
{
	m_vPosition = vPosition;
}
void AVTexture2D::SetColor(AVCOLOR& color)
{
	m_Color = color;
}

D3DXVECTOR2& AVTexture2D::GetPosition()
{ 
	return m_vPosition;	
}

AVCOLOR& AVTexture2D::GetColor()	
{ 
	return m_Color;		
}

LPDIRECT3DTEXTURE9* AVTexture2D::GetTexture()
{ 
	return &m_Texture; 
}

D3DXIMAGE_INFO&	AVTexture2D::GetTextureInfo()
{ 
	return m_Info;	
}

RECT& AVTexture2D::GetRect()
{ 
	return m_Rect;	 
}