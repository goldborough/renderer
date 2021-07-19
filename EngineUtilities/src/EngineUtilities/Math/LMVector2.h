#if !defined(LMVECTOR2_H)

#define LMVECTOR2_H


class LMVector2
{
public:
	float x;
	float y;

	LMVector2();
	LMVector2(float fx, float fy);
	LMVector2(LMVector2 & v);
	LMVector2(const LMVector2& v);
	LMVector2(int i);
	~LMVector2();

	void operator += (const LMVector2& v);
	void operator -= (const LMVector2& v);
	void operator *= (const LMVector2& v);
	void operator /= (const LMVector2& v);

	bool operator == (const LMVector2 & v);
	bool operator != (const LMVector2 & v);

	void operator = (const LMVector2& v);//todo added
	LMVector2 operator - (const LMVector2& rhs) const;    // subtract rhs//todo added
	LMVector2 operator + (const LMVector2& v);//todo added
	LMVector2 operator * (const float f);//todo added
	LMVector2 operator * (const LMVector2& v);
	//todo added

	friend LMVector2 operator / (int scalar, LMVector2 const& v);
	friend LMVector2 operator / (LMVector2 const& v, int scalar);

	float operator [](int i) const;//todo added
	float& operator [](int i);//todo added

	const LMVector2& get() const;

};

#endif