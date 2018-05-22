#pragma once

#include "AVTexture2D.h"
#include "ActionManager.h"

class Sprite : public AVTexture2D, public ActionManager
{
protected:
	ScaleInfo				m_scale;

	float					m_angle;

	D3DXVECTOR2				m_anchorPoint;

	bool					m_isUse;

public:
	Sprite(void);
	virtual ~Sprite(void);

	virtual void Update();
	virtual void Render();

	bool GetisUse();
	void SetisUse(bool is);

	void SetanchorPoint(D3DXVECTOR2 &v);
	void SetAngle(float Angle);
	void SetScale(float scale);
	void SetScale(float x, float y);
	void SetOpacity(unsigned int opacity);
};

