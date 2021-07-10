#pragma once

namespace elm {

	struct WindowCreationInfoStruct {
		int width;
		int height;
		bool fullscreen;
	};

	struct InitEngineInfoStruct {
		WindowCreationInfoStruct windowCreationInfo;
	};

}