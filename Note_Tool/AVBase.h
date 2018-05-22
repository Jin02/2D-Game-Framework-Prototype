#pragma once



class AVBase
{

public:
	AVBase(void);
	~AVBase(void);

	virtual void Update() = 0;
	virtual void Render() = 0;
};