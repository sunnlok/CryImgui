#pragma once
#include "CryInput\IHardwareMouse.h"
#include "CryInput\IInput.h"

class CImguiRenderer;

class  CImguiImpl : IHardwareMouseEventListener, ISystemEventListener, IInputEventListener
{
	friend class CImguiRenderNode;

public:

	CImguiImpl();
	~CImguiImpl();

	void InitImgui();

	void OnPreSystemUpdate();
	void Update();
	void OnPreRenderUpdate();

	static CImguiImpl* Get();

	virtual void OnHardwareMouseEvent(int iX, int iY, EHARDWAREMOUSEEVENT eHardwareMouseEvent, int wheelDelta = 0) override;


	virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;


	virtual bool OnInputEvent(const SInputEvent& event) override;

	IMaterial* GetFontMaterial() { return m_pFontMaterial; }
protected:
	ITexture* GetFontTexture() { return m_pFontTexture; }

private:
	int m_bShowDemoWindow = 0;

	void InitImguiFontTexture();

	_smart_ptr<ITexture>			m_pFontTexture = nullptr;
	IMaterial*			m_pFontMaterial = nullptr;
	IMaterial*			m_pImageTest = nullptr;

	std::unique_ptr<CImguiRenderer> m_pRenderer;
};