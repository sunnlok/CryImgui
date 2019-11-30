#pragma once

#include <CryFlowGraph/IFlowBaseNode.h>

class CWindowNode : public CFlowBaseNode<eNCT_Singleton>
{
public:
	CWindowNode(SActivationInfo* pActInfo) {};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig_Void("Begin", _HELP("Begin the window")),
			InputPortConfig<string>("Name",  _HELP("Window Name")),
			InputPortConfig<bool>("Closable", true, _HELP("Should the window be closable")),
			{ 0 }
		};

		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_Void("Next", _HELP("Run next Node")),
			OutputPortConfig<bool>("Open",_HELP("Is the window still open")),
			OutputPortConfig<bool>("Visible",_HELP("Is the window visible")),
			{0}
		};

		config.pInputPorts = in_config;
		config.sDescription = _HELP("Start a new ImguiWindow");
		config.pOutputPorts = out_config;
		config.SetCategory(EFLN_APPROVED);
		
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo) override;

	virtual void GetMemoryUsage(ICrySizer* s) const override
	{
		s->Add(*this);
	}

};

class CWindowEndNode : public CFlowBaseNode<eNCT_Singleton>
{
public:
	CWindowEndNode(SActivationInfo* pActInfo) {};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig_Void("End", _HELP("End a window")),
			{ 0 }
		};

		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_Void("Next", _HELP("Run next Node")),
			{0}
		};
		config.pOutputPorts = out_config;

		config.pInputPorts = in_config;
		config.sDescription = _HELP("End an ImGui Window");
		config.SetCategory(EFLN_APPROVED);

	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo) override;

	virtual void GetMemoryUsage(ICrySizer* s) const override
	{
		s->Add(*this);
	}

};

class CTextNode : public CFlowBaseNode<eNCT_Singleton>
{
public:
	CTextNode(SActivationInfo* pActInfo) {};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig_Void("Draw", _HELP("Start a label")),
			InputPortConfig<string>("Text", _HELP("Text to display")),
			{ 0 }
		};
		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_Void("Next", _HELP("Run next Node")),
			{0}
		};
		config.pOutputPorts = out_config;

		config.pInputPorts = in_config;
		config.sDescription = _HELP("ImGui Text");
		config.SetCategory(EFLN_APPROVED);
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo) override;

	virtual void GetMemoryUsage(ICrySizer* s) const override
	{
		s->Add(*this);
	}

};

class CLabelTextNode : public CFlowBaseNode<eNCT_Singleton>
{
public:
	CLabelTextNode(SActivationInfo* pActInfo) {};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig_Void("Draw", _HELP("Start a label")),
			InputPortConfig<string>("Label", _HELP("Lable to display")),
			InputPortConfig<string>("Text", _HELP("Text to display")),
			{ 0 }
		};
		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_Void("Next", _HELP("Run next Node")),
			{0}
		};
		config.pOutputPorts = out_config;

		config.pInputPorts = in_config;
		config.sDescription = _HELP("ImGui Label");
		config.SetCategory(EFLN_APPROVED);
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo) override;

	virtual void GetMemoryUsage(ICrySizer* s) const override
	{
		s->Add(*this);
	}

};

class CButtonNode : public CFlowBaseNode<eNCT_Singleton>
{
public:
	CButtonNode(SActivationInfo* pActInfo) {};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig_AnyType("Draw", _HELP("Start a label")),
			InputPortConfig<string>("Label", _HELP("Button Label")),
			InputPortConfig<Vec3>("Size", _HELP("Button Size")),
			{ 0 }
		};
		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_Void("Next", _HELP("Run next Node")),
			OutputPortConfig_Void("Pressed", _HELP("The Button was pressed")),
			{0}
		};
		config.pOutputPorts = out_config;

		config.pInputPorts = in_config;
		config.sDescription = _HELP("ImGui Label");
		config.SetCategory(EFLN_APPROVED);
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo) override;

	virtual void GetMemoryUsage(ICrySizer* s) const override
	{
		s->Add(*this);
	}

};

class CVec3InputNode : public CFlowBaseNode<eNCT_Singleton>
{
public:
	CVec3InputNode(SActivationInfo* pActInfo) {};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig_AnyType("Draw", _HELP("Start a Vec3 Input")),
			InputPortConfig<string>("Label", _HELP("Input Label")),
			InputPortConfig<Vec3>("Input", _HELP("The field input")),
			{ 0 }
		};
		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_Void("Next", _HELP("Run next Node")),
			OutputPortConfig<Vec3>("Input", _HELP("The new input data")),
			{0}
		};
		config.pOutputPorts = out_config;

		config.pInputPorts = in_config;
		config.sDescription = _HELP("ImGui Label");
		config.SetCategory(EFLN_APPROVED);
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo) override;

	virtual void GetMemoryUsage(ICrySizer* s) const override
	{
		s->Add(*this);
	}
};