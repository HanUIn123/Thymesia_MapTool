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
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_05.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_06.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossInteriorArches02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_ChurchWindowGrilles01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_LongStairs01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Plains_CastleArch_Ruin_01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Trim_01a.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_8x8_Broken_01c.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_8x8_Broken_01d.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_8x8_Broken_01e.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing_base01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing_pillar01_2.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing01_3.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Brick_stone_stairs_1_a.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Gate_17d.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_ground_Road_Middle_250x250cm_1_a.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/T_P_BossRoomVines01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossArtriumCircleRailing_Down02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossArtriumCircleRailing_Down03.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossArtriumCircleRailing_Down04.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Top01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up04.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up03.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing03_1.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Fortress_BossDoor_Left01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Fortress_BossDoor_Right01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Debris_01a.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Debris_02a.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Scafold_01b.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Scafold_01c.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_14.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_16.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_13.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_rock_03.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_curb_02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_CemeteryStairs01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_CemeteryStairs02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Brick_Floor.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Grass0.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Archive_Chair01.png"), IMG_NONANIM_MODEL, 1);
    //P_Archive_Chair01

    //=============================================================================================================================

    // IMG_GROUND_MODEL
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/GroundObjects/Grass0.png"), IMG_GROUND_MODEL, 1);

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
    m_pTerrainBuffer = static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain")));

    m_pNavigation = static_cast<CNavigation*>(m_pTerrain->Find_Component(TEXT("Com_Navigation")));

    return S_OK;
}

void CLevel_GamePlay::Update(_float fTimeDelta)
{
    //ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered() ? m_bImguiHovered : !m_bImguiHovered;
    static int iMenuTypeNumber = MENU_TYPE::MT_END;

    ImGui::Begin("Object");

    ImGuiIO IO = ImGui::GetIO();

    ImGui::Begin("TOOL MENU");
    if (ImGui::RadioButton("NONANIM_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_PICKING_NONANIMMODEL))
    {
        m_bNonAnimObjectMenuSelected = true;
        m_bAnimObjectMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bGrondMenuSelected = false;
        m_iNonAnimModelIndex = -1;
    }
    if (ImGui::RadioButton("ANIM_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_PICKING_ANIMMODEL))
    {
        m_bNonAnimObjectMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bAnimObjectMenuSelected = true;
        m_bGrondMenuSelected = false;
    }
    if (ImGui::RadioButton("NAVIGATION_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_NAVI))
    {
        m_bNaviMenuSelected = true;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
        m_bGrondMenuSelected = false;
    }
    if (ImGui::RadioButton("GROUND_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_GROUND))
    {
        m_bGrondMenuSelected = true;
        m_bNaviMenuSelected = false;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
    }

    if (m_pGameInstance->Get_DIKeyState(DIK_R) & 0x80)
    {
        m_bConnectingMode = true;
    }
    else
    {
        m_bConnectingMode = false;
    }


    if (ImGui::Button("Turn FrustumSphere"))
    {
        m_bFrustumSphere = !m_bFrustumSphere;

        for (auto& pObject : m_Objects)
        {
            pObject->Set_FrustumSphere(m_bFrustumSphere);
        }
    }

    if (ImGui::Button("Mesh Picking"))
    {
        m_bIsMeshPickingMode = true;
        m_bIsTerrainPickingMode = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Terrain Picking"))
    {
        m_bIsTerrainPickingMode = true;
        m_bIsMeshPickingMode = false;
    }

    ImGui::InputFloat3("Object_Pos", m_fObjectPos);
    ImGui::InputFloat3("Object_Scale", m_fMeshScale);
    ImGui::InputFloat3("Object_Rotation (Quaternion)", m_fObjectRotation);
    ImGui::InputFloat("FrustumRadius", &m_fFrustumRadius);

    if (ImGui::Button("Delete_ObjectIndex"))
    {
        m_iNonAnimModelIndex = -1;

        m_pPrevObject = nullptr;
        m_pCurrentObjectTransformCom = nullptr;
    }

    if (ImGui::Button("Create_Object"))
    {
        Add_NonAnimObjects();
    }

    if (m_bNonAnimObjectMenuSelected)
    {
        if (!IO.WantCaptureMouse)
        {
            if (m_pGameInstance->isMouseEnter(DIM_LB))
            {
                if (m_bNonAnimObjectMenuSelected || m_bAnimObjectMenuSelected)
                {
                    if (m_bIsMeshPickingMode)
                    {
                        vector<Mesh_Pos> vMesh;

                        for (auto& pObject : m_Objects)
                        {
                            CObject::MESHINFO pInfo;

                            if (pObject != nullptr && pObject->Picking_Objects(pInfo))
                            {
                                Mesh_Pos vPos{};
                                vPos.fPosition = pInfo.fPosition;
                                vPos.fDist = pInfo.fDist;
                                vPos.pObject = pObject;

                                vMesh.push_back(vPos);
                            }
                        }

                        if (vMesh.size() != 0)
                        {
                            sort(vMesh.begin(), vMesh.end(), [](Mesh_Pos a, Mesh_Pos b) {
                                if (a.fDist < b.fDist) return true;
                                else
                                    return false;
                                });

                            _float3 fPos = { 0.f ,0.f ,0.f };

                            fPos = vMesh.front().fPosition;

                            m_fMeshPickPos = fPos;

                            m_fObjectPos[0] = fPos.x;

                            m_fObjectPos[1] = fPos.y;

                            m_fObjectPos[2] = fPos.z;

                            cout << m_fMeshPickPos.x << " ";

                            cout << m_fMeshPickPos.y << " ";

                            cout << m_fMeshPickPos.z << " ";

                            cout << "\n";

                            m_pCurrentObject = vMesh.front().pObject;
                            m_pCurrentObjectTransformCom = m_pCurrentObject->Get_Transfrom();

                            Add_NonAnimObjects();

                        }
                    }
                    else if (m_bIsTerrainPickingMode)
                    {
                        if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_PICKING_NONANIMMODEL)))
                        {
                            Add_NonAnimObjects();
                        }
                    }
                }
            }
        }
    }
    else if (m_bAnimObjectMenuSelected)
    {
        Add_AnimObjects();
    }
    else if (m_bNaviMenuSelected)
    {
        if (m_pGameInstance->isMouseEnter(DIM_LB))
        {
            Picking_Points();
        }
    }
    else if (m_bGrondMenuSelected)
    {
        Show_MouseRange(MENU_TYPE::MT_GROUND, fTimeDelta);

        if (m_pGameInstance->isMouseEnter(DIM_LB))
        {
            if (m_bGrondMenuSelected)
            {
                if (m_bIsTerrainPickingMode)
                {
                    if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_GROUND)))
                    {
                        Add_GroundObjects();
                    }
                }
            }
        
        }
    }


    if (m_pCurrentObject != nullptr)
    {
        ImGui::Begin("Current Object Info");

        CObject::OBJECT_INFO Info{};

        Info = m_pCurrentObject->Get_ObjectInfo();

        _vector vCurPos = XMLoadFloat4(&Info.fPosition);
        _vector vCurScale = XMLoadFloat3(&Info.fScale);
        _vector vCurRotation = XMLoadFloat3(&Info.fRotation);
        _float  fFrustumRadius = Info.fFrustumRadius;

        _float vCurPosArray[3] = { XMVectorGetX(vCurPos), XMVectorGetY(vCurPos),  XMVectorGetZ(vCurPos) };
        _float vCurScaleArray[3] = { XMVectorGetX(vCurScale), XMVectorGetY(vCurScale),  XMVectorGetZ(vCurScale) };
        _float vCurRotationArray[3] = { XMVectorGetX(vCurRotation), XMVectorGetY(vCurRotation),  XMVectorGetZ(vCurRotation) };

        ImGui::InputFloat2("Position_Min_Max", m_fPosMax);

        ImGui::SliderFloat3("Position", vCurPosArray, m_fPosMax[0], m_fPosMax[1]);

        ImGui::InputFloat2("Scale_Min_Max", m_fScaleMax);
        ImGui::SliderFloat3("Scale", vCurScaleArray, m_fScaleMax[0], m_fScaleMax[1]);

        ImGui::InputFloat2("Rotation_Min_Max", m_fRotationMax);
        ImGui::SliderFloat3("Rotation", vCurRotationArray, m_fRotationMax[0], m_fRotationMax[1]);

        ImGui::InputFloat("Radius_MAx", &m_fRadiusMax);
        ImGui::SliderFloat("fFrustumRadius", &fFrustumRadius, 0.f, m_fRadiusMax);

        m_pCurrentObjectTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(vCurPosArray[0], vCurPosArray[1], vCurPosArray[2], 1.f));
        m_pCurrentObjectTransformCom->Rotation(XMConvertToRadians(vCurRotationArray[0]), XMConvertToRadians(vCurRotationArray[1]), XMConvertToRadians(vCurRotationArray[2]));
        m_pCurrentObjectTransformCom->Scaling(_float3(vCurScaleArray[0], vCurScaleArray[1], vCurScaleArray[2]));
        m_pCurrentObject->Set_FrustumRadius(fFrustumRadius);

        if (ImGui::Button("Delete This Object"))
        {
            m_pGameInstance->Add_DeadObject(L"Layer_Object", m_pCurrentObject);

            for (list<CObject*>::iterator pObject = m_Objects.begin(); pObject != m_Objects.end();)
            {
                if ((*pObject) == m_pCurrentObject)
                {
                    pObject = m_Objects.erase(pObject);
                }
                else
                    pObject++;
            }
            m_pCurrentObject = nullptr;
        }

        ImGui::End();
    }

    if (iMenuTypeNumber == MENU_TYPE::MT_PICKING_ANIMMODEL || iMenuTypeNumber == MENU_TYPE::MT_PICKING_NONANIMMODEL)
    {
        if (ImGui::Button("Save_Models"))
        {
            Save_Objects();
        }

        ImGui::SameLine();

        if (ImGui::Button("Load_Models"))
        {
            Load_Objects();
        }
    }

    if (iMenuTypeNumber == MENU_TYPE::MT_NAVI)
    {
        if (ImGui::Button("Save_Navi"))
        {
            Save_Navi();
        }

        ImGui::SameLine();

        if (ImGui::Button("Load_Navi"))
        {
            Load_Navi();
        }
    }

    Active_PreviewModelImage();

    Delete_Cell_Mode();


    ImGui::End();

    if (m_bNonAnimObjectMenuSelected)
        Setting_NonAnimObjectList();

    if (m_bGrondMenuSelected)
        Setting_GroundObjectList();

    ImGui::End();


    // 마우스 범위 표시용 imgui window
    ImGui::Begin("Device Settings", NULL, ImGuiWindowFlags_MenuBar);
    ImGui::SliderFloat("Mouse Range", &(m_fInstallRange), 1.0f, 20.0f);
    ImGui::SliderFloat("Object Spacing", &m_fSpacingValue, 1.0f, 10.0f);
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

    LIGHT_DESC            LightDesc{};

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
    LightDesc.vSpecular  = _float4(0.3f, 0.3f, 0.3f, 1.f);   */

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
    CCamera_Free::FREE_CAMERA_DESC      Desc = {};

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
            case IMG_GROUND_MODEL:
                m_vecGroundModelSRVs.push_back(pSRV);
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

    CObject::OBJECT_DESC Desc{};

    Desc.fPosition = { m_fObjectPos[0], m_fObjectPos[1], m_fObjectPos[2], 1.f };
    Desc.fFrustumRadius = m_fFrustumRadius;
    Desc.fScaling = { m_fMeshScale[0], m_fMeshScale[1], m_fMeshScale[2] };
    Desc.fRotation = { m_fObjectRotation[0], m_fObjectRotation[1] , m_fObjectRotation[2] };
    Desc.ObjectName = m_strObjectNames[m_iNonAnimModelIndex];
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

    for (_uint i = 0; i < 50; ++i)
    {
        _uint  iTextureIndex = iCurrentItem * 3 + i;

        if (iTextureIndex < m_vecNonAnimModelSRVs.size())
        {
            if (ImGui::ImageButton(("NonAnimModel" + to_string(iTextureIndex)).c_str(), (ImTextureID)m_vecNonAnimModelSRVs[iTextureIndex], ImVec2(50.0f, 50.0f)))
            {
                m_iNonAnimModelIndex = iTextureIndex;

                m_pGameInstance->Add_DeadObject(TEXT("Layer_Object"), m_pPrevObject);

                CObject::OBJECT_DESC ObjectDesc = {};
                ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
                ObjectDesc.fFrustumRadius = m_fFrustumRadius;
                ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
                ObjectDesc.fRotation = { 0.0f, 0.0f, 0.0f };
                ObjectDesc.ObjectName = m_strObjectNames[m_iNonAnimModelIndex];

                m_pPrevObject = reinterpret_cast<CObject*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_NonMoveObject"), LEVEL_GAMEPLAY, TEXT("Layer_Object"), &ObjectDesc));

                if (nullptr != m_pPrevObject)
                {
                    m_pPrevObjectTrasnformCom = m_pPrevObject->Get_Transfrom();
                }
            }

            if ((i + 1) % 4 != 0)
            {
                ImGui::SameLine();
            }
        }
    }
}

void CLevel_GamePlay::Active_PreviewModelImage()
{
    _float3 vMousePos;
    if (m_bNonAnimObjectMenuSelected && m_pPrevObject && m_bIsTerrainPickingMode)
    {
        vMousePos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))));

        if (nullptr != m_pPrevObjectTrasnformCom)
        {
            m_pPrevObjectTrasnformCom->Scaling(_float3(0.01f, 0.01f, 0.01f));
            m_pPrevObjectTrasnformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(vMousePos.x, vMousePos.y, vMousePos.z, 1.0f));
        }
    }
    else if (m_bNonAnimObjectMenuSelected && m_pPrevObject && m_bIsMeshPickingMode)
    {
        for (auto& pObject : m_Objects)
        {
            CObject::MESHINFO pInfo;

            if (pObject != nullptr && pObject->Picking_Objects(pInfo))
            {
                Mesh_Pos vPos{};
                vPos.fPosition = pInfo.fPosition;
                vPos.fDist = pInfo.fDist;
                vPos.pObject = pObject;
                vMousePos = vPos.fPosition;

                if (nullptr != m_pPrevObjectTrasnformCom)
                {
                    m_pPrevObjectTrasnformCom->Scaling(_float3(0.01f, 0.01f, 0.01f));
                    m_pPrevObjectTrasnformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(vMousePos.x, vMousePos.y, vMousePos.z, 1.0f));
                }
            }
        }
    }
}

void CLevel_GamePlay::Add_GroundObjects()
{
    //if (m_iNonAnimModelIndex == -1)
    //    return;

    CEnvironmentObject::ENVIRONMENT_OBJECT_DESC EnvironmentDesc = {};
    EnvironmentDesc.fPosition = { m_fObjectPos[0], m_fObjectPos[1], m_fObjectPos[2], 1.f };
    EnvironmentDesc.fFrustumRadius = m_fFrustumRadius;
    EnvironmentDesc.fScaling = { m_fMeshScale[0], m_fMeshScale[1], m_fMeshScale[2] };
    EnvironmentDesc.fRotation = { m_fObjectRotation[0], m_fObjectRotation[1] , m_fObjectRotation[2] };
    EnvironmentDesc.ObjectName = m_strGroundObjectNamess[m_iGroundModelIndex];
    EnvironmentDesc.fSpace = m_fSpacingValue;
    
    D3D11_MAPPED_SUBRESOURCE tagSubResource = {};
    m_pContext->Map(m_pTerrainBuffer->Get_VB_Buffer(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &tagSubResource);
    m_pVertices = static_cast<VTXNORTEX*>(tagSubResource.pData);

    for (_float i = -m_fInstallRange; i <= m_fInstallRange; i += m_fSpacingValue)
    {
        for (_float j = -m_fInstallRange; j <= m_fInstallRange; j += m_fSpacingValue)
        {
            _float worldX = m_fPickPos.x + j;
            _float worldZ = m_fPickPos.z + i;
            _uint iIndex = static_cast<_uint>(worldZ) * m_pTerrainBuffer->Get_NumVerticesX() + static_cast<_uint>(worldX);

            if (iIndex < 0 || iIndex >= m_pTerrainBuffer->Get_NumVerticesX() * m_pTerrainBuffer->Get_NumVerticesZ())
                continue;

            XMFLOAT3 terrainPos = m_pVertices[iIndex].vPosition;
            EnvironmentDesc.vecPosition.push_back(terrainPos);  
        }
    }
    m_pContext->Unmap(m_pTerrainBuffer->Get_VB_Buffer(), 0);

    CEnvironmentObject* pObject = reinterpret_cast<CEnvironmentObject*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_GroundObject"), LEVEL_GAMEPLAY, TEXT("Layer_GroundObject"), &EnvironmentDesc));

    if (pObject != nullptr)
        m_EnvironmentObjects.push_back(pObject);
}

void CLevel_GamePlay::Setting_GroundObjectList()
{
    if (ImGui::CollapsingHeader("Ground Model List"))
        return;

    const char* szItems[] = { "Ground Model List" };

    static int iCurrentItem = 0;
    ImGui::Combo("##5", &iCurrentItem, szItems, IM_ARRAYSIZE(szItems));

    for (_uint i = 0; i < 1; ++i)
    {
        _uint  iTextureIndex = iCurrentItem * 3 + i;

        if (iTextureIndex < m_vecGroundModelSRVs.size())
        {
            if (ImGui::ImageButton(("GroundModel" + to_string(iTextureIndex)).c_str(), (ImTextureID)m_vecGroundModelSRVs[iTextureIndex], ImVec2(50.0f, 50.0f)))
            {
                m_iGroundModelIndex = iTextureIndex;

                //m_pGameInstance->Add_DeadObject(TEXT("Layer_GroundObject"), m_pPrevObject);

                CObject::OBJECT_DESC ObjectDesc = {};
                ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
                ObjectDesc.fFrustumRadius = m_fFrustumRadius;
                ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
                ObjectDesc.fRotation = { 0.0f, 0.0f, 0.0f };
                ObjectDesc.ObjectName = m_strGroundObjectNamess[m_iGroundModelIndex];

                //m_pPrevObject = reinterpret_cast<CObject*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_NonMoveObject"), LEVEL_GAMEPLAY, TEXT("Layer_Object"), &ObjectDesc));
                //
                //if (nullptr != m_pPrevObject)
                //{
                //    m_pPrevObjectTrasnformCom = m_pPrevObject->Get_Transfrom();
                //}
            }

            if ((i + 1) % 4 != 0)
            {
                ImGui::SameLine();
            }
        }
    }

}

HRESULT CLevel_GamePlay::Save_Objects()
{
    wstring fileName;
    OpenFileDialoge(L"ObjectData.txt", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
        return E_FAIL;

    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Create ObjectData File!");
        return E_FAIL;
    }


    DWORD dwByte = 0;

    _uint iObjectCount = static_cast<_uint>(m_Objects.size());
    WriteFile(hFile, &iObjectCount, sizeof(_uint), &dwByte, nullptr);

    for (auto& pObject : m_Objects)
    {
        if (nullptr != pObject)
        {
            CObject::OBJECT_INFO Info = pObject->Get_ObjectInfo();

            WriteFile(hFile, Info.szName, MAX_PATH, &dwByte, nullptr);
            WriteFile(hFile, &Info.fPosition, sizeof(_float4), &dwByte, nullptr);
            WriteFile(hFile, &Info.fRotation, sizeof(_float3), &dwByte, nullptr);
            WriteFile(hFile, &Info.fScale, sizeof(_float3), &dwByte, nullptr);
            WriteFile(hFile, &Info.fFrustumRadius, sizeof(_float), &dwByte, nullptr);
        }
    }

    MSG_BOX("Save Monster Complete");
    CloseHandle(hFile);

    return S_OK;
}

HRESULT CLevel_GamePlay::Load_Objects()
{
    wstring fileName;
    OpenFileDialoge(L"ObjectData.txt", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
        return E_FAIL;

    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Load ObjectData File!");
        return E_FAIL;
    }

    for (auto& pObject : m_Objects)
    {
        m_pGameInstance->Add_DeadObject(L"Layer_Object", pObject);
    }
    m_Objects.clear();

    DWORD dwByte = 0;

    _uint iSize = 0;

    ReadFile(hFile, &iSize, sizeof(_uint), &dwByte, nullptr);

    for (size_t i = 0; i < iSize; i++)
    {
        CObject::OBJECT_DESC Desc{};

        _char szLoadName[MAX_PATH] = {};

        ReadFile(hFile, szLoadName, MAX_PATH, &dwByte, nullptr);
        ReadFile(hFile, &Desc.fPosition, sizeof(_float4), &dwByte, nullptr);
        ReadFile(hFile, &Desc.fRotation, sizeof(_float3), &dwByte, nullptr);
        ReadFile(hFile, &Desc.fScaling, sizeof(_float3), &dwByte, nullptr);
        ReadFile(hFile, &Desc.fFrustumRadius, sizeof(_float), &dwByte, nullptr);

        Desc.ObjectName = szLoadName;

        CObject* pObject = reinterpret_cast<CObject*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_NonMoveObject"), LEVEL_GAMEPLAY, TEXT("Layer_Object"), &Desc));

        if (pObject != nullptr)
            m_Objects.push_back(pObject);
    }

    CloseHandle(hFile);

}

void CLevel_GamePlay::OpenFileDialoge(const _tchar* _pDefaultFileName, const _tchar* _pFilter, std::wstring& outFileName)
{
    OPENFILENAME ofn;
    _tchar szFile[MAX_PATH] = {};

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = _pFilter;
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = L"txt";
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    wcscpy_s(szFile, MAX_PATH, _pDefaultFileName);

    if (GetSaveFileName(&ofn))
    {
        outFileName = szFile;
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

HRESULT CLevel_GamePlay::Picking_Points()
{
    if (m_bIsMeshPickingMode)
    {
        for (auto& pObject : m_Objects)
        {
            _float3 fPos = { 0.f, 0.f, 0.f };
            CObject::MESHINFO pInfo;

            if (pObject != nullptr && pObject->Picking_Objects(pInfo))
            {
                Mesh_Pos vPos{};
                vPos.fPosition = pInfo.fPosition;
                vPos.fDist = pInfo.fDist;
                vPos.pObject = pObject;
                m_fWholePickPos = vPos.fPosition;
            }
        }
    }
    else
    {
        m_fPickPos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))));
        m_fWholePickPos = m_fPickPos;
    }

    if (m_fWholePickPos.y == -0.5f)
        return S_OK;

    m_fWholePickPos.y += 0.1f;

    if (m_bDeleteMode)
    {
        m_vecPickedPoints.push_back(m_fWholePickPos);
        return S_OK;
    }

    if (m_bConnectingMode)
    {
        XMFLOAT3 vSelectedCordinate = Pick_Closest_Cube(m_fWholePickPos);

        if (vSelectedCordinate.x != FLT_MAX)
        {
            m_vecSelectedCubes.push_back(vSelectedCordinate);

            if (m_vecSelectedCubes.size() == 2)
            {
                Create_Line_Between_Cubes(m_vecSelectedCubes[0], m_vecSelectedCubes[1]);
                m_vecSelectedCubes.clear();
                m_bConnectingMode = false;
            }
        }
        return S_OK;
    }

    m_vecPickedPoints.push_back(m_fWholePickPos);

    if (m_vecPickedPoints.size() == 3 && m_bFirstPick)
    {
        tagWholeCellPoints.fCellPoints[0] = m_vecPickedPoints[0];
        tagWholeCellPoints.fCellPoints[1] = m_vecPickedPoints[1];
        tagWholeCellPoints.fCellPoints[2] = m_vecPickedPoints[2];

        m_pNavigation->Create_Cell(tagWholeCellPoints.fCellPoints);
        m_vecWholeCellPoints.push_back(tagWholeCellPoints);

        tagWholeCellPoints.fPrevPoints[0] = tagWholeCellPoints.fCellPoints[0];
        tagWholeCellPoints.fPrevPoints[1] = tagWholeCellPoints.fCellPoints[1];

        m_iNumCellCount++;
        m_bFirstPick = false;
        m_vecPickedPoints.clear();
    }
    else if (m_vecPickedPoints.size() < 3 && !m_bFirstPick)
    {
        // m_vecPickedPoints[0]는 고정된 새로 선택한 점을 의미함.
        // m_vecWholeCellPoints에 있는 모든 cell points 중 가장 가까운 두 점을 찾음.
        auto NearPoints = Compute_NearPoints(m_vecWholeCellPoints, m_vecPickedPoints[0]);

        // 가장 가까운 두 점과 새로 선택한 점을 이용해 Cell을 생성.
        tagWholeCellPoints.fCellPoints[0] = NearPoints.first;
        tagWholeCellPoints.fCellPoints[1] = NearPoints.second;
        tagWholeCellPoints.fCellPoints[2] = m_vecPickedPoints[0];

        // 생성된 Cell이 시계방향인지 판단.
        XMVECTOR vNewCellpoint1 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[0]);
        XMVECTOR vNewCellpoint2 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[1]);
        XMVECTOR vNewCellpoint3 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[2]);

        if (Is_CWTriangle(vNewCellpoint1, vNewCellpoint2, vNewCellpoint3)) {
            // 강제로 순서를 변경하여 올바른 방향으로 만듦.
            swap(tagWholeCellPoints.fCellPoints[1], tagWholeCellPoints.fCellPoints[2]);

            m_pNavigation->Create_Cell(tagWholeCellPoints.fCellPoints);
            m_vecWholeCellPoints.push_back(tagWholeCellPoints);

            tagWholeCellPoints.fPrevPoints[0] = tagWholeCellPoints.fCellPoints[1];
            tagWholeCellPoints.fPrevPoints[1] = tagWholeCellPoints.fCellPoints[2];
        }

        m_iNumCellCount++;
        m_vecPickedPoints.clear();
    }

    return S_OK;


}

_float CLevel_GamePlay::Compute_Cell_Distance(const XMFLOAT3& _NewPickingPoint, const XMFLOAT3& _PrevPickedPoint)
{
    return sqrtf(powf(_PrevPickedPoint.x - _NewPickingPoint.x, 2) + powf(_PrevPickedPoint.y - _NewPickingPoint.y, 2) + powf(_PrevPickedPoint.z - _NewPickingPoint.z, 2));
}

_bool CLevel_GamePlay::Is_CWTriangle(const XMVECTOR& _NearestCellPoint1, const XMVECTOR& _NearestCellPoint2, const XMVECTOR& _PickedNewPoint)
{
    // 가장 가까운 point 1 과 point 2의 방향벡터! 
    XMVECTOR vDir1 = XMVectorSubtract(_NearestCellPoint2, _NearestCellPoint1);

    // 내가 찍은 점하고 point1 하고의 방향벡터.
    XMVECTOR vDir2 = XMVectorSubtract(_PickedNewPoint, _NearestCellPoint1);

    // 이제 그 둘의 방향벡터를 외적해서 뽑아내내 결과값 하나가 0 보다 크면 삼각형이 된거임. 
    // 0보다 작으면 삼각형이 안되는거임 말이안됨ㅋㅋ
    // Cell 클래스의 IsIn 함수 좀 참고했음
    _float fTriangleValue = XMVectorGetX(XMVector3Length(XMVector3Cross(vDir1, vDir2)));

    // 외적하고나고나서 값을 보는데, 만약에 0 이면, 삼각형을 만드는데 필요한 세 점이 한 선에 있거나 그런거임
    // 그래서 무적권 양수가 되야 삼각형이 되었구나 라고 알 수 있셈.
    if (fTriangleValue > 0.0f)
        return true;
    else
        return false;
}

pair<XMFLOAT3, XMFLOAT3> CLevel_GamePlay::Compute_NearPoints(const vector<CELL_POINTS>& _vecTagCells, const XMFLOAT3& _newPoints)
{
    _float fMinDistance = FLT_MAX;
    pair<XMFLOAT3, XMFLOAT3> NearestPoints;

    for (const auto& cell : _vecTagCells)
    {
        for (_uint i = 0; i < 3; ++i)
        {
            for (_uint j = i + 1; j < 3; ++j)
            {
                // fCellPoints[0] 하고 fCellPoints[1] 하고 각각의 거리 fDist1, fDist2 를 구해가지고,
                _float fDist1 = Compute_Cell_Distance(_newPoints, cell.fCellPoints[i]);
                _float fDist2 = Compute_Cell_Distance(_newPoints, cell.fCellPoints[j]);

                // 만약에 처음 fMinDistance가 float_max로 되어있는데, 그거보다 작으면, 
                // 이제는 지금 찍은 점과 기존의 두 점의 dist가 최소가 된다. 
                // 그리고 가장 근접한 두 점은 이 때의 cell.fCellpoints[i] 와 cell.fcellpoints[j]가 된다. 
                // cell.fCellPoints[0] ~~ cell.fCellPoints[1],cell.fCellPoints[2] 랑.
                // cell.fCellPoints[1] ~ cell.fCellPoints[2] 랑,
                // cell.fCellPoints[2] ~ 는 없음. 
                // 3번 검사해서, 
                if (fDist1 + fDist2 < fMinDistance)
                {
                    fMinDistance = fDist1 + fDist2;
                    NearestPoints = { cell.fCellPoints[i], cell.fCellPoints[j] };
                }
            }
        }
    }
    return NearestPoints;
}

XMFLOAT3 CLevel_GamePlay::Pick_Closest_Cube(const XMFLOAT3& clickPos)
{
    // 고른 점의 반경 허용 범위 수치 ( 내가 찍은 부근의 2 이하의 점이 내가 선택한 점이 되는 것) 
    const float PICK_RADIUS = 2.0f;

    _float fMinDistance = FLT_MAX;
    XMFLOAT3 vSelectedCordinate = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

    // m_vecWholeCellPoints 에 담겨 있는 전체 점들을 순회하자.
    // vCordinate 에그 전체 순회해서 찾은 점들의 좌표를 담아주고 Compute_Cell_Distance 계산함수로 ㄱㄱ
    // 그래서 내가 찍은 부근 의 위치 포인트와 원래 vector 컨테이너에 담겨있던, 점들의 거리를 반환해서 fDistance 에 넣어줌
    // 그래서 그 fDistance 가 허용치 2.0f 보다 작고 하면~ 최소 거리를 그냥 그 2.0f 보다 작은 그 값으로 넣어주고,(일시적으로 초기화해주는 느낌임)
    // 내가 선택한 부근의 좌표 점을 이제 해당 cell 의 꼭지점 좌표로 바꿔서 최종적으로 반환해줌.
    for (const auto& cell : m_vecWholeCellPoints)
    {
        for (int i = 0; i < 3; ++i)
        {
            XMFLOAT3 vCordinate = cell.fCellPoints[i];
            _float fDistance = Compute_Cell_Distance(clickPos, vCordinate);

            if (fDistance < PICK_RADIUS && fDistance < fMinDistance)
            {
                fMinDistance = fDistance;
                vSelectedCordinate = vCordinate;
            }
        }
    }

    return vSelectedCordinate;
}

void CLevel_GamePlay::Create_Line_Between_Cubes(const XMFLOAT3& point1, const XMFLOAT3& point2)
{
    tagWholeCellPoints.fCellPoints[0] = point1;
    tagWholeCellPoints.fCellPoints[1] = point2;

    vector<XMFLOAT3> vecAllPoints;
    for (const auto& cell : m_vecWholeCellPoints)
    {
        for (int i = 0; i < 3; ++i)
        {
            vecAllPoints.push_back(cell.fCellPoints[i]);
        }
    }

    XMFLOAT3 vThirdPoint = Compute_Closest_Point(vecAllPoints, point1, point2);

    if (vThirdPoint.x == FLT_MAX)
        return;

    tagWholeCellPoints.fCellPoints[2] = vThirdPoint;
    XMVECTOR vNewCellpoint1 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[0]);
    XMVECTOR vNewCellpoint2 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[1]);
    XMVECTOR vNewCellpoint3 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[2]);

    if (!Is_CWTriangle(vNewCellpoint1, vNewCellpoint2, vNewCellpoint3))
    {
        swap(tagWholeCellPoints.fCellPoints[0], tagWholeCellPoints.fCellPoints[1]);
    }

    m_pNavigation->Create_Cell(tagWholeCellPoints.fCellPoints);
    m_vecWholeCellPoints.push_back(tagWholeCellPoints);
    m_iNumCellCount++;
}

XMFLOAT3 CLevel_GamePlay::Compute_Closest_Point(const vector<XMFLOAT3>& vAllpoints, const XMFLOAT3& point1, const XMFLOAT3& point2)
{
    // 여기서는 내가 고른 두 점 [0] [1] 이 나왔으면, [2] 째도 있어야하니 그걸 선택하는 함수임. 
    _float fMinDistance = FLT_MAX;
    XMFLOAT3 closestPoint = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

    // points 이게, 전체 vecWholeCellPoints 에 담겨있었던 셀의 꼭지점 좌표들을 의미하고 
    for (const auto& point : vAllpoints)
    {
        if (point.x == point1.x && point.y == point1.y && point.z == point1.z)
            continue;
        if (point.x == point2.x && point.y == point2.y && point.z == point2.z)
            continue;

        _float dist1 = Compute_Cell_Distance(point, point1);
        _float dist2 = Compute_Cell_Distance(point, point2);
        _float totalDist = dist1 + dist2;

        if (totalDist < fMinDistance)
        {
            fMinDistance = totalDist;
            closestPoint = point;
        }
    }

    return closestPoint;
}

_bool CLevel_GamePlay::Is_Point_InTriangle(const XMVECTOR& _Point, const XMVECTOR& _VertexPoint0, const XMVECTOR& _VertexPoint1, const XMVECTOR& _VertexPoint2)
{
    //내적 ( 외적 ( ab, at ) , 외적 ( at, ac ) ) > 0 
    //[출처] - 삼각형 안에 점이 있는지 확인하는 방법 | 작성자 콜라곰

    XMVECTOR v0v1 = XMVectorSubtract(_VertexPoint1, _VertexPoint0);
    XMVECTOR v1v2 = XMVectorSubtract(_VertexPoint2, _VertexPoint1);
    XMVECTOR v2v0 = XMVectorSubtract(_VertexPoint0, _VertexPoint2);

    XMVECTOR v0p = XMVectorSubtract(_Point, _VertexPoint0);
    XMVECTOR v1p = XMVectorSubtract(_Point, _VertexPoint1);
    XMVECTOR v2p = XMVectorSubtract(_Point, _VertexPoint2);

    XMVECTOR vCrossValue0 = XMVector3Cross(v0v1, v0p);
    XMVECTOR vCrossValue1 = XMVector3Cross(v1v2, v1p);
    XMVECTOR vCrossValue2 = XMVector3Cross(v2v0, v2p);

    XMVECTOR vNormal = XMVector3Cross(v0v1, XMVectorSubtract(_VertexPoint2, _VertexPoint0));

    _float  fDotValue0 = XMVectorGetX(XMVector3Dot(vCrossValue0, vNormal));
    _float  fDotValue1 = XMVectorGetX(XMVector3Dot(vCrossValue1, vNormal));
    _float  fDotValue2 = XMVectorGetX(XMVector3Dot(vCrossValue2, vNormal));

    return (fDotValue0 >= 0.0f && fDotValue1 >= 0.0f && fDotValue2 >= 0.0f);
}

HRESULT CLevel_GamePlay::Delete_Cell_Mode()
{
    if (m_pGameInstance->Get_DIKeyState(DIK_F) & 0x80)
    {
        m_bDeleteMode = true;

        if (!m_vecPickedPoints.empty())
        {
            Delete_Cell();

            m_vecPickedPoints.clear();
        }
    }
    else
    {
        m_bDeleteMode = false;
    }

    return S_OK;
}

HRESULT CLevel_GamePlay::Delete_Cell()
{
    if (m_vecPickedPoints.empty())
        return E_FAIL;

    XMFLOAT3 vPickedPoint = m_vecPickedPoints[0];

    for (auto iter = m_vecWholeCellPoints.begin(); iter != m_vecWholeCellPoints.end(); ++iter)
    {
        const auto& pCell = *iter;

        if (Is_Point_InTriangle(XMLoadFloat3(&vPickedPoint), XMLoadFloat3(&pCell.fCellPoints[0]), XMLoadFloat3(&pCell.fCellPoints[1]), XMLoadFloat3(&pCell.fCellPoints[2])))
        {
            m_pNavigation->Delete_Cell(pCell.fCellPoints);

            m_vecWholeCellPoints.erase(iter);

            m_iNumCellCount--;
            return S_OK;
        }
    }

    return E_FAIL;
}

HRESULT CLevel_GamePlay::Save_Navi()
{
    wstring fileName; OpenFileDialoge(L"NavigationData.txt", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
        return E_FAIL;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Create NavigationData File!");
        return E_FAIL;
    }

    DWORD dwByte = 0;

    WriteFile(hFile, &m_iNumCellCount, sizeof(_uint), &dwByte, nullptr);

    for (auto& pCellPoints : m_vecWholeCellPoints)
    {
        WriteFile(hFile, pCellPoints.fCellPoints, sizeof(_float3) * 3, &dwByte, nullptr);
    }
    MSG_BOX("Success Save");
    CloseHandle(hFile);

    return S_OK;

}

HRESULT CLevel_GamePlay::Load_Navi()
{
    wstring fileName; OpenFileDialoge(L"Select Navigation Data", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
    {
        MSG_BOX("No file selected!");
        return E_FAIL;
    } HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Open NavigationData File!");
        return E_FAIL;
    } DWORD dwByte = 0;
    _uint iLoadedCellCount = 0;
    ReadFile(hFile, &iLoadedCellCount, sizeof(_uint), &dwByte, nullptr);
    for (_uint i = 0; i < iLoadedCellCount; ++i)
    {
        CELL_POINTS cellPoints; ReadFile(hFile, cellPoints.fCellPoints, sizeof(_float3) * 3, &dwByte, nullptr
        );
        _bool bIsDuplicate = false;
        for (const auto& existingCell : m_vecWholeCellPoints)
        {
            if (memcmp(existingCell.fCellPoints, cellPoints.fCellPoints, sizeof(_float3) * 3) == 0)
            {
                bIsDuplicate = true; break;
            }
        }
        if (!bIsDuplicate)
        {
            m_pNavigation->Create_Cell(cellPoints.fCellPoints); m_vecWholeCellPoints.push_back(cellPoints); m_iNumCellCount++;
        }
    }
    CloseHandle(hFile);
    MSG_BOX("Navigation Data Loaded Successfully!");
    return S_OK;

}

HRESULT CLevel_GamePlay::Show_MouseRange(MENU_TYPE _eMenuType, _float _fTimeDelta)
{
    m_fPickPos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))));

    m_pTerrain->Set_TerrainPickPos(m_fPickPos, m_fInstallRange);
    

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

    for (auto& pSRV : m_vecGroundModelSRVs)
        Safe_Release(pSRV);
    m_vecGroundModelSRVs.clear();
}
