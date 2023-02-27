#pragma once

#include "EngineCore/FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextFront::Front, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextFront::Front t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', t.FrontId, 'm');
			context.GetTextPropertiesParser().FrontModif(t);
		}
	};

}


