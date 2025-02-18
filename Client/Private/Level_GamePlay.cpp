#include "pch.h" 
#include "Level_GamePlay.h"
#include "GameInstance.h"
#include "Camera_Free.h"
#include "Layer.h"	


CLevel_GamePlay::CLevel_GamePlay(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel { pDevice, pContext }
{
	
}

HRESULT CLevel_GamePlay::Initialize()
{
	/*if (FAILED(Ready_Lights()))
		return E_FAIL;*/

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;

	//if (FAILED(Ready_Layer_Structure(TEXT("Layer_Structure"))))
	//	return E_FAIL;	


	// 테스트용 사다리 레이어 준비 함수 호출
	if (FAILED(Ready_Layer_Ladder(TEXT("Layer_Ladder"))))
		return E_FAIL;




	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Effect(TEXT("Layer_Effect"))))	
		return E_FAIL;

	if (FAILED(Ready_Layer_UI(TEXT("Layer_UI"))))
		return E_FAIL;

	if (FAILED(Ready_Lights()))	
		return E_FAIL;	

	//m_pGameInstance->CheckGroup(GROUP_TYPE::PLAYER,        GROUP_TYPE::MONSTER);		
	//m_pGameInstance->CheckGroup(GROUP_TYPE::PLAYER_WEAPON, GROUP_TYPE::MONSTER);		
	//m_pGameInstance->CheckGroup(GROUP_TYPE::PLAYER,		   GROUP_TYPE::OBJECT);	
	
	return S_OK;
}

void CLevel_GamePlay::Update(_float fTimeDelta)
{
	
}

HRESULT CLevel_GamePlay::Render() 
{
#ifdef _DEBUG
	SetWindowText(g_hWnd, TEXT("게임플레이 레벨입니다."));
#endif

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Lights()
{
	//m_pPlayer = m_pGameInstance->Get_Player_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Player"));	

	if (FAILED(m_pGameInstance->SetUp_ShadowLight(XMVectorSet(232.f, 200.f, 150.f, 1.f), XMVectorSet(232.f, 62.f, 60.f, 1.f),	
		XMConvertToRadians(60.f), g_iWinSizeX / static_cast<_float>(g_iWinSizeY), 0.1f, 800.f	
		, m_pGameInstance->Get_Player_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Player")))))	
		return E_FAIL;

	LIGHT_DESC				LightDesc{};

	/* 2월 8일 빛 */
	LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(1.f, 1.f, 1.f, 0.f);
	LightDesc.vDiffuse   = _float4(0.9f, 0.9f, 0.9f, 1.f);
	LightDesc.vAmbient   = _float4(0.6f, 0.6f, 0.6f, 1.f);
	LightDesc.vSpecular  = _float4(0.3f, 0.3f, 0.3f, 1.f);


	/*LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;	
	LightDesc.vDirection = _float4(1.f, 1.f, 1.f, 0.f);	
	LightDesc.vDiffuse   = _float4(0.9f, 0.9f, 0.9f, 1.f);	
	LightDesc.vAmbient   = _float4(0.5f, 0.5f, 0.5f, 1.f);	
	LightDesc.vSpecular  = _float4(0.3f, 0.3f, 0.3f, 1.f);	*/

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Terrain"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;

	//for (size_t i = 0; i < 3; i++)
	//{
	//	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_ForkLift"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
	//		return E_FAIL;
	//}

	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Sky"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;



	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Structure(const _tchar* pLayerTag)
{
	/* 여기서 맵 파일 하나하나 다 읽어와야함 */

	_ulong dwByte = {}; 
	//HANDLE hFile = CreateFile(TEXT("../Map_File/real76.bin"), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	HANDLE hFile = CreateFile(TEXT("../Map_File/real143.bin"), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	while (true)
	{
		_tchar Layer_Name[MAX_PATH] = {}; //레이어 이름										
		ReadFile(hFile, Layer_Name, MAX_PATH, &dwByte, nullptr);

		if (dwByte == 0)
			break;
		/* 이름 작업 */
		_char   Prototype_Name[MAX_PATH] = {};

		ReadFile(hFile, Prototype_Name, MAX_PATH, &dwByte, nullptr);


		_float4x4 WorldMatrix = {};
		ReadFile(hFile, &WorldMatrix, sizeof(_float4x4), &dwByte, nullptr);
		//int a = 4;

		_tchar Translate_wchar[MAX_PATH] = {};
		MultiByteToWideChar(CP_ACP, 0, Prototype_Name, static_cast<_int>(strlen(Prototype_Name)), Translate_wchar, MAX_PATH);

		/* 이제 TRANSFORM만 건들면 될듯함.*/
		//int b = 4;
		if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, Translate_wchar, LEVEL_GAMEPLAY, Layer_Name)))
			return E_FAIL;

		//CTransform* pTrasnform = dynamic_cast<CTransform*>(
		//* Find GaemObject 만들어야 할듯
		// 구분할 수 있는 방법을 생각해봐야할듯.
		map<const _wstring, class CLayer*>* Level_Layers = m_pGameInstance->Get_Layers();		

		auto& Level_GamePlay = Level_Layers[3];

		for (auto& Layers : Level_GamePlay)
		{
			//auto& iter = find(Level_GamePlay.begin(), Level_GamePlay.end(), Layer_Name);	
			auto iter = Level_GamePlay.find(Layer_Name);

			if (iter == Level_GamePlay.end())
				return E_FAIL;

			else
			{
				CTransform* pTranform = dynamic_cast<CTransform*>(
					iter->second->Get_GameObject_List().back()->Find_Component(TEXT("Com_Transform")));	

				pTranform->Set_WorldMatrix(WorldMatrix);	
			}
		}
	}
	CloseHandle(hFile);
	
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const _tchar* pLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Player"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))	
		return E_FAIL;	

	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_LobTrap"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CCamera_Free::FREE_CAMERA_DESC		Desc = {};

	
	Desc.vEye = _float3(0.f, 10.f, -7.f);
	Desc.vAt = _float3(0.f, 0.f, 0.f);

	Desc.fFovy = XMConvertToRadians(60.f);
	Desc.fNear = 0.1f;
	Desc.fFar = 800.f;
	Desc.fMouseSensor = 0.05f;
	Desc.fSpeedPerSec = 25.f;
	Desc.fRotationPerSec = XMConvertToRadians(90.f);


	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Camera_Free"), LEVEL_GAMEPLAY, pLayerTag, &Desc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Boss_Magician"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Boss_Varg"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Effect(const _tchar* pLayerTag)
{

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_UI(const _tchar* pLayerTag)
{

	return S_OK;

}

HRESULT CLevel_GamePlay::Ready_Layer_Ladder(const _tchar* pLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Ladder"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;

	return S_OK;
}

CLevel_GamePlay * CLevel_GamePlay::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CLevel_GamePlay*	pInstance = new CLevel_GamePlay(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed To Created : CLevel_GamePlay");
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_GamePlay::Free()
{
	__super::Free();

}
