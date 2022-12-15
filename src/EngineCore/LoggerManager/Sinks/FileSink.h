#pragma once

#include <ostream>
#include <fstream>
#include <filesystem>

#include "LoggerManager/Detail/LoggerSink.h"

namespace EngineCore::LoggerManager::Sinks
{
    template <typename CharType>
    class BasicConsoleSink : public Detail::BasicLoggerSink<CharType>
    {
        public:
            using Base = Detail::BasicLoggerSink<CharType>;
            using typename Base::PatternType;
            using typename Base::NameType;
            using typename Base::BufferType;

        public:
            BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name)
                : Base(std::forward<NameType>(name))
                , m_Stream(stream)
            {}

            BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name, Detail::AsyncSink isAsync)
                : Base(std::forward<NameType>(name), isAsync)
                , m_Stream(stream)
            {}

        public:
            std::basic_ostream<CharType>& GetStream() { return m_Stream; }
        
        protected:
            void WriteImpl(const BufferType& bufferToPrint) override
            {
                m_Stream.write(bufferToPrint.data(), bufferToPrint.size());
                m_Stream.write("\n", 1);
                m_Stream.flush();
            }
            
        private:
            std::basic_ostream<CharType>& m_Stream;
    };

    template <typename CharType>
    class BasicFileSink : public Detail::BasicLoggerSink<CharType>
    {
        public:
            using Base = Detail::BasicLoggerSink<CharType>;
            using typename Base::PatternType;
            using typename Base::NameType;
            using typename Base::BufferType;

        public:
            BasicFileSink(const std::filesystem::path& filePath, NameType&& name, Detail::AsyncSink isAsync)
                : Base(std::forward<NameType>(name), isAsync)
                , m_Stream(filePath, std::ios::out)
            {}

        public:
            std::basic_ostream<CharType>& GetStream() { return m_Stream; }
        
        protected:
            void WriteImpl(const BufferType& bufferToPrint) override
            {
                m_Stream.write(bufferToPrint.data(), bufferToPrint.size());
                m_Stream.write("\n", 1);
                m_Stream.flush();
            }

        private:
            std::basic_ofstream<CharType> m_Stream;
    };
}

namespace EngineCore::LoggerManager::Sinks
{
    using ConsoleSink = BasicConsoleSink<char>;
    using FileSink = BasicFileSink<char>;
}