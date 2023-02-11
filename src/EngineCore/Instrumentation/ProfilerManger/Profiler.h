#pragma once

#include "EngineCore/Core/Core.h"
#include "LoggerManager/LoggerManager.h"

#include "Event.h"
#include "AllEvents.h"
#include "Utils.h"

namespace EngineCore::Instrumentation
{
	class Profiler
	{
	public:
		explicit Profiler(std::string&& name)
			: Name(name)
			, Logger(name)
			{
				Events.clear();
				Events.push_back(DurationEvent(name, "Profiler"));
				GetProfilerProfile().Start();
			}

		~Profiler() {}

	public:
		DurationEvent& GetProfilerProfile() 						{ return *reinterpret_cast<DurationEvent*>(&Events[0]); }
		void AddEvent(const Event& event) 							{ Events.push_back(event); }
		inline EngineCore::LoggerManager::BasicLogger& GetLogger() 	{ return Logger; }

	public:
		static Profiler& GetInstance()								{ static Profiler profiler("Profiler"); return profiler; }

	public:
		std::string Name;
		EngineCore::LoggerManager::BasicLogger Logger;
		std::vector<Event> Events;
	};
}
