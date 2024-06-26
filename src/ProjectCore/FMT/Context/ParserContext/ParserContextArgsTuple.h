#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"
#include "ProjectCore/FMT/Context/BasicContext/BasicArgsTupleInterface.h"

namespace ProjectCore::FMT::Detail
{
    template <typename... Types>
    struct ParserContextArgsTuple;

    template <>
    struct ParserContextArgsTuple<>
    {
    public:
        ParserContextArgsTuple() = default;

    public:
        static inline constexpr std::size_t Size() { return 0; }

    public:
        template <typename FormatterContext>
        inline void RunTypeAtIndex(FormatterContext&, Detail::FormatIndex)
        {
            throw Detail::FMTBufferWrongIndex();
        }

        template <typename FormatterContext>
        inline Detail::FormatIndex GetIndexOfCurrentNamedArg(FormatterContext&, Detail::FormatIndex)
        {
            return Detail::FormatIndex();
        }

        inline std::any GetTypeAtIndex(Detail::FormatIndex) { return {}; }

        template <typename T>
        inline void GetTypeAtIndexCast(T*, Detail::FormatIndex) {}

        template <typename T>
        inline void GetTypeAtIndexConvert(T*, Detail::FormatIndex) {}
    };

    template <typename Type, typename... Rest>
    struct ParserContextArgsTuple<Type, Rest...> : ParserContextArgsTuple<Rest...>
    {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        ParserContextArgsTuple(TypeWithoutRef& t, Rest&... rest) : ParserContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}

    private:
        TypeWithoutRef& m_Value;

    public:
        static inline constexpr std::size_t Size() { return sizeof...(Rest) + 1; }

    public:
        template <typename FormatterContext>
        inline void RunTypeAtIndex(FormatterContext &context, Detail::FormatIndex idx)
        {
            if (idx.Is0())
                return context.RunType(m_Value);
            return ParserContextArgsTuple<Rest...>::RunTypeAtIndex(context, idx.GetPrev());
        }

    public:
        template <typename FormatterContext>
        inline Detail::FormatIndex GetIndexOfCurrentNamedArg(FormatterContext& context, Detail::FormatIndex beginSearchIndex)
        {
            if constexpr (Detail::IsANamedArgs<Detail::GetBaseType<TypeWithoutRef>>::value)
            {
                if (context.Format().NextIsANamedArgs(m_Value.GetName()))
                    return beginSearchIndex;
            }
            return ParserContextArgsTuple<Rest...>::GetIndexOfCurrentNamedArg(context, beginSearchIndex.GetNext());
        }

    public:
        inline std::any GetTypeAtIndex(Detail::FormatIndex idx)
        {
            if (idx.Is0())
                return std::any{&m_Value};
            return ParserContextArgsTuple<Rest...>::GetTypeAtIndex(idx.GetPrev());
        }

    public:
        template <typename T>
        inline void GetTypeAtIndexCast(T* value, Detail::FormatIndex idx)
        {
            if (idx.Is0())
            {
                if constexpr (FMTIsContextSame<TypeWithoutRef, T>)
                {
                    return *value = m_Value;
                }
                else
                {
                    // Warrning : Need to transmit : 'Could not convert'
                    return;
                }
            }
            return ParserContextArgsTuple<Rest...>::template GetTypeAtIndexCast<T>(value, idx.GetPrev());
        }

        template <typename T>
        inline void GetTypeAtIndexConvert(T* value, Detail::FormatIndex idx)
        {
            if (idx.Is0())
            {
                if constexpr (FMTCanContextConvert<TypeWithoutRef, T>)
                {
                    *value = FMTContextConvert<TypeWithoutRef, T>::Convert(m_Value);
                    return;
                }
                else
                {
                    // Warrning : Need to transmit : 'Could not convert'
                    return;
                }
            }
            return ParserContextArgsTuple<Rest...>::template GetTypeAtIndexConvert<T>(value, idx.GetPrev());
        }
    };

    template <typename Context, typename... Args>
    class ParserContextArgsTupleInterface : public BasicContextArgsTupleInterface<Context>
    {
    public:
        using Base              = BasicContextArgsTupleInterface<Context>;
        using ContextArgsType   = ParserContextArgsTuple<Args...>;
        
        using Base::m_Context;
        
    public:
        ParserContextArgsTupleInterface(Args&&... args)
            : Base()
            , m_contextArgs(std::forward<Args>(args)...)
        {}
        ~ParserContextArgsTupleInterface() override = default;

    public:
        std::size_t Size() override
        {
            return m_contextArgs.Size();
        }

        void RunTypeAtIndex(Detail::FormatIndex idx) override
        {
            return m_contextArgs.RunTypeAtIndex(*m_Context, idx);
        }

        Detail::FormatIndex GetIndexOfCurrentNamedArg() override
        {
            return m_contextArgs.GetIndexOfCurrentNamedArg(*m_Context, Detail::FormatIndex{0});
        }

        std::any GetTypeAtIndexImpl(Detail::FormatIndex idx) override
        {
            return m_contextArgs.GetTypeAtIndex(idx);
        }

        void RunFuncAtImpl(Detail::FormatIndex idx, std::function<void(std::any)> func) override
        {
            return func(m_contextArgs.GetTypeAtIndex(idx));
        }

    public:
        template <typename T>
        T GetTAtConvert(Detail::FormatIndex idx)
        {
            T res;
            m_contextArgs.template GetTypeAtIndexConvert<T>(&res, idx);
            return res;
        }

        Detail::FormatIndex GetFormatIndexAt(Detail::FormatIndex idx) override
        {
            return GetTAtConvert<Detail::FormatIndex>(idx);
        }

        typename Context::StringViewFormat GetStringAt(Detail::FormatIndex idx) override
        {
            return GetTAtConvert<typename Context::StringViewFormat>(idx);
        }

        int64_t GetIntAt(Detail::FormatIndex idx) override
        {
            return GetTAtConvert<int64_t>(idx);
        }

    protected:
        ContextArgsType m_contextArgs;
    };
}
