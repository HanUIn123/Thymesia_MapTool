#include "..\Public\UIObject.h"
#include "GameInstance.h"

CUIObject::CUIObject(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CGameObject { pDevice, pContext }
{
}

CUIObject::CUIObject(const CUIObject & Prototype)
	: CGameObject( Prototype )
	, m_ViewMatrix { Prototype.m_ViewMatrix }
	, m_ProjMatrix { Prototype.m_ProjMatrix }
{
}

HRESULT CUIObject::Initialize_Prototype()
{
	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixIdentity());



	return S_OK;
}

HRESULT CUIObject::Initialize(void * pArg)
{
	/* 현재 뷰포트의 정보를 얻어온다. */
	UIOBJECT_DESC*		pDesc = static_cast<UIOBJECT_DESC*>(pArg);

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
		
	_uint2			vViewportSize = m_pGameInstance->Get_ViewportSize();

	m_pTransformCom->Scaling(_float3(pDesc->fSizeX, pDesc->fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(pDesc->fX - (vViewportSize.x * 0.5f), -pDesc->fY + (vViewportSize.y * 0.5f), 0.f, 1.f));

	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH(static_cast<_float>(vViewportSize.x), static_cast<_float>(vViewportSize.y), pDesc->fNear, pDesc->fFar));

	return S_OK;
}

void CUIObject::Priority_Update(_float fTimeDelta)
{
}

void CUIObject::Update(_float fTimeDelta)
{
}

void CUIObject::Late_Update(_float fTimeDelta)
{
}

HRESULT CUIObject::Render()
{
	return S_OK;
}


void CUIObject::Free()
{
	__super::Free();


}
