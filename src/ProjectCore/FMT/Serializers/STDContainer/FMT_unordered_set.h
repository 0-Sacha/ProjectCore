#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"
#include <unordered_set>

namespace ProjectCore::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::unordered_set<T>, FormatterContext>
    {
        static void Format(const std::unordered_set<T>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_set<T>>, FormatterContext>::Format(t, context);
        }
    };

    template <typename T, typename FormatterContext>
    struct FormatterType<std::unordered_multiset<T>, FormatterContext>
    {
        static void Format(const std::unordered_multiset<T>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::unordered_multiset<T>>, FormatterContext>::Format(t, context);
        }
    };
}
