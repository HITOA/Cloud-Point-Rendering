#pragma once

#include <functional>
#include <vector>

#include "elmstruct.h"
#include "rendering/renderer.h"
#include "rendering/api/glrenderingapi.h"

namespace elm {
	class Core {
	public:
		Core();
		~Core();
		void Init(InitEngineInfoStruct* initEngineInfo);
		void Run();
		void operator+=(std::function<void()> callback);
	private:
		void CreateRenderer();
		void Compose();
	private:
		rendering::Renderer* renderer;
		std::vector<std::function<void()>> callbacks;
	};
}