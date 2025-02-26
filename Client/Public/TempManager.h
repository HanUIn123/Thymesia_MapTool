#pragma once
#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)
class CTempManager : public CBase
{
    DECLARE_SINGLETON(CTempManager)

public:
    CTempManager();
    virtual ~CTempManager();

private:
    CGameInstance* m_pGameInstance = { nullptr };
private:
    ID3D11RasterizerState* m_pFrameStateRS[2] = { nullptr };
    D3D11_RASTERIZER_DESC                   m_tagRasterizeDesc[2] = {};
    void                                    InitRenderStates();
public:
    void                                    SwitchFrameMode();

private:
    _bool                                   m_bWireFrameMode = { false };

public:
    void                                    Temp_Initialize(CGameInstance* _pGameInstance);
    void                                    Temp_Update();
    void                                    Temp_Render();
    void                                    Temp_Release();
private:
    virtual void Free() override;
};
END