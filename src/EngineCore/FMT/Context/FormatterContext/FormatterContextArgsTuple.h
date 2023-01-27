
#pragma once

#include "FMT/Detail/Detail.h"
#include "FMT/Context/BasicContext/Utils/BasicContextArgsTupleInterface.h"

#include "Utils/FormatterType.h"

namespace EngineCore::FMT::Detail {

	template <typename... Types>
	struct FormatterContextArgsTuple;

    template <>
    struct FormatterContextArgsTuple<> {

    public:
        FormatterContextArgsTuple() = default;

	public:
		static inline constexpr std::size_t Size() { return 0; }

    public:
        template <typename FormatterContext>
        inline void RunTypeAtIndex(FormatterContext &context, const Detail::FormatIndex& idx)
                    { throw Detail::FormatBufferWrongIndex(); }

        template <typename FormatterContext>
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatterContext& context, const Detail::FormatIndex& beginSearchIndex)
                    { return Detail::FormatIndex(); }

        inline std::any GetTypeAtIndex(const Detail::FormatIndex& idx)
                    { return {}; }

        template <typename T>
        inline void GetTypeAtIndexCast(T* value, const Detail::FormatIndex& idx)
                    { }

        template <typename T>
        inline void GetTypeAtIndexConvert(T* value, const Detail::FormatIndex& idx)
                    { }
    };

    template <typename Type, typename... Rest>
    struct FormatterContextArgsTuple<Type, Rest...> : FormatterContextArgsTuple<Rest...>
    {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        FormatterContextArgsTuple(const TypeWithoutRef& t, Rest&&... rest)    : FormatterContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}

    private:
        const TypeWithoutRef &m_Value;

    public:
        static inline constexpr std::size_t Size() { return sizeof...(Rest) + 1; }

    public:
        template <typename FormatterContext>
        inline void RunTypeAtIndex(FormatterContext &context, const Detail::FormatIndex& idx) {
            if (idx.Is0())
                return context.RunType(m_Value);
            return FormatterContextArgsTuple<Rest...>::RunTypeAtIndex(context, idx.GetPrev());
        }

    public:
        template<typename FormatterContext>
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatterContext& context, const Detail::FormatIndex& beginSearchIndex) {
            if constexpr (Detail::IsANamedArgs<Detail::GetBaseType<TypeWithoutRef>>::value)
            {
                if (context.Format().NextIsANamedArgs(m_Value.GetName()))
                    return beginSearchIndex;
            }
            return FormatterContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }

    public:
        inline std::any GetTypeAtIndex(const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return std::any{&m_Value};
            return FormatterContextArgsTuple<Rest...>::GetTypeAtIndex(idx.GetPrev());
        }

    public:
        template <typename T>
        inline void GetTypeAtIndexCast(T* value, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
            {
                if constexpr (FormatterContextArgsTupleSameAs<T, T>::SameAs)
                    return *value = m_Value;
            }
            return FormatterContextArgsTuple<Rest...>::template GetTypeAtIndexCast<T>(value, idx.GetPrev());
        }

        template <typename T>
        inline void GetTypeAtIndexConvert(T* value, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
            {
                if constexpr (FormatterContextArgsTupleConvertFunc<TypeWithoutRef, T>::IsConvertible)
                    return *value = FormatterContextArgsTupleConvertFunc<TypeWithoutRef, T>::Convert(m_Value);;
            }
            return FormatterContextArgsTuple<Rest...>::template GetTypeAtIndexConvert<T>(value, idx.GetPrev());
        }
    };


    template<typename Context, typename... Args>
    class FormatterContextArgsTupleInterface : public BasicContextArgsTupleInterface<Context>
    {
        public:
            using Base 	            = BasicContextArgsTupleInterface<Context>;
            using ContextArgsType 	= FormatterContextArgsTuple<Args...>;
            
            using Base::m_Context;
            
        public:
            FormatterContextArgsTupleInterface(Args&&... args)
                : Base()
                , m_contextArgs(std::forward<Args>(args)...)
            {}
            
        public:
            int Size() override
                    { return m_contextArgs.Size(); }

            void RunTypeAtIndex(const Detail::FormatIndex& idx) override
                    { return m_contextArgs.RunTypeAtIndex(*m_Context, idx); }

            Detail::FormatIndex GetIndexOfCurrentNameArg() override
                    { return m_contextArgs.GetIndexOfCurrentNameArg(*m_Context, Detail::FormatIndex{0}); }

            std::any GetTypeAtIndexImpl(const Detail::FormatIndex& idx) override
                    { return m_contextArgs.GetTypeAtIndex(idx); }

            void RunFuncAtImpl(const Detail::FormatIndex& idx, std::function<void(std::any)> func) override
            {
                return func(m_contextArgs.GetTypeAtIndex(idx));
            }

        public:
            template <typename T>
            T GetTAtConvert(const Detail::FormatIndex& idx)
            {
                T res;
                m_contextArgs.template GetTypeAtIndexConvert<T>(&res, idx);
                return res;
            }

            Detail::FormatIndex GetFormatIndexAt(const Detail::FormatIndex& idx) override
                    { return GetTAtConvert<Detail::FormatIndex>(idx); }

            typename Context::StringViewFormat GetStringAt(const Detail::FormatIndex& idx) override
                    { return GetTAtConvert<typename Context::StringViewFormat>(idx); }

            int64_t GetIntAt(const Detail::FormatIndex& idx) override
                    { return GetTAtConvert<int64_t>(idx); }

        protected:
            ContextArgsType m_contextArgs;
    };
}