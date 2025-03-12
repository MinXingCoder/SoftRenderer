#pragma once
namespace math
{
	template <typename T>
	class Vector3;

	template <typename T>
	class Vector4;

	template <typename T>
	class Vector2
	{
	public:
		Vector2() : x(0), y(0)
		{}
		Vector2(T _x, T _y) : x(_x), y(_y)
		{}
		Vector2(const Vector2<T>& v) : x(v.x), y(v.y)
		{}
		Vector2(const Vector3<T>& v) : x(v.x), y(v.y)
		{}
		Vector2(const Vector4<T>& v) : x(v.x), y(v.y)
		{}

		T operator[](int i) const
		{
			STATIC_ASSERT(i >= 0 && i <= 1);
			if (i == 0) return x;
			if (i == 1) return y;
		}

		T& operator[](int i)
		{
			STATIC_ASSERT(i >= 0 && i <= 1);
			if (i == 0) return x;
			if (i == 1) return y;
		}

		Vector2<T> operator=(const Vector3<T>& v)
		{
			x = v.x; y = v.y;
			return *this;
		}

		Vector2<T> operator=(const Vector4<T>& v)
		{
			x = v.x; y = v.y;
			return *this;
		}

		Vector2<T> operator+(const Vector2<T>& v) const
		{
			return Vector2<T>(x + v.x, y + v.y);
		}

		Vector2<T> operator+=(const Vector2<T>& v)
		{
			x += v.x; y += v.y;
			return *this;
		}

		Vector2<T> operator*(T s) const
		{
			return Vector2<T>(x * s, y * s);
		}

		Vector2<T> operator*=(T s)
		{
			x *= s; y *= s;
			return *this;
		}

		Vector2<T> operator/(T s) const
		{
			float inv = static_cast<float>(1) / s;
			return Vector2<T>(x * inv, y * inv);
		}

		Vector2<T> operator/=(T s)
		{
			float inv = static_cast<float>(1) / s;
			x *= inv; y *= inv;
			return *this;
		}

		Vector2<T> operator-() const
		{
			return Vector2<T>(-x, -y);
		}

		void print()
		{
			std::cout << "Vector2 is:" << std::endl;
			std::cout << "x = " << x << ", y = " << y << std::endl;
			std::cout << std::endl;
		}

	public:
		T x;
		T y;
	};

	template <typename T>
	class Vector3
	{
	public:
		Vector3() : x(0), y(0), z(0)
		{}
		Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
		{}
		Vector3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z)
		{}
		Vector3(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z)
		{}

		T operator[](int i) const
		{
			STATIC_ASSERT(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			if (i == 2) return z;
		}

		T& operator[](int i)
		{
			STATIC_ASSERT(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			if (i == 2) return z;
		}

		Vector3<T> operator=(const Vector2<T>& v)
		{
			x = v.x; y = v.y;
			return *this;
		}

		Vector3<T> operator=(const Vector4<T>& v)
		{
			x = v.x; y = v.y; z = v.z;
			return *this;
		}

		Vector3<T> operator+(const Vector3<T>& v) const
		{
			return Vector3<T>(x + v.x, y + v.y, z + v.z);
		}

		Vector3<T> operator+=(const Vector3<T>& v)
		{
			x += v.x; y += v.y; z += v.z;
			return *this;
		}

		Vector3<T> operator-(const Vector3<T>& v)
		{
			return Vector3<T>(x - v.x, y - v.y, z - v.z);
		}

		Vector3<T> operator-=(const Vector3<T>& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
			return *this;
		}

		Vector3<T> operator*(T s) const
		{
			return Vector3<T>(x * s, y * s, z * s);
		}

		Vector3<T> operator*=(T s)
		{
			x *= s; y *= s; z *= s;
			return *this;
		}

		Vector3<T> operator/(T s) const
		{
			float inv = static_cast<float>(1) / s;
			return Vector3<T>(x * inv, y * inv, z * inv);
		}

		Vector3<T> operator/=(T s)
		{
			float inv = static_cast<float>(1) / s;
			x *= inv; y *= inv; z *= inv;
			return *this;
		}

		Vector3<T> operator-() const
		{
			return Vector3<T>(-x, -y, -z);
		}

		void print()
		{
			std::cout << "Vector3 is:" << std::endl;
			std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
			std::cout << std::endl;
		}

	public:
		T x;
		T y;
		T z;
	};

	template <typename T>
	class Vector4
	{
	public:
		Vector4() : x(0), y(0), z(0), w(0)
		{}
		Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w)
		{}
		Vector4(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w)
		{}

		T operator[](int i) const
		{
			STATIC_ASSERT(i >= 0 && i <= 3);
			if (i == 0) return x;
			if (i == 1) return y;
			if (i == 2) return z;
			if (i == 3) return w;
		}

		T& operator[](int i)
		{
			STATIC_ASSERT(i >= 0 && i <= 3);
			if (i == 0) return x;
			if (i == 1) return y;
			if (i == 2) return z;
			if (i == 3) return w;
		}

		Vector4<T> operator=(const Vector2<T>& v)
		{
			x = v.x; y = v.y;
			return *this;
		}

		Vector4<T> operator=(const Vector3<T>& v)
		{
			x = v.x; y = v.y; z = v.z; w = v.w;
			return *this;
		}

		Vector4<T> operator+(const Vector4<T>& v) const
		{
			return Vector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		Vector4<T> operator+=(const Vector4<T>& v)
		{
			x += v.x; y += v.y; z += v.z; w += v.w;
			return *this;
		}

		Vector4<T> operator-(const Vector4<T>& v) const
		{
			return Vector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		Vector4<T> operator-=(const Vector4<T>& v)
		{
			x -= v.x; y -= v.y; z -= v.z; w -= v.w;
			return *this;
		}

		Vector4<T> operator*(T s) const
		{
			return Vector4<T>(x * s, y * s, z * s, w * s);
		}
		
		Vector4<T> operator*=(T s)
		{
			x *= s; y *= s; z *= s; w *= s;
			return *this;
		}

		Vector4<T> operator*=(const Vector3<T>& v)
		{
			x *= v.x; y *= v.y; z *= v.z; w *= v.w;
			return *this;
		}

		Vector4<T> operator/(T f) const
		{
			float inv = static_cast<float>(1) / f;
			return Vector4(x * inv, y * inv, z * inv, w * inv);
		}

		Vector4<T> operator/=(T f)
		{
			float inv = static_cast<float>(1) / f;
			x *= inv; y *= inv; z *= inv; w *= inv;
			return *this;
		}

		Vector4<T> operator-() const
		{
			return Vector4<T>(-x, -y, -z, -w);
		}

		void print()
		{
			std::cout << "Vector4 is:" << std::endl;
			std::cout << "x = " << x << ", y = " << y << ", z = " << z << ", w = " << w << std::endl;
			std::cout << std::endl;
		}

	public:
		T x;
		T y;
		T z;
		T w;
	};

	using vec2f = Vector2<float>;
	using vec2i = Vector2<int>;
	using vec3f = Vector3<float>;
	using vec3i = Vector3<int>;
	using vec4f = Vector4<float>;
	using vec4i = Vector4<int>;
}