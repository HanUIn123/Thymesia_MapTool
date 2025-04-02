#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "GameInstance.h"


BEGIN(Engine)
class CModel;
class CShader;
class CCollider;
END

BEGIN(Client)
class CSpecificObject final : public CGameObject
{
public:
    struct SpecificObject_Desc : public CGameObject::GAMEOBJECT_DESC
    {
        _float      fFrustumRadius = {};
        _float4		fRotation = { };
        _float3     fScale = {};
        string		ObjectName = {};
        _uint		iPassNum = { 0 };
    };

    struct SpecificObject_Info
    {
        _char   szName[MAX_PATH] = {};
        _float4	fPosition;
        _float3 fScale;
        _float4 fRotation;
        _float  fFrustumRadius;
        _uint	iPassNum;
    };

private:
    CSpecificObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    CSpecificObject(const CSpecificObject& Prototype);
    virtual ~CSpecificObject() = default;

public:
    virtual HRESULT                 Initialize_Prototype() override;
    virtual HRESULT                 Initialize(void* pArg) override;
    virtual void                    Priority_Update(_float fTimeDelta) override;
    virtual void                    Update(_float fTimeDelta) override;
    virtual void                    Late_Update(_float fTimeDelta) override;
    virtual HRESULT                 Render() override;
public:
    SpecificObject_Info             Get_SpecificObjectInfo();
        
    SpecificObject_Desc             Get_SpecificObjectDesc() {return m_tagDesc; }
    _float4                         Get_SpecificObjectPosition() { return m_fPosition; }
    _float3                         Get_SpecificObjectScale() { return m_fScale; }
    _float4                         Get_SpecificObjectRotation() { return m_fRotation; }
    _float                          Get_SpecificObjectFrustumRadius() { return m_fFrustumRadius; }

    void                            Set_SpecificObjectPosition(_float4 _vPosition);
    void                            Set_SpecificObjectScale(_float3 _vScale);
    void                            Set_SpecificObjectRotation(_float4 _vRotation);

    void		                    Set_FrustumRadius(_float fFrustumRadius);
    void                            Set_FrustumSphere(_bool bSphere) {m_bFrustumSphere = bSphere;}

private:
    CShader*                        m_pShaderCom = { nullptr };
    CModel*                         m_pModelCom = { nullptr };
    CCollider*                      m_pColliderCom = { nullptr };
    _float		                    m_fFrustumRadius = { 0.f };
    _float4		                    m_fRotation = { 0.f, 0.f, 0.f , 0.0f};
    _float3		                    m_fScale = { 0.f, 0.f, 0.f };
    _float4                         m_fPosition = { 0.0f, 0.0f, 0.0f ,0.0f };
    _char		                    m_MeshName[MAX_PATH] = {};
    _bool		                    m_bFrustumSphere = { true };

    SpecificObject_Info             m_tagSpecificInfo = {};
    SpecificObject_Desc             m_tagDesc = {};
private:
    virtual HRESULT                 Ready_Components();
    virtual HRESULT                 Bind_ShaderResources();

public:
    static CSpecificObject*         Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    virtual CGameObject*            Clone(void* pArg) override;
    virtual void                    Free() override;

};
END

