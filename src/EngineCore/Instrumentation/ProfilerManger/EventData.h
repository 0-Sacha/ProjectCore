#pragma once

#include "EngineCore/Json/Json.h"

namespace EngineCore::Instrumentation
{
    class EventData
    {
    public:
        virtual void ToJson(JSON::Detail::JsonFormatter& formatter) const = 0;
        virtual void FromJson(JSON::Detail::JsonParser& parser) = 0;
    };

    class EventDataJsonObject final : public EventData
    {
    public:
        void ToJson(JSON::Detail::JsonFormatter& formatter) const override
        {
            JSON::JsonSerializer<JSON::JsonStructObject>::Dump(Data, formatter);
        }
        void FromJson(JSON::Detail::JsonParser& parser) override
        {
            JSON::JsonSerializer<JSON::JsonStructObject>::Load(Data, parser);
        }
        JSON::JsonStructObject Data;
    };
}