#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "GameInstance.h"


BEGIN(Engine)
class CModel;
class CShader;
class CCalculator;
class CMesh;
class CCollider;
END

BEGIN(Client)
class CEnvironmentObject abstract : public CGameObject
{
public:
    struct INSTANCE_INFO
    {
        XMMATRIX		mInstanceToWorld;
    };

public:
    struct ENVIRONMENT_OBJECT_DESC : public CGameObject::GAMEOBJECT_DESC
    {
        _float fFrustumRadius = { 0.f };
        _float3 fRotation = {};
        string ObjectName = {};
        _float fRange = {};
        _float fSpace = {};
        //_float fPosition= {};
        vector<_float3> vecPosition = {};


    };

public:
    struct EN_OBJECT_INFO
    {
        _char szName[MAX_PATH] = {};
        _float4 fPosition;
        _float3 fScale;
        _float3 fRotation;
        _float fFrustumRadius;
    };

    struct EN_MESH_INFO
    {
        _float fDist;
        _float3 fPosition;
    };

protected:
    CEnvironmentObject(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
    CEnvironmentObject(const CEnvironmentObject& _Prototype);
    virtual ~CEnvironmentObject() = default;

protected:
    virtual HRESULT Initialize(void* _pArg) override;
public:
    _bool           Picking_En_Objects(EN_MESH_INFO& _pInfo);
    EN_OBJECT_INFO  Get_EnvironmentObjectInfo();

    void            Set_FrustumRadius(_float _fFrustumRadius);
    void            Set_FrustumSphere(_bool _bSphere) {
        m_bFrustumSphere = _bSphere;
    }
	virtual void Update_InstanceBuffer();

protected:
    CShader* m_pShaderCom = { nullptr };
    CModel* m_pModelCom = { nullptr };
    CCalculator* m_pCalculatorCom = { nullptr };
    CCollider* m_pColliderCom = { nullptr };
protected:
    vector<CMesh*> m_vecMeshes;

    _float		   m_fFrustumRadius = { 0.f };
    _float3		   m_fRotation = { 0.f, 0.f, 0.f };
    _float3		   m_fScale = { 0.f, 0.f, 0.f };
    _char		   m_EnvironmentMeshName[MAX_PATH] = {};
    _bool		   m_bFrustumSphere = { true };
    


protected:
    vector<VTX_MODEL_INSTANCE> m_vecInstanceData;
    _uint m_iNumInstance = {};
    
public:
    vector<VTX_MODEL_INSTANCE> Get_ModelInstanceVector() { return m_vecInstanceData; }

protected:
    virtual HRESULT Ready_Components();
    virtual HRESULT Bind_ShaderResources() PURE;

public:
    virtual CGameObject* Clone(void* _pArg) = 0;
    virtual void Free() override;

};

END