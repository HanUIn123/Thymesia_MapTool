#include "pch.h" 
#include "Loader.h"
#include "Body_Player.h"
#include "GameInstance.h"
#include "Camera_Free.h"
#include "BackGround.h"
#include "Weapon.h"
#include "Player.h"

#pragma region 보스 
#include "Boss_Magician.h"
#include "Boss_Varg.h"
#pragma endregion 

#pragma region 환경요소 
#include "Sky.h"
#include "Terrain.h"
#include "NonMoveObject.h"
#pragma endregion 

#pragma region 인스턴싱요소
#include "GroundObject.h"
#pragma endregion




#pragma region 테스트용 사다리
#include "Ladder.h"
#pragma endregion



CLoader::CLoader(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
	, m_pGameInstance { CGameInstance::GetInstance()}
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pContext);
	Safe_AddRef(m_pDevice);
}

_uint APIENTRY Thread_Main(void* pArg)
{
	CLoader*		pLoader = static_cast<CLoader*>(pArg);

	pLoader->Start_Loading();

	return 0;
}

HRESULT CLoader::Initialize(LEVELID eNextLevelID)
{


	m_eNextLevelID = eNextLevelID;

	InitializeCriticalSection(&m_CriticalSection);

	// m_eNextLevelID가 필요로하는 자원을 로드해주기위한 스레드를 만들어낸다. 
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::Start_Loading()
{
	EnterCriticalSection(&m_CriticalSection);

	CoInitializeEx(nullptr, 0);

	HRESULT			hr = {};

	switch (m_eNextLevelID)
	{
	case LEVEL_LOGO:
		hr = Loading_For_Level_Logo();
		break;
	case LEVEL_GAMEPLAY:
		hr = Loading_For_Level_GamePlay();
		break;
	}

	if (FAILED(hr))
		return E_FAIL;

	LeaveCriticalSection(&m_CriticalSection);

	return S_OK;
}

void CLoader::SetUp_WindowText()
{
	SetWindowText(g_hWnd, m_szLoadingText);
}

HRESULT CLoader::Loading_For_Level_Logo()
{

#pragma region Logo 
	lstrcpyW(m_szLoadingText, TEXT("텍스쳐 원형을 생성한다."));
	/* For.Prototype_Component_Texture_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_BackGround"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/ThymesiaUI/LoadingScreen/LoadingScreen_%d.dds"), 8))))
		return E_FAIL;

	lstrcpyW(m_szLoadingText, TEXT("셰이더 원형을 생성한다."));
	//D3D11_INPUT_ELEMENT_DESC	VertexElements[] = {
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA , 0 },			
	//};

	/* For.Prototype_Component_Shader_VtxPosTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Shader_VtxPosTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxPosTex.hlsl"), VTXPOSTEX::Elements, VTXPOSTEX::iNumElements))))
		return E_FAIL;


	lstrcpyW(m_szLoadingText, TEXT("모델 원형을 생성한다."));
	/* For.Prototype_Component_VIBuffer_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_VIBuffer_Rect"),
		CVIBuffer_Rect::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	lstrcpyW(m_szLoadingText, TEXT("객체 원형을 생성한다."));

	/* For.Prototype_GameObject_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pDevice, m_pContext))))
		return E_FAIL;	

	/* 로딩이 완료되었습ㄴ미다 */
	lstrcpyW(m_szLoadingText, TEXT("로딩끝."));
	m_isFinished = true;

	return S_OK;
#pragma endregion 
}

HRESULT CLoader::Loading_For_Level_GamePlay()
{
	/* 게임플레이레벨을 위한 자원을 로드합니다.  */
	lstrcpyW(m_szLoadingText, TEXT("게임플레이레벨을 위한 자원을 로딩 중입니다."));

	// 초기 설정을 위한 트랜스폼 
	_matrix PreTransformMatrix = XMMatrixIdentity();	

#pragma region 지형
	lstrcpyW(m_szLoadingText, TEXT("텍스쳐 원형을 생성한다."));
	/* For.Prototype_Component_Texture_Terrain*/
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Tile%d.dds"), 2))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture__MouseRange"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/MouseRange.png"), 1))))
		return E_FAIL;
	
	lstrcpyW(m_szLoadingText, TEXT("터레인 컴포넌트 생성"));
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Terrain")
		, CVIBuffer_Terrain::Create(m_pDevice, m_pContext, 100, 100, 1, nullptr))))
		return E_FAIL;


	/* For.Prototype_GameObject_Terrain */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Terrain"),	
		CTerrain::Create(m_pDevice, m_pContext))))		
		return E_FAIL;	
#pragma endregion 



#pragma region Sky
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Sky"),
		CSky::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Sky */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Sky"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"), 4))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxCube */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxCube"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxCube.hlsl"), VTXCUBE::Elements, VTXCUBE::iNumElements))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Cube"),
		CVIBuffer_Cube::Create(m_pDevice, m_pContext))))
		return E_FAIL;

#pragma endregion 

#pragma region 카메라 
	/* For.Prototype_GameObject_Camera_Free */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Camera_Free"),
		CCamera_Free::Create(m_pDevice, m_pContext))))
		return E_FAIL;
#pragma endregion 


#pragma region 인스턴스 버퍼 
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Cube"),
	//	CVIBuffer_Instancing::Create(m_pDevice, m_pContext))))
	//	return E_FAIL;
#pragma endregion


#pragma region 셰이더

	lstrcpyW(m_szLoadingText, TEXT("셰이더 원형을 생성한다."));
	/* For.Prototype_Component_Shader_VtxNorTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxNorTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxNorTex.hlsl"), VTXNORTEX::Elements, VTXNORTEX::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxMesh */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxMesh"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxMesh.hlsl"), VTXMESH::Elements, VTXMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxMesh */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxInstanceMesh"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxInstanceMesh.hlsl"), VTX_MODEL_INSTANCE::Elements, VTX_MODEL_INSTANCE::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Shader_VtxMeshNoDefferd */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxMeshNoDefferd"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxMeshNoDefferd.hlsl"), VTXMESH::Elements, VTXMESH::iNumElements))))	
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxAnimMesh */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxAnimMesh"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxAnimMesh.hlsl"), VTXANIMMESH::Elements, VTXANIMMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxAnimMeshNoDefferd */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxAnimMeshNoDefferd"),	
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxAnimMeshNoDefferd.hlsl"), VTXANIMMESH::Elements, VTXANIMMESH::iNumElements))))	
		return E_FAIL;	


	/* For.Prototype_Component_Shader_VtxPosTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxPosTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxPosTex.hlsl"), VTXPOSTEX::Elements, VTXPOSTEX::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxPosTexInstance */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxPosTexInstance"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxPosTexInstance.hlsl"), VTX_RECT_INSTANCE::Elements, VTX_RECT_INSTANCE::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxPointInstance */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxPointInstance"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxPointInstance.hlsl"), VTX_POINT_INSTANCE::Elements, VTX_POINT_INSTANCE::iNumElements))))
		return E_FAIL;

#pragma endregion 


#pragma region 카쿠 모델
	//lstrcpyW(m_szLoadingText, TEXT("카쿠 모델을 생성한다."));
	///* For.Prototype_Component_Model_Kaku*/
	//PreTransformMatrix = /*XMMatrixScaling(0.015f, 0.015f, 0.015f) **/ XMMatrixRotationY(XMConvertToRadians(180.f));
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Kaku"),
	//	CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Kaku/2_03_kaku_2.fbx", CModel::MODEL_ANIM, PreTransformMatrix))))
	//	return E_FAIL;
	//
	/////* For.Prototype_GameObject_Player */
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Player"),
	//	CPlayer::Create(m_pDevice, m_pContext))))
	//	return E_FAIL;

	/////* For.Prototype_GameObject_Body_Player */
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Body_Player"),
	//	CBody_Player::Create(m_pDevice, m_pContext))))
	//	return E_FAIL;

#pragma endregion 

#pragma region 카쿠 무기 모델 
	//lstrcpyW(m_szLoadingText, TEXT("카쿠 무기 모델을 생성한다."));
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Kaku_Weapon"),
	//	CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/KakuWeapon/weapon.fbx", CModel::MODEL_NONANIM))))
	//	return E_FAIL;
	//
	//
	/////* For.Prototype_GameObject_Weapon */
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Weapon"),
	//	CWeapon::Create(m_pDevice, m_pContext))))
	//	return E_FAIL;	

#pragma endregion 

#pragma region Navigation 
	//lstrcpyW(m_szLoadingText, TEXT("네비게이션 원형을 생성한다."));	
	///* For.Prototype_Component_Navigation */	
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Navigation"),	
	//	CNavigation::Create(m_pDevice, m_pContext, TEXT("../Navigation_File/test49.bin")))))	
	//	return E_FAIL;	
	lstrcpyW(m_szLoadingText, TEXT("네비게이션 원형을 생성한다."));
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Navigation"), CNavigation::CreateOnly(m_pDevice, m_pContext))))
		return E_FAIL;
#pragma endregion 

#pragma region Collider

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_AABB"),
		CCollider::Create(m_pDevice, m_pContext,CCollider::TYPE_AABB))))	
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_SPHERE"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_SPHERE))))	
		return E_FAIL;

#pragma endregion

#pragma region Calculator

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Calculator"),
		CCalculator::Create(m_pDevice, m_pContext))))
		return E_FAIL;

#pragma endregion

#pragma region 티메시아 캐릭터 
	lstrcpyW(m_szLoadingText, TEXT("티메시아 모델을 생성한다."));	
	/* For.Prototype_Component_Model_Kaku*/
	PreTransformMatrix = /*XMMatrixScaling(0.015f, 0.015f, 0.015f) **/ XMMatrixRotationY(XMConvertToRadians(180.f));		
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Corner"),	
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Thymesia/realtest.fbx", CModel::MODEL_ANIM, PreTransformMatrix))))
		return E_FAIL;		

	///* For.Prototype_GameObject_Body_Player */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Body_Player"),	
		CBody_Player::Create(m_pDevice, m_pContext))))	
		return E_FAIL;	
	
	///* For.Prototype_GameObject_Player */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Player"),	
		CPlayer::Create(m_pDevice, m_pContext))))	
		return E_FAIL;	

#pragma endregion 


#pragma region Objects
	//LopTrap
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_LobTrap"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/LobTrap/LobTrap.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//SM_Wall_Shelf
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Wall_Shelf"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Sall_Shelf/SM_Wall_Shelf.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//P_Rag03
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_Rag03"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_Rag03/P_Rag03.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//SM_WoodFence03
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_WoodFence03"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_WoodFence03/SM_WoodFence03.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//SM_WoodFence04
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_WoodFence04"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_WoodFence04/SM_WoodFence04.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//SM_WoodStairs03
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_WoodStairs03"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_WoodStairs03/SM_WoodStairs03.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//SM_WoodStairs03
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_HORSE_P_WoodenFrame02_05"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/HORSE_P_WoodenFrame02_05/HORSE_P_WoodenFrame02_05.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//P_BossAtriumCircle01
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossAtriumCircle01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossAtriumCircle01/P_BossAtriumCircle01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//P_BossCemetery_02_02
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossCemetery_02_02"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossCemetery_02_02/P_BossCemetery_02_02.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	//P_BossCemetery_04
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossCemetery_04"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossCemetery_04/P_BossCemetery_04.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossCemetery_05"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossCemetery_05/P_BossCemetery_05.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossCemetery_06"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossCemetery_06/P_BossCemetery_06.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossInteriorArches02"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossInteriorArches02/P_BossInteriorArches02.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_ChurchWindowGrilles01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_ChurchWindowGrilles01/P_ChurchWindowGrilles01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_LongStairs01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_LongStairs01/P_LongStairs01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Plains_CastleArch_Ruin_01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Plains_CastleArch_Ruin_01/SM_Plains_CastleArch_Ruin_01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Trim_01a"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Trim_01a/SM_Trim_01a.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Wall_8x8_Broken_01c"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Wall_8x8_Broken_01c/SM_Wall_8x8_Broken_01c.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Wall_8x8_Broken_01d"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Wall_8x8_Broken_01d/SM_Wall_8x8_Broken_01d.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Wall_8x8_Broken_01e"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Wall_8x8_Broken_01e/SM_Wall_8x8_Broken_01e.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Railing_base01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/Railing_base01/Railing_base01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Railing_pillar01_2"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/Railing_pillar01_2/Railing_pillar01_2.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Railing01_3"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/Railing01_3/Railing01_3.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Brick_stone_stairs_1_a"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Brick_stone_stairs_1_a/SM_Brick_stone_stairs_1_a.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Gate_17d"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Gate_17d/SM_Gate_17d.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_ground_Road_Middle_250x250cm_1_a"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_ground_Road_Middle_250x250cm_1_a/SM_ground_Road_Middle_250x250cm_1_a.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


 	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_T_P_BossRoomVines01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossRoomVines01/P_BossRoomVines01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossArtriumCircleRailing_Down02"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossArtriumCircleRailing_Down02/P_BossAtriumCircleRailing_Down02.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossArtriumCircleRailing_Down03"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossArtriumCircleRailing_Down03/P_BossAtriumCircleRailing_Down03.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossArtriumCircleRailing_Down04"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossArtriumCircleRailing_Down04/P_BossAtriumCircleRailing_Down04.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossAtriumCircleRailing_Top01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossAtriumCircleRailing_Top01/P_BossAtriumCircleRailing_Top01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

 	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossAtriumCircleRailing_Up01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossAtriumCircleRailing_Up01/P_BossAtriumCircleRailing_Up01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossAtriumCircleRailing_Up02"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossAtriumCircleRailing_Up02/P_BossAtriumCircleRailing_Up02.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossAtriumCircleRailing_Up04"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossAtriumCircleRailing_Up04/P_BossAtriumCircleRailing_Up04.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_BossAtriumCircleRailing_Up03"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_BossAtriumCircleRailing_Up03/P_BossAtriumCircleRailing_Up03.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Railing03_1"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/Railing03_1/Railing03_1.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_Fortress_BossDoor_Left01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_Fortress_BossDoor_Left01/P_Fortress_BossDoor_Left01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_Fortress_BossDoor_Right01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_Fortress_BossDoor_Right01/P_Fortress_BossDoor_Right01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Debris_01a"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Debris_01a/SM_Debris_01a.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Debris_02a"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Debris_02a/SM_Debris_02a.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;
		
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Scafold_01b"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Scafold_01b/SM_Scafold_01b.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Scafold_01c"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_Scafold_01c/SM_Scafold_01c.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_fence_14"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_fence_14/SM_fence_14.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_fence_16"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_fence_16/SM_fence_16.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_fence_13"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_fence_13/SM_fence_13.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_rock_03"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_rock_03/SM_rock_03.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_curb_02"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/SM_curb_02/SM_curb_02.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_CemeteryStairs01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_CemeteryStairs01/P_CemeteryStairs01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Brick_Floor"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/Brick_Floor/brickFloor.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_P_Archive_Chair01"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/P_Archive_Chair01/P_Archive_Chair01.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Ladder"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Objects/Ladder/Ladder.fbx", CModel::MODEL_NONANIM, PreTransformMatrix,true))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_NonMoveObject"),
		CNonMoveObject::Create(m_pDevice, m_pContext))))
		return E_FAIL;

#pragma endregion


#pragma region GroundObjects

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Grass0"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/GroundObjects/Grass0/Grass0.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tree0"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/GroundObjects/Tree0/Tree0.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_House0"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/GroundObjects/House0/House_51.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_GroundObject"),
		CGroundObject::Create(m_pDevice, m_pContext))))
		return E_FAIL;
#pragma endregion





#pragma region 테스트용 사다리
	//lstrcpyW(m_szLoadingText, TEXT("사다리 모델을 생성한다."));
	///* For.Prototype_Component_Model_Ladder*/
	//PreTransformMatrix = /*XMMatrixScaling(0.015f, 0.015f, 0.015f) **/ XMMatrixRotationY(XMConvertToRadians(180.f));
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Ladder"),
	//	CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Ladder/Ladder.fbx", CModel::MODEL_NONANIM, PreTransformMatrix))))
	//	return E_FAIL;

	/////* For.Prototype_GameObject_Player */
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Ladder"),
	//	CLadder::Create(m_pDevice, m_pContext))))
	//	return E_FAIL;



#pragma endregion 
#pragma region 티메시아 보스

	PreTransformMatrix = XMMatrixRotationY(XMConvertToRadians(180.f));
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Boss_Magician"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Boss/Boss_Magician/Boss_Magician.fbx", CModel::MODEL_ANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Boss_Magician"),
		CBoss_Magician::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	PreTransformMatrix = XMMatrixRotationY(XMConvertToRadians(180.f));
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Boss_Varg"),
		CModel::Create(m_pDevice, m_pContext, "../Bin/Resources/Models/Boss/Boss_Varg/Boss_Varg.fbx", CModel::MODEL_ANIM, PreTransformMatrix))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Boss_Varg"),
		CBoss_Varg::Create(m_pDevice, m_pContext))))
		return E_FAIL;

#pragma endregion 
	/* 로딩이 완료되었습ㄴ미다 */
	lstrcpyW(m_szLoadingText, TEXT("로딩끝."));	
	m_isFinished = true;
	return S_OK;
}

CLoader * CLoader::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, LEVELID eNextLevelID)
{
	CLoader*	pInstance = new CLoader(pDevice, pContext);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed To Created : CLoader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	__super::Free();

	WaitForSingleObject(m_hThread, INFINITE);

	DeleteObject(m_hThread);

	CloseHandle(m_hThread);

	DeleteCriticalSection(&m_CriticalSection);

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pContext);
	Safe_Release(m_pDevice);
}
