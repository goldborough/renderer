#include "LMVector2.h"

LMVector2::LMVector2()
{
	x = 0.0f;
	y = 0.0f;
}

LMVector2::LMVector2(float fx, float fy)
{
	x = fx;
	y = fy;
}

LMVector2::LMVector2(LMVector2 & v)
{
	x = v.x;
	y = v.y;
}

LMVector2::LMVector2(const LMVector2& v)
{
	x = v.x;
	y = v.y;
}

LMVector2::LMVector2(int i)
{
	x = i, y = i;
}

LMVector2::~LMVector2()
{
	x = 0.0f;
	y = 0.0f;
}

void LMVector2::operator += (const LMVector2 & v)
{
	x += v.x;
	y += v.y;
}

void LMVector2::operator -= (const LMVector2& v)
{
	x -= v.x;
	y -= v.y;
}

void LMVector2::operator *= (const LMVector2& v)
{
	x *= v.x;
	y *= v.y;
}

void LMVector2::operator /= (const LMVector2& v)
{
	x /= v.x;
	y /= v.y;
	
}

bool LMVector2::operator == (const LMVector2 & v)
{
	return v.x == x && v.y == y;
}

bool LMVector2::operator != (const LMVector2 & v)
{
	return v.x != x || v.y != y;
}

void LMVector2::operator = (const LMVector2& v)
{
	x = v.x;
	y = v.y;
}

LMVector2 LMVector2::operator + (const LMVector2& v)
{
	return LMVector2(x + v.x, y + v.y);
}

LMVector2 LMVector2::operator * (const float f)
{
	return LMVector2(x * f, y * f);
}

LMVector2 LMVector2::operator * (const LMVector2& v)
{
	return LMVector2(x * v.x, y * v.y);
}

LMVector2 operator * (LMVector2 const& v1, LMVector2 const& v2)
{
	return LMVector2(v2.x * v1.x, v2.y * v1.y);//for gle imp
}

LMVector2 LMVector2::operator - (const LMVector2& rhs) const
{
	return LMVector2(x - rhs.x, y - rhs.y);
}

LMVector2 operator / (int scalar, LMVector2 const& v)
{
	return LMVector2(scalar / v.x, scalar / v.y);
}

LMVector2 operator / (LMVector2 const& v, int scalar)
{
	return LMVector2(v.x / scalar, v.y / scalar);
}

float LMVector2::operator[](int i) const
{
	return (&x)[i];
}

float& LMVector2::operator [] (int i)
{
	return (&x)[i];
}

const LMVector2& LMVector2::get() const
{
	return *this;
}