#if !defined(LMVECTOR4_H)
#define LMVECTOR4_H

#include "LMVector3.h"

class LMVector4
{
private:
	
public:
	
	union {
		float x;
		float r;
	};
	union {
		float y;
		float g;
	};
	union {
		float z;
		float b;
	};
	union {
		float w;
		float a;
	};

	//removed values pointers lesson 22 to size better
	//left, top, right, bottom


	LMVector4();
	LMVector4(float x, float y, float z, float w);
	LMVector4(LMVector3& v, float f);
	LMVector4(const LMVector4& v);

	~LMVector4();

	void operator += (const LMVector4& v);
	void operator -= (const LMVector4& v);
	void operator *= (const LMVector4& v);
	void operator /= (const LMVector4& v);

	bool operator == (const LMVector4 & v);
	bool operator != (const LMVector4 & v);

	void operator  = (const float& f);
	void operator += (const float& f);
	void operator -= (const float& f);
	void operator *= (const float& f);
	void operator /= (const float& f);

	void operator = (const LMVector4 &v);
	LMVector4 operator + (const LMVector4 &v);
	LMVector4 operator * (const float f);

	float operator [](int i) const;
	float & operator [](int i);

	LMVector3 toV3();

	/*float &x() const;
	float &y() const;
	float &z() const;
	float &w() const;

	float&r();
	float&g();
	float&b();
	float&a();*/

	float&left();
	float&top();
	float&right();
	float&bottom();

	const LMVector4& get() const;
};

#endif