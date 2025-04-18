#pragma once

#include <string.h>
#include <assert.h>
#include "vector.h"
#include <iostream>

namespace math
{
	template <typename T>
	class Matrix44;

	template <typename T>
	class Matrix33
	{
	public:
		/*
		* 0, 3, 6,
		* 1, 4, 7,
		* 2, 5, 8
		*/

		Matrix33() = default;
		Matrix33(T v)
		{
			m[0] = m[4] = m[8] = v;
		}
		Matrix33(const Matrix33<T>& src)
		{
			memcpy((void*)m, (void*)src.m, sizeof(T) * 9);
		}
		/*
		*   0,4,8,12,
		*   1,5,9,13,
		*   2,6,10,14,
		*   3,7,11,15
		*/
		Matrix33(const Matrix44<T>& src)
		{
			m[0] = src.m[0]; m[3] = src.m[4]; m[6] = src.m[8];
			m[1] = src.m[1]; m[4] = src.m[5]; m[7] = src.m[9];
			m[2] = src.m[2]; m[5] = src.m[6]; m[8] = src.m[10];
		}

		Matrix33 operator*(const T& s)
		{
			Matrix33<T> result;

			auto col0 = this->getColum(0) * s;
			auto col1 = this->getColum(1) * s;
			auto col2 = this->getColum(2) * s;

			result.setColum(col0, 0);
			result.setColum(col1, 1);
			result.setColum(col2, 2);

			return result;
		}

		Vector3<T> operator*(const Vector3<T>& v)
		{
			return Vector3<T>(
				m[0] * v.x + m[3] * v.y + m[6] * v.z,
				m[1] * v.x + m[4] * v.y + m[7] * v.z,
				m[2] * v.x + m[5] * v.y + m[8] * v.z
			);
		}

		void set(T m00, T m01, T m02, 
					  T m10, T m11, T m12, 
					  T m20, T m21, T m22)
		{
			m[0] = m00; m[3] = m01; m[6] = m02;
			m[1] = m10; m[4] = m11; m[7] = m12;
			m[2] = m20; m[5] = m21; m[8] = m22;
		}

		void set(const uint32_t& row, const uint32_t& col, T t)
		{
			assert(row < 3 && col < 3);
			m[col * 3 + row] = t;
		}

		Matrix33 identity()
		{
			set(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1
			);

			return *this;
		}

		Vector3<T> getColum(const uint32_t& col) const
		{
			assert(col < 3);
			return Vector3<T>(m[col * 3], m[col * 3] + 1, m[col * 3] + 2);
		}

		void setColum(const Vector3<T>& cvalue, const uint32_t& col)
		{
			assert(col < 3);
			m[col * 3] = cvalue.x;
			m[col * 3 + 1] = cvalue.y;
			m[col * 4 + 2] = cvalue.z;
		}

		void printMatrix() const
		{
			std::cout << "Matrix33 is:" << std::endl;
			std::cout << m[0] << "," << m[3] << "," << m[6] << std::endl;
			std::cout << m[1] << "," << m[4] << "," << m[7] << std::endl;
			std::cout << m[2] << "," << m[5] << "," << m[8] << std::endl;
			std::cout << std::endl;
		}

	public:
		T m[9] = { 1, 0, 0,
						0, 1, 0
						0, 0, 1 };
	};

	/*
	* 0,4,8,12
	* 1,5,9,13
	* 2,6,10,14
	* 3,7,11,15
	*/
	template <typename T>
	class Matrix44
	{
	public:
		Matrix44() {}
		
		Matrix44(T v)
		{
			m[0] = m[5] = m[10] = m[15] = v;
		}
		Matrix44(const Matrix44<T>& src)
		{
			memcpy((void*)m, src.m, sizeof(T) * 16);
		}

		Matrix44 operator*(const T& s)
		{
			Matrix44 result;
			auto col0 = getColum(0) * s;
			auto col1 = getColum(1) * s;
			auto col2 = getColum(2) * s;
			auto col3 = getColum(3) * s;

			result.setColum(col0, 0);
			result.setColum(col1, 1);
			result.setColum(col2, 2);
			result.setColum(col3, 3);

			return result;
		}

		Vector4<T> operator*(const Vector4<T>& v)
		{
			return Vector4<T>(m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w,
											m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w,
											m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w,
											m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w);
		}

		T get(const uint32_t& row, const uint32_t& col) const
		{
			return m[col * 4 + row];
		}

		void set(const uint32_t& row, const uint32_t& col, T t)
		{
			assert(row < 4 && col < 4);
			m[col * 4 + row] = t;
		}

		void set(T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33)
		{
			m[0] = m00; m[4] = m01; m[8] = m02; m[12] = m03;
			m[1] = m10; m[5] = m11; m[9] = m12; m[13] = m13;
			m[2] = m20; m[6] = m21; m[10] = m22; m[14] = m23;
			m[3] = m30; m[7] = m31; m[11] = m32; m[15] = m33;
		}

		Matrix44<T> identity()
		{
			set(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
			return *this;
		}

		Vector4<T> getColum(const uint32_t& col) const
		{
			assert(col < 4);
			return Vector4<T>(
				m[col * 4], m[col * 4 + 1], m[col * 4 + 2], m[col * 4 +3]
			);
		}

		void setColum(const Vector4<T>& cvalue, const uint32_t& col)
		{
			assert(col < 4);
			m[col * 4] = cvalue.x;
			m[col * 4 + 1] = cvalue.y;
			m[col * 4 + 2] = cvalue.z;
			m[col * 4 + 3] = cvalue.w;
		}

		void printMatrix() const
		{
			std::cout << "Matrix44 is:" << std::endl;
			std::cout << m[0] << "," << m[4] << "," << m[8] << "," << m[12] << std::endl;
			std::cout << m[1] << "," << m[5] << "," << m[9] << "," << m[13] << std::endl;
			std::cout << m[2] << "," << m[6] << "," << m[10] << "," << m[14] << std::endl;
			std::cout << m[3] << "," << m[7] << "," << m[11] << "," << m[15] << std::endl;
			std::cout << std::endl;
		}

	public:
		T m[16] = { 1, 0, 0, 0,
						   0, 1, 0, 0,
						   0, 0, 1, 0,
						   0, 0, 0, 1 };
	};

	using mat3f = Matrix33<float>;
	using mat4f = Matrix44<float>;
}