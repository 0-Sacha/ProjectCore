#pragma once

#include "ProjectCore/FMT/Context/BasicContext/BasicContextInclude.h"
#include "ProjectCore/FMT/Detail/Buffer/FMTBufferIn/FMTBufferIn.h"

#include "ParserType.h"

#include "ParserContextArgsTuple.h"

#include "ParserTextPropertiesExecutor/IParserTextPropertiesExecutor.h"

namespace ProjectCore::FMT::Context
{
    template<typename CharFormat, typename CharBuffer>
    class BasicParserContext : public BasicContext<CharFormat>
    {
    public:
        using Base = BasicContext<CharFormat>;
        using M_Type = BasicParserContext<CharFormat, CharBuffer>;

        friend Base;

        using typename Base::CharFormatType;
        using typename Base::FormatDataType;
        using typename Base::StringViewFormat;
        using typename Base::FormatBufferType;
        using typename Base::ContextArgsInterface;
        using typename Base::TextPropertiesParser;

        using StringViewBuffer    = std::basic_string_view<CharBuffer>;
        using BufferInType        = Detail::FMTBufferIn<CharBuffer>;

    public:
        BasicParserContext(Detail::BufferInProperties<CharBuffer> bufferProperties, Detail::IParserTextPropertiesExecutor<BufferInType>& textPropertiesExecutor, const Detail::TextProperties::Properties* parentContextProperties = nullptr);
        ~BasicParserContext() override = default;

    protected:
        using Base::m_Format;
        using Base::m_ValuesIndex;
        using Base::m_FormatData;
        using Base::m_ContextArgsInterface;
        using Base::m_TextPropertiesParser;

        BufferInType         m_BufferIn;

    public:
        using Base::Format;
        using Base::GetFormatData;
        using Base::ForwardFormatData;
        using Base::SetFormatData;

        inline BufferInType& BufferIn()                    { return m_BufferIn; }
        inline const BufferInType& BufferIn() const        { return m_BufferIn; }

    public:
        using Base::Run;

    protected:
        void FormatToParamsString(const CharFormat* buffer, std::size_t size) override {
            m_BufferIn.IsSameForwardThrow(buffer, size);
        }

        void FormatExecParams() override {
            if (Parse() == false)
                if (m_BufferIn.IsEqualToForward('{') == false)
                    throw Detail::FMTParseError();
        }

        void SetArgsInterfaceCurrentContex() override                                   { m_ContextArgsInterface->SetContext(this); }

    public:
        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContext(const Detail::BufferInProperties<NewCharFormat>& bufferInProperties, NewContextArgs&& ...args);
        
        template<typename NewCharFormat, std::size_t SIZE, typename ...NewContextArgs>
        inline void SubContextArrayFMT(const NewCharFormat (&format)[SIZE], NewContextArgs&& ...args)
        {
            Detail::BufferInProperties<NewCharFormat> properties(format);
            return SubContext(properties, std::forward<NewContextArgs>(args)...);
        }

        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContextPtrFMT(const NewCharFormat* buffer, std::size_t size, NewContextArgs&& ...args)
        {
            Detail::BufferInProperties<NewCharFormat> properties(buffer, size);
            return SubContext(properties, std::forward<NewContextArgs>(args)...);
        }

    public:
        using Base::GetFormatIndexThrow;

    protected:
        using Base::ParseFormatDataBase;
        using Base::ParseFormatDataSpecial;
        using Base::ParseFormatDataCustom;
        using Base::ParseFormatData;

        using Base::ParseSpecial;
        using Base::ParseVariable;
        using Base::Parse;

    protected:
        using Base::ParseTimer;
        using Base::ParseDate;
        using Base::ParseSetter;

        void ParseTimer() override;
        void ParseDate() override;
        void ParseSetter() override;

    public:
        using Base::FormatReadParameterThrow;
        using Base::FormatDataApplyNextOverride;

    public:
        // Type formating from FormatterType<>
        template<typename Type, typename ...Rest>
        inline void RunType(Type& type, Rest&... rest)          { RunType(type); RunType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void RunType(Type& type) { ParserType<typename Detail::FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Parse(type, *this); }

        template<typename Type, typename ...Rest>
        inline void RunSubType(Type& type, Rest& ...rest)       { RunSubType(type); RunSubType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void RunSubType(Type& type) {
            if (m_FormatData.NextOverride.size() == 0)
                return RunType(type);
            FormatDataType formatDataCopy = m_FormatData;
            FormatDataApplyNextOverride();
            RunType(type); 
            m_FormatData = formatDataCopy;
        }

        // Only support basic type that are considered as basic by Buffer class
        template<typename Type, typename ...Rest>
        inline void BasicRunType(Type& type, Rest&... rest)             { BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void BasicRunType(Type& type)    { m_BufferIn.BasicReadType(type); }

        template<typename Type, typename ...Rest>
        inline void BasicRunSubType(Type& type, Rest&... rest)              { BasicRunSubType(type); BasicRunSubType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void BasicRunSubType(Type& type) {
            if (m_FormatData.NextOverride.size() == 0)
                return BasicRunType(type);
            FormatDataType formatDataCopy = m_FormatData;
            FormatDataApplyNextOverride();
            BasicRunType(type); 
            m_FormatData = formatDataCopy;
        }

        // Type formating from ParserType<>
        template<typename Type, typename ...Rest>
        inline void ReadType(Type& type, Rest&... rest)        { RunType(type, std::forward<Rest>(rest)...); }
        template<typename Type, typename ...Rest>
        inline void ReadSubType(Type& type, Rest&... rest)    { RunSubType(type, std::forward<Rest>(rest)...); }

        // Only support basic type that are considered as basic by Buffer class
        template<typename Type, typename ...Rest>
        inline void BasicReadType(Type& type, Rest&... rest)    { BasicRunType(type, std::forward<Rest>(rest)...); }
        template<typename Type, typename ...Rest>
        inline void BasicSubReadType(Type& type, Rest&... rest)    { BasicRunSubType(type, std::forward<Rest>(rest)...); }

    public:
        using Base::GetStringViewParamUntil;
        using Base::GetStringViewUntil;
        using Base::ReadDataType;
    };
}

#include "BaseParse/ParseTextPropertiesColor.h"
#include "BaseParse/ParseTextPropertiesStyle.h"
#include "BaseParse/ParseTextPropertiesFront.h"
#include "BaseParse/BaseParser.h"
#include "BaseParse/ParseSTDLib.h"
#include "BaseParse/ParseChrono.h"

#include "ParserTextPropertiesExecutor/ParserNOTextPropertiesExecutor.h"
#include "ParserTextPropertiesExecutor/ParserANSITextPropertiesExecutor.h"
