//
// Vector.h
//
// Simple templated vector implementation
//
// 09.28.2008 Jon C. Martin

#ifndef _VECTOR_H
#define _VECTOR_H

template <class T>
struct VectorT
{
public:

	VectorT()
	:	mX(T(0))
	,	mY(T(0))
	{}
	
	VectorT(T x, T y)
	:	mX(x)
	,	mY(y)
	{}

	friend VectorT& operator+=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX += right.mX;
		left.mY += right.mY;

		return left;
	}
	friend VectorT& operator-=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX -= right.mX;
		left.mY -= right.mY;

		return left;
	}
	friend VectorT& operator*=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX *= right.mX;
		left.mY *= right.mY;

		return left;
	}
	friend VectorT& operator/=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX /= right.mX;
		left.mY /= right.mY;

		return left;
	}
	friend VectorT operator+(const VectorT<T>& left, const VectorT<T>& right)
	{
		left += right;

		return left;
	}

	friend VectorT operator- (const VectorT<T>& left, const VectorT<T>& right)
	{
		left -= right;

		return left;
	}
	friend VectorT operator*(const VectorT<T>& left, const VectorT<T>& right)
	{
		left *= right;

		return left;
	}
	friend VectorT operator/ (const VectorT<T>& left, const VectorT<T>& right)
	{
		left /= right;

		return left;
	}
	T mX;
	T mY;
};

#endif


