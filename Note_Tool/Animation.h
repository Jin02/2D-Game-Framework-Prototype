#pragma once

#include "Sprite.h"
#include <stdarg.h>
#include <vector>

class Animation : public Sprite
{
	std::vector<AVRECT*> m_RectVector;

	int		m_AnimationScene;
	int		m_playNum;
	int		m_repeat;

	float	m_fLimit;
	float	m_fTime;

	bool	m_isStop;

public:
	Animation(void);
	~Animation(void);

	void addScene(AVRECT *rect, ...);
	void addOneScene(AVRECT *rect);
	void SetFrame(float fTime, int num = INFINITY);
	void deleteAnimation();

	void Start();
	void Pause();
	void Stop();

	virtual void Update();
	virtual void Render();
};

