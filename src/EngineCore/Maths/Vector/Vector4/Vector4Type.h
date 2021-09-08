#pragma once

#include "../Vector.h"

namespace EngineCore {

	template<typename T, typename ComputeAlgorithm>
	struct Vector<4, T, ComputeAlgorithm>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//
		union {
			struct { T x, y, z, w; };
		};

		inline constexpr static size_t Length() { return 4; }
		inline constexpr static size_t Count() { return 4; }
		inline constexpr static size_t Size() { return 4; }

		constexpr T& Data(const uint8_t idx);
		constexpr const T& Data(const uint8_t idx) const;

		constexpr T& operator[](const uint8_t idx);
		constexpr const T& operator[](const uint8_t idx) const;


		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//
		constexpr Vector();
		template<typename K> constexpr Vector(K scalar);
		template<typename K1, typename K2, typename K3, typename K4> constexpr Vector(K1 x, K2 y, K3 z, K4 w);
		template<typename K> constexpr Vector(const Vector<4, K>& vec);



		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//



		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const Vector<4, T>& rhs) const;
		constexpr bool operator!=(const Vector<4, T>& rhs) const;



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<4, T> operator+();
		// operator -I
		constexpr Vector<4, T> operator-();
		// operator ++I
		template<typename K> constexpr Vector<4, T>& operator++();
		// operator --I
		template<typename K> constexpr Vector<4, T>& operator--();
		// operator I++
		template<typename K> constexpr Vector<4, T>  operator++(int);
		// operator I--
		template<typename K> constexpr Vector<4, T>  operator--(int);

		// operator =
		template<typename K> constexpr Vector<4, T>& operator=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator=(const Vector<4, K>& vec);

		// operator +=
		template<typename K> constexpr Vector<4, T>& operator+=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator+=(const Vector<4, K>& vec);

		// operator -=
		template<typename K> constexpr Vector<4, T>& operator-=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator-=(const Vector<4, K>& vec);

		// operator *=
		template<typename K> constexpr Vector<4, T>& operator*=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator*=(const Vector<4, K>& vec);

		// operator /=
		template<typename K> constexpr Vector<4, T>& operator/=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator/=(const Vector<4, K>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator ~I
		constexpr Vector<4, T> operator~();

		constexpr Vector<4, T> operator&&(const Vector<4, T>& rhs);
		constexpr Vector<4, T> operator||(const Vector<4, T>& rhs);

		// operator %=
		template<typename K> constexpr Vector<4, T>& operator%=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator%=(const Vector<4, K>& vec);

		// operator &=
		template<typename K> constexpr Vector<4, T>& operator&=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator&=(const Vector<4, K>& vec);

		// operator |=
		template<typename K> constexpr Vector<4, T>& operator|=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator|=(const Vector<4, K>& vec);

		// operator ^=
		template<typename K> constexpr Vector<4, T>& operator^=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator^=(const Vector<4, K>& vec);

		// operator <<=
		template<typename K> constexpr Vector<4, T>& operator<<=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator<<=(const Vector<4, K>& vec);

		// operator >>=
		template<typename K> constexpr Vector<4, T>& operator>>=(const K scalar);
		template<typename K> constexpr Vector<4, T>& operator>>=(const Vector<4, K>& vec);
	};



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K> constexpr Vector<4, T> operator+(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator+(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator+(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator -
	template<typename T, typename K> constexpr Vector<4, T> operator-(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator-(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator-(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator *
	template<typename T, typename K> constexpr Vector<4, T> operator*(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator*(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator*(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator /
	template<typename T, typename K> constexpr Vector<4, T> operator/(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator/(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator/(const Vector<4, T>& lhs, const Vector<4, K>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K> constexpr Vector<4, T> operator%(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator%(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator%(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator &
	template<typename T, typename K> constexpr Vector<4, T> operator&(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator&(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator&(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator |
	template<typename T, typename K> constexpr Vector<4, T> operator|(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator|(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator|(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator ^
	template<typename T, typename K> constexpr Vector<4, T> operator^(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator^(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator^(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator <<
	template<typename T, typename K> constexpr Vector<4, T> operator<<(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator<<(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator<<(const Vector<4, T>& lhs, const Vector<4, K>& rhs);

	// operator >>
	template<typename T, typename K> constexpr Vector<4, T> operator>>(const Vector<4, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator>>(const K lhs, const Vector<4, T>& rhs);
	template<typename T, typename K> constexpr Vector<4, T> operator>>(const Vector<4, T>& lhs, const Vector<4, K>& rhs);
}


#include "Vector4Type.inl"
