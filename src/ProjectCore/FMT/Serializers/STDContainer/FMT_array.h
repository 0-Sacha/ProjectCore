#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/FormatterType.h"
#include <array>

namespace ProjectCore::FMT
{
    template <typename T, std::size_t SIZE, typename FormatterContext>
    struct FormatterType<std::array<T, SIZE>, FormatterContext>
    {
        static void Format(const std::array<T, SIZE>& t, FormatterContext& context) {
            FormatterType<ForwardAsSTDEnumerable<std::array<T, SIZE>>, FormatterContext>::Format(t, context);
        }
    };
}
