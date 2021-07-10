#pragma once

#include <sstream>
#include <stdexcept>
#include <functional>

#include "api/renderingapi.h"

namespace elm::rendering {
	class Renderer {
	public:
		Renderer(RenderingApi* api);
		void Init(InitEngineInfoStruct* initEngineInfo);
		void Run(std::function<void()> callback);
		void StartCompose();
		void EndCompose();
		template<typename T>
		static inline Renderer* MakeRenderer() {
			RenderingApi* api = new T();
			return new Renderer(api);
		}
	private:
		RenderingApi* api;
	};
}