#pragma once;
#include <CryRenderer/CustomPass.h>
#include "Imgui/imgui.h"

struct SRTDrawList
{
	// This is what you have to render
	ImVector<ImDrawCmd>     CmdBuffer;          // Draw commands. Typically 1 command = 1 GPU draw call, unless the command is a callback.
	ImVector<ImDrawIdx>     IdxBuffer;          // Index buffer. Each command consume ImDrawCmd::ElemCount of those
	ImVector<ImDrawVert>    VtxBuffer;          // Vertex buffer.
	ImDrawListFlags         Flags;              // Flags, you may poke into these to adjust anti-aliasing settings per-primitive.
};

struct SRTDrawData
{
	int             TotalIdxCount;          // For convenience, sum of all ImDrawList's IdxBuffer.Size
	int             TotalVtxCount;          // For convenience, sum of all ImDrawList's VtxBuffer.Size
	ImVec2          DisplayPos;             // Upper-left position of the viewport to render (== upper-left of the orthogonal projection matrix to use)
	ImVec2          DisplaySize;            // Size of the viewport to render (== io.DisplaySize for the main viewport) (DisplayPos + DisplaySize == lower-right of the orthogonal projection matrix to use)
	ImVec2          FramebufferScale;       // Amount of pixels for each unit of DisplaySize. Based on io.DisplayFramebufferScale. Generally (1,1) on normal display, (2,2) on OSX with Retina display.
};

class CImguiRenderer : public Cry::Renderer::CustomPass::ICustomRendererImplementation
{
public:
	CImguiRenderer(Cry::Renderer::CustomPass::ICustomPassRenderer* pUIRenderer, Vec2i rtDimensions);

	void RenderImgui();

	virtual bool RT_Initalize(std::unique_ptr<Cry::Renderer::CustomPass::ICustomRendererInstance> pInstance) override;


	virtual void RT_Shutdown() override;


	virtual void RT_Update(bool bLoadingThread = false) override;


	virtual void RT_Render() override;

	Cry::Renderer::CustomPass::ICustomPassRenderer* m_pUIRenderer;

	struct SMvpMat
	{
		Vec4	m_mvpMat[4];
	} m_mvpConstant;
	bool bConstantWasDirty;
	
	ITexture* m_pFontTexture = nullptr;


	void SetBlendMode(uint32 flags) { m_blendMode = flags; }
private:
	void UpdateRenderTarget();

	uint32 m_blendMode = GS_BLSRC_SRCALPHA | GS_BLDST_ONEMINUSSRCALPHA;
	uint32 m_blendModeRT = GS_BLSRC_SRCALPHA | GS_BLDST_ONEMINUSSRCALPHA;

	void DrawCommandList(const SRTDrawList &list, int meshIDX);
	bool IsPassDataDirty();
	void UpdateBuffers(const SRTDrawList &list, int meshIDX);
	void DrawRenderCommand(const ImDrawCmd &cmd, int meshIDX);
	void AdjustRenderMeshes();
	void UpdatePassParams(Cry::Renderer::CustomPass::SPassParams &params);

	_smart_ptr<IShader>		m_pImguiShader;
	bool m_bInitialized = false;

	std::vector<_smart_ptr<IRenderMesh>> m_renderMeshes;

	CryCriticalSection m_renderLock;
	Vec2i	m_renderDimensions;

	SRTDrawData				m_rtDrawData;
	std::vector<SRTDrawList> m_rtDrawLists;

	//std::unique_ptr<IDynTexture> m_pDynRT;


	_smart_ptr<ITexture> m_pRenderTarget;
	int m_texID = 0;

	int							m_currentBufferOffset;
	std::vector<std::pair<uintptr_t, uintptr_t>>  m_bufferHandles;

	ITexture*	m_pLastRT = nullptr;

	uint32		m_currentVtxOffset = 0;
	uint32		m_currentIdxOffset = 0;

	std::unique_ptr<Cry::Renderer::CustomPass::ICustomRendererInstance> m_pInstance;

	uintptr_t m_mvpConstantBuffer = INVALID_BUFFER;

	bool m_bClearOnEmpty;
};