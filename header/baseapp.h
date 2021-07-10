#pragma once

#include "core.h"
#include "elmstruct.h"

namespace elm {
	class BaseApp {
	public:
		void Run();
		virtual void Init(InitEngineInfoStruct& initEngineInfo) = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
	private:
		Core core;
	};
}