#pragma once

#include <CrySystem/ICryPlugin.h>

#include <CryGame/IGameFramework.h>

class CImguiImpl;

class CPlugin 
	: public Cry::IEnginePlugin
	, public ISystemEventListener
{
public:
	CRYINTERFACE_SIMPLE(IEnginePlugin)
	CRYGENERATE_SINGLETONCLASS_GUID(CPlugin, "CryImgui", "DD0FF1F4-29CA-42CF-BDF3-C55FCD9FE61C"_cry_guid)

	virtual ~CPlugin();
	
	//! Retrieve name of plugin.
	virtual const char* GetName() const override { return "CryImgui"; }

	//! Retrieve category for the plugin.
	virtual const char* GetCategory() const override { return "UI"; }

	//! This is called to initialize the new plugin.
	virtual bool Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;

	// ISystemEventListener
	virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
	// ~ISystemEventListener

	CImguiImpl*	GetImplementation();

	virtual void MainUpdate(float frameTime) override;


	virtual void UpdateBeforeSystem() override;


	virtual void UpdateBeforeRender() override;

};