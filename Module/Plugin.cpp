#include "StdAfx.h"
#include "Plugin.h"

#include <CrySchematyc/Env/IEnvRegistry.h>
#include <CrySchematyc/Env/EnvPackage.h>
#include <CrySchematyc/Utils/SharedString.h>

// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>
#include "ImguiImpl.h"

static CImguiImpl* g_pImguiImpl = nullptr;

CPlugin::~CPlugin()
{
	gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);

	delete g_pImguiImpl;

	if (gEnv->pSchematyc)
	{
		gEnv->pSchematyc->GetEnvRegistry().DeregisterPackage(CPlugin::GetCID());
	}
}

bool CPlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this,"CPlugin");

	g_pImguiImpl = new CImguiImpl();

	EnableUpdate(IEnginePlugin::EUpdateStep::MainUpdate, true);
	EnableUpdate(IEnginePlugin::EUpdateStep::BeforeSystem, true);
	EnableUpdate(IEnginePlugin::EUpdateStep::BeforeRender, true);
	return true;
}



CImguiImpl* CPlugin::GetImplementation()
{
	return g_pImguiImpl;
}


void CPlugin::MainUpdate(float frameTime)
{
	g_pImguiImpl->Update();
}	

void CPlugin::UpdateBeforeSystem()
{
	g_pImguiImpl->OnPreSystemUpdate();
}

void CPlugin::UpdateBeforeRender()
{
	g_pImguiImpl->OnPreRenderUpdate();
}

void CPlugin::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	switch (event)
	{
	case ESYSTEM_EVENT_REGISTER_SCHEMATYC_ENV:
	{
		// Register all components that belong to this plug-in
		auto staticAutoRegisterLambda = [](Schematyc::IEnvRegistrar& registrar)
		{
			// Call all static callback registered with the CRY_STATIC_AUTO_REGISTER_WITH_PARAM
			Detail::CStaticAutoRegistrar<Schematyc::IEnvRegistrar&>::InvokeStaticCallbacks(registrar);
		};

		if (gEnv->pSchematyc)
		{
			gEnv->pSchematyc->GetEnvRegistry().RegisterPackage(
				stl::make_unique<Schematyc::CEnvPackage>(
					CPlugin::GetCID(),
					"Imgui",
					"",
					"UI",
					staticAutoRegisterLambda
					)
			);
		}
	}
	break;
	}
}

CRYREGISTER_SINGLETON_CLASS(CPlugin)