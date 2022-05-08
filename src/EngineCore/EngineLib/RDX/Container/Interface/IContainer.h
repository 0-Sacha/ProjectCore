#pragma once
#include "EngineCore/EngineLib/RDX/RDXCore.h"

namespace EngineCore::RDX::BasicInterface {

	template <typename T>
	class IContainer {
	public:
		virtual BasicInterface<T>::SizeType Count() = 0;
		virtual bool IsEmpty() = 0;
	};

}