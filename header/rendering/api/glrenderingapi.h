#pragma once

#include <sstream>
#include <charconv>
#include <stdexcept>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderingapi.h"
#include "../../elmstruct.h"
#include "../../file/filesystem.h"

namespace elm::rendering {
	class GLRenderingApi : public RenderingApi {
	public:
		~GLRenderingApi();
		void Init(InitEngineInfoStruct* initEngineInfo);
		void Run();
		void SetGameLoopCallback(std::function<void()> callback);
		//rendering function
		void ClearColor(float r, float g, float b, float a);
		void ClearBuffer();
		void SwapBuffers();
		void Draw();
	private:
		void InitGlew();
		void InitGlfw();
		void SetGlfwHint();
		void CreateWindow(int width, int height, const char* name, bool fullscreen);
		int LoadShader(std::vector<char> data, int type);
		int CompileShaders(std::vector<int> shadersId);
		void CreatePipeline();
		void GetWorkGroupsCapabilities();
	private:
		GLFWmonitor* pMonitor; //Primary monitor
		GLFWwindow* window;
		std::function<void()> callback;
		std::vector<int> programs;
		int workgroupCapabilities[7];
	};
}