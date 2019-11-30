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

add_sources("CryImgui_nodes.cpp"
SOURCE_GROUP "Flowgraph"
	"Flowgraph/ImguiNodes.cpp"
	"Flowgraph/ImguiNodes.h"
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

add_sources("CryImgui_Widgets.cpp"
SOURCE_GROUP "Widgets"
	"Widgets/PerfMonitor.cpp"
	"Widgets/PerfMonitor.h"
)

add_sources("NoUberFile"
	SOURCE_GROUP "Root"
		"StdAfx.cpp"
)

end_sources()


CryEngineModule(CryImgui PCH "StdAfx.cpp" SOLUTION_FOLDER "CryPlugins")

target_link_options(${THIS_PROJECT} PUBLIC /INCREMENTAL)
target_compile_options(${THIS_PROJECT} PUBLIC /ZI)

target_include_directories(${THIS_PROJECT} PRIVATE "${CRYENGINE_DIR}/Code/CryEngine/CryCommon" PUBLIC ../Interface)

if (PLUGIN_LIVE++)
include(${CRYENGINE_DIR}/Code/CryPlugins/Live++/Live++.cmake)
LIVEPP_ENABLE_FOR_TARGET(${THIS_PROJECT})
endif()
