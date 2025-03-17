#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
//class CCollider;
class CVIBuffer_Cube;
class CShader;
END

BEGIN(Client)
class CTempCollider : public CGameObject
{
public:
    struct TC_DESC : public CGameObject::GAMEOBJECT_DESC
    {
        _float4 fPosition = {};
        _float3 fRotation = {};
        _float3 fScale = {};
        //TRIGGER_TYPE eTriggerType = {};
    };

    struct TC_INFO
    {
        _float4 fPosition = {};
        _float3 fRotation = {};
        _float3 fScale = {};
    };

private:
    CTempCollider(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
    CTempCollider(const CTempCollider& _Prototype);
    virtual ~CTempCollider() = default;

public:
    virtual HRESULT										Initialize_Prototype() override;
    virtual HRESULT										Initialize(void* _pArg) override;

    virtual void										Priority_Update(_float _fTimeDelta) override;
    virtual void										Update(_float _fTimeDelta) override;
    virtual void										Late_Update(_float _fTimeDelta) override;

    virtual HRESULT										Render() override;

    TC_INFO                                             Get_Info() const { return m_tagInfoTempCollider; }
    void                                                Set_Info(TC_INFO _tagInfo) { m_tagInfoTempCollider = _tagInfo; }
public:
    HRESULT                                             Ready_Components();
    HRESULT                                             Bind_ShaderResources();

    _bool                                               Check_Collision_With_Player();
    TRIGGER_TYPE                                        m_eTriggerType = { TRIGGER_TYPE::TT_END };

    _float4                                             Get_TempColliderPosition() const { return m_tagInfoTempCollider.fPosition; }
    _float3                                             Get_TempColliderScale()const { return m_tagInfoTempCollider.fScale; }
    void                                                Set_TempColliderScale(_float3 _vScale);
private:
    //CCollider* m_pColliderCom = { nullptr };
    CVIBuffer_Cube* m_pVIBufferCom = { nullptr };
    CShader* m_pShaderCom = { nullptr };


private:
    _bool                                               m_bFade = { false };
    TC_INFO                                             m_tagInfoTempCollider;
public:
    static CTempCollider* Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
    virtual CGameObject* Clone(void* _pArg) override;
    virtual void                                        Free() override;
};
END