#pragma once

#pragma warning (disable:4172)


#define LEFT		0
#define RIGHT		1

#define AV_MOUSE_DOWN	1
#define AV_MOUSE_UP	2

typedef struct AVRECT{
	float x,y,w,h;

	AVRECT(float _x = 0, float _y = 0, float _w = 0, float _h = 0)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

}AVRECT;

typedef struct AVCOLOR{

	float a,r,g,b;

	AVCOLOR(float _a = 255, float _r = 255, float _g = 255, float _b = 255)
	{
		a = _a;
		r = _r;
		g = _g;
		b = _b;
	}

}AVCOLOR;

class ScaleInfo
{
public:
	float x;
	float y;

	ScaleInfo();
	ScaleInfo( float _x, float _y );

	~ScaleInfo();

	ScaleInfo& operator += ( const ScaleInfo& s);
	ScaleInfo& operator -= ( const ScaleInfo& s);
	ScaleInfo& operator /= ( const ScaleInfo& s);
	ScaleInfo& operator *= ( const ScaleInfo& s);

	ScaleInfo& operator + ( const ScaleInfo& s);
	ScaleInfo& operator - ( const ScaleInfo& s);
	ScaleInfo& operator / ( const ScaleInfo& s);
	ScaleInfo& operator * ( const ScaleInfo& s);
	
	bool operator == ( const ScaleInfo& s);
	bool operator != ( const ScaleInfo& s);

};