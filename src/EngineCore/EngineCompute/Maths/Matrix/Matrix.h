#pragma once

#include "EngineCore/EngineCompute/Maths/Vector/Vector.h"

namespace EngineCore::EngineCompute {

	// Matrix are row-major order
	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename ComputeAlgorithm = Detail::EngineCompute::EngineComputeDefault>
	struct Matrix;

	template <typename From, std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	concept MatrixConvertibleTo = requires(From to) {
		requires From::GetNumberOfColumns() == COLUMNS_COUNT;
		requires From::GetNumberOfRows()	== ROWS_COUNT;
		requires std::is_convertible_v<typename From::ValueType, T>;
	};

	template <typename From, typename MatType>
	concept MatrixConvertibleToM = requires(From to) {
		requires From::GetNumberOfColumns() == MatType::GetNumberOfColumns();
		requires From::GetNumberOfRows()	== MatType::GetNumberOfRows();
		requires std::is_convertible_v<typename From::ValueType, typename MatType::ValueType>;
	};
}

namespace EngineCore::EngineCompute {

template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename FormatContext>
struct EngineCore::Instrumentation::Fmt::FormatType<EngineCore::EngineCompute::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, FormatContext>
{
	static void Write(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& mat, FormatContext& context) {
		context.BufferOut().PushBack('{');

		std::size_t stride = context.GetStride();

		bool first = true;
		for (auto i = 0; i < mat.GetNumberOfRows(); ++i) {
			if (first)  first = false;
			else		{ context.BufferOut().PushBack('\n'); context.BufferOut().AddSpaces(stride); }
			context.WriteType(mat.GetRow(i));
		}

		context.BufferOut().PushBack('}');
	}
};

template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename UnFormatContext>
struct EngineCore::Instrumentation::Fmt::UnFormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, UnFormatContext>
{
	static void Read(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& mat, UnFormatContext& context) {
		context.BufferOut().IsEqualForwardThrow('{');
		bool first = true;
		for (auto i = 0; i < mat.GetNumberOfRows(); ++i) {
			if (first)	first = false;
			else		{ context.BufferOut().PushBack(','); context.BufferOut().PushBack(' '); }

			typename EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>::RowType row;
			context.ReadType(row);
			mat.SetRow(row);
		}
		context.BufferOut().IsEqualForwardThrow('}');
	}
};









