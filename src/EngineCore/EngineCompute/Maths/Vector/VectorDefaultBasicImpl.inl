#pragma once

#include "VectorDefaultBasicImpl.h"

namespace EngineCore::EngineCompute {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector()
		: data{} {}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& vec)
		: data{ vec.data } {}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto ... value)
		: data { static_cast<ValueType>(value)... } {}

	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto scalar) {
		std::fill(data.begin(), data.end(), static_cast<ValueType>(scalar));
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		data = vec.data;
	}

	
	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <std::size_t COUNT, typename ValueType>
	inline constexpr bool Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator==(const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		return data == rhs.data;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr bool Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator!=(const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		return !(*this == rhs);
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator&&(const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this, &rhs]() mutable { auto res = this->data[i] && rhs.data[i]; ++i; return res; });
		return newVec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator||(const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this, &rhs]() mutable { auto res = this->data[i] || rhs.data[i]; ++i; return res; });
		return newVec;
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+() const {
		return *this;
	}

	// operator -I
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-() const {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this]() mutable { auto res = -this->data[i]; ++i; return res; });
		return newVec;
	}

	// operator ~I
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator~() const {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this]() mutable { auto res = ~this->data[i]; ++i; return res; });
		return newVec;
	}


	// operator ++I
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator++() {
		for (ValueType& value : data)
			++value;
		return *this;
	}

	// operator --I
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator--() {
		for (ValueType& value : data)
			--value;
		return *this;
	}

	// operator I++
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator++(int) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator--(int) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}


	// operator =
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		std::fill(data.begin(), data.end(), static_cast<ValueType>(scalar));
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		data = vec.data;
		return *this;
	}

	// operator +=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value += scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value + vec.data[i]; i++; return res; });
		return *this;
	}

	// operator -=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value -= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value - vec.data[i]; i++; return res; });
		return *this;
	}

	// operator *=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value *= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator*=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value * vec.data[i]; i++; return res; });
		return *this;
	}

	// operator /=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value /= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator/=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value / vec.data[i]; i++; return res; });
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator%=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value %= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator%=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value % vec.data[i]; i++; return res; });
		return *this;
	}

	// operator &=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator&=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value &= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator&=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value & vec.data[i]; i++; return res; });
		return *this;
	}

	// operator |=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator|=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value |= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator|=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value | vec.data[i]; i++; return res; });
		return *this;
	}

	// operator ^=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator^=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value ^= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator^=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value ^ vec.data[i]; i++; return res; });
		return *this;
	}

	// operator <<=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator<<=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value <<= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator<<=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value << vec.data[i]; i++; return res; });
		return *this;
	}

	// operator >>=
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator>>=(const std::convertible_to<ValueType> auto scalar) {
		for (ValueType& value : data)
			value >>= scalar;
		return *this;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator>>=(const VectorConvertibleTo<COUNT, ValueType> auto& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](ValueType value) mutable { auto res = value >> vec.data[i]; i++; return res; });
		return *this;
	}


	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] + rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs + rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] + rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator -
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] - rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs - rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] - rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator *
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] * rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs * rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] * rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator /
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] / rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs / rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] / rhs.data[i]; ++i; return res; });
		return vec;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] % rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs % rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] % rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator &
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] & rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs & rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] & rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator |
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] | rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs | rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] | rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator ^
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] ^ rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs ^ rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] ^ rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator <<
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] << rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs << rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] << rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator >>
	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] >> rhs; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs >> rhs.data[i]; ++i; return res; });
		return vec;
	}

	template <std::size_t COUNT, typename ValueType>
	inline constexpr Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs) {
		Vector<COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] >> rhs.data[i]; ++i; return res; });
		return vec;
	}
}
