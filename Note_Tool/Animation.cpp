#include "Animation.h"
#include "AVDirector.h"

Animation::Animation(void)
{
	m_fLimit			= 0;
	m_fTime				= 0;
	m_AnimationScene	= 0;
	m_repeat			= 0;
	m_playNum			= 1;
	m_isStop			= true;
}

Animation::~Animation(void)
{
	deleteAnimation();
}

void Animation::addScene(AVRECT *rect, ...)
{
	va_list		list;
	AVRECT		*_rect = rect;
	
	va_start( list, rect);

	while( _rect != NULL )
	{
		m_RectVector.push_back(new AVRECT(*_rect)); 
		_rect = va_arg( list, AVRECT* ); 
	}
}

void Animation::addOneScene(AVRECT *rect)
{
	m_RectVector.push_back(new AVRECT(*rect));
}

void Animation::deleteAnimation()
{
	for(int i=0; i<m_RectVector.size(); i++)	SAFE_DELETE(m_RectVector[i]);
	m_RectVector.clear();
}

void Animation::SetFrame(float fTime, int num)
{
	m_fLimit  = fTime;
	m_playNum = num;
}

void Animation::Update()
{
	static AVDirector *director = AVDirector::GetDiector();

	if(m_isStop) return;

	if( (m_fTime += director->GetTickTime()) >= m_fLimit )
	{
		
		if( ++m_AnimationScene == m_RectVector.size() )
		{
			if( m_playNum-1 != m_repeat )	m_repeat++;
			else							m_isStop = true;

			m_AnimationScene = 0;
		}

		m_fTime = 0;
	}


	Sprite::Update();
}

void Animation::Render()
{
	m_Rect.left		= m_RectVector[m_AnimationScene]->x;
	m_Rect.right	= m_RectVector[m_AnimationScene]->x + m_RectVector[m_AnimationScene]->w;
	m_Rect.top		= m_RectVector[m_AnimationScene]->y;
	m_Rect.bottom	= m_RectVector[m_AnimationScene]->y + m_RectVector[m_AnimationScene]->h;

	Sprite::Render();
}

void Animation::Start()
{
	m_isStop = false;
	if( m_playNum-1 != m_repeat )	m_repeat = 0;
}

void Animation::Pause()
{
	m_isStop = true;
}

void Animation::Stop()
{
	m_isStop = true;
	m_AnimationScene = 0;
	m_repeat = 0;
}