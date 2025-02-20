#include "pch.h" 
#include "..\Public\Camera_Free.h"

#include "GameInstance.h"
#include "Player.h"
#include "Layer.h"

CCamera_Free::CCamera_Free(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CCamera{ pDevice, pContext }
{

}

CCamera_Free::CCamera_Free(const CCamera_Free & Prototype)
	: CCamera(Prototype)
{

}

HRESULT CCamera_Free::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera_Free::Initialize(void * pArg)
{
	FREE_CAMERA_DESC*		pDesc = static_cast<FREE_CAMERA_DESC*>(pArg);

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_fMouseSensor = pDesc->fMouseSensor;

	return S_OK;
}


void CCamera_Free::Priority_Update(_float fTimeDelta)
{
	if (GetKeyState('W') & 0x8000)
		m_pTransformCom->Go_Straight(fTimeDelta);
	if (GetKeyState('S') & 0x8000)
		m_pTransformCom->Go_Backward(fTimeDelta);
	if (GetKeyState('A') & 0x8000)
		m_pTransformCom->Go_Left(fTimeDelta);
	if (GetKeyState('D') & 0x8000)
		m_pTransformCom->Go_Right(fTimeDelta);

	if (m_pGameInstance->isKeyEnter(DIK_Q))
	{
		if (m_bStop)
			m_bStop = false;
		else
			m_bStop = true;
	}

	if (!m_bStop)
	{
		_long		MouseMove = { 0 };

		if (MouseMove = m_pGameInstance->Get_DIMouseMove(DIMS_X))
		{
			m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta * m_fSensor * MouseMove);
		}

		if (MouseMove = m_pGameInstance->Get_DIMouseMove(DIMS_Y))
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), fTimeDelta * m_fSensor * MouseMove);
		}

	}

	if (!m_bStop)
		Mouse_Fix();

	__super::Priority_Update(fTimeDelta);


}

void CCamera_Free::Update(_float fTimeDelta)
{
	ImGui::Begin("CurPos");

	_vector vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_float fCurPos[3] = { XMVectorGetX(vPos),  XMVectorGetY(vPos) ,  XMVectorGetZ(vPos) };

	ImGui::Text("X: %f ", fCurPos[0]);
	ImGui::Text("Y: %f ", fCurPos[1]);
	ImGui::Text("Z: %f ", fCurPos[2]);

	ImGui::InputFloat3("Camera Pos", m_fCurPos);

	if (ImGui::Button("Teleport"))
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fCurPos[0], m_fCurPos[1], m_fCurPos[2], 1.f));
	}

	ImGui::End();
}

void CCamera_Free::Late_Update(_float fTimeDelta)
{
	

}

HRESULT CCamera_Free::Render()
{
	return S_OK;
}

void CCamera_Free::Mouse_Fix()
{
	_uint				iNumViewports = { 1 };
	D3D11_VIEWPORT		ViewportDesc{};

	m_pContext->RSGetViewports(&iNumViewports, &ViewportDesc);

	POINT	ptMouse{ ViewportDesc.Width / 2.f, ViewportDesc.Height / 2.f };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

CCamera_Free * CCamera_Free::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CCamera_Free*	pInstance = new CCamera_Free(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CCamera_Free");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_Free::Clone(void * pArg)
{
	CCamera_Free*	pInstance = new CCamera_Free(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : CCamera_Free");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_Free::Free()
{
	__super::Free();

	Safe_Release(m_pPlayerTransformCom);	
}
