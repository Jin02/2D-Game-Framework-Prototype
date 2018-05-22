#include "Information.h"

ScaleInfo::ScaleInfo()
{
	x = y = 1.f;
}

ScaleInfo::~ScaleInfo()
{
}

ScaleInfo::ScaleInfo( float _x, float _y )
{
	x = _x;
	y = _y;
}

ScaleInfo& ScaleInfo:: operator+( const ScaleInfo& s)
{
	ScaleInfo temp(x+s.x, y+s.y);
	return temp;
}

ScaleInfo& ScaleInfo:: operator-( const ScaleInfo& s)
{
	ScaleInfo temp(x-s.x, y-s.y);
	return temp;
}

ScaleInfo& ScaleInfo:: operator/( const ScaleInfo& s)
{
	ScaleInfo temp(x/s.x, y/s.y);
	return temp;
}

ScaleInfo& ScaleInfo:: operator*( const ScaleInfo& s)
{
	ScaleInfo temp(x*s.x, y*s.y);
	return temp;
}

ScaleInfo& ScaleInfo:: operator+=( const ScaleInfo& s)
{
	return this->operator+(s);
}

ScaleInfo& ScaleInfo:: operator-=( const ScaleInfo& s)
{
	return this->operator-(s);
}

ScaleInfo& ScaleInfo:: operator/=( const ScaleInfo& s)
{
	return this->operator/(s);
}

ScaleInfo& ScaleInfo:: operator*=( const ScaleInfo& s)
{
	return this->operator*(s);
}

bool ScaleInfo:: operator==( const ScaleInfo& s)
{
	if( x == s.x && y == s.y ) return true;
	return false;
}

bool ScaleInfo:: operator!=( const ScaleInfo& s)
{
	return !(this->operator==(s));
}