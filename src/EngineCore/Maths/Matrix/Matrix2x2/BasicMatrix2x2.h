#pragma once

#include "../Matrix.h"


namespace EngineCore {

	//------------- Matrix2x2 -------------//
	template <typename Type>
	struct Matrix<2, 2, Type, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType		= Type;
		using ColumnType	= Vector<2, ValueType, EngineCompute::EngineComputeBasic>;
		using RowType		= Vector<2, ValueType, EngineCompute::EngineComputeBasic>;

		union {
			std::array<ValueType, 4>	data;
			std::array<RowType, 2>		rows;
		};

		static inline constexpr std::size_t GetNumberOfColumns()			{ return 2; }
		static inline constexpr std::size_t GetNumberOfRows()				{ return 2; }
		static inline constexpr std::size_t GetNumberOfElementsInAColumn()	{ return GetNumberOfRows(); }
		static inline constexpr std::size_t GetNumberOfElementsInARow()		{ return GetNumberOfColumns(); }
		static inline constexpr std::size_t GetMaxNumberOfElements()		{ return GetNumberOfColumns() * GetNumberOfRows(); }

		inline constexpr std::array<ValueType, 4>&			GetArray()				{ return data; }
		inline constexpr const std::array<ValueType, 4>&	GetArray() const		{ return data; }
		inline constexpr std::array<RowType, 2>&			GetRowsArray()			{ return rows; }
		inline constexpr const std::array<RowType, 2>&		GetRowsArray() const	{ return rows; }

		inline constexpr RowType& operator[](const std::size_t idx)				{ ENGINE_CORE_ASSERT(idx < GetMaxNumberOfElements()); return rows[idx]; }
		inline constexpr const RowType& operator[](const std::size_t idx) const { ENGINE_CORE_ASSERT(idx < GetMaxNumberOfElements()); return rows[idx]; }

		inline constexpr RowType GetRow(const std::size_t idx) const			{ return rows[idx]; }
		inline constexpr void SetRow(const std::size_t idx, const RowType& row)	{ rows[idx] = row; }

		inline constexpr ColumnType GetColumn(const std::size_t idx) const				{ return ColumnType(data[idx], data[idx + 2]); }
		inline constexpr void SetColumn(const std::size_t idx, const ColumnType& col)	{ data[idx] = col.x; data[idx + 2] = col.y; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		// Construct as identity
		constexpr Matrix();

		// Copy Matrix
		constexpr Matrix(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);
	
		// Construct as multiple of the identity matrix
		constexpr Matrix(const std::convertible_to<ValueType> auto scalar);
		
		// Initialization with row-major order
		constexpr Matrix(	const std::convertible_to<ValueType> auto x0, const std::convertible_to<ValueType> auto y0,
							const std::convertible_to<ValueType> auto x1, const std::convertible_to<ValueType> auto y1);
		
		// Initialize both rows
		constexpr Matrix(const VectorConvertibleTo<2, ValueType> auto&& row0, const VectorConvertibleTo<2, ValueType> auto&& row1);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//


		//------------------------------------------------//
		//------------- Main Matrix Function -------------//
		//------------------------------------------------//
		// 
		// Not sure for the name
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& ComputeMultAsAddInPlace(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);
		// Not sure for the name
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  ComputeMultAsAdd(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);

		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> Transpose();

		constexpr ValueType Determinant();

		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> Inverse();

		// Row, column
		static constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> FromOuterProduct(const VectorConvertibleTo<2, ValueType> auto&& row0, const VectorConvertibleTo<2, ValueType> auto&& row1);
		
		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//

		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);
		constexpr bool operator!=(const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator+();
		// operator -I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator-();

		// operator ++I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator--(int);


		// operator =
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);

		// operator +=
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);

		// operator -=
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);

		// operator *=
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);

		// operator /=
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat);
	};

	// -----------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator+(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator+(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);

	// operator -
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator-(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator-(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);
	
	// operator *
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);

	// row in input
	template<typename ValueType> constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ColumnType operator*(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs);
	// column in input
	template<typename ValueType> constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::RowType operator*(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);

	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);
	template<typename ValueType> constexpr Matrix<3, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const MatrixConvertibleTo<3, 2, ValueType> auto& rhs);
	template<typename ValueType> constexpr Matrix<4, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const MatrixConvertibleTo<4, 2, ValueType> auto& rhs);


	// operator /
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator/(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);

	// row in input
	template<typename ValueType> constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ColumnType operator/(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs);
	// column in input
	template<typename ValueType> constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::RowType operator/(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);

	template<typename ValueType> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator/(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);
}