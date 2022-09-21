#pragma once

#include "BasicContext.h"
#include "BasicContextCoreImpl.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	std::basic_string_view<CharFormat> BasicContext<CharFormat, ContextPackageSaving, Master>::ParseNextOverrideFormatData() {
		m_Format.IgnoreSpace();
		m_Format.ParamGoTo('{', '=', ':');
		m_Format.IgnoreSpace();
		m_Format.IsEqualToForward('=', ':');
		m_Format.IgnoreSpace();
		m_Format.ParamGoTo('{');

		const CharFormat* begin = m_Format.GetBufferCurrentPos();
		m_Format.IsEqualToForwardThrow('{');
		int scopes = 0;
		while (m_Format.IsEndOfParameter() == false || scopes > 0)
		{
			m_Format.GoTo('\'', '}', '{');
			if (m_Format.IsEqualToForward('\''))
				m_Format.GoToForward('\'');
			else if (m_Format.IsEqualToForward('{'))
				scopes++;
			else if (scopes > 0 && m_Format.IsEqualToForward('}'))
				scopes--;
		}
		m_Format.IsEqualToForwardThrow('}');
		const CharFormat* end = m_Format.GetBufferCurrentPos();
		return std::basic_string_view<CharFormat>(begin, end);
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataBase_ValueIntPrint(const Detail::ValueIntPrint type) {
		m_FormatData.IntPrint = type;
		if (m_Format.IsEqualToForward('#')) m_FormatData.TrueValue = true;
		FormatReadParameterThrow(m_FormatData.DigitSize.Value);
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataBase() {

			 if (m_Format.IsEqualToForward('C')) { ParseFormatDataColor(); }
		else if (m_Format.IsEqualToForward('S')) { ParseFormatDataStyle(); }
		else if (m_Format.IsEqualToForward('F')) { ParseFormatDataFront(); }

		else if (m_Format.IsEqualToForward('B')) { ParseFormatDataBase_ValueIntPrint(Detail::ValueIntPrint::Bin); }
		else if (m_Format.IsEqualToForward('X')) { ParseFormatDataBase_ValueIntPrint(Detail::ValueIntPrint::Hex); }
		else if (m_Format.IsEqualToForward('O')) { ParseFormatDataBase_ValueIntPrint(Detail::ValueIntPrint::Oct); }
		else if (m_Format.IsEqualToForward('D')) { ParseFormatDataBase_ValueIntPrint(Detail::ValueIntPrint::Dec); }

		else if (m_Format.IsEqualToForward('L')) { m_FormatData.PrintStyle = Detail::PrintStyle::LowerCase; }
		else if (m_Format.IsEqualToForward('U')) { m_FormatData.PrintStyle = Detail::PrintStyle::UpperCase; }

		else if (m_Format.IsEqualToForward('A')) { m_FormatData.Safe = true; }

		else if (m_Format.IsEqualToForward('W')) { m_FormatData.KeepNewStyle = true; }

		else if (m_Format.IsEqualToForward('N')) { m_FormatData.NextOverride = ParseNextOverrideFormatData(); }
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataSpecial_ShiftType(const Detail::ShiftType type) {
		m_FormatData.ShiftType = type;
		FormatReadParameterThrow(m_FormatData.ShiftSize.Value);
		if (m_Format.IsEqualToForward(':'))
		{
			m_FormatData.ShiftPrint.Before = m_Format.GetAndForward();
			m_FormatData.ShiftPrint.After = m_FormatData.ShiftPrint.Before;
			if (m_Format.IsEqualToForward('|'))
				m_FormatData.ShiftPrint.After = m_Format.GetAndForward();
			m_FormatData.ShiftPrint.Validate();
		}
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataSpecial() {
		if (m_Format.IsEqualToForward('{'))
		{
			Detail::FormatIndex formatIndex = GetFormatIndexThrow();
			if ((m_FormatData.ModifyTestThrow(GetTypeAtIndex<FormatDataType>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::ValueIntPrint>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::PrintStyle>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::DigitSize>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::ShiftSize>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::FloatPrecision>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::ShiftPrint>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::ShiftType>(formatIndex))
			 || m_FormatData.ModifyTestThrow(GetTypeAtIndex<Detail::FormatSpecifier<CharFormat>>(formatIndex))) == false)
			throw Detail::FormatGivenTypeError{};
			m_Format.IsEqualToForwardThrow('}');
		}
		else if (m_Format.IsEqualToForward('=')) { m_FormatData.TrueValue = true; }

		else if (m_Format.IsEqualToForward('.')) { FormatReadParameterThrow(m_FormatData.FloatPrecision.Value); }

		else if (m_Format.IsEqualToForward('>')) { ParseFormatDataSpecial_ShiftType(Detail::ShiftType::Right); 	}
		else if (m_Format.IsEqualToForward('<')) { ParseFormatDataSpecial_ShiftType(Detail::ShiftType::Left); 	}
		else if (m_Format.IsEqualToForward('^')) { ParseFormatDataSpecial_ShiftType(Detail::ShiftType::Center); }
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataCustom() {
		StringViewFormat name = GetStringViewParamUntil(' ', '=', '\'', '{', ',');
		m_Format.ParamGoTo('=', '\'', '{', ',');
		m_Format.IsEqualToForward('=');
		m_Format.IgnoreSpace();

		if (m_Format.IsEqualToForward('\'')) {
			StringViewFormat value = GetStringViewUntil('\'');
			m_FormatData.AddSpecifier(name, value);
		}
		else if (m_Format.IsADigit()) {
			Detail::DataType value = ReadDataType();
			m_FormatData.AddSpecifier(name, value);
		}
		else if (m_Format.IsEqualToForward('{')) {
			Detail::FormatIndex idx = GetFormatIndexThrow();
			// FIXME
			// m_FormatData.AddSpecifier(name, GetTypeAtIndexAuto(idx));
			m_Format.IsEqualToForward('}');
		}
		else if (m_Format.IsEqualTo(',', '}')) {
			m_FormatData.AddSpecifier(name);
		}
	}

	/////---------- Impl ----------/////
	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatData() {
		// ':' for classic use ; '{' for NextOverride
		if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('{')) {
			m_FormatData.HasSpec = true;
			while (!m_Format.IsEndOfParameter()) {
				m_Format.Forward();
				m_Format.IgnoreSpace();

				if(m_Format.IsUpperCase())
					ParseFormatDataBase();
				else if(!m_Format.IsLowerCase())
					ParseFormatDataSpecial();
				else
					ParseFormatDataCustom();

				m_Format.ParamGoTo(',');
			}
		}
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	Detail::FormatIndex BasicContext<CharFormat, ContextPackageSaving, Master>::GetFormatIndexThrow() {
		const CharFormat* mainSubFormat = m_Format.GetBufferCurrentPos();

		// I : if there is no number specified : ':' or '}'
		if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}'))
			if(m_ValuesIndex.IsValid())
				return m_ValuesIndex.GetAndNext();

		// II: A number(idx)
		Detail::FormatIndex subIndex;
		subIndex.SetContext(m_ValuesIndex);
		if (m_Format.ReadUInt(subIndex.Index))
			if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}'))
				if (subIndex.IsValid())
					return subIndex;

		m_Format.SetBufferCurrentPos(mainSubFormat);

		// III : A name
		Detail::FormatIndex indexOfNamedArg = GetIndexOfCurrentNameArg();
		indexOfNamedArg.SetContext(m_ValuesIndex);
		if(indexOfNamedArg.IsValid())
			return indexOfNamedArg;

		m_Format.SetBufferCurrentPos(mainSubFormat);

		// VI : { which is a idx to a number
		if (m_Format.IsEqualToForward('{'))
		{
			try {
				Detail::FormatIndex recIndex = GetFormatIndexThrow();
				recIndex.SetContext(m_ValuesIndex);

				if(recIndex.IsValid())
				{
					m_Format.IsEqualToForwardThrow('}');
					Detail::FormatIndex finalRecIndex = GetTypeAtIndexConvertThrow<Detail::FormatIndex>(recIndex);
					finalRecIndex.SetContext(m_ValuesIndex);
					if(finalRecIndex.IsValid())
						return finalRecIndex;
				}
				
				throw Detail::FormatParseError();

			} catch (const Detail::FormatError&)
			{}
		}
		m_Format.SetBufferCurrentPos(mainSubFormat);

		return Detail::FormatIndex();
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseSpecial() {
			 if (m_Format.IsEqualTo('C') && m_Format.NextIsEqualToForward(':', '}'))		{ ParseColor(); 	}
		else if (m_Format.IsEqualTo('S') && m_Format.NextIsEqualToForward(':', '}'))		{ ParseStyle(); 	}
		else if (m_Format.IsEqualTo('F') && m_Format.NextIsEqualToForward(':', '}'))		{ ParseFront(); 	}
		else if (m_Format.IsEqualTo('T') && m_Format.NextIsEqualToForward(':', '}'))		{ ParseTimer(); 	}
		else if (m_Format.IsEqualTo('D') && m_Format.NextIsEqualToForward(':', '}'))		{ ParseDate(); 		}
		else if (m_Format.IsEqualTo('K') && m_Format.NextIsEqualToForward(':'))			{ ParseSetter();	}
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseVariable(Detail::FormatIndex formatIdx) {
		FormatDataType saveFormatData = m_FormatData;
		m_FormatData = FormatDataType{};
		ContextPackageSaving savePackage = ContextStyleSave();

		if (!m_FormatData.IsInit)
			ParseFormatData();

		RunTypeAtIndex(formatIdx);

		if (m_FormatData.KeepNewStyle == false)
			ContextStyleRestore(savePackage);

		m_FormatData = saveFormatData;
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	bool BasicContext<CharFormat, ContextPackageSaving, Master>::Parse() {
		m_Format.Forward();						// Skip {

		if (m_Format.IsUpperCase()) {
			ParseSpecial();
			m_Format.GoOutOfParameter();		// Skip }
			return true;
		}

		Detail::FormatIndex formatIdx = GetFormatIndexThrow();
		if (formatIdx.IsValid()) {
			ParseVariable(formatIdx);
			m_Format.GoOutOfParameter();		// Skip }
			return true;
		}

		return false;
	}
}


