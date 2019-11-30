#include "StdAfx.h"
#include "ImguiNodes.h"
#include "Imgui/imconfig.h"
#include "Imgui/imgui.h"
#include "CryFlowGraph/IFlowSystem.h"


void CWindowNode::ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
{
	if (event == IFlowNode::eFE_Activate)
	{
		if (IsPortActive(pActInfo, 0))
		{
			auto name = GetPortString(pActInfo, 1);
			auto bClosable = GetPortBool(pActInfo, 2);
			bool bOpen	=  true;
			
			auto bVisible = ImGui::Begin(name.c_str(), bClosable ? &bOpen : nullptr);

			if (bVisible)
				ActivateOutput(pActInfo, 0, 1);
			else
				ImGui::End();

			ActivateOutput(pActInfo, 1, bOpen);
			ActivateOutput(pActInfo, 2, bVisible);
		}
	}
}

void CWindowEndNode::ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
{
	if (event == IFlowNode::eFE_Activate)
		if (IsPortActive(pActInfo, 0))
		{
			ImGui::End();
			ActivateOutput(pActInfo, 0, 1);
		}
			
}

void CTextNode::ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
{
	if (event == IFlowNode::eFE_Activate)
	{
		if (IsPortActive(pActInfo, 0))
		{
			auto text = GetPortString(pActInfo, 1);
			ImGui::Text(text.c_str());

			ActivateOutput(pActInfo, 0, 1);
		}
	}	
}

void CLabelTextNode::ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
{
	if (event == IFlowNode::eFE_Activate)
	{
		if (IsPortActive(pActInfo, 0))
		{
			auto label = GetPortString(pActInfo, 1);
			auto text = GetPortString(pActInfo, 2);

			ImGui::LabelText(label.c_str(), text.c_str());

			ActivateOutput(pActInfo, 0, 1);
		}
	}
}

void CButtonNode::ProcessEvent(EFlowEvent event, SActivationInfo * pActInfo)
{
	if (event == IFlowNode::eFE_Activate)
	{
		if (IsPortActive(pActInfo, 0))
		{
			auto label = GetPortString(pActInfo, 1);
			auto size = GetPortVec3(pActInfo, 2);


			auto bOpen = ImGui::Button(label.c_str(), ImVec2(size.x, size.y));

			ActivateOutput(pActInfo, 0, 1);
			if(bOpen)
				ActivateOutput(pActInfo, 1, 1);
		}
	}
}

void CVec3InputNode::ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
{
	if (event == IFlowNode::eFE_Activate)
	{
		if (IsPortActive(pActInfo, 0))
		{
			auto label = GetPortString(pActInfo, 1);
			auto inputVec = GetPortVec3(pActInfo, 2);

			float inputs[] = { inputVec.x, inputVec.y, inputVec.z };
			ImGui::InputFloat3(label.c_str(), inputs);

			inputVec = Vec3(inputs[0], inputs[1], inputs[2]);

			ActivateOutput(pActInfo, 0, 1);
			ActivateOutput<Vec3>(pActInfo, 1, inputVec);
		}
	}
}


REGISTER_FLOW_NODE("ImGui:Window:BeginWindow", CWindowNode)
REGISTER_FLOW_NODE("ImGui:Window:EndWindow", CWindowEndNode)
REGISTER_FLOW_NODE("ImGui:Inputs:Vec3Input", CVec3InputNode)
REGISTER_FLOW_NODE("ImGui:Text", CTextNode)
REGISTER_FLOW_NODE("ImGui:Label", CLabelTextNode)
REGISTER_FLOW_NODE("ImGui:Button", CButtonNode)



