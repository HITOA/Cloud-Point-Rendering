#include "../header/core.h"

elm::Core::Core()
{
	renderer = nullptr;
}

elm::Core::~Core()
{
	delete renderer;
}

void elm::Core::Init(elm::InitEngineInfoStruct* initEngineInfo)
{
	CreateRenderer();
	renderer->Init(initEngineInfo);
}

void elm::Core::Run()
{
	renderer->Run(std::bind(&Core::Compose, this));
}

void elm::Core::operator+=(std::function<void()> callback)
{
	this->callbacks.push_back(callback);
}

void elm::Core::CreateRenderer()
{
	this->renderer = rendering::Renderer::MakeRenderer<rendering::GLRenderingApi>();
}

void elm::Core::Compose()
{
	renderer->StartCompose();
	for (auto callback : callbacks) {
		callback();
	}
	renderer->EndCompose();
}
