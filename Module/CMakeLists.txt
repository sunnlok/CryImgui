if(DEDICATED_SERVER)
	return()
endif()

option(PLUGIN_IMGUI "Enable the imgui plugin" ON)
if (NOT PLUGIN_IMGUI)
	return()
endif()

start_sources()
sources_platform(ALL)
add_sources("CryImgui_core.cpp"
	SOURCE_GROUP "Root"
		"Plugin.cpp"
		"Plugin.h"
		"StdAfx.cpp"
        "StdAfx.h"
        "CVars.cpp"
        "CVars.h"
        "ImguiImpl.cpp"
        "ImguiImpl.h"
		"resource.h"
)

add_sources("CryImgui_renderer.cpp"
SOURCE_GROUP "Render"
	"Render/ImguiRenderer.h"
	"Render/ImguiRenderer.cpp"


)

add_sources("CryImgui_imgui.cpp"
SOURCE_GROUP "Imgui"
    "Imgui/imconfig.h"
	"Imgui/imgui.cpp"
	"Imgui/imgui.h"
	"Imgui/imgui_demo.cpp"
	"Imgui/imgui_draw.cpp"
	"Imgui/imgui_widgets.cpp"
	"Imgui/imgui_internal.h"
	"Imgui/imstb_rectpack.h"
	"Imgui/imstb_textedit.h"
	"Imgui/imstb_truetype.h"
)

add_sources("NoUberFile"
	SOURCE_GROUP "Root"
		"StdAfx.cpp"
)

end_sources()


CryEngineModule(CryImgui PCH "StdAfx.cpp" SOLUTION_FOLDER "CryPlugins")

target_include_directories(${THIS_PROJECT} PRIVATE "${CRYENGINE_DIR}/Code/CryEngine/CryCommon" PUBLIC ../Interface)

include(${CRYENGINE_DIR}/Code/CryPlugins/Live++/Live++.cmake)
LIVEPP_ENABLE_FOR_TARGET(${THIS_PROJECT})