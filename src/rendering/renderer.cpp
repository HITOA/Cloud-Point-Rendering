#include "../../header/rendering/renderer.h"

elm::rendering::Renderer::Renderer(RenderingApi* api)
{
	this->api = api;
}

void elm::rendering::Renderer::Init(InitEngineInfoStruct* initEngineInfo)
{
	api->Init(initEngineInfo);
}

void elm::rendering::Renderer::Run(std::function<void()> callback)
{
	api->SetGameLoopCallback(callback);
	api->Run();
}

void elm::rendering::Renderer::StartCompose()
{
	api->ClearColor(0.0, 0.0, 0.0, 1.0);
	api->ClearBuffer();
}

void elm::rendering::Renderer::EndCompose()
{
	api->SwapBuffers();
}
