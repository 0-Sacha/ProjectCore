#pragma once

#include "FMTBufferIn.h"
#include "Integer.h"

namespace EngineCore::FMT::Detail {

	//------------------ Buffer Read Int ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void FMTBufferIn<CharBuffer>::ReadIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Dec:
				if (formatData.ShiftType == ShiftType::Nothing) FastReadInt(i);
				else											BasicReadInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				BasicReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				BasicReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				BasicReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		FastReadInt(i);
	}

	//------------------ Buffer Read UInt ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void FMTBufferIn<CharBuffer>::ReadUIntFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			switch (formatData.IntPrint) {
			case ValueIntPrint::Dec:
				if (formatData.ShiftType == ShiftType::Nothing) FastReadUInt(i);
				else											BasicReadUInt(i, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
			case ValueIntPrint::Bin:
				BasicReadIntAsBin(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			case ValueIntPrint::Hex:
				BasicReadIntAsHex(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue, formatData.PrintStyle);
			case ValueIntPrint::Oct:
				BasicReadIntAsOct(i, formatData.DigitSize, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint, formatData.TrueValue);
			}
		}
		FastReadUInt(i);
	}

	//------------------ Buffer Read Float ------------------//
	template<typename CharBuffer>
	template<typename T, typename FormatDataCharType>
	void FMTBufferIn<CharBuffer>::ReadFloatFormatData(T& i, const FormatData<FormatDataCharType>& formatData) {
		if (formatData.HasSpec) {
			if (formatData.ShiftType == ShiftType::Nothing)	FastReadFloat(i, formatData.FloatPrecision);
			else											BasicReadFloat(i, formatData.FloatPrecision, formatData.ShiftType, formatData.ShiftSize, formatData.ShiftPrint);
		}
		FastReadFloat(i, formatData.FloatPrecision);
	}
}