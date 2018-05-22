#include "Sprite.h"
#include "AVDirector.h"

Sprite::Sprite(void) :
ActionManager(&(AVTexture2D::m_vPosition), 
		&m_angle,
		&m_scale, 
		&m_Color.a)
{
	m_scale			= ScaleInfo(1.f, 1.f);
	m_angle			= AV_DI(0);
	m_anchorPoint	= D3DXVECTOR2( 0.0f, 0.0f );

	m_isUse		= true;
}

Sprite::~Sprite(void)
{
}

void Sprite::Update()
{
	if( m_isUse == false ) return;

	ActionUpdate();
}

void Sprite::Render()
{
	if( m_isUse == false ) return;

	D3DXMATRIX Tmat, rotation, scale, translation[2];

	float width  = AVTexture2D::m_Rect.right - AVTexture2D::m_Rect.left;
	float height = AVTexture2D::m_Rect.bottom - AVTexture2D::m_Rect.top;

	//float width  = m_Info.Width;
	//float height = m_Info.Height;

	static LPD3DXSPRITE sprite = AVDirector::GetDiector()->GetApplication()->GetD3DSprite();

	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&scale);

	for(int i=0; i<2; i++)D3DXMatrixIdentity(&translation[i]);

	sprite->SetTransform( &scale ); // 한개만 해줘도 상관없음.

	D3DXMatrixTranslation(&translation[0], 
		-(width * m_anchorPoint.x), 
		-(height* m_anchorPoint.y), 
		0);

	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, 1.f);
	D3DXMatrixRotationZ(&rotation, m_angle);

	D3DXVECTOR2 vector = AVTexture2D::m_vPosition;

	D3DXMatrixTranslation(&translation[1], 
		AVTexture2D::m_vPosition.x, 
		AVTexture2D::m_vPosition.y, 
		0);	

	Tmat = translation[0] * scale * rotation * translation[1];

	sprite->SetTransform( &Tmat );

	D3DCOLOR color = D3DCOLOR_ARGB((int)m_Color.a, (int)m_Color.r, (int)m_Color.g, (int)m_Color.b);
	sprite->Draw(m_Texture, &m_Rect, NULL, NULL, color);

	D3DXMatrixIdentity(&scale);
	sprite->SetTransform( &scale );
}

bool Sprite::GetisUse()
{
	return m_isUse;
}

void Sprite::SetisUse(bool is)
{
	m_isUse = is;
}

void Sprite::SetanchorPoint(D3DXVECTOR2 &v)
{
	m_anchorPoint = v;
}

void Sprite::SetAngle(float Angle)
{
	if( Angle > AV_DI(360) )	Angle -= AV_DI(360);
	if( Angle < AV_DI(0) )		Angle += AV_DI(360);

	m_angle = Angle;
}

void Sprite::SetScale(float scale)
{
	m_scale.x = scale;
	m_scale.y = scale;
}

void Sprite::SetScale(float x, float y)
{
	m_scale.x = x;
	m_scale.y = y;
}

void Sprite::SetOpacity(unsigned int opacity)
{
	m_Color.a = opacity;
}