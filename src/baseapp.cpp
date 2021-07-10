#include "../header/baseapp.h"

void elm::BaseApp::Run()
{
	InitEngineInfoStruct initEngineInfo;
	Init(initEngineInfo);
	core.Init(&initEngineInfo);

	Start();
	core += std::bind(&BaseApp::Update, this);
	core.Run();
}
