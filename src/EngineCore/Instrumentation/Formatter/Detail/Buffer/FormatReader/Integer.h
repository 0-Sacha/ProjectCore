#pragma once

<<<<<<<< HEAD:src/EngineCore/FMT/Core/Buffer/FormatReader/Integer.h
#include "FMT/Core/Buffer/Format.h"
========
#include "FMT/Detail/Buffer/Format.h"
>>>>>>>> 040fab10b4777918832b29a04b07add2d411d3ab:src/EngineCore/Instrumentation/Formatter/Detail/Buffer/FormatReader/Integer.h

namespace EngineCore::FMT::Detail {
	template<typename CharFormat>
	template<typename T>
	bool FormatterMemoryFormat<CharFormat>::ReadInt(T& i) {
		T res{};
		bool sign		= IsEqualToForward('-');
		bool isValid	= IsADigit();

		while (IsADigit())
			res = res * 10 + static_cast<T>(GetAndForward() - '0');

		if (isValid)
			i = sign ? -res : res;

		return isValid;
	}

	template<typename CharFormat>
	template<typename T>
	bool FormatterMemoryFormat<CharFormat>::ReadUInt(T& i) {
		T res{};
		bool isValid = IsADigit();

		while (IsADigit())
			res = res * 10 + static_cast<T>(GetAndForward() - '0');

		if (isValid) i = res;

		return isValid;
	}
}