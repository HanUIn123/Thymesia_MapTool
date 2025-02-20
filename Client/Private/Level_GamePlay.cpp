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

    // ���̾� �̸��̶�, ��ü �ּ�
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
        m_iNonAnimModelIndex = -1;
    }
    if (ImGui::RadioButton("ANIM_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_PICKING_ANIMMODEL))
    {
        m_bNonAnimObjectMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bAnimObjectMenuSelected = true;
    }
    if (ImGui::RadioButton("NAVIGATION_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_NAVI))
    {
        m_bNaviMenuSelected = true;
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



    // if (ImGui::Button("Save_Models"))
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

    if (iMenuTypeNumber == MENU_TYPE::MT_NAVI)
    {
        if (ImGui::Button("Save_Navi"))
        {

        }

        ImGui::SameLine();

        if (ImGui::Button("Load_Navi"))
        {

        }
    }

    Delete_Cell_Mode();


    ImGui::End();

    if (m_bNonAnimObjectMenuSelected)
        Setting_NonAnimObjectList();

    ImGui::End();
}

HRESULT CLevel_GamePlay::Render()
{
#ifdef _DEBUG
    SetWindowText(g_hWnd, TEXT("�����÷��� �����Դϴ�."));
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

    /* 2�� 8�� �� */
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
    /* ���⼭ �� ���� �ϳ��ϳ� �� �о�;��� */

    _ulong dwByte = {};
    //HANDLE hFile = CreateFile(TEXT("../Map_File/real76.bin"), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    HANDLE hFile = CreateFile(TEXT("../Map_File/real143.bin"), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    while (true)
    {
        _tchar Layer_Name[MAX_PATH] = {}; //���̾� �̸�                              
        ReadFile(hFile, Layer_Name, MAX_PATH, &dwByte, nullptr);

        if (dwByte == 0)
            break;
        /* �̸� �۾� */
        _char   Prototype_Name[MAX_PATH] = {};

        ReadFile(hFile, Prototype_Name, MAX_PATH, &dwByte, nullptr);


        _float4x4 WorldMatrix = {};
        ReadFile(hFile, &WorldMatrix, sizeof(_float4x4), &dwByte, nullptr);
        //int a = 4;

        _tchar Translate_wchar[MAX_PATH] = {};
        MultiByteToWideChar(CP_ACP, 0, Prototype_Name, static_cast<_int>(strlen(Prototype_Name)), Translate_wchar, MAX_PATH);

        /* ���� TRANSFORM�� �ǵ�� �ɵ���.*/
        //int b = 4;
        if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, Translate_wchar, LEVEL_GAMEPLAY, Layer_Name)))
            return E_FAIL;

        //CTransform* pTrasnform = dynamic_cast<CTransform*>(
        //* Find GaemObject ������ �ҵ�
        // ������ �� �ִ� ����� �����غ����ҵ�.
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

HRESULT CLevel_GamePlay::Picking_Points()
{
    m_fPickPos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))));

    if (m_fPickPos.y == -0.5f)
        return S_OK;

    m_fPickPos.y += 0.1f;

    if (m_bDeleteMode)
    {
        m_vecPickedPoints.push_back(m_fPickPos);
        return S_OK;
    }

    if (m_bConnectingMode)
    {
        XMFLOAT3 vSelectedCordinate = Pick_Closest_Cube(m_fPickPos);
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

    m_vecPickedPoints.push_back(m_fPickPos);

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
    else if (m_vecPickedPoints.size() < 3 && m_bFirstPick == false)
    {
        // m_vecPickedPoints[0] �� ���� ����������, ���� "����" ��� �� ���� �ǹ���.
        // m_vecWholeCellPoints �� �ִ� ��� cell points ���̶� ����ؼ� ���� ���� ����� ������ 
        // Compute_NearPoints ��� <xmfloat3, xmfloat3> ��� pair Ÿ������ ��� �ִ� NearPoints�� ó����.
        auto NearPoints = Compute_NearPoints(m_vecWholeCellPoints, m_vecPickedPoints[0]);

        // ���� ���� �� ���� ���� ���ϰ� NearPoints�� ù ��° ���� �� �� ��° ���Ұ�, ��췯���� Cell�� ����!! 
        tagWholeCellPoints.fCellPoints[0] = NearPoints.first;
        tagWholeCellPoints.fCellPoints[1] = NearPoints.second;
        tagWholeCellPoints.fCellPoints[2] = m_vecPickedPoints[0];

        // �׸��� �� ��췯�� ������� Cell �� �ð�������� �Ȱ��� �ƴ���, IsCWTriangle �Լ��� �Ǵ�����.
        // vNewCellpoint1 �� ���� ���� ���� ���� ����� ���� ù ��° ������ point.
        // vNewCellpoint2 �� ���� ���� ���� ���� ����� ���� �� ��° ������ point.
        // vNewCellpoint3 �� ���� ���� �� point.
        XMVECTOR vNewCellpoint1 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[0]);
        XMVECTOR vNewCellpoint2 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[1]);
        XMVECTOR vNewCellpoint3 = XMLoadFloat3(&tagWholeCellPoints.fCellPoints[2]);

        if (Is_CWTriangle(vNewCellpoint1, vNewCellpoint2, vNewCellpoint3))
        {
            // ���������� �׳� ���� �ٲ����. �̰ž��ϸ� ������. (�ٵ� �� ������ �׷��� ������;�𸣰���)
            // �ƹ��� �ص� ��ٺ��� [2] - [0] - [1] �ؾ��ϴµ� ���߳���, [2] - [1] - [0] �̷��� �ǹ���;;
            // �׷��� �ٲ���� ���⼭ ���������� �� ������ �ǰ�.
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
    // ���� ����� point 1 �� point 2�� ���⺤��! 
    XMVECTOR vDir1 = XMVectorSubtract(_NearestCellPoint2, _NearestCellPoint1);

    // ���� ���� ���ϰ� point1 �ϰ��� ���⺤��.
    XMVECTOR vDir2 = XMVectorSubtract(_PickedNewPoint, _NearestCellPoint1);

    // ���� �� ���� ���⺤�͸� �����ؼ� �̾Ƴ��� ����� �ϳ��� 0 ���� ũ�� �ﰢ���� �Ȱ���. 
    // 0���� ������ �ﰢ���� �ȵǴ°��� ���̾ȵʤ���
    // Cell Ŭ������ IsIn �Լ� �� ��������
    _float fTriangleValue = XMVectorGetX(XMVector3Length(XMVector3Cross(vDir1, vDir2)));

    // �����ϰ����� ���� ���µ�, ���࿡ 0 �̸�, �ﰢ���� ����µ� �ʿ��� �� ���� �� ���� �ְų� �׷�����
    // �׷��� ������ ����� �Ǿ� �ﰢ���� �Ǿ����� ��� �� �� �ּ�.
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
                // fCellPoints[0] �ϰ� fCellPoints[1] �ϰ� ������ �Ÿ� fDist1, fDist2 �� ���ذ�����,
                _float fDist1 = Compute_Cell_Distance(_newPoints, cell.fCellPoints[i]);
                _float fDist2 = Compute_Cell_Distance(_newPoints, cell.fCellPoints[j]);

                // ���࿡ ó�� fMinDistance�� float_max�� �Ǿ��ִµ�, �װź��� ������, 
                // ������ ���� ���� ���� ������ �� ���� dist�� �ּҰ� �ȴ�. 
                // �׸��� ���� ������ �� ���� �� ���� cell.fCellpoints[i] �� cell.fcellpoints[j]�� �ȴ�. 
                // cell.fCellPoints[0] ~~ cell.fCellPoints[1],cell.fCellPoints[2] ��.
                // cell.fCellPoints[1] ~ cell.fCellPoints[2] ��,
                // cell.fCellPoints[2] ~ �� ����. 
                // 3�� �˻��ؼ�, 
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
    // �� ���� �ݰ� ��� ���� ��ġ ( ���� ���� �α��� 2 ������ ���� ���� ������ ���� �Ǵ� ��) 
    const float PICK_RADIUS = 2.0f;

    _float fMinDistance = FLT_MAX;
    XMFLOAT3 vSelectedCordinate = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

    // m_vecWholeCellPoints �� ��� �ִ� ��ü ������ ��ȸ����.
    // vCordinate ���� ��ü ��ȸ�ؼ� ã�� ������ ��ǥ�� ����ְ� Compute_Cell_Distance ����Լ��� ����
    // �׷��� ���� ���� �α� �� ��ġ ����Ʈ�� ���� vector �����̳ʿ� ����ִ�, ������ �Ÿ��� ��ȯ�ؼ� fDistance �� �־���
    // �׷��� �� fDistance �� ���ġ 2.0f ���� �۰� �ϸ�~ �ּ� �Ÿ��� �׳� �� 2.0f ���� ���� �� ������ �־��ְ�,(�Ͻ������� �ʱ�ȭ���ִ� ������)
    // ���� ������ �α��� ��ǥ ���� ���� �ش� cell �� ������ ��ǥ�� �ٲ㼭 ���������� ��ȯ����.
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
    // ���⼭�� ���� �� �� �� [0] [1] �� ��������, [2] °�� �־���ϴ� �װ� �����ϴ� �Լ���. 
    _float fMinDistance = FLT_MAX;
    XMFLOAT3 closestPoint = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

    // points �̰�, ��ü vecWholeCellPoints �� ����־��� ���� ������ ��ǥ���� �ǹ��ϰ� 
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
    //���� ( ���� ( ab, at ) , ���� ( at, ac ) ) > 0 
    //[��ó] - �ﰢ�� �ȿ� ���� �ִ��� Ȯ���ϴ� ��� | �ۼ��� �ݶ��

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

}

HRESULT CLevel_GamePlay::Load_Navi()
{


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
