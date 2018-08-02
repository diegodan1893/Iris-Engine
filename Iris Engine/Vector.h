#pragma once

#include <cinttypes>

template<typename T>
struct Vector2
{
	T x;
	T y;

	Vector2() {}
	Vector2(T x, T y)
		:x(x),
		 y(y)
	{
	}

	inline Vector2& operator=(const Vector2& other)
	{
		if (this != &other)
		{
			this->x = other.x;
			this->y = other.y;
		}

		return *this;
	}

	inline Vector2& operator+=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	inline Vector2& operator-=(const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	inline Vector2& operator*=(const T& other)
	{
		this->x *= other;
		this->y *= other;

		return *this;
	}

	inline Vector2& operator/=(const T& other)
	{
		this->x /= other;
		this->y /= other;

		return *this;
	}

	friend Vector2 operator+(Vector2 lhs, const Vector2& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend Vector2 operator-(Vector2 lhs, const Vector2& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend Vector2 operator*(Vector2 lhs, const T& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	friend Vector2 operator*(const T& lhs, Vector2 rhs)
	{
		rhs *= lhs;
		return rhs;
	}

	friend Vector2 operator/(Vector2 lhs, const T& rhs)
	{
		lhs /= rhs;
		return lhs;
	}

	friend Vector2 operator/(const T& lhs, Vector2 rhs)
	{
		rhs /= lhs;
		return rhs;
	}
};

template<typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	Vector3() {}
	Vector3(T x, T y, T z)
		:x(x),
		 y(y),
		 z(z)
	{
	}
};

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	Color() {}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
		:r(r),
		 g(g),
		 b(b),
		 a(a)
	{
	}
};

struct Margin
{
	int top;
	int right;
	int bottom;
	int left;

	Margin() {}
	Margin(int top, int right, int bottom, int left)
		:top(top),
		 right(right),
		 bottom(bottom),
		 left(left)
	{
	}
};

template<typename T>
struct Rect
{
	T x;
	T y;
	T w;
	T h;

	Rect() {}
	Rect(T x, T y, T w, T h)
		:x(x),
		 y(y),
		 w(w),
		 h(h)
	{
	}
};

template<typename T>
inline T lerp(const T& a, const T& b, float alpha)
{
	return (1.0f - alpha) * a + alpha * b;
}
