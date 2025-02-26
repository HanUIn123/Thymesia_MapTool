#include "pch.h"
#include "TempManager.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CTempManager)

CTempManager::CTempManager()
{
}

CTempManager::~CTempManager()
{
    for (size_t i = 0; i <= 1; ++i)
        m_pFrameStateRS[i]->Release();

    Temp_Release();
}

void CTempManager::InitRenderStates()
{
    for (size_t i = 0; i <= 1; ++i)
    {
        if (i == 0)
            m_tagRasterizeDesc[i].FillMode = D3D11_FILL_WIREFRAME;
        else
            m_tagRasterizeDesc[1].FillMode = D3D11_FILL_SOLID;

        m_tagRasterizeDesc[i].CullMode = D3D11_CULL_NONE;
        m_tagRasterizeDesc[i].DepthClipEnable = true;
        m_pGameInstance->Get_Device()->CreateRasterizerState(&m_tagRasterizeDesc[i], &m_pFrameStateRS[i]);
    }
}

void CTempManager::SwitchFrameMode()
{
    ImGui::Begin("Switch FrameMode", NULL, ImGuiWindowFlags_MenuBar);
    ImGui::Checkbox("Switching To WireFrame", &m_bWireFrameMode);
    if (ImGui::Button("WireFrame On"))
        m_bWireFrameMode = true;
    if (ImGui::Button("WireFrame Off"))
        m_bWireFrameMode = false;
    ImGui::End();
}

void CTempManager::Temp_Initialize(CGameInstance* _pGameInstance)
{
    m_pGameInstance = _pGameInstance;

    InitRenderStates();
}

void CTempManager::Temp_Update()
{
}

void CTempManager::Temp_Render()
{
    if (m_bWireFrameMode)
        m_pGameInstance->Get_Context()->RSSetState(m_pFrameStateRS[0]);
    else
        m_pGameInstance->Get_Context()->RSSetState(m_pFrameStateRS[1]);
}

void CTempManager::Temp_Release()
{
}

void CTempManager::Free()
{
    __super::Free();
}
