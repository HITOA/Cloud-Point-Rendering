#pragma once

#include "../../elmstruct.h"
#include <functional>

#define DEFAULT_HEIGHT -1
#define DEFAULT_WIDTH -1

namespace elm::rendering {
	class RenderingApi {
	public:
		virtual void Init(InitEngineInfoStruct* initEngineInfo) = 0;
		virtual void Run() = 0;
		virtual void SetGameLoopCallback(std::function<void()> callback) = 0;
		//rendering function
		virtual void ClearColor(float r, float g, float b, float a) = 0;
		virtual void ClearBuffer() = 0;
		virtual void SwapBuffers() = 0;
	};
}