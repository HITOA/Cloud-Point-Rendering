#include "../../../header/rendering/api/glrenderingapi.h"

elm::rendering::GLRenderingApi::~GLRenderingApi()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void elm::rendering::GLRenderingApi::Init(InitEngineInfoStruct* initEngineInfo)
{
	InitGlfw();
	SetGlfwHint();
	CreateWindow(initEngineInfo->windowCreationInfo.width,
		initEngineInfo->windowCreationInfo.height,
		"AppTest",
		initEngineInfo->windowCreationInfo.fullscreen);
	InitGlew();
	GetWorkGroupsCapabilities();
	printf("WorkGroup Count : (%i, %i, %i)\nWorkGroup Size : (%i, %i, %i)\nInvocation : %i", workgroupCapabilities[0],
		workgroupCapabilities[1],
		workgroupCapabilities[2],
		workgroupCapabilities[3],
		workgroupCapabilities[4],
		workgroupCapabilities[5],
		workgroupCapabilities[6]);
	CreatePipeline();
}

void elm::rendering::GLRenderingApi::Run()
{
	do {
		callback();
		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));
}

void elm::rendering::GLRenderingApi::SetGameLoopCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void elm::rendering::GLRenderingApi::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void elm::rendering::GLRenderingApi::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void elm::rendering::GLRenderingApi::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void elm::rendering::GLRenderingApi::InitGlew()
{
	glewExperimental = true;

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::stringstream msg;
		msg << "Error with glew initialization. Code : " << err;
		std::runtime_error(msg.str().c_str());
	}
}

void elm::rendering::GLRenderingApi::InitGlfw()
{
	if (glfwInit() == GLFW_FALSE) {
		const char* description;
		int err = glfwGetError(&description);

		if (description)
			throw std::runtime_error(description);

		std::stringstream msg;
		msg << "Error with glfw initialization. Code : " << err;
		std::runtime_error(msg.str().c_str());
	}
}

void elm::rendering::GLRenderingApi::SetGlfwHint()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void elm::rendering::GLRenderingApi::CreateWindow(int width, int height, const char* name, bool fullscreen)
{
	pMonitor = glfwGetPrimaryMonitor();

	if (pMonitor == nullptr)
		throw std::runtime_error("Primary monitor not found.");

	const GLFWvidmode* vidmod = glfwGetVideoMode(pMonitor);

	if (width <= -1)
		width = vidmod->width;
	if (height <= -1)
		height = vidmod->height;

	window = glfwCreateWindow(
		width,
		height,
		name,
		fullscreen ? pMonitor : nullptr,
		nullptr);

	if (window == nullptr) {
		const char* description;
		int err = glfwGetError(&description);

		if (description)
			throw std::runtime_error(description);

		std::stringstream msg;
		msg << "Error with window creation. Code : " << err;
		std::runtime_error(msg.str().c_str());
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
}

int elm::rendering::GLRenderingApi::LoadShader(std::vector<char> data, int type)
{
	int shaderId = glCreateShader(type);
	int infoLogLength;

	char* src = data.data();
	int size = data.size();

	glShaderSource(shaderId, 1, &src, &size);
	glCompileShader(shaderId);

	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		char* errMsg = (char*)malloc(infoLogLength + 1);
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, errMsg);
		throw std::runtime_error(errMsg);
	}

	return shaderId;
}

int elm::rendering::GLRenderingApi::CompileShaders(std::vector<int> shadersId)
{
	int infoLogLength;
	int programId = glCreateProgram();

	for (auto shaderId : shadersId) {
		glAttachShader(programId, shaderId);
	}

	glLinkProgram(programId);

	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		char* errMsg = (char*)malloc(infoLogLength + 1);
		glGetShaderInfoLog(programId, infoLogLength, NULL, errMsg);
		throw std::runtime_error(errMsg);
	}

	for (auto shaderId : shadersId) {
		glDetachShader(programId, shaderId);
		glDeleteShader(shaderId);
	}

	return programId;
}

void elm::rendering::GLRenderingApi::CreatePipeline()
{
	if (!elm::file::Exist("C:/Users/HITO/source/repos/Elementary/x64/Release/Data/GL/Computeshader.s"))
		throw std::runtime_error("Can't find pipeline assets.");
	std::vector<char> src = elm::file::ReadFile("C:/Users/HITO/source/repos/Elementary/x64/Release/Data/GL/Computeshader.s");
	int sId = LoadShader(src, GL_COMPUTE_SHADER);
	int pId = CompileShaders(std::vector<int>({sId}));
	programs.push_back(pId);
}

void elm::rendering::GLRenderingApi::GetWorkGroupsCapabilities()
{
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workgroupCapabilities[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workgroupCapabilities[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workgroupCapabilities[2]);

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workgroupCapabilities[3]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workgroupCapabilities[4]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workgroupCapabilities[5]);

	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workgroupCapabilities[6]);
}
