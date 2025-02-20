#pragma once
#include "pch.h" 
#include "Level_GamePlay.h"
#include "Camera_Free.h"
#include "Layer.h"	

#include "GameObject.h"

CLevel_GamePlay::CLevel_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    : CLevel{ pDevice, pContext }
{
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/HORSE_P_WoodenFrame02_05.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Rag03.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_Shelf.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_WoodFence03.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_WoodFence04.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_WoodStairs03.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircle01.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_02_02.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_04.dds"), IMG_NONANIM_MODEL, 1);

    // 레이어 이름이랑, 객체 주소
    //m_pGameInstance->Add_DeadObject()
}

HRESULT CLevel_GamePlay::Initialize()
{
    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
        return E_FAIL;
    if (FAILED(Ready_Lights()))
        return E_FAIL;

    m_pCamera = static_cast<CCamera_Free*>(m_pGameInstance->Get_GameObject(TEXT("Prototype_GameObject_Camera_Free"), LEVEL_GAMEPLAY, TEXT("Layer_Camera")));
    m_pTerrain = static_cast<CTerrain*>(m_pGameInstance->Get_GameObject(TEXT("Prototype_GameObject_Terrain"), LEVEL_GAMEPLAY, TEXT("Layer_BackGround")));

    return S_OK;
}

void CLevel_GamePlay::Update(_float fTimeDelta)
{
    ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered() ? m_bImguiHovered : !m_bImguiHovered;
    static int iMenuTypeNumber = MENU_TYPE::MT_END;

	ImGui::Begin("Object");
	
	ImGuiIO IO = ImGui::GetIO();

    ImGui::Begin("TOOL MENU");
    if (ImGui::RadioButton("NONANIM_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_PICKING_NONANIMMODEL))
    {
        m_bNonAnimObjectMenuSelected = true;
        m_bAnimObjectMenuSelected = false;
        m_iNonAnimModelIndex = -1;
    }
    if (ImGui::RadioButton("ANIM_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_PICKING_ANIMMODEL))
    {
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = true;
    }

	ImGui::InputFloat3("Object_Pos", m_fObjectPos);
	ImGui::InputFloat3("Object_Scale", m_fMeshScale);
	ImGui::InputFloat3("Object_Rotation (Quaternion)", m_fObjectRotation);
	ImGui::InputFloat("FrustumRadius", &m_fFrustumRadius);
    if (m_bNonAnimObjectMenuSelected)
    {
        if (!IO.WantCaptureMouse)
        {
            if (m_pGameInstance->isMouseEnter(DIM_LB))
            {
                if (m_bNonAnimObjectMenuSelected || m_bAnimObjectMenuSelected)
                {
                    for (auto& pObject : m_Objects)
                    {
                        _float3 fPos = { 0.f ,0.f ,0.f };

                        if (pObject->Picking_Objects(fPos))
                        {
                            m_fMeshPickPos = fPos;

                            m_fObjectPos[0] = fPos.x;

                            m_fObjectPos[1] = fPos.y;

                            m_fObjectPos[2] = fPos.z;

                            cout << m_fMeshPickPos.x << " ";

                            cout << m_fMeshPickPos.y << " ";

                            cout << m_fMeshPickPos.z << " ";

                            cout << "\n";

                            m_pCurrentObjectTransformCom = pObject->Get_Transfrom();

                            Add_NonAnimObjects();
                        }
                    }
                }


                //  Terrain Picking
                if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_PICKING_NONANIMMODEL)))
                {
                    Add_NonAnimObjects(); //  Terrain Picking 즉시 배치
                }
            }
        }  
    }
    else if (m_bAnimObjectMenuSelected)
    {
        Add_AnimObjects();
    }

    if (m_pCurrentObjectTransformCom != nullptr)
    {
        ImGui::Begin("Current Object Info");

        _vector vCurPos = m_pCurrentObjectTransformCom->Get_State(CTransform::STATE_POSITION);
        _vector vCurScale = XMLoadFloat3(&m_pCurrentObjectTransformCom->Get_Scale());
        _vector vCurRotation = XMLoadFloat3(&m_pCurrentObjectTransformCom->Get_Rotation());

        _float vCurPosArray[3] = { XMVectorGetX(vCurPos), XMVectorGetY(vCurPos),  XMVectorGetZ(vCurPos) };
        _float vCurScaleArray[3] = { XMVectorGetX(vCurScale), XMVectorGetY(vCurScale),  XMVectorGetZ(vCurScale) };
        _float vCurRotationArray[3] = { XMVectorGetX(vCurRotation), XMVectorGetY(vCurRotation),  XMVectorGetZ(vCurRotation) };

        ImGui::InputFloat3("Position", vCurPosArray);
        ImGui::InputFloat3("Scale", vCurScaleArray);
        ImGui::InputFloat3("Rotation", vCurRotationArray);

        m_pCurrentObjectTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(vCurPosArray[0], vCurPosArray[1], vCurPosArray[2], 1.f));
        m_pCurrentObjectTransformCom->Rotation(XMConvertToRadians(vCurRotationArray[0]), XMConvertToRadians(vCurRotationArray[1]), XMConvertToRadians(vCurRotationArray[2]));
        m_pCurrentObjectTransformCom->Scaling(_float3(vCurScaleArray[0], vCurScaleArray[1], vCurScaleArray[2]));

        ImGui::End();
    }


    if (iMenuTypeNumber == MENU_TYPE::MT_PICKING_ANIMMODEL || iMenuTypeNumber == MENU_TYPE::MT_PICKING_NONANIMMODEL)
    {
        if (ImGui::Button("Save_Models"))
        {

        }

        ImGui::SameLine();

        if (ImGui::Button("Load_Models"))
        {

        }
    }

    ImGui::End();

    if(m_bNonAnimObjectMenuSelected)
        Setting_NonAnimObjectList();
	

    ImGui::End();
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
    if (FAILED(m_pGameInstance->SetUp_ShadowLight(XMVectorSet(232.f, 200.f, 150.f, 1.f), XMVectorSet(232.f, 62.f, 60.f, 1.f),
        XMConvertToRadians(60.f), g_iWinSizeX / static_cast<_float>(g_iWinSizeY), 0.1f, 800.f
        , m_pGameInstance->Get_Player_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Player")))))
        return E_FAIL;

    LIGHT_DESC				LightDesc{};

    /* 2월 8일 빛 */
    LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
    LightDesc.vDirection = _float4(1.f, 1.f, 1.f, 0.f);
    LightDesc.vDiffuse = _float4(0.9f, 0.9f, 0.9f, 1.f);
    LightDesc.vAmbient = _float4(0.6f, 0.6f, 0.6f, 1.f);
    LightDesc.vSpecular = _float4(0.3f, 0.3f, 0.3f, 1.f);


    /*LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
    LightDesc.vDirection = _float4(1.f, 1.f, 1.f, 0.f);
    LightDesc.vDiffuse   = _float4(0.9f, 0.9f, 0.9f, 1.f);
    LightDesc.vAmbient   = _float4(0.5f, 0.5f, 0.5f, 1.f);
    LightDesc.vSpecular  = _float4(0.3f, 0.3f, 0.3f, 1.f);	*/

    if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
        return E_FAIL;

    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const _tchar* pLayerTag)
{
    if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Terrain"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
        return E_FAIL;

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

    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const _tchar* pLayerTag)
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

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const _tchar* pLayerTag)
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

HRESULT CLevel_GamePlay::Resister_ObjectList_PreviewImage(const _tchar* _pImageFilePath, IMGUI_TEXTURE_TYPE _eImguiTextureType, _uint _iTextureNumber)
{
    for (_uint i = 0; i < _iTextureNumber; ++i)
    {
        _tchar      szEXT[MAX_PATH] = {};
        _wsplitpath_s(_pImageFilePath, nullptr, 0, nullptr, 0, nullptr, 0, szEXT, MAX_PATH);

        for (_uint i = 0; i < _iTextureNumber; ++i)
        {
            //ID3D11Texture2D* pTexture2D = { nullptr };
            ID3D11ShaderResourceView* pSRV = { nullptr };

            _tchar                      szTextureFilePath[MAX_PATH] = TEXT("");

            wsprintf(szTextureFilePath, _pImageFilePath, i);

            HRESULT     hr = {};

            if (false == lstrcmp(szEXT, TEXT(".dds")))
            {
                hr = CreateDDSTextureFromFile(m_pDevice, szTextureFilePath, nullptr, &pSRV);
            }
            else if (false == lstrcmp(szEXT, TEXT(".tga")))
            {
                hr = E_FAIL;
            }
            else
            {
                hr = CreateWICTextureFromFile(m_pDevice, szTextureFilePath, nullptr, &pSRV);
            }

            if (FAILED(hr))
                return E_FAIL;

            switch (_eImguiTextureType)
            {
            case IMG_ANIM_MODEL:
                m_vecAnimModelSRVs.push_back(pSRV);
                break;
            case IMG_NONANIM_MODEL:
                m_vecNonAnimModelSRVs.push_back(pSRV);
                break;
            }
        }
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    return S_OK;
}

void CLevel_GamePlay::Add_NonAnimObjects()
{
    if (m_iNonAnimModelIndex == -1)
        return;

    const char* ObjectNames[] = {
          "HORSE_P_WoodenFrame02_05",
          "P_Rag03",
          "SM_Wall_Shelf",
          "SM_WoodFence03",
          "SM_WoodFence04",
          "SM_WoodStairs03",
          "P_BossAtriumCircle01",
          "P_BossCemetery_02_02",
          "P_BossCemetery_04",
    };

    CObject::OBJECT_DESC Desc{};

    Desc.fPosition = { m_fObjectPos[0], m_fObjectPos[1], m_fObjectPos[2], 1.f };
    Desc.fFrustumRadius = m_fFrustumRadius;
    Desc.fScaling = { m_fMeshScale[0], m_fMeshScale[1], m_fMeshScale[2] };
    Desc.fRotation = { m_fObjectRotation[0], m_fObjectRotation[1] , m_fObjectRotation[2] };
    Desc.ObjectName = ObjectNames[m_iNonAnimModelIndex];

    CObject* pObject = reinterpret_cast<CObject*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_NonMoveObject"), LEVEL_GAMEPLAY, TEXT("Layer_Object"), &Desc));

    if (pObject != nullptr)
        m_Objects.push_back(pObject);
}

void CLevel_GamePlay::Add_AnimObjects()
{

}

void CLevel_GamePlay::Setting_NonAnimObjectList()
{
    if (ImGui::CollapsingHeader("Model List"))
        return;

    const char* szItems[] = { "Model List" };

    static int iCurrentItem = 0;
    ImGui::Combo("##3", &iCurrentItem, szItems, IM_ARRAYSIZE(szItems));

    for (_uint i = 0; i < 9; ++i)
    {
        _uint  iTextureIndex = iCurrentItem * 3 + i;

        if (iTextureIndex < m_vecNonAnimModelSRVs.size())
        {
            if (ImGui::ImageButton(("NonAnimModel" + to_string(iTextureIndex)).c_str(), (ImTextureID)m_vecNonAnimModelSRVs[iTextureIndex], ImVec2(50.0f, 50.0f)))
            {
                m_iNonAnimModelIndex = iTextureIndex;
            }

            if ((i + 1) % 3 != 0)
            {
                ImGui::SameLine();
            }
        }
    }
}

HRESULT CLevel_GamePlay::Pick_Object(MENU_TYPE _eMenuType)
{
    m_fPickPos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))));

    if (m_fPickPos.y < 0)
        return E_FAIL;

    m_fObjectPos[0] = m_fPickPos.x;
    m_fObjectPos[1] = m_fPickPos.y;
    m_fObjectPos[2] = m_fPickPos.z;

    return S_OK;
}

CLevel_GamePlay* CLevel_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CLevel_GamePlay* pInstance = new CLevel_GamePlay(pDevice, pContext);

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

    for (auto& pSRV : m_vecAnimModelSRVs)
        Safe_Release(pSRV);
    m_vecAnimModelSRVs.clear();

    for (auto& pSRV : m_vecNonAnimModelSRVs)
        Safe_Release(pSRV);
    m_vecNonAnimModelSRVs.clear();
}
