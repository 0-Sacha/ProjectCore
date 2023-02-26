#pragma once

#include "BasicBufferManager.h"

namespace EngineCore::FMT::Detail {

    template <typename CharType, std::size_t Count>
    class StaticBufferManager : public BasicBufferManager<CharType>
    {
        public:
            CharType* GetBuffer() override { return m_Buffer; }
            const CharType* GetBuffer() const override { return m_Buffer; }
            std::size_t GetBufferSize() const override { return Count; }
        
        public:
            bool AddSize(const std::size_t count) override { return false; }

        private:
            CharType m_Buffer[Count];
    };

}