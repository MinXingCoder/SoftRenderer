#pragma once
#include "vector.h"

namespace math
{
	template<typename T, typename S>
	inline Vector2<T> operator * (S s, const Vector2<T>& v)
	{
		return v * s;
	}

	template<typename T, typename S>
	inline Vector3<T> operator * (S s, const Vector3<T>& v)
	{
		return v * s;
	}

	template<typename T, typename S>
	inline Vector4<T> operator * (S s, const Vector4<T>& v)
	{
		return v * s;
	}

	template<typename T>
	inline Vector2<T> operator * (const Vector2<T>& v0, const Vector2<T>& v1)
	{
		return Vector2<T>(v0.x * v1.x, v0.y * v1.y);
	}

	template<typename T>
	inline Vector3<T> operator * (const Vector3<T>& v0, const Vector3<T>& v1)
	{
		return Vector3<T>(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
	}

	template<typename T>
	inline Vector4<T> operator * (const Vector4<T>& v0, const Vector4<T>& v1)
	{
		return Vector4<T>(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
	}

	template<typename T>
	inline Vector2<T> abs(const Vector2<T>& v)
	{
		return Vector2<T>(std::abs(v.x), std::abs(v.y));
	}

	template<typename T>
	inline Vector3<T> abs(const Vector3<T>& v)
	{
		return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}

	template<typename T>
	inline Vector4<T> abs(const Vector4<T>& v)
	{
		return Vector4<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w));
	}

	template<typename T>
	inline T dot(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return (v1.x * v2.x, +v1.y * v2.y);
	}

	template<typename T>
	inline T dot(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}

	template<typename T>
	inline T dot(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
	}

	template<typename T>
	inline T cross(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return (v1.y * v2.x - v1.x * v2.y);
	}

	template<typename T>
	inline Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	template<typename T>
	inline float lengthSquared(const Vector2<T>& v)
	{
		return v.x * v.x + v.y * v.y;
	}

	template<typename T>
	inline float lengthSquared(const Vector3<T>& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}

	template<typename T>
	inline float lengthSquared(const Vector4<T>& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}

	template<typename T>
	inline T length(const Vector2<T>& v)
	{
		return std::sqrt(lengthSquared(v));
	}

	template<typename T>
	inline T length(const Vector3<T>& v)
	{
		return std::sqrt(lengthSquared(v));
	}

	template<typename T>
	inline T length(const Vector4<T>& v)
	{
		return std::sqrt(lengthSquared(v));
	}

	template<typename T>
	inline Vector2<T> normalize(const Vector2<T>& v)
	{
		return v / length(v);
	}

	template<typename T>
	inline Vector3<T> normalize(const Vector3<T>& v)
	{
		return v / length(v);
	}

	template<typename  T>
	inline Vector4<T> normalize(const Vector4<T>& v)
	{
		return v / length(v);
	}
}