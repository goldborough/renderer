#if !defined(LMVECTOR3_H)
#define LMVECTOR3_H


class LMVector3
{
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



	LMVector3();
	LMVector3(float x, float y, float z);
	LMVector3(LMVector3 & v);
	LMVector3(const LMVector3& v);
	LMVector3(int i);
	LMVector3(float f);
	~LMVector3();

	void operator += (const LMVector3& v);
	void operator -= (const LMVector3& v);
	void operator *= (const LMVector3& v);
	void operator /= (const LMVector3& v);

	bool operator == (const LMVector3 & v);
	bool operator != (const LMVector3 & v);

	void operator  = (const float& f);
	void operator += (const float& f);
	void operator -= (const float& f);
	void operator *= (const float& f);
	void operator /= (const float& f);
	
	void operator = (const LMVector3 &v);
	LMVector3 operator - (const LMVector3& rhs) const;    // subtract rhs
	LMVector3 operator + (const LMVector3 &v);
	LMVector3 operator * (const float f);
	LMVector3 operator * (const LMVector3& v);
	friend LMVector3 operator* (LMVector3 const& v1, LMVector3 const& v2);

	friend LMVector3 operator / (int scalar, LMVector3 const& v);
	friend LMVector3 operator / (LMVector3 const& v, int scalar);

	float operator [](int i) const;
	float & operator [](int i);

	void set(float vx, float vy, float vz);

	float dot(const LMVector3& vec) const;          // dot product
	LMVector3 cross(const LMVector3& vec) const;        // cross product

	float Length(); // added for opengl example 16

	float LengthSq();
	
	float Magnitude();

	float DisplacementMag(const LMVector3 & v);

	void Normalize();

	bool IsInRegion(LMVector3 * start, LMVector3 * end);

	bool IsRangeFurther(const LMVector3 & v, float range);

	const LMVector3& get() const;

	static LMVector3 cross(LMVector3 const& x, LMVector3 const& y);//ogl new
	static float dot(LMVector3 const& x, LMVector3 const& y);//ogl new


};


inline float LMVector3::dot(const LMVector3& rhs) const {
	return (x*rhs.x + y * rhs.y + z * rhs.z);
}

inline LMVector3 LMVector3::cross(const LMVector3& rhs) const {
	return LMVector3(y*rhs.z - z * rhs.y, z*rhs.x - x * rhs.z, x*rhs.y - y * rhs.x);
}


// 
// 
// 
// 
// 

inline LMVector3 LMVector3::cross(LMVector3 const& x, LMVector3 const& y) // ogl impl test also math.h
{
	return LMVector3(
		x.y * y.z - y.y * x.z,
		x.z * y.x - y.z * x.x,
		x.x * y.y - y.x * x.y);
}

inline float LMVector3::dot(LMVector3 const& x, LMVector3 const& y) // ogl impl test also math.h
{
	LMVector3 tmp(x * y);
	return tmp.x + tmp.y + tmp.z;
}

#endif