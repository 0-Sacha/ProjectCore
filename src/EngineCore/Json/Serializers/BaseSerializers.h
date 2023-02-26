#pragma once

#include "../JsonObjects.h"
#include "../JsonSerializer.h"

#include "EngineCore/FMT/Detail/Forwarders.h"

#include <utility>

namespace EngineCore::JSON
{
    // Int Types
    template <>
	struct JsonSerializer<std::int8_t>
    {
        static inline void Load(std::int8_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadInt(t, parser);
        }
		static inline void Dump(const std::int8_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::int16_t>
    {
        static inline void Load(std::int16_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadInt(t, parser);
        }
		static inline void Dump(const std::int16_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::int32_t>
    {
        static inline void Load(std::int32_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadInt(t, parser);
        }
		static inline void Dump(const std::int32_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::int64_t>
    {
        static inline void Load(std::int64_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadInt(t, parser);
        }
		static inline void Dump(const std::int64_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpInt(t, formatter);
        }
    };


    // UInt Types
    template <>
	struct JsonSerializer<std::uint8_t>
    {
        static inline void Load(std::uint8_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint8_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpUInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::uint16_t>
    {
        static inline void Load(std::uint16_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint16_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpUInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::uint32_t>
    {
        static inline void Load(std::uint32_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint32_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpUInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::uint64_t>
    {
        static inline void Load(std::uint64_t& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint64_t& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpUInt(t, formatter);
        }
    };


    // Float Types
    template <>
	struct JsonSerializer<float>
    {
        static inline void Load(float& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadFloat(t, parser);
        }
		static inline void Dump(const float& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpFloat(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<double>
    {
        static inline void Load(double& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadFloat(t, parser);
        }
		static inline void Dump(const double& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpFloat(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<long double>
    {
        static inline void Load(long double& t, Detail::JsonParser& parser) {
            JsonNumberSerializer::LoadFloat(t, parser);
        }
		static inline void Dump(const long double& t, Detail::JsonFormatter& formatter) {
            JsonNumberSerializer::DumpFloat(t, formatter);
        }
    };


    template <typename Char>
	struct JsonSerializer<FMT::Detail::ForwardAsChar<Char>>
    {
        static inline void Load(Char& t, Detail::JsonParser& parser) {
            parser.BufferIn().Skip('"');
            t = parser.BufferIn().GetAndForward();
            parser.BufferIn().Skip('"'); 
        }
		static inline void Dump(const Char& t, Detail::JsonFormatter& formatter) {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack(t);
            formatter.BufferOut().PushBack('"');
        }
    };
    template <typename Char, std::size_t SIZE>
	struct JsonSerializer<FMT::Detail::ForwardAsCharArray<Char, SIZE>>
    {
        static inline void Load(Char(&t)[SIZE], Detail::JsonParser& parser) {
            parser.BufferIn().Skip('"');
            parser.BufferIn().Skip('"'); 
        }
		static inline void Dump(const Char(&t)[SIZE], Detail::JsonFormatter& formatter) {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack('"');
        }
    };
    template <typename Char>
	struct JsonSerializer<FMT::Detail::ForwardAsCharPointer<Char>>
    {
        static inline void Load(Char* t, Detail::JsonParser& parser) {
            parser.BufferIn().Skip('"');
            parser.BufferIn().Skip('"'); 
        }
		static inline void Dump(const Char* t, Detail::JsonFormatter& formatter) {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack('"');
        }
    };

    template <>
	struct JsonSerializer<char>
    {
        static inline void Load(char& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char>>::Load(t, parser);
        }
		static inline void Dump(const char& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<wchar_t>
    {
        static inline void Load(wchar_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<wchar_t>>::Load(t, parser);
        }
		static inline void Dump(const wchar_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<wchar_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char8_t>
    {
        static inline void Load(char8_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char8_t>>::Load(t, parser);
        }
		static inline void Dump(const char8_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char8_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char16_t>
    {
        static inline void Load(char16_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char16_t>>::Load(t, parser);
        }
		static inline void Dump(const char16_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char16_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char32_t>
    {
        static inline void Load(char32_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char32_t>>::Load(t, parser);
        }
		static inline void Dump(const char32_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char32_t>>::Dump(t, formatter);
        }
    };

    template <std::size_t SIZE>
	struct JsonSerializer<char[SIZE]>
    {
        static inline void Load(char(&t)[SIZE], Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char, SIZE>>::Load(t, parser);
        }
		static inline void Dump(const char(&t)[SIZE], Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char, SIZE>>::Dump(t, formatter);
        }
    };
    template <std::size_t SIZE>
	struct JsonSerializer<wchar_t[SIZE]>
    {
        static inline void Load(wchar_t(&t)[SIZE], Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<wchar_t, SIZE>>::Load(t, parser);
        }
		static inline void Dump(const wchar_t(&t)[SIZE], Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<wchar_t, SIZE>>::Dump(t, formatter);
        }
    };
    template <std::size_t SIZE>
	struct JsonSerializer<char8_t[SIZE]>
    {
        static inline void Load(char8_t(&t)[SIZE], Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char8_t, SIZE>>::Load(t, parser);
        }
		static inline void Dump(const char8_t(&t)[SIZE], Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char8_t, SIZE>>::Dump(t, formatter);
        }
    };
    template <std::size_t SIZE>
	struct JsonSerializer<char16_t[SIZE]>
    {
        static inline void Load(char16_t(&t)[SIZE], Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char16_t, SIZE>>::Load(t, parser);
        }
		static inline void Dump(const char16_t(&t)[SIZE], Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char16_t, SIZE>>::Dump(t, formatter);
        }
    };
    template <std::size_t SIZE>
	struct JsonSerializer<char32_t[SIZE]>
    {
        static inline void Load(char32_t(&t)[SIZE], Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char32_t, SIZE>>::Load(t, parser);
        }
		static inline void Dump(const char32_t(&t)[SIZE], Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char32_t, SIZE>>::Dump(t, formatter);
        }
    };
    
    template <>
	struct JsonSerializer<char*>
    {
        static inline void Load(char* t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char>>::Load(t, parser);
        }
		static inline void Dump(const char* t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<wchar_t*>
    {
        static inline void Load(wchar_t* t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<wchar_t>>::Load(t, parser);
        }
		static inline void Dump(const wchar_t* t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<wchar_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char8_t*>
    {
        static inline void Load(char8_t* t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char8_t>>::Load(t, parser);
        }
		static inline void Dump(const char8_t* t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char8_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char16_t*>
    {
        static inline void Load(char16_t* t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char16_t>>::Load(t, parser);
        }
		static inline void Dump(const char16_t* t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char16_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char32_t*>
    {
        static inline void Load(char32_t* t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char32_t>>::Load(t, parser);
        }
		static inline void Dump(const char32_t* t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsCharPointer<char32_t>>::Dump(t, formatter);
        }
    };

    template <typename T>
	struct JsonSerializer<T*>
    {
        static inline void Load(T* t, Detail::JsonParser& parser) {
            if (t == nullptr) throw JsonGivenTypeError{};
            JsonSerializer<T>::Load(*t, parser);
        }
		static inline void Dump(const T* t, Detail::JsonFormatter& formatter) {
            if (t == nullptr) throw JsonGivenTypeError{};
            JsonSerializer<T>::Dump(*t, formatter);
        }
    };

    template <typename T, std::size_t SIZE>
	struct JsonSerializer<T[SIZE]>
    {
        using ArraySubObjectType = T;
        
        static inline void Load(T(&t)[SIZE], Detail::JsonParser& parser) {
            JsonArraySerializer::LoadAllSubObjects<T[SIZE]>(t, parser);
        }
        static inline void AddArraySubObject(T(&t)[SIZE], std::size_t idx, ArraySubObjectType&& subObject) {
            t[idx] = std::move(subObject);
        }

		static inline void Dump(const T(&t)[SIZE], Detail::JsonFormatter& formatter) {
            JsonArraySerializer::DumpBegin(formatter);
            for (std::size_t idx = 0; idx < SIZE; ++idx) 
                JsonArraySerializer::DumpObject(t[idx], idx, formatter);
            JsonArraySerializer::DumpEnd(formatter);
        }
    };
}