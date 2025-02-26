#include "pch.h" 
#include "Player.h"
#include "GameInstance.h"
#include "Body_Player.h"
#include "Weapon.h"


CPlayer::CPlayer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CContainerObject(pDevice, pContext)
{

}

CPlayer::CPlayer(const CPlayer& Prototype)
	:CContainerObject(Prototype)
	, m_iState(Prototype.m_iState)
{

}

HRESULT CPlayer::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	strcpy_s(m_szName, "PLAYER");

	CGameObject::GAMEOBJECT_DESC        Desc{};

	Desc.fSpeedPerSec = 25.f;
	Desc.fRotationPerSec = XMConvertToRadians(90.f);


	if (FAILED(__super::Initialize(&Desc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	if (FAILED(Ready_PartObjects()))
		return E_FAIL;

	_vector vInitialPosition = XMVectorSet(2.5f, 0.0f, 2.5f, 1.0f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vInitialPosition);

	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::PLAYER, this);

	m_pTransformCom->Scaling(_float3(0.002f, 0.002f, 0.002f));

	//m_pNavigationCom->Set_CurrentNaviIndex(vInitialPosition);

	return S_OK;
}

void CPlayer::Priority_Update(_float fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);

	_long MouseMoveX = m_pGameInstance->Get_DIMouseMove(DIMS_X);
	_long MouseMoveY = m_pGameInstance->Get_DIMouseMove(DIMS_Y);

	_vector vCurPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	_vector CamRight = XMVector3Normalize(m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_VIEW).r[0]);
	_vector CamLeft = XMVector3Normalize(m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_VIEW).r[0]) * -1.f;


#pragma region Mouse_Input

#pragma endregion 

#pragma region KeyBoard Input
	//if (m_pGameInstance->Get_DIKeyState(DIK_UP) & 0x80)
	//{
	//	m_pTransformCom->Go_Straight(fTimeDelta, m_pNavigationCom);
	//}
	//if (m_pGameInstance->Get_DIKeyState(DIK_DOWN) & 0x80)
	//{
	//	m_pTransformCom->Go_Backward(fTimeDelta, m_pNavigationCom);
	//}
	//if (m_pGameInstance->Get_DIKeyState(DIK_LEFT) & 0x80)
	//{
	//	m_pTransformCom->Go_Left(fTimeDelta, m_pNavigationCom);
	//}
	//if (m_pGameInstance->Get_DIKeyState(DIK_RIGHT) & 0x80)
	//{
	//	m_pTransformCom->Go_Right(fTimeDelta, m_pNavigationCom);
	//}

	//_float fPosY = XMVectorGetY(vCurPosition);

	//if (m_pGameInstance->Get_DIKeyState(DIK_E) & 0x80)
	//{
	//	m_bRiding = true;
	//	fPosY += fTimeDelta;
	//	cout << "플레이어 높이 : " << fPosY << endl;

	//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSetY(vCurPosition, fPosY));
	//	m_pNavigationCom->Set_CurCellIndex(m_pNavigationCom->Find_Closest_Cell(m_pTransformCom->Get_State(CTransform::STATE_POSITION)));
	//}
	//if (m_pGameInstance->Get_DIKeyState(DIK_T) & 0x80)
	//{
	//	m_bRiding = false;
	//}
	//if (m_pGameInstance->Get_DIKeyState(DIK_R) & 0x80)
	//{
	//	m_bRiding = true;
	//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSetY(vCurPosition, 0.1f));
	//	m_pNavigationCom->Set_CurCellIndex(m_pNavigationCom->Find_Closest_Cell(m_pTransformCom->Get_State(CTransform::STATE_POSITION)));
	//}
#pragma endregion 

}

void CPlayer::Update(_float fTimeDelta)
{
	_vector		vCurPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_vector test = { 0.f,0.f,0.f,1.f };

	//_vector		vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	//if (!m_bRiding)
	//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSetY(vPosition, m_pNavigationCom->Compute_Height(vPosition)));

	m_pColliderCom->Update(XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrix_Ptr()));

	__super::Update(fTimeDelta);
}

void CPlayer::Late_Update(_float fTimeDelta)
{
	__super::Late_Update(fTimeDelta);

	/* 잠시 네비게이션 정확히 타는지 확인할려고 넣는 코드 */
#ifdef _DEBUG
	m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
#endif
	m_fTimeDelta = fTimeDelta;


	/* 이전 상태 저장하기 */
	m_iPreState = m_iState;



}

HRESULT CPlayer::Render()
{
#ifdef _DEBUG
	//m_pNavigationCom->Render();	
	//m_pColliderCom->Render();	
#endif 

	//cout << "현재 네비  : " << m_pNavigationCom->Get_CurCellIndex() << endl;

	return S_OK;
}

HRESULT CPlayer::Ready_Components()
{
	/* Com_Navigation */
	CNavigation::NAVIGATION_DESC   Desc{};

	/* 초기 디버깅 플레이어가 서있는 셀의 인덱스 */
	Desc.iCurrentCellIndex = 0;

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Navigation"),
		TEXT("Com_Navigation"), reinterpret_cast<CComponent**>(&m_pNavigationCom), &Desc)))
		return E_FAIL;


	/* Com_Collider */
	CBounding_Sphere::BOUNDING_SPHERE_DESC SphereDesc{};


	SphereDesc.fRadius = 125.f;
	SphereDesc.vCenter = _float3(0.f, SphereDesc.fRadius + 60.f, 0.f);


	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_SPHERE"),
		TEXT("Com_Collider"), reinterpret_cast<CComponent**>(&m_pColliderCom), &SphereDesc)))
		return E_FAIL;


	m_pColliderCom->Set_Collider_Name("Player");


	return S_OK;
}

HRESULT CPlayer::Ready_PartObjects()
{
	CBody_Player::BODY_PLAYER_DESC BodyDesc{};

	BodyDesc.pParentState = &m_iState;
	BodyDesc.pParentWorldMatrix = m_pTransformCom->Get_WorldMatrix_Ptr();
	BodyDesc.fSpeedPerSec = 0.f;
	//BodyDesc.fSpeedPerSec = 1.f;
	BodyDesc.fRotationPerSec = 0.f;

	if (FAILED(__super::Add_PartObject(TEXT("Part_Body"), LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Body_Player"), &BodyDesc)))
		return E_FAIL;

	m_pModel = dynamic_cast<CModel*>(Find_PartObject_Component(TEXT("Part_Body"), TEXT("Com_Model")));


	return S_OK;
}


void CPlayer::OnCollisionEnter(CGameObject* _pOther)
{

}


void CPlayer::OnCollision(CGameObject* _pOther)
{

}

void CPlayer::OnCollisionExit(CGameObject* _pOther)
{

}

CPlayer* CPlayer::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CPlayer* pInstance = new CPlayer(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CPlayer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CPlayer::Clone(void* pArg)
{
	CPlayer* pInstance = new CPlayer(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : CPlayer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pColliderCom);
	Safe_Release(m_pNavigationCom);
}
