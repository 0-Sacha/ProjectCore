#pragma once

#include "EngineCore/Json/Detail/Buffer/JsonBufferOut.h"
#include "EngineCore/Json/JsonContext/JsonObjects/JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    class JsonFormatter
    {
    public:
        JsonFormatter(EngineCore::FMT::Detail::BasicBufferManager<char>& bufferManager)
            : m_BufferOut(bufferManager)
            , m_Indent(0)
            , m_IndentSize(4)
            , m_IndentWithSpaces(true)
            , m_OneLine(false)
        {}

    public:
        void DumpJsonObject(const Detail::JsonObject& object);

    public:
        JsonBufferOut& BufferOut() { return m_BufferOut; }
        const JsonBufferOut& BufferOut() const { return m_BufferOut; }

    protected:
        JsonBufferOut m_BufferOut;

    public:
        void Indent()
        {
            if (m_OneLine) return;

            if (m_IndentWithSpaces)
                m_BufferOut.PushBack(' ', m_Indent * m_IndentSize);
            else
                m_BufferOut.PushBack('\t', m_Indent * m_IndentSize);
        }

        void NewLine()          { if (m_OneLine) return; m_BufferOut.PushBack('\n'); Indent(); }
        void BeginNewObject()   { ++m_Indent; }
        void EndNewObject()     { --m_Indent; }

    protected:
        std::size_t m_Indent;
        std::size_t m_IndentSize;
		bool m_IndentWithSpaces;
		bool m_OneLine;
    };
}
