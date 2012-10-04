//
// Vector.h
//
// Simple templated vector implementation
//
// 09.28.2008 Jon C. Martin

#ifndef _VECTOR_H
#define _VECTOR_H

namespace ecrobot // 03/13/2009 added by takashic
{
template <class T>
/**
 * Simple templated vector implementation.
 */
struct VectorT
{
public:

	/**
	 * Constructor.
	 * Initialized with 0.
	 */
	VectorT()
	:	mX(T(0))
	,	mY(T(0))
	{}
	
	/**
	 * Constructor.
	 * @param x First index value
	 * @param y Second index value
	 */
	VectorT(T x, T y)
	:	mX(x)
	,	mY(y)
	{}

	/** Add assignment */
	friend VectorT& operator+=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX += right.mX;
		left.mY += right.mY;

		return left;
	}
	/** Subtract assignment */
	friend VectorT& operator-=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX -= right.mX;
		left.mY -= right.mY;

		return left;
	}
	/** Multiply assignment */
	friend VectorT& operator*=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX *= right.mX;
		left.mY *= right.mY;

		return left;
	}
	/** Devision assignment */
	friend VectorT& operator/=(VectorT<T>& left, const VectorT<T>& right)
	{
		left.mX /= right.mX;
		left.mY /= right.mY;

		return left;
	}
	/** Add */
	friend VectorT operator+(const VectorT<T>& left, const VectorT<T>& right)
	{
		left += right;

		return left;
	}
	/** Subtract */
	friend VectorT operator- (const VectorT<T>& left, const VectorT<T>& right)
	{
		left -= right;

		return left;
	}
	/** Multiply */
	friend VectorT operator*(const VectorT<T>& left, const VectorT<T>& right)
	{
		left *= right;

		return left;
	}
	/** Devision */
	friend VectorT operator/ (const VectorT<T>& left, const VectorT<T>& right)
	{
		left /= right;

		return left;
	}

	/** Fist index value of VectorT */
	T mX;
	/** Second index value of VectorT */
	T mY;
};
}

#endif


