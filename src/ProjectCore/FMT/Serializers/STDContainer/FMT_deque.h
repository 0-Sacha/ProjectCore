#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"
#include <deque>

namespace ProjectCore::FMT
{
    template <typename T, typename FormatterContext>
    struct FormatterType<std::deque<T>, FormatterContext>
    {
        static void Format(const std::deque<T>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::deque<T>>, FormatterContext>::Format(t, context);
        }
    };
}
