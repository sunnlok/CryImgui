#include "StdAfx.h"
#include "Plugin.h"

#include <CrySchematyc/Env/IEnvRegistry.h>
#include <CrySchematyc/Env/EnvPackage.h>
#include <CrySchematyc/Utils/SharedString.h>

// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>
#include "ImguiImpl.h"
#include "CrySystem/SystemInitParams.h"

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
	if (initParams.bDedicatedServer)
		return false;

	gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this,"CPlugin");

	g_pImguiImpl = new CImguiImpl();

#ifndef PRE_5_5
	EnableUpdate(IEnginePlugin::EUpdateStep::MainUpdate, true);
#else
	SetUpdateFlags(EPluginUpdateType::EUpdateType_Update);
#endif
	return true;
}



CImguiImpl* CPlugin::GetImplementation()
{
	return g_pImguiImpl;
}

#ifdef PRE_5_5
void CPlugin::OnPluginUpdate(EPluginUpdateType updateType)
{
	if (gEnv->IsDedicated())
		return;

	g_pImguiImpl->Update();
}
#else
void CPlugin::MainUpdate(float frameTime)
{
	if (gEnv->IsDedicated())
		return;

	g_pImguiImpl->Update();
}	
#endif

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