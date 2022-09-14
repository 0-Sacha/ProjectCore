#pragma once

#include "Formatter/Context/FormatContext/Utils/FormatType.h"
#include <unordered_set>

namespace EngineCore::FMT {
	template<typename T, typename FormatContext>
	struct FormatType<std::unordered_set<T>, FormatContext>
	{
		static void Write(const std::unordered_set<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::unordered_set<T>>, FormatContext>::Write(t, context);
		}
	};

	template<typename T, typename FormatContext>
	struct FormatType<std::unordered_multiset<T>, FormatContext>
	{
		static void Write(const std::unordered_multiset<T>& t, FormatContext& context) {
			FormatType<ForwardAsSTDEnumerable<std::unordered_multiset<T>>, FormatContext>::Write(t, context);
		}
	};
}