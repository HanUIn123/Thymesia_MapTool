#pragma once
#include "pch.h" 
#include "Level_GamePlay.h"
#include "Camera_Free.h"
#include "Layer.h"   
#include "Terrain.h"

#include "GameObject.h"

#include "GroundObject.h"

CLevel_GamePlay::CLevel_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    : CLevel{ pDevice, pContext }
{
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/HORSE_P_WoodenFrame02_05.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Rag03.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_Shelf.dds"), IMG_NONANIM_MODEL, 1);
    // Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_WoodStairs03.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircle01.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_02_02.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_04.dds"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_05.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossCemetery_06.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossInteriorArches02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_ChurchWindowGrilles01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_LongStairs01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Plains_CastleArch_Ruin_01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_8x8_Broken_01c.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_8x8_Broken_01d.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_8x8_Broken_01e.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/T_P_BossRoomVines01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossArtriumCircleRailing_Down02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossArtriumCircleRailing_Down03.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossArtriumCircleRailing_Down04.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Top01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up04.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BossAtriumCircleRailing_Up03.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Fortress_BossDoor_Left01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Fortress_BossDoor_Right01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Debris_01a.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Debris_02a.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Scafold_01b.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Scafold_01c.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_CemeteryStairs01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_CemeteryStairs02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_CemeteryStairs03.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Archive_Chair01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Ladder.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_crypt_01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_crypt_05.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_crypt_06.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_crypt_08.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_crypt_09.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_14.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_16.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_03.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_08.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_fence_15.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/House_0.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/House_3.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Brick_Floor.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Cross.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/HORSE_P_WoodenStand02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BloodTent02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_BloodWoodChair01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Boss_Floor01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_Boss_Floor02.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/P_WoodenChair01.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/chandelier04.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Tower.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Railing.png"), IMG_NONANIM_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Greenhouse_Elevator01.png"), IMG_NONANIM_MODEL, 1);

    //=============================================================================================================================

    // IMG_GROUND_MODEL
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/GroundObjects/Grass0.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/GroundObjects/Tree0.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing_base01.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing_pillar01_2.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing03_1.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Railing01_3.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_BaseWall_01_Corner.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_BaseWall_02_Plain.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Separator.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Barrel_Closed.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_WoodFence03.dds"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_WoodFence04.dds"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Stairs.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Stairs02.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_LogPile_03.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Brick_stone_stairs_1_a.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Gate_17d.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Fence_04.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Wall_Combined_03.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_ground_Road_Middle_250x250cm_1_a.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/Brick_Floor.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/House_0.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/House_3.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Planks.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_WoodStair03.png"), IMG_GROUND_MODEL, 1);
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/SM_Trim_01a.png"), IMG_GROUND_MODEL, 1);

    //=============================================================================================================================
    Resister_ObjectList_PreviewImage(TEXT("../Bin/Resources/Textures/Imgui_PreviewTextures/TempCollider/TempCollider%d.png"), IMG_TRIGGER_OBJECT, 1);


    /*

        "SM_BaseWall_01_Corner",
        "SM_BaseWall_02_Plain",
        "SM_Separator",
        "SM_Barrel_Closed",
        "SM_WoodFence03",
        "SM_WoodFence04",
        "SM_Stairs",
        "SM_Stairs02",
        "SM_LogPile_03",*/
}

HRESULT CLevel_GamePlay::Initialize()
{
    Ready_TerrainMasking();

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
    static int iMenuTypeNumber = MENU_TYPE::MT_END;

    if (m_pGameInstance->isKeyPressed(DIK_O))
        m_bGroundObjectMouseState = !m_bGroundObjectMouseState;

    ImGui::Begin("Object");

    ImGuiIO IO = ImGui::GetIO();

    ImGui::Begin("TOOL MENU");
    if (ImGui::RadioButton("NONANIM_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_PICKING_NONANIMMODEL))
    {
        m_bNonAnimObjectMenuSelected = true;
        m_bAnimObjectMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bGrondMenuSelected = false;
        m_bTerrainHeightSelected = false;
        m_bTerrainMaskSelected = false;
        m_bTerrainWaterMaskSelected = false;
        m_bTriggerObjectMenuSelected = false;
        m_iNonAnimModelIndex = -1;
    }
    if (ImGui::RadioButton("ANIM_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_PICKING_ANIMMODEL))
    {
        m_bNonAnimObjectMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bAnimObjectMenuSelected = true;
        m_bGrondMenuSelected = false;
        m_bTerrainHeightSelected = false;
        m_bTerrainMaskSelected = false;
        m_bTerrainWaterMaskSelected = false;
        m_bTriggerObjectMenuSelected = false;
    }
    if (ImGui::RadioButton("NAVIGATION_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_NAVI))
    {
        m_bNaviMenuSelected = true;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
        m_bGrondMenuSelected = false;
        m_bTerrainHeightSelected = false;
        m_bTerrainMaskSelected = false;
        m_bTerrainWaterMaskSelected = false;
        m_bTriggerObjectMenuSelected = false;
    }
    if (ImGui::RadioButton("GROUND_MODEL_PICKING", &iMenuTypeNumber, MENU_TYPE::MT_GROUND))
    {
        m_bGrondMenuSelected = true;
        m_bNaviMenuSelected = false;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
        m_bTerrainHeightSelected = false;
        m_bTerrainMaskSelected = false;
        m_bTerrainWaterMaskSelected = false;
        m_bTriggerObjectMenuSelected = false;
    }
    if (ImGui::RadioButton("TERRAIN_HEIGHT", &iMenuTypeNumber, MENU_TYPE::MT_HEIGHT))
    {
        m_bTerrainHeightSelected = true;
        m_bGrondMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
        m_bTerrainMaskSelected = false;
        m_bTerrainWaterMaskSelected = false;
        m_bTriggerObjectMenuSelected = false;
    }

    if (ImGui::RadioButton("TERRAIN_MASK", &iMenuTypeNumber, MENU_TYPE::MT_TERRAIN_MASK))
    {
        m_bTerrainHeightSelected = false;
        m_bGrondMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
        m_bTerrainMaskSelected = true;
        m_bTerrainWaterMaskSelected = false;
        m_bTriggerObjectMenuSelected = false;
    }


    if (ImGui::RadioButton("WATER_MASK", &iMenuTypeNumber, MENU_TYPE::MT_WATER_MASK))
    {
        m_bTerrainHeightSelected = false;
        m_bGrondMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
        m_bTerrainMaskSelected = false;
        m_bTerrainWaterMaskSelected = true;
        m_bTriggerObjectMenuSelected = false;
    }

    if (ImGui::RadioButton("TRIGGER OBJECT PICKING", &iMenuTypeNumber, MENU_TYPE::MT_TRIGGER))
    {
        m_bTriggerObjectMenuSelected = true;
        m_bTerrainHeightSelected = false;
        m_bGrondMenuSelected = false;
        m_bNaviMenuSelected = false;
        m_bNonAnimObjectMenuSelected = false;
        m_bAnimObjectMenuSelected = false;
        m_bTerrainWaterMaskSelected = false;
        m_bTerrainMaskSelected = false;
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
    ImGui::InputInt("PassNumber", &m_iPassIndex);

    if (ImGui::Button("Delete_ObjectIndex"))
    {
        m_iNonAnimModelIndex = -1;

        m_pPrevObject = nullptr;
        m_pPrevObjectTrasnformCom = nullptr;
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
        if (!IO.WantCaptureMouse)
        {
            if (m_pGameInstance->isMouseEnter(DIM_LB))
            {
                Picking_Points();
            }
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
        else if (m_pGameInstance->isMouseEnter(DIM_RB))
        {
        }
    }
    else if (m_bTerrainHeightSelected)
    {
        ImGui::InputFloat("Terrain_Height", &m_fTerrainHeightSetting);

        Show_MouseRange(MENU_TYPE::MT_HEIGHT, fTimeDelta);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && !IO.WantCaptureMouse)
        {
            if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_HEIGHT)))
            {
                Raising_Terrain(fTimeDelta, true);
            }
        }
        if (m_pGameInstance->Get_DIKeyState(DIK_R) && !IO.WantCaptureMouse)
        {
            if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_HEIGHT)))
            {
                Raising_Terrain(fTimeDelta, false);
            }
        }
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000 && !IO.WantCaptureMouse)
        {
            if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_HEIGHT)))
            {
                Set_Terrain_Height(m_fTerrainHeightSetting);
            }
        }

    }
    else if (m_bTriggerObjectMenuSelected)
    {
        if (!IO.WantCaptureMouse)
        {
            if (m_pGameInstance->isMouseEnter(DIM_LB))
            {
                //if (m_bIsMeshPickingMode)
                //{
                //    vector<Mesh_Pos> vMesh;

                //    for (auto& pObject : m_Objects)
                //    {
                //        CObject::MESHINFO pInfo;

                //        if (pObject != nullptr && pObject->Picking_Objects(pInfo))
                //        {
                //            Mesh_Pos vPos{};
                //            vPos.fPosition = pInfo.fPosition;
                //            vPos.fDist = pInfo.fDist;
                //            vPos.pObject = pObject;

                //            vMesh.push_back(vPos);
                //        }
                //    }

                //    if (vMesh.size() != 0)
                //    {
                //        sort(vMesh.begin(), vMesh.end(), [](Mesh_Pos a, Mesh_Pos b) {
                //            if (a.fDist < b.fDist) return true;
                //            else
                //                return false;
                //            });

                //        _float3 fPos = { 0.f ,0.f ,0.f };

                //        fPos = vMesh.front().fPosition;

                //        m_fMeshPickPos = fPos;

                //        m_fObjectPos[0] = fPos.x;

                //        m_fObjectPos[1] = fPos.y;

                //        m_fObjectPos[2] = fPos.z;

                //        Add_TriggerObjects();

                //    }
                //}
                //else if (m_bIsTerrainPickingMode)
                //{
                //    if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_TRIGGER)))
                //    {
                //        Add_TriggerObjects();
                //    }
                //}

                _float3 vPickPos = {};
                if (m_pGameInstance->Compute_PickPos(&vPickPos))
                {
                    m_fObjectPos[0] = vPickPos.x;
                    m_fObjectPos[1] = vPickPos.y;
                    m_fObjectPos[2] = vPickPos.z;

                    Add_TriggerObjects();
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
        ImGui::SliderFloat("fFrustumRadius", &fFrustumRadius, 1.f, m_fRadiusMax);

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
            Load_Navi(1);
        }
    }

    if (iMenuTypeNumber == MENU_TYPE::MT_HEIGHT)
    {
        if (ImGui::Button("Save_Height"))
            Save_HeightMap();

        ImGui::SameLine();

        if (ImGui::Button("Load_Height"))
            Load_HeightMap();
    }


    if (iMenuTypeNumber == MENU_TYPE::MT_TRIGGER)
    {
        if (ImGui::Button("Save_Trigger"))
            Save_TriggerObjects();
        ImGui::SameLine();

        if (ImGui::Button("Load Trigger"))
            Load_TriggerObjects();



        //ImGui::CollapsingHeader("Trigger Object Settings");
        //ImGui::InputFloat3("Trigger_ObjectScale", m_fTriggerScale);
        //ImGui::End();
    }

    ImGui::Checkbox("Creating NaviTerritory", &m_bFinishPickingNavi_InCurrentFloor);
    if (ImGui::Button("Finish Create Navi"))
    {
        m_bFinishPickingNavi_InCurrentFloor = true;
        m_bFirstPick = true;
        ImGui::Text("You Can Create");
    }
    if (ImGui::Button("Start Create Navi"))
    {
        m_bFinishPickingNavi_InCurrentFloor = false;
        ImGui::Text("You Done!");
    }

    ImGui::Begin("Device Settings", NULL, ImGuiWindowFlags_MenuBar);

    ImGui::Checkbox("Mode Select", &m_iModeSelected);
    if (ImGui::Button("Choose Number"))
    {
        m_iModeSelected = true;
        m_fInstallRange = 1.0f;
    }

    if (m_iModeSelected)
        ImGui::SliderFloat("##10Choose Number", &m_fInstanceCount, 1.0f, 300.0f);

    if (ImGui::Button("Mouse Range"))
    {
        m_iModeSelected = false;
        m_fInstanceCount = 1.0f;
    }

    if (!m_iModeSelected)
        ImGui::SliderFloat("##9Mouse Range", &(m_fInstallRange), 0.0f, 20.0f);


    ImGui::SliderFloat("Object Spacing", &m_fSpacingValue, 1.0f, 10.0f);
    ImGui::End();

    //Active_PreviewModelImage();

    Delete_Cell_Mode(1);

    ImGui::InputFloat4("Monster_Pos", m_vMonsterPos);
    ImGui::InputInt("Monster_Index", &m_fMonsterIndex);

    //ZeroMemory(&m_MonsterInfo, sizeof(m_MonsterInfo));

    if (ImGui::Button("Add_MonsterInfo"))
    {
        m_MonsterInfos[m_fMonsterIndex].vMonsterPos.push_back(_float4(m_vMonsterPos[0], m_vMonsterPos[1], m_vMonsterPos[2], 1.f));
    }

    if (ImGui::Button("Save_MonsterIndex"))
    {
        Save_Monster_Index();
    }

    if (m_bTerrainMaskSelected)
    {
        if (!IO.WantCaptureMouse)
        {
            if (m_pGameInstance->Get_DIMouseState(DIM_LB))
            {
                if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_TERRAIN_MASK)))
                {
                    Make_MaskTexture(XMLoadFloat3(&m_fPickPos));
                }
            }


            if (m_pGameInstance->Get_DIMouseState(DIM_RB))
            {
                if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_TERRAIN_MASK)))
                {
                    if (SUCCEEDED(Erase_MaskTexture(XMLoadFloat3(&m_fPickPos))))
                    {
                        MSG_BOX("Succeeded To Create Texture");
                    }
                }
            }
        }


        ImGui::InputInt("MaskIndex", &m_iMaskTextureIndex);

        if (ImGui::Button("Make_Mask_DDS"))
        {
            if (FAILED(Save_MaskTexture(m_iMaskTextureIndex)))
            {
                MSG_BOX("Failed To Created MaskTexture!");
            }
        }

        if (ImGui::Button("Load_Mask_DDS"))
        {
            if (FAILED(Load_MaskTexture(m_iMaskTextureIndex)))
            {
                MSG_BOX("Failed To Loaded MaskTexture!");
            }
        }
    }


    if (m_bTerrainWaterMaskSelected)
    {
        if (!IO.WantCaptureMouse)
        {
            if (m_pGameInstance->Get_DIMouseState(DIM_LB))
            {
                if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_WATER_MASK)))
                {
                    Make_WaterMapTexture(XMLoadFloat3(&m_fPickPos));
                }
            }


            if (m_pGameInstance->Get_DIMouseState(DIM_RB))
            {
                if (SUCCEEDED(Pick_Object(MENU_TYPE::MT_WATER_MASK)))
                {
                    Erase_WaterMapTexture(XMLoadFloat3(&m_fPickPos));
                }
            }
        }


        ImGui::InputInt("WaterMapIndex", &m_iMaskTextureIndex);

        if (ImGui::Button("Make_WaterMap_DDS"))
        {
            if (FAILED(Save_WaterMapTexture(m_iMaskTextureIndex)))
            {
                MSG_BOX("Failed To Created MaskTexture!");
            }
        }

        if (ImGui::Button("Load_WaterMap_DDS"))
        {
            if (FAILED(Load_WaterMapTexture(m_iMaskTextureIndex)))
            {
                MSG_BOX("Failed To Loaded MaskTexture!");
            }
        }
    }
    //m_bTerrainWaterMaskSelected
    ImGui::End();

    if (m_bNonAnimObjectMenuSelected)
        Setting_NonAnimObjectList();

    if (m_bGrondMenuSelected)
    {
        Setting_GroundObjectList();
    }

    if (m_bTriggerObjectMenuSelected)
    {
        Setting_TriggerObjects();

        Update_TriggerObjects();
    }

    Update_InstanceObjects();

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
    /*  if (FAILED(m_pGameInstance->SetUp_ShadowLight(XMVectorSet(232.f, 200.f, 150.f, 1.f), XMVectorSet(232.f, 62.f, 60.f, 1.f),
          XMConvertToRadians(60.f), static_cast<_float>(g_iWinSizeX / g_iWinSizeY), 0.1f, 800.f
          , m_pGameInstance->Get_Player_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Player")))))
          return E_FAIL;*/

    LIGHT_DESC            LightDesc{};

    /* 2월 8일 빛 *//*
    LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
    LightDesc.vDirection = _float4(1.f, 1.f, 1.f, 0.f);
    LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
    LightDesc.vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
    LightDesc.vSpecular = _float4(0.5f, 0.5f, 0.5f, 1.f);*/


    LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
    LightDesc.vDirection = _float4(1.f, 1.f, 1.f, 0.f);
    LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
    LightDesc.vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
    LightDesc.vSpecular = _float4(0.3f, 0.3f, 0.3f, 1.f);

    if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
        return E_FAIL;

    ZeroMemory(&LightDesc, sizeof(LightDesc));

    LightDesc.eType = LIGHT_DESC::TYPE_POINT;

    //  LightDesc.vDirection = _float4(1.f, -1.f, 0.f, 0.f);
    LightDesc.vPosition = _float4(-378.5, 12.000, -64.000, 1.f);
    LightDesc.vDiffuse = _float4(0.8f, 0.8f, 0.8f, 1.f);

    LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

    //_float4(1.f, 1.f, 1.f, 1.f);
    LightDesc.vSpecular = _float4(0.5f, 0.5f, 0.5f, 1.f);
    LightDesc.fRange = 15.f;


    if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
        return E_FAIL;

    ZeroMemory(&LightDesc, sizeof(LightDesc));

    LightDesc.eType = LIGHT_DESC::TYPE_POINT;

    //  LightDesc.vDirection = _float4(1.f, -1.f, 0.f, 0.f);
    LightDesc.vPosition = _float4(83.0f, 7.5f, -118.0f, 1.0f);
    LightDesc.vDiffuse = _float4(1.0f, 1.0f, 1.0f, 1.f);
    LightDesc.vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
    LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);
    LightDesc.fRange = 30.f;

    if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const _tchar* pLayerTag)
{
    CTerrain::TERRAINDESC pDesc = {};

    if (m_pCopyMaskSRV != nullptr)
        pDesc.pMaskTexture = m_pCopyMaskSRV;

    if (m_pCopyWaterMapSRV != nullptr)
        pDesc.pWaterMapTexture = m_pCopyWaterMapSRV;

    if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Terrain"), LEVEL_GAMEPLAY, pLayerTag, &pDesc)))
        return E_FAIL;

    if (FAILED(m_pGameInstance->Add_GameObject_To_Layer(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Sky"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
        return E_FAIL;

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

    //Desc.vEye = _float3(0.f, 10.f, -7.f);
    //Desc.vAt = _float3(0.f, 0.f, 0.f);

    Desc.vEye = _float3(30.0f, 10.0f, -150.0f);
    Desc.vAt = _float3(30.f, 0.f, -143.f);

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
            case IMG_TRIGGER_OBJECT:
                m_vecTriggerObjectSRVs.push_back(pSRV);
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
    Desc.iPassNum = { (_uint)m_iPassIndex };

    switch (m_iNonMoveObjectListIndex)
    {
    case 1:
        Desc.ObjectName = m_strObjectNames[m_iNonAnimModelIndex];
        break;

    case 2:
        Desc.ObjectName = m_strGroundObjectGraveStoneNames[m_iNonAnimModelIndex];
        break;

    case 3:
        Desc.ObjectName = m_strObjectUrnNames[m_iNonAnimModelIndex];
        break;

    case 4:
        Desc.ObjectName = m_strGroundObjectDeseasednames[m_iNonAnimModelIndex];
        break;

    case 5:
        Desc.ObjectName = m_strGroundObjectTombStoneNames[m_iNonAnimModelIndex];
        break;
    default:
        return;
    }


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
    {
        m_iNonMoveObjectListIndex = 1;

        const char* szItems[] = { "Model List" };

        static int iCurrentItem = 0;
        ImGui::Combo("##3", &iCurrentItem, szItems, IM_ARRAYSIZE(szItems));

        for (_uint i = 0; i < 65; ++i)
        {
            _uint  iTextureIndex = iCurrentItem * 3 + i;

            if (iTextureIndex < m_vecNonAnimModelSRVs.size())
            {
                if (ImGui::ImageButton(("NonAnimModel" + to_string(iTextureIndex)).c_str(), (ImTextureID)m_vecNonAnimModelSRVs[iTextureIndex], ImVec2(50.0f, 50.0f)))
                {
                    m_iNonAnimModelIndex = iTextureIndex;

                    //m_pGameInstance->Add_DeadObject(TEXT("Layer_Object"), m_pPrevObject);

                    CObject::OBJECT_DESC ObjectDesc = {};
                    ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
                    ObjectDesc.fFrustumRadius = m_fFrustumRadius;
                    ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
                    ObjectDesc.fRotation = { 0.0f, 0.0f, 0.0f };
                    ObjectDesc.ObjectName = m_strObjectNames[m_iNonAnimModelIndex];

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
    else if (ImGui::CollapsingHeader("Grave_Stone Model List"))
    {
        m_iNonMoveObjectListIndex = 2;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectGraveStoneNames, IM_ARRAYSIZE(m_strGroundObjectGraveStoneNames)))
        {
            m_iNonAnimModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectGraveStoneNames[m_iNonAnimModelIndex];

        }

    }
    else if (ImGui::CollapsingHeader("Urn Model List"))
    {
        m_iNonMoveObjectListIndex = 3;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strObjectUrnNames, IM_ARRAYSIZE(m_strObjectUrnNames)))
        {
            m_iNonAnimModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strObjectUrnNames[m_iNonAnimModelIndex];

        }

    }
    else if (ImGui::CollapsingHeader("Deseased Model List"))
    {
        m_iNonMoveObjectListIndex = 4;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectDeseasednames, IM_ARRAYSIZE(m_strGroundObjectDeseasednames)))
        {
            m_iNonAnimModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectDeseasednames[m_iNonAnimModelIndex];

        }

    }
    else if (ImGui::CollapsingHeader("TombStone Model List"))
    {
        m_iNonMoveObjectListIndex = 5;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectTombStoneNames, IM_ARRAYSIZE(m_strGroundObjectTombStoneNames)))
        {
            m_iNonAnimModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectTombStoneNames[m_iNonAnimModelIndex];

        }

    }
 }

    //m_strGroundObjectDeseasednames
    //m_strGroundObjectTreenames

void CLevel_GamePlay::Active_PreviewModelImage()
{
    _float3 vMousePos;
    if (m_bNonAnimObjectMenuSelected && m_pPrevObject && m_bIsTerrainPickingMode)
    {
        vMousePos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))), m_pTerrain->Get_Transfrom());

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

    ImGuiIO IO = ImGui::GetIO();

    if (!IO.WantCaptureMouse)
    {
        CEnvironmentObject::ENVIRONMENT_OBJECT_DESC EnvironmentDesc = {};
        EnvironmentDesc.fPosition = { m_fObjectPos[0], m_fObjectPos[1], m_fObjectPos[2], 1.f };
        EnvironmentDesc.fFrustumRadius = m_fFrustumRadius;

        EnvironmentDesc.fScaling = { m_fMeshScale[0], m_fMeshScale[1], m_fMeshScale[2] };
        EnvironmentDesc.fRotation = { 0.0f, 0.1f, 0.0f, 1.0f };

        EnvironmentDesc.iPassNum = { (_uint)m_iPassIndex };

        switch (m_iGroundObjectListIndex)
        {
        case 0:
            EnvironmentDesc.ObjectName = m_strGroundObjectNamess[m_iGroundModelIndex];
            break;
        case 1:
            EnvironmentDesc.ObjectName = m_strGorundobjectClothesNames[m_iGroundModelIndex];
            break;
        case 2:
            EnvironmentDesc.ObjectName = m_strGroundObjectTreenames[m_iGroundModelIndex];
            break;
        case 3:
            EnvironmentDesc.ObjectName = m_strGroundObjectCurbNames[m_iGroundModelIndex];
            break;

        case 4:
            EnvironmentDesc.ObjectName = m_strGroundObjectFenceNames[m_iGroundModelIndex];
            break;

        case 5:
            EnvironmentDesc.ObjectName = m_strGroundObjectRocknames[m_iGroundModelIndex];
            break;

        case 6:
            EnvironmentDesc.ObjectName = m_strGorundobjectRailingNames[m_iGroundModelIndex];
            break;

        case 7:
            EnvironmentDesc.ObjectName = m_strGroundObjectCircusBalloonNames[m_iGroundModelIndex];
            break;

        case 8:
            EnvironmentDesc.ObjectName = m_strGroundObjectCircusHangsNames[m_iGroundModelIndex];
            break;

        case 9:
            EnvironmentDesc.ObjectName = m_strGroundObjectCircusTreeNames[m_iGroundModelIndex];
            break;
        default:
            return;

        }
        EnvironmentDesc.fSpace = m_fSpacingValue;
        EnvironmentDesc.isBasicMode = m_iModeSelected;
        EnvironmentDesc.vecBoxSize = m_vecBoxSize;

        m_vecBoxSize.push_back(1);
        EnvironmentDesc.iBoxSize = m_vecBoxSize.back();

        if (m_iModeSelected == false)
        {
            D3D11_MAPPED_SUBRESOURCE tagSubResource = {};
            m_pContext->Map(m_pTerrainBuffer->Get_VB_Buffer(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &tagSubResource);
            m_pVertices = static_cast<VTXNORTEX*>(tagSubResource.pData);

            XMMATRIX matWorld = XMLoadFloat4x4(m_pTerrain->Get_Transfrom()->Get_WorldMatrix_Ptr());
            XMMATRIX matWorldInv = XMMatrixInverse(nullptr, matWorld);

            XMVECTOR vPickPosWorld = XMLoadFloat3(&m_fPickPos);
            XMVECTOR vPickPosLocal = XMVector3TransformCoord(vPickPosWorld, matWorldInv);

            XMFLOAT3 fPickPosLocal;
            XMStoreFloat3(&fPickPosLocal, vPickPosLocal);

            XMFLOAT3 fPickPosWorld;
            XMStoreFloat3(&fPickPosWorld, vPickPosWorld);

            for (_float i = -m_fInstallRange; i <= m_fInstallRange; i += m_fSpacingValue)
            {
                for (_float j = -m_fInstallRange; j <= m_fInstallRange; j += m_fSpacingValue)
                {
                    _float fLocalX = fPickPosLocal.x + j;
                    _float fLocalZ = fPickPosLocal.z + i;
                    _uint iIndex = static_cast<_uint>(fLocalZ) * m_pTerrainBuffer->Get_NumVerticesX() + static_cast<_uint>(fLocalX);

                    if (iIndex < 0 || iIndex >= m_pTerrainBuffer->Get_NumVerticesX() * m_pTerrainBuffer->Get_NumVerticesZ())
                        continue;

                    XMFLOAT3 terrainLocalPos = m_pVertices[iIndex].vPosition;
                    XMVECTOR terrainWorldPos = XMVector3TransformCoord(XMLoadFloat3(&terrainLocalPos), matWorld);

                    XMFLOAT3 fTerrainWorldPos;
                    XMStoreFloat3(&fTerrainWorldPos, terrainWorldPos);

                    EnvironmentDesc.vecInstancePosition.push_back(fTerrainWorldPos);
                    m_vecInstancedGroundObjectPos.push_back(fTerrainWorldPos);

                    EnvironmentDesc.vecInstanceScale.push_back(EnvironmentDesc.fScaling);
                    m_vecInstancedGroundObjectScale.push_back(EnvironmentDesc.fScaling);

                    EnvironmentDesc.vecInstanceRotation.push_back(EnvironmentDesc.fRotation);
                    m_vecInstancedGroundObjectRotation.push_back(EnvironmentDesc.fRotation);

                    EnvironmentDesc.vecBoxSize.push_back(EnvironmentDesc.iBoxSize);
                    m_vecBoxSize.push_back(EnvironmentDesc.iBoxSize);

                    m_iInstancingModelSize++;
                }
            }
            m_pContext->Unmap(m_pTerrainBuffer->Get_VB_Buffer(), 0);
        }
        else
        {
            EnvironmentDesc.fInstanceCount = m_fInstanceCount;

            XMFLOAT3 terrainPos = m_fPickPos;
            for (_uint i = 0; i < m_fInstanceCount; ++i)
            {
                EnvironmentDesc.vecInstancePosition.push_back(terrainPos);
                m_vecInstancedGroundObjectPos.push_back(terrainPos);

                EnvironmentDesc.vecInstanceScale.push_back(EnvironmentDesc.fScaling);
                m_vecInstancedGroundObjectScale.push_back(EnvironmentDesc.fScaling);

                EnvironmentDesc.vecInstanceRotation.push_back(EnvironmentDesc.fRotation);
                m_vecInstancedGroundObjectRotation.push_back(EnvironmentDesc.fRotation);

                EnvironmentDesc.vecBoxSize.push_back(EnvironmentDesc.iBoxSize);
                m_vecBoxSize.push_back(EnvironmentDesc.iBoxSize);
            }

            m_iInstancingModelSize++;
        }

        CEnvironmentObject* pObject = reinterpret_cast<CEnvironmentObject*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_GroundObject"), LEVEL_GAMEPLAY, TEXT("Layer_GroundObject"), &EnvironmentDesc));
        if (pObject != nullptr)
        {
            m_EnvironmentObjects.push_back(pObject);
        }
    }
}

void CLevel_GamePlay::Setting_GroundObjectList()
{
    if (ImGui::CollapsingHeader("Ground Model List"))
    {
        m_iGroundObjectListIndex = 0;

        const char* szItems[] = { "Ground Model List" };

        static int iCurrentItem = 0;
        ImGui::Combo("##5", &iCurrentItem, szItems, IM_ARRAYSIZE(szItems));

        for (_uint i = 0; i < 26; ++i)
        {
            _uint  iTextureIndex = iCurrentItem * 3 + i;
            m_iRandGroundModelIndex = rand() % (iTextureIndex + 1);

            if (iTextureIndex < m_vecGroundModelSRVs.size())
            {
                if (ImGui::ImageButton(("GroundModel" + to_string(iTextureIndex)).c_str(), (ImTextureID)m_vecGroundModelSRVs[iTextureIndex], ImVec2(50.0f, 50.0f)))
                {
                    m_iGroundModelIndex = iTextureIndex;

                    CEnvironmentObject::ENVIRONMENT_OBJECT_DESC ObjectDesc = {};
                    ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
                    ObjectDesc.fFrustumRadius = m_fFrustumRadius;
                    ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
                    ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f, 0.f };
                    ObjectDesc.ObjectName = m_strGroundObjectNamess[m_iGroundModelIndex];
                }

                if ((i + 1) % 4 != 0)
                {
                    ImGui::SameLine();
                }
            }
        }
    }
    else if (ImGui::CollapsingHeader("Clothes Model List"))
    {
        m_iGroundObjectListIndex = 1;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGorundobjectClothesNames, IM_ARRAYSIZE(m_strGorundobjectClothesNames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CEnvironmentObject::ENVIRONMENT_OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f, 0.f };
            ObjectDesc.ObjectName = m_strGorundobjectClothesNames[m_iGroundModelIndex];

        }
    }
    else if (ImGui::CollapsingHeader("Curb Clothes Model List"))
    {
        m_iGroundObjectListIndex = 3;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectCurbNames, IM_ARRAYSIZE(m_strGroundObjectCurbNames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CEnvironmentObject::ENVIRONMENT_OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f, 0.f };
            ObjectDesc.ObjectName = m_strGroundObjectCurbNames[m_iGroundModelIndex];

        }
    }
    else  if (ImGui::CollapsingHeader("Fence Clothes Model List"))
    {
        m_iGroundObjectListIndex = 4;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectFenceNames, IM_ARRAYSIZE(m_strGroundObjectFenceNames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CEnvironmentObject::ENVIRONMENT_OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f, 0.f };
            ObjectDesc.ObjectName = m_strGroundObjectFenceNames[m_iGroundModelIndex];

        }

    }
    else   if (ImGui::CollapsingHeader("Rock Model List"))
    {
        m_iGroundObjectListIndex = 5;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectRocknames, IM_ARRAYSIZE(m_strGroundObjectRocknames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CEnvironmentObject::ENVIRONMENT_OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f, 0.f };
            ObjectDesc.ObjectName = m_strGroundObjectRocknames[m_iGroundModelIndex];

        }
    }
    else if (ImGui::CollapsingHeader("Tree Model List"))
    {
        m_iGroundObjectListIndex = 2;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectTreenames, IM_ARRAYSIZE(m_strGroundObjectTreenames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectTreenames[m_iGroundModelIndex];

        }
    }
    else   if (ImGui::CollapsingHeader("Railing Model List"))
    {
        m_iGroundObjectListIndex = 6;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGorundobjectRailingNames, IM_ARRAYSIZE(m_strGorundobjectRailingNames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CEnvironmentObject::ENVIRONMENT_OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f, 0.f };
            ObjectDesc.ObjectName = m_strGorundobjectRailingNames[m_iGroundModelIndex];

        }
    }

    else if (ImGui::CollapsingHeader("Balloon Model List"))
    {
        m_iGroundObjectListIndex = 7;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectCircusBalloonNames, IM_ARRAYSIZE(m_strGroundObjectCircusBalloonNames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectCircusBalloonNames[m_iGroundModelIndex];

        }

        }

    else if (ImGui::CollapsingHeader("Hangs List"))
    {
        m_iGroundObjectListIndex = 8;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectCircusHangsNames, IM_ARRAYSIZE(m_strGroundObjectCircusHangsNames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectCircusHangsNames[m_iGroundModelIndex];

        }

        }

    else if (ImGui::CollapsingHeader("Circus Tree List"))
    {
        m_iGroundObjectListIndex = 9;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectCircusTreeNames, IM_ARRAYSIZE(m_strGroundObjectCircusTreeNames)))
        {
            m_iGroundModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectCircusTreeNames[m_iGroundModelIndex];

        }
    }
}

void CLevel_GamePlay::Raising_Terrain(_float _fTimeDelta, _bool _bUp)
{
    XMMATRIX matWorld = XMLoadFloat4x4(m_pTerrain->Get_Transfrom()->Get_WorldMatrix_Ptr());
    XMMATRIX matWorldInv = XMMatrixInverse(nullptr, matWorld);

    XMVECTOR vPickPosWorld = XMLoadFloat3(&m_fPickPos);
    XMVECTOR vPickPosLocal = XMVector3TransformCoord(vPickPosWorld, matWorldInv);

    XMFLOAT3 fPickPosLocal;
    XMStoreFloat3(&fPickPosLocal, vPickPosLocal);

    XMFLOAT3 fPickPosWorld;
    XMStoreFloat3(&fPickPosWorld, vPickPosWorld);

    D3D11_MAPPED_SUBRESOURCE tagSubResource = {};
    m_pContext->Map(m_pTerrainBuffer->Get_VB_Buffer(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &tagSubResource);
    m_pVertices = static_cast<VTXNORTEX*>(tagSubResource.pData);

    for (_float i = -m_fInstallRange; i <= m_fInstallRange; i += m_fSpacingValue)
    {
        for (_float j = -m_fInstallRange; j <= m_fInstallRange; j += m_fSpacingValue)
        {
            _float fLocalX = fPickPosLocal.x + j;
            _float fLocalZ = fPickPosLocal.z + i;
            _uint iIndex = static_cast<_uint>(fLocalZ) * m_pTerrainBuffer->Get_NumVerticesX() + static_cast<_uint>(fLocalX);

            if (iIndex < 0 || iIndex >= m_pTerrainBuffer->Get_NumVerticesX() * m_pTerrainBuffer->Get_NumVerticesZ())
                continue;

            if (_bUp)
                m_pVertices[iIndex].vPosition.y += 0.01f;
            else
                m_pVertices[iIndex].vPosition.y -= 0.01f;
        }
    }
    m_pContext->Unmap(m_pTerrainBuffer->Get_VB_Buffer(), 0);

    XMVECTOR* pVertexPos = m_pTerrainBuffer->Get_VertexPos();

    for (_float i = -m_fInstallRange; i <= m_fInstallRange; i += m_fSpacingValue)
    {
        for (_float j = -m_fInstallRange; j <= m_fInstallRange; j += m_fSpacingValue)
        {
            _float fLocalX = fPickPosLocal.x + j;
            _float fLocalZ = fPickPosLocal.z + i;
            _uint iIndex = static_cast<_uint>(fLocalZ) * m_pTerrainBuffer->Get_NumVerticesX() + static_cast<_uint>(fLocalX);

            if (iIndex < 0 || iIndex >= m_pTerrainBuffer->Get_NumVerticesX() * m_pTerrainBuffer->Get_NumVerticesZ())
                continue;

            pVertexPos[iIndex] = XMLoadFloat3(&m_pVertices[iIndex].vPosition);
        }
    }
}

void CLevel_GamePlay::Set_Terrain_Height(_float _fHeight)
{
    XMMATRIX matWorld = XMLoadFloat4x4(m_pTerrain->Get_Transfrom()->Get_WorldMatrix_Ptr());
    XMMATRIX matWorldInv = XMMatrixInverse(nullptr, matWorld);

    XMVECTOR vPickPosWorld = XMLoadFloat3(&m_fPickPos);
    XMVECTOR vPickPosLocal = XMVector3TransformCoord(vPickPosWorld, matWorldInv);

    XMFLOAT3 fPickPosLocal;
    XMStoreFloat3(&fPickPosLocal, vPickPosLocal);

    XMFLOAT3 fPickPosWorld;
    XMStoreFloat3(&fPickPosWorld, vPickPosWorld);

    D3D11_MAPPED_SUBRESOURCE tagSubResource = {};
    m_pContext->Map(m_pTerrainBuffer->Get_VB_Buffer(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &tagSubResource);
    m_pVertices = static_cast<VTXNORTEX*>(tagSubResource.pData);

    for (_float i = -m_fInstallRange; i <= m_fInstallRange; i += m_fSpacingValue)
    {
        for (_float j = -m_fInstallRange; j <= m_fInstallRange; j += m_fSpacingValue)
        {
            _float fLocalX = fPickPosLocal.x + j;
            _float fLocalZ = fPickPosLocal.z + i;
            _uint iIndex = static_cast<_uint>(fLocalZ) * m_pTerrainBuffer->Get_NumVerticesX() + static_cast<_uint>(fLocalX);

            if (iIndex < 0 || iIndex >= m_pTerrainBuffer->Get_NumVerticesX() * m_pTerrainBuffer->Get_NumVerticesZ())
                continue;

            m_pVertices[iIndex].vPosition.y = _fHeight;
        }
    }
    m_pContext->Unmap(m_pTerrainBuffer->Get_VB_Buffer(), 0);

    XMVECTOR* pVertexPos = m_pTerrainBuffer->Get_VertexPos();

    for (_float i = -m_fInstallRange; i <= m_fInstallRange; i += m_fSpacingValue)
    {
        for (_float j = -m_fInstallRange; j <= m_fInstallRange; j += m_fSpacingValue)
        {
            _float fLocalX = fPickPosLocal.x + j;
            _float fLocalZ = fPickPosLocal.z + i;
            _uint iIndex = static_cast<_uint>(fLocalZ) * m_pTerrainBuffer->Get_NumVerticesX() + static_cast<_uint>(fLocalX);

            if (iIndex < 0 || iIndex >= m_pTerrainBuffer->Get_NumVerticesX() * m_pTerrainBuffer->Get_NumVerticesZ())
                continue;

            pVertexPos[iIndex] = XMLoadFloat3(&m_pVertices[iIndex].vPosition);
        }
    }
}

void CLevel_GamePlay::Add_TriggerObjects()
{
    if (m_iTempColliderListIndex == -1)
        return;

    CTempCollider::TC_DESC Desc{};

    Desc.fPosition = { m_fObjectPos[0], m_fObjectPos[1], m_fObjectPos[2], 1.f };
    Desc.fScale = { m_fTriggerScale[0], m_fTriggerScale[1], m_fTriggerScale[2] };
    Desc.fRotation = { m_fObjectRotation[0], m_fObjectRotation[1] , m_fObjectRotation[2] };

    CTempCollider* pTempCollider = reinterpret_cast<CTempCollider*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_TempColliderObject"), LEVEL_GAMEPLAY, TEXT("Layer_TriggerObject"), &Desc));

    if (pTempCollider != nullptr)
        m_vecTempColliderObjects.push_back(pTempCollider);
}

void CLevel_GamePlay::Setting_TriggerObjects()
{
    if (ImGui::CollapsingHeader("Trigger List"))
    {
        m_iNonMoveObjectListIndex = 1;

        const char* szItems[] = { "Trigger List" };

        static int iCurrentItem = 0;
        ImGui::Combo("##3", &iCurrentItem, szItems, IM_ARRAYSIZE(szItems));

        for (_uint i = 0; i < 2; ++i)
        {
            _uint  iTextureIndex = iCurrentItem * 3 + i;

            if (iTextureIndex < m_vecTriggerObjectSRVs.size())
            {
                if (ImGui::ImageButton(("Trigger Object" + to_string(iTextureIndex)).c_str(), (ImTextureID)m_vecTriggerObjectSRVs[iTextureIndex], ImVec2(50.0f, 50.0f)))
                {
                    m_iTempColliderListIndex = iTextureIndex;
                }

                if ((i + 1) % 4 != 0)
                {
                    ImGui::SameLine();
                }
            }
        }
    }
    else if (ImGui::CollapsingHeader("Grave_Stone Model List"))
    {
        m_iNonMoveObjectListIndex = 2;

        static int iCurrentItem = 0;
        if (ImGui::Combo("##3", &iCurrentItem, m_strGroundObjectGraveStoneNames, IM_ARRAYSIZE(m_strGroundObjectGraveStoneNames)))
        {
            m_iNonAnimModelIndex = iCurrentItem;

            CObject::OBJECT_DESC ObjectDesc = {};
            ObjectDesc.fPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            ObjectDesc.fFrustumRadius = m_fFrustumRadius;
            ObjectDesc.fScaling = { 0.0f, 0.0f, 0.0f };
            ObjectDesc.fRotation = { 0.0f, 0.1f, 0.0f };
            ObjectDesc.ObjectName = m_strGroundObjectGraveStoneNames[m_iNonAnimModelIndex];
        }
    }
}

void CLevel_GamePlay::Delete_TriggerObjects()
{
    if (m_vecTempColliderObjects.empty())
        return;

    _float3 vPickedPos;
    if (!m_pGameInstance->Compute_PickPos(&vPickedPos))
        return;

    _float fMinDistance = FLT_MAX;
    auto closestIter = m_vecTempColliderObjects.end();

    for (auto iter = m_vecTempColliderObjects.begin(); iter != m_vecTempColliderObjects.end(); ++iter)
    {
        CTempCollider* pCollider = *iter;
        if (pCollider == nullptr)
            continue;

        _float4 vColliderPos = pCollider->Get_TempColliderPosition();

        _float fDistance = sqrtf(
            pow(vColliderPos.x - vPickedPos.x, 2) +
            pow(vColliderPos.y - vPickedPos.y, 2) +
            pow(vColliderPos.z - vPickedPos.z, 2)
        );

        if (fDistance < fMinDistance)
        {
            fMinDistance = fDistance;
            closestIter = iter;
        }
    }

    if (closestIter != m_vecTempColliderObjects.end() && fMinDistance < 1.0f)
    {
        CTempCollider* pClosestCollider = *closestIter;
        m_pGameInstance->Add_DeadObject(TEXT("Layer_TriggerObject"), pClosestCollider);  
        m_vecTempColliderObjects.erase(closestIter); 
    }
}

void CLevel_GamePlay::Update_TriggerObjects()
{
    if (m_vecTempColliderObjects.empty())
        return;

    ImGui::Begin("Trigger Object Editor");

    static int selectedIndex = -1; 
    static _float3 scale = { 1.0f, 1.0f, 1.0f }; 

    if (ImGui::CollapsingHeader("Trigger List"))
    {
        for (int i = 0; i < m_vecTempColliderObjects.size(); ++i)
        {
            string label = "Trigger " + to_string(i);
            if (ImGui::Selectable(label.c_str(), selectedIndex == i))
            {
                selectedIndex = i;
                scale = m_vecTempColliderObjects[i]->Get_TempColliderScale();
            }
        }
    }

    if (selectedIndex != -1 && selectedIndex < m_vecTempColliderObjects.size())
    {
        ImGui::Text("Adjust Scale");
        if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0.1f, 10.0f))
        {
            m_vecTempColliderObjects[selectedIndex]->Set_TempColliderScale(scale);
        }
    }

    ImGuiIO IO = ImGui::GetIO();

    if (m_bTriggerObjectMenuSelected)
    {
        if (!IO.WantCaptureMouse)
        {
            if (m_pGameInstance->isMouseEnter(DIM_RB)) 
            {
                Delete_TriggerObjects();
            }
        }
    }

    ImGui::End();
}

void CLevel_GamePlay::Update_InstanceObjects()
{
    ImGui::Begin("Instanced Ground Objects", NULL, ImGuiWindowFlags_MenuBar);
    {
        if (m_EnvironmentObjects.empty())
        {
            ImGui::End();
            return;
        }

        if (m_vecBoxSize.size() != m_EnvironmentObjects.size())
        {
            m_vecBoxSize.resize(m_EnvironmentObjects.size(), 1);
        }

        for (_uint iGroupIndex = 0; iGroupIndex < m_EnvironmentObjects.size(); ++iGroupIndex)
        {
            auto& pEnvironmentObject = m_EnvironmentObjects[iGroupIndex];
            vector<VTX_MODEL_INSTANCE>& vecInstanceData = pEnvironmentObject->Get_ModelInstanceVector();
            CGroundObject* pGroundObject = dynamic_cast<CGroundObject*>(pEnvironmentObject);

            if (ImGui::CollapsingHeader(("InstanceGroup " + to_string(iGroupIndex)).c_str()))
            {
                for (_uint i = 0; i < vecInstanceData.size(); ++i)
                {
                    char label[32];
                    sprintf_s(label, "Instance %d##%p", i, pGroundObject);

                    if (ImGui::Selectable(label, m_pSelectedInstancedObject == pGroundObject && m_iSelectedInstanceIndex == i))
                    {
                        m_pSelectedInstancedObject = pGroundObject;
                        m_iSelectedInstanceIndex = i;
                        m_bDraggingInstanceModel = true;
                    }

                    if (m_pSelectedInstancedObject == pGroundObject && m_iSelectedInstanceIndex == i)
                    {
                        _bool bInstanceTransformInfoUpdated = false;

                        //_uint iSize = vecInstanceData.size();

                        //m_vecInstancedGroundObjectPos.resize(iSize);
                        //m_vecInstancedGroundObjectScale.resize(iSize);
                        //m_vecInstancedGroundObjectRotation.resize(iSize);

                        //_matrix matInstance = {};
                        //matInstance.r[0] = XMLoadFloat4(&vecInstanceData[m_iSelectedInstanceIndex].InstanceMatrix[0]);
                        //matInstance.r[1] = XMLoadFloat4(&vecInstanceData[m_iSelectedInstanceIndex].InstanceMatrix[1]);
                        //matInstance.r[2] = XMLoadFloat4(&vecInstanceData[m_iSelectedInstanceIndex].InstanceMatrix[2]);
                        //matInstance.r[3] = XMLoadFloat4(&vecInstanceData[m_iSelectedInstanceIndex].InstanceMatrix[3]);

                        //XMVECTOR scale, rotation, translation;
                        //XMMatrixDecompose(&scale, &rotation, &translation, matInstance);

                        //_vector vPrePos, vPreScale, vPreRot;
                        //vPrePos = XMLoadFloat3(&m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex]);
                        //vPreScale = XMLoadFloat3(&m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex]);
                        //vPreRot = XMLoadFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]);

                        //_vector vTest = XMVector3Length(rotation);

                  /*
                        if (!XMVector3IsNaN(rotation) && !isnan(XMVectorGetX(vTest)) && !(XMVectorGetX(vTest) > 10000.f)) 
                        {
                            XMStoreFloat3(&m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex], translation);
                            XMStoreFloat3(&m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex], scale);
                            XMStoreFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex], rotation);
                        }
                        else
                        {
                            XMStoreFloat3(&m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex], vPrePos);
                            XMStoreFloat3(&m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex], vPreScale);
                            XMStoreFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex], vPreRot);
                        }*/
                        pEnvironmentObject->Get_Transforms(m_vecInstancedGroundObjectScale, m_vecInstancedGroundObjectPos, m_vecInstancedGroundObjectRotation);


                        if (m_pGameInstance->isKeyEnter(DIK_Z))
                        {
                            XMVECTOR vCurrentPosition = XMLoadFloat3(&m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex]);
                            XMVECTOR vCurrentScale = XMLoadFloat3(&m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex]);
                            XMVECTOR vCurrentRotation = XMLoadFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]);

                            vCurrentRotation.m128_f32[2] *= -1.f;

                            XMVECTOR vAdditionalRotation = XMQuaternionRotationAxis(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(180.0f));

                            XMVECTOR vNewRotation = XMQuaternionMultiply(vAdditionalRotation, vCurrentRotation);

                            XMStoreFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex], vNewRotation);

                            m_pSelectedInstancedObject->Update_InstanceBuffer
                            (
                                m_iSelectedInstanceIndex,
                                m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex],
                                m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex],
                                m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]
                            );
                        }
                        else if (m_pGameInstance->isKeyEnter(DIK_X))
                        {
                            XMVECTOR vCurrentPosition = XMLoadFloat3(&m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex]);
                            XMVECTOR vCurrentScale = XMLoadFloat3(&m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex]);
                            XMVECTOR vCurrentRotation = XMLoadFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]);

                            XMVECTOR quaternion = XMQuaternionRotationAxis(XMVectorSet(0, 1.f, 0, 0), XM_PI);

                            XMStoreFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex], XMQuaternionMultiply(vCurrentRotation, quaternion));

                            /*    XMStoreFloat3(&m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex], vChangedScale);*/

                            m_pSelectedInstancedObject->Update_InstanceBuffer
                            (
                                m_iSelectedInstanceIndex,
                                m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex],
                                m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex],
                                m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]
                            );
                        }
                        else
                        {
                            if (ImGui::DragFloat3(("Position##" + to_string(i)).c_str(), (float*)&m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex], 0.1f))
                                bInstanceTransformInfoUpdated = true;
                            if (ImGui::DragFloat3(("Scale##" + to_string(i)).c_str(), (float*)&m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex], 0.1f, 0.1f, 10.0f))
                                bInstanceTransformInfoUpdated = true;
                            if (ImGui::DragFloat4(("Rotation##" + to_string(i)).c_str(), (float*)&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex], 0.1f, -1.f, 1.f))
                                bInstanceTransformInfoUpdated = true;

                        }
                        if (bInstanceTransformInfoUpdated)
                        {
                        
                            m_pSelectedInstancedObject->Update_InstanceBuffer
                            (
                                m_iSelectedInstanceIndex,
                                m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex],
                                m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex],
                                m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]
                            );
                        }
                    }
                }
            }
            char Name[32];
            sprintf_s(Name, "Box Scale %d", iGroupIndex);
            if (ImGui::SliderInt(Name, &m_vecBoxSize[iGroupIndex], 1, 80))
            {
                m_bDraggingInstanceModel = false;
                pGroundObject->Set_BoxSize(m_vecBoxSize[iGroupIndex]);
            }
            ImGui::Separator();
        }

        if (m_bGrondMenuSelected)
        {
            if (m_pGameInstance->isMouseEnter(DIM_RB))
            {
                _float3 vPickedPos;
                if (m_pGameInstance->Compute_PickPos(&vPickedPos))
                {
                    _uint iClosestInstanceIndex = -1;
                    _float fMinDistance = FLT_MAX;
                    CGroundObject* pClosestObject = nullptr;

                    for (auto& pEnvironmentObject : m_EnvironmentObjects)
                    {
                        CGroundObject* pGroundObject = dynamic_cast<CGroundObject*>(pEnvironmentObject);
                        if (!pEnvironmentObject)
                            continue;

                        for (_uint i = 0; i < pGroundObject->Get_InstanceCount(); ++i)
                        {
                            XMFLOAT3 fInstancePos = pGroundObject->Get_InstancePosition()[i];

                            _float fDistance = sqrtf(
                                pow(fInstancePos.x - vPickedPos.x, 2) +
                                pow(fInstancePos.y - vPickedPos.y, 2) +
                                pow(fInstancePos.z - vPickedPos.z, 2)
                            );

                            if (fDistance < fMinDistance)
                            {
                                fMinDistance = fDistance;
                                iClosestInstanceIndex = i;
                                pClosestObject = pGroundObject;
                            }
                        }
                    }

                    if (nullptr != pClosestObject && iClosestInstanceIndex != -1)
                        pClosestObject->Delete_InstanceObject(iClosestInstanceIndex);
                }
            }
        }

    }
    ImGui::End();
}

void CLevel_GamePlay::Update_InstanceMove()
{
    ImGuiIO IO = ImGui::GetIO();

    if (!m_pSelectedInstancedObject || m_iSelectedInstanceIndex < 0 /*|| m_bGrondMenuSelected || m_bDraggingInstanceModel*/)
        return;

    _float3 vMousePos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))), m_pTerrain->Get_Transfrom());

    if (m_bDraggingInstanceModel)
    {
        m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex] = vMousePos;

        XMVECTOR vCurrentQuaternion = XMLoadFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]);

        if (m_pGameInstance->Get_DIKeyState(DIK_E) & 0x80)
        {
            XMVECTOR vValueQuaternion = XMQuaternionRotationAxis(XMVectorSet(0, 1, 0, 0), 0.07f);
            vCurrentQuaternion = XMQuaternionMultiply(vCurrentQuaternion, vValueQuaternion);
        }
        else if (m_pGameInstance->Get_DIKeyState(DIK_R) & 0x80)
        {
            XMVECTOR vValueQuaternion = XMQuaternionRotationAxis(XMVectorSet(0, 1, 0, 0), -0.07f);
            vCurrentQuaternion = XMQuaternionMultiply(vCurrentQuaternion, vValueQuaternion);
        }

        vCurrentQuaternion = XMQuaternionNormalize(vCurrentQuaternion);

        XMStoreFloat4(&m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex], vCurrentQuaternion);

        m_pSelectedInstancedObject->Update_InstanceBuffer(
            m_iSelectedInstanceIndex,
            m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex],
            m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex],
            m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]
        );

        if (m_pGameInstance->Get_DIKeyState(DIK_T) & 0x80)
        {
            m_bDraggingInstanceModel = false;
            m_pSelectedInstancedObject->Update_InstanceBuffer
            (
                m_iSelectedInstanceIndex,
                m_vecInstancedGroundObjectPos[m_iSelectedInstanceIndex],
                m_vecInstancedGroundObjectScale[m_iSelectedInstanceIndex],
                m_vecInstancedGroundObjectRotation[m_iSelectedInstanceIndex]
            );

            m_pSelectedInstancedObject = nullptr;
            m_iSelectedInstanceIndex = -1;
        }
    }
}


XMFLOAT3 CLevel_GamePlay::Compute_ClosestInstanceModelPoint(const XMFLOAT3& _fClickPos)
{
    const float PICK_RADIUS = 1.0f;
    _float fMinDistance = FLT_MAX;
    XMFLOAT3 vSelectedCordinate = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

    for (auto& fInstanceModelPos : m_vecInstancedGroundObjectPos)
    {
        XMFLOAT3 vCordinate = fInstanceModelPos;
        _float fDistance = Compute_Cell_Distance(_fClickPos, vCordinate);

        if (fDistance < PICK_RADIUS && fDistance < fMinDistance)
        {
            fMinDistance = fDistance;
            vSelectedCordinate = vCordinate;
        }
    }
    return vSelectedCordinate;
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
    DWORD dwByte2 = 0;

    // 일반 오브젝트
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
            WriteFile(hFile, &Info.iPassNum, sizeof(_uint), &dwByte, nullptr);
        }
    }

    // 인스턴스  객체 저장
    _uint iEnvironmentObjectCount = static_cast<_uint>(m_EnvironmentObjects.size());
    WriteFile(hFile, &iEnvironmentObjectCount, sizeof(_uint), &dwByte2, nullptr);

    for (_uint iGroupIndex = 0; iGroupIndex < m_EnvironmentObjects.size(); ++iGroupIndex)
    {
        auto& pEnvironmentObject = m_EnvironmentObjects[iGroupIndex];
        CEnvironmentObject::EN_OBJECT_INFO EnvironmentInfo = pEnvironmentObject->Get_EnvironmentObjectInfo();

        WriteFile(hFile, EnvironmentInfo.szName, MAX_PATH, &dwByte2, nullptr);
        WriteFile(hFile, &EnvironmentInfo.iPassNum, sizeof(_uint), &dwByte, nullptr);

        vector<VTX_MODEL_INSTANCE> vecInstanceData = pEnvironmentObject->Get_ModelInstanceVector();
        _uint iInstanceCount = static_cast<_uint>(vecInstanceData.size());

        WriteFile(hFile, &iInstanceCount, sizeof(_uint), &dwByte2, nullptr);
        for (size_t k = 0; k < iInstanceCount; ++k)
        {
            WriteFile(hFile, &vecInstanceData[k].InstanceMatrix, sizeof(XMFLOAT4X4), &dwByte2, nullptr);

            XMFLOAT4X4 matrix;
            memcpy(&matrix, vecInstanceData[k].InstanceMatrix, sizeof(XMFLOAT4X4));

            XMMATRIX matWorld = XMLoadFloat4x4(&matrix);

            XMVECTOR scale, rotation, translation;
            XMMatrixDecompose(&scale, &rotation, &translation, matWorld);

            XMFLOAT4 quaternion;
            XMStoreFloat4(&quaternion, rotation);

            WriteFile(hFile, &quaternion, sizeof(XMFLOAT4), &dwByte2, nullptr);
            //WriteFile(hFile, &m_vecBoxSize[iGroupIndex], sizeof(_int), &dwByte2, nullptr);

            _int iBoxSize = m_vecBoxSize[iGroupIndex];
            WriteFile(hFile, &iBoxSize, sizeof(_int), &dwByte2, nullptr);
        }
    }

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

    //for (auto& pObject : m_Objects)
    //{
    //    m_pGameInstance->Add_DeadObject(L"Layer_Object", pObject);
    //}
    //m_Objects.clear();

    for (auto& pEnvironmentObject : m_EnvironmentObjects)
    {
        m_pGameInstance->Add_DeadObject(L"Layer_GroundObject", pEnvironmentObject);
    }
    m_EnvironmentObjects.clear();
    m_vecInstancedGroundObjectPos.clear();
    m_vecInstancedGroundObjectScale.clear();
    m_vecInstancedGroundObjectRotation.clear();

    DWORD dwByte = 0;
    DWORD dwByte2 = 0;

    _uint iSize = 0;
    _uint iSize2 = 0;

    // 일반 오브젝트
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
        ReadFile(hFile, &Desc.iPassNum, sizeof(_uint), &dwByte, nullptr);

        Desc.ObjectName = szLoadName;

        CObject* pObject = reinterpret_cast<CObject*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_NonMoveObject"), LEVEL_GAMEPLAY, TEXT("Layer_Object"), &Desc));

        if (pObject != nullptr)
            m_Objects.push_back(pObject);
    }

    ReadFile(hFile, &iSize2, sizeof(_uint), &dwByte2, nullptr);
    vector<_int> vecBoxSize;
    _int vectorBoxSize = {};

    for (_uint i = 0; i < iSize2; ++i)
    {
        CEnvironmentObject::ENVIRONMENT_OBJECT_DESC Desc = {};
        _char szLoadName[MAX_PATH] = {};

        ReadFile(hFile, szLoadName, MAX_PATH, &dwByte2, nullptr);
        ReadFile(hFile, &Desc.iPassNum, sizeof(_uint), &dwByte, nullptr);
        Desc.ObjectName = szLoadName;

        _uint iInstanceCount = 0;
        ReadFile(hFile, &iInstanceCount, sizeof(_uint), &dwByte2, nullptr);

        vector<VTX_MODEL_INSTANCE> vecInstanceData(iInstanceCount);
        vector<XMFLOAT3> vecInstancePosition(iInstanceCount);
        vector<XMFLOAT3> vecInstanceScale(iInstanceCount);
        vector<XMFLOAT4> vecInstanceRotation(iInstanceCount);

        vectorBoxSize++;
        for (_uint k = 0; k < iInstanceCount; ++k)
        {
            ReadFile(hFile, &vecInstanceData[k].InstanceMatrix, sizeof(XMFLOAT4X4), &dwByte2, nullptr);

            XMFLOAT4X4 matrix;
            memcpy(&matrix, vecInstanceData[k].InstanceMatrix, sizeof(XMFLOAT4X4));

            XMMATRIX matWorld = XMLoadFloat4x4(&matrix);

            XMVECTOR scale, rotation, translation;
            XMMatrixDecompose(&scale, &rotation, &translation, matWorld);

            XMStoreFloat3(&vecInstancePosition[k], translation);
            XMStoreFloat3(&vecInstanceScale[k], scale);

            XMFLOAT4 quaternion;
            ReadFile(hFile, &quaternion, sizeof(XMFLOAT4), &dwByte2, nullptr);
            rotation = XMLoadFloat4(&quaternion);

            vecInstanceRotation[k] = quaternion;

            vecBoxSize.resize(vectorBoxSize);
            ReadFile(hFile, &vecBoxSize[i], sizeof(_int), &dwByte2, nullptr);
        }

        Desc.vecInstancePosition = vecInstancePosition;
        Desc.vecInstanceScale = vecInstanceScale;
        Desc.vecInstanceRotation = vecInstanceRotation;
        Desc.vecBoxSize = vecBoxSize;/*
        m_vecInstancedGroundObjectPos = vecInstancePosition;
        m_vecInstancedGroundObjectScale = vecInstanceScale;
        m_vecInstancedGroundObjectRotation = vecInstanceRotation;*/


        CEnvironmentObject* pEnvironment = reinterpret_cast<CEnvironmentObject*>(
            m_pGameInstance->Add_GameObject_To_Layer_Take(
                LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_Object_GroundObject"),
                LEVEL_GAMEPLAY, TEXT("Layer_GroundObject"), &Desc)
            );

        if (pEnvironment != nullptr)
        {
            pEnvironment->Set_ModelInstanceVector(vecInstanceData);
            m_EnvironmentObjects.push_back(pEnvironment);

            m_vecInstancedGroundObjectPos.insert(m_vecInstancedGroundObjectPos.end(), vecInstancePosition.begin(), vecInstancePosition.end());
            m_vecInstancedGroundObjectScale.insert(m_vecInstancedGroundObjectScale.end(), vecInstanceScale.begin(), vecInstanceScale.end());
            m_vecInstancedGroundObjectRotation.insert(m_vecInstancedGroundObjectRotation.end(), vecInstanceRotation.begin(), vecInstanceRotation.end());
            //m_vecBoxSize.insert(m_vecBoxSize.end(), vecBoxSize.begin(), vecBoxSize.end());
            m_vecBoxSize = vecBoxSize;


            for (_uint t = 0; t < vecBoxSize.size(); ++t)
            {
                dynamic_cast<CGroundObject*>(pEnvironment)->Set_BoxSize(vecBoxSize[t]);
            }
        }
    }

    CloseHandle(hFile);

    S_OK;
}

HRESULT CLevel_GamePlay::Save_Monster_Index()
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

    // 일반 오브젝트
    _uint iObjectCount = static_cast<_uint>(m_MonsterInfos.size());
    WriteFile(hFile, &iObjectCount, sizeof(_uint), &dwByte, nullptr);

    for (auto& MonsterInfo : m_MonsterInfos)
    {
        _int iPosSize = MonsterInfo.vMonsterPos.size();
        WriteFile(hFile, &iPosSize, sizeof(_int), &dwByte, nullptr);
        if (iPosSize > 0)
            WriteFile(hFile, &MonsterInfo.vMonsterPos[0], iPosSize * sizeof(_float4), &dwByte, nullptr);
        WriteFile(hFile, &MonsterInfo.iMonsterIndex, sizeof(_int), &dwByte, nullptr);
    }

    CloseHandle(hFile);

    return S_OK;
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

HRESULT CLevel_GamePlay::Save_TriggerObjects()
{
    wstring fileName;
    OpenFileDialoge(L"TriggerObject.txt", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
        return E_FAIL;

    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Create TriggerData File!");
        return E_FAIL;
    }

    DWORD dwByte = 0;

    _uint iTriggerObjectCount = static_cast<_uint>(m_vecTempColliderObjects.size());
    WriteFile(hFile, &iTriggerObjectCount, sizeof(_uint), &dwByte, nullptr);


    for (auto& pTriggerObject : m_vecTempColliderObjects)
    {
        if (nullptr != pTriggerObject)
        {
            CTempCollider::TC_INFO tagInfo = pTriggerObject->Get_Info();
            WriteFile(hFile, &tagInfo.fPosition, sizeof(_float4), &dwByte, nullptr);
            WriteFile(hFile, &tagInfo.fRotation, sizeof(_float3), &dwByte, nullptr);
            WriteFile(hFile, &tagInfo.fScale, sizeof(_float3), &dwByte, nullptr);

        }
    }

    MSG_BOX("Success Save");
    CloseHandle(hFile);

    return S_OK;
}

HRESULT CLevel_GamePlay::Load_TriggerObjects()
{
    wstring fileName;
    OpenFileDialoge(L"TriggerObjectData.txt", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
        return E_FAIL;

    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Load TriggerObjectData File!");
        return E_FAIL;
    }

    for (auto& pTempColliders : m_vecTempColliderObjects)
    {
        m_pGameInstance->Add_DeadObject(L"Layer_TriggerObject", pTempColliders);
    }
    m_vecTempColliderObjects.clear();

    DWORD dwByte = 0;

    _uint iSize = 0;
    ReadFile(hFile, &iSize, sizeof(_uint), &dwByte, nullptr);

    m_vecTempColliderObjects.reserve(iSize);

    CTempCollider::TC_INFO Info = {  };
    for (size_t i = 0; i < iSize; i++)
    {
        CTempCollider::TC_DESC Desc{};
        //
        ReadFile(hFile, &Desc.fPosition, sizeof(_float4), &dwByte, nullptr);
        ReadFile(hFile, &Desc.fRotation, sizeof(_float3), &dwByte, nullptr);
        ReadFile(hFile, &Desc.fScale, sizeof(_float3), &dwByte, nullptr);

        CTempCollider* pTempCollider = reinterpret_cast<CTempCollider*>(m_pGameInstance->Add_GameObject_To_Layer_Take(LEVEL_GAMEPLAY, TEXT("Prototype_GameObject_TempColliderObject"), LEVEL_GAMEPLAY, TEXT("Layer_TriggerObject"), &Desc));

        if (nullptr != pTempCollider)
            m_vecTempColliderObjects.push_back(pTempCollider);
    }

    return S_OK;
}

HRESULT CLevel_GamePlay::Save_HeightMap()
{
    wstring fileName;
    OpenFileDialoge(L"TerrainHeight.txt", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
        return E_FAIL;

    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Create TerrainHegiht File!");
        return E_FAIL;
    }

    DWORD dwByte = 0;

    _uint iTotalBufferNum = m_pTerrainBuffer->Get_NumVerticesX() * m_pTerrainBuffer->Get_NumVerticesZ();
    WriteFile(hFile, &iTotalBufferNum, sizeof(_uint), &dwByte, nullptr);
    WriteFile(hFile, m_pVertices, sizeof(VTXNORTEX) * iTotalBufferNum, &dwByte, nullptr);

    MSG_BOX("Succeded To Save TerraingHeight File!");
    CloseHandle(hFile);

    return S_OK;
}

HRESULT CLevel_GamePlay::Load_HeightMap()
{
    wstring fileName;
    OpenFileDialoge(L"TerrainHeight.txt", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
        return E_FAIL;

    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Load TerrainHeight File!");
        return E_FAIL;
    }

    DWORD dwByte = 0;

    _uint iBufferTotalCount = {};
    ReadFile(hFile, &iBufferTotalCount, sizeof(_uint), &dwByte, nullptr);

    D3D11_MAPPED_SUBRESOURCE tagSubResource = {};
    m_pContext->Map(m_pTerrainBuffer->Get_VB_Buffer(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &tagSubResource);
    m_pVertices = static_cast<VTXNORTEX*>(tagSubResource.pData);

    ReadFile(hFile, tagSubResource.pData, sizeof(VTXNORTEX) * iBufferTotalCount, &dwByte, nullptr);

    m_pContext->Unmap(m_pTerrainBuffer->Get_VB_Buffer(), 0);

    CloseHandle(hFile);

    UINT iVertexStride = sizeof(VTXNORTEX);
    UINT iOffset = 0;
    ID3D11Buffer* pVertexBuffer = m_pTerrainBuffer->Get_VB_Buffer();
    m_pContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &iVertexStride, &iOffset);
    MSG_BOX("Success To Load TerrainHeight File!");

    return S_OK;
}

HRESULT CLevel_GamePlay::Pick_Object(MENU_TYPE _eMenuType)
{
    m_fPickPos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))), m_pTerrain->Get_Transfrom());

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
        m_fPickPos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))), m_pTerrain->Get_Transfrom());
        m_fWholePickPos = m_fPickPos;
    }

    if (m_fWholePickPos.y == -0.5f)
        return S_OK;

    m_fWholePickPos.y += 0.2f;

    _uint iFloorNumber = Determine_FloorNumber(m_fWholePickPos);
    m_iFloorNumber = iFloorNumber;

    if (m_bFinishPickingNavi_InCurrentFloor && iFloorNumber)
    {
        return S_OK;
    }

    if (m_bDeleteMode)
    {
        m_mapFloorPickedPoints[iFloorNumber].push_back(m_fWholePickPos);
        return S_OK;
    }

    if (m_bConnectingMode)
    {
        XMFLOAT3 vSelectedCordinate = Pick_Closest_Cube(m_fWholePickPos, iFloorNumber);

        if (vSelectedCordinate.x != FLT_MAX)
        {
            m_mapSelectedCube[iFloorNumber].push_back(vSelectedCordinate);

            if (m_mapSelectedCube[iFloorNumber].size() == 2)
            {
                Create_Line_Between_Cubes(m_mapSelectedCube[iFloorNumber][0], m_mapSelectedCube[iFloorNumber][1], iFloorNumber);
                m_mapSelectedCube[iFloorNumber].clear();
                m_bConnectingMode = false;
            }
        }
        return S_OK;
    }

    m_mapFloorPickedPoints[iFloorNumber].push_back(m_fWholePickPos);

    if (m_mapFloorPickedPoints[iFloorNumber].size() == 3 && m_bFirstPick && !m_bConnectingMode)
    {
        m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[0] = m_mapFloorPickedPoints[iFloorNumber][0];
        m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[1] = m_mapFloorPickedPoints[iFloorNumber][1];
        m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[2] = m_mapFloorPickedPoints[iFloorNumber][2];

        m_pNavigation->Create_Cell(m_mapTagWholeCellPoints[iFloorNumber].fCellPoints);
        m_mapWholeCellPoints[iFloorNumber].push_back(m_mapTagWholeCellPoints[iFloorNumber]);

        m_mapTagWholeCellPoints[iFloorNumber].fPrevPoints[0] = m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[0];
        m_mapTagWholeCellPoints[iFloorNumber].fPrevPoints[1] = m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[1];

        m_iNumCellCount++;
        m_bFirstPick = false;
        m_mapFloorPickedPoints[iFloorNumber].clear();
    }
    else if (m_mapFloorPickedPoints[iFloorNumber].size() < 3 && !m_bFirstPick && !m_bConnectingMode)
    {
        auto NearPoints = Compute_NearPoints(m_mapWholeCellPoints[iFloorNumber], m_mapFloorPickedPoints[iFloorNumber][0]);

        m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[0] = NearPoints.first;
        m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[1] = NearPoints.second;
        m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[2] = m_mapFloorPickedPoints[iFloorNumber][0];

        XMVECTOR vNewCellpoint1 = XMLoadFloat3(&m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[0]);
        XMVECTOR vNewCellpoint2 = XMLoadFloat3(&m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[1]);
        XMVECTOR vNewCellpoint3 = XMLoadFloat3(&m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[2]);

        if (Is_CWTriangle(vNewCellpoint1, vNewCellpoint2, vNewCellpoint3))
        {
            swap(m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[1], m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[2]);

            m_pNavigation->Create_Cell(m_mapTagWholeCellPoints[iFloorNumber].fCellPoints);
            m_mapWholeCellPoints[iFloorNumber].push_back(m_mapTagWholeCellPoints[iFloorNumber]);

            m_mapTagWholeCellPoints[iFloorNumber].fPrevPoints[0] = m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[1];
            m_mapTagWholeCellPoints[iFloorNumber].fPrevPoints[1] = m_mapTagWholeCellPoints[iFloorNumber].fCellPoints[2];
        }

        m_iNumCellCount++;
        m_mapFloorPickedPoints[iFloorNumber].clear();
    }

    return S_OK;
}

_float CLevel_GamePlay::Compute_Cell_Distance(const XMFLOAT3& _NewPickingPoint, const XMFLOAT3& _PrevPickedPoint)
{
    return sqrtf(powf(_PrevPickedPoint.x - _NewPickingPoint.x, 2) + powf(_PrevPickedPoint.y - _NewPickingPoint.y, 2) + powf(_PrevPickedPoint.z - _NewPickingPoint.z, 2));
}

_bool CLevel_GamePlay::Is_CWTriangle(const XMVECTOR& _NearestCellPoint1, const XMVECTOR& _NearestCellPoint2, const XMVECTOR& _PickedNewPoint)
{
    XMVECTOR vDir1 = XMVectorSubtract(_NearestCellPoint2, _NearestCellPoint1);

    XMVECTOR vDir2 = XMVectorSubtract(_PickedNewPoint, _NearestCellPoint1);

    _float fTriangleValue = XMVectorGetX(XMVector3Length(XMVector3Cross(vDir1, vDir2)));

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
                _float fDist1 = Compute_Cell_Distance(_newPoints, cell.fCellPoints[i]);
                _float fDist2 = Compute_Cell_Distance(_newPoints, cell.fCellPoints[j]);
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

XMFLOAT3 CLevel_GamePlay::Pick_Closest_Cube(const XMFLOAT3& clickPos, _uint _iFloorNumber)
{
    const float PICK_RADIUS = 1.5f;

    _float fMinDistance = FLT_MAX;
    XMFLOAT3 vSelectedCordinate = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

    for (const auto& cell : m_mapWholeCellPoints[_iFloorNumber])
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

void CLevel_GamePlay::Create_Line_Between_Cubes(const XMFLOAT3& _Point1, const XMFLOAT3& _Point2, _uint _iFloorNumber)
{
    m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[0] = _Point1;
    m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[1] = _Point2;

    vector<XMFLOAT3> vecAllPoints;
    for (const auto& cell : m_mapWholeCellPoints[_iFloorNumber])
    {
        for (int i = 0; i < 3; ++i)
        {
            vecAllPoints.push_back(cell.fCellPoints[i]);
        }
    }

    XMFLOAT3 vThirdPoint = Compute_Closest_Point(vecAllPoints, _Point1, _Point2);

    if (vThirdPoint.x == FLT_MAX)
        return;

    m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[2] = vThirdPoint;
    XMVECTOR vNewCellpoint1 = XMLoadFloat3(&m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[0]);
    XMVECTOR vNewCellpoint2 = XMLoadFloat3(&m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[1]);
    XMVECTOR vNewCellpoint3 = XMLoadFloat3(&m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[2]);

    if (!Is_CWTriangle(vNewCellpoint1, vNewCellpoint2, vNewCellpoint3))
    {
        swap(m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[0], m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints[1]);
    }

    m_pNavigation->Create_Cell(m_mapTagWholeCellPoints[_iFloorNumber].fCellPoints);
    m_mapWholeCellPoints[_iFloorNumber].push_back(m_mapTagWholeCellPoints[_iFloorNumber]);

    m_iNumCellCount++;
}

XMFLOAT3 CLevel_GamePlay::Compute_Closest_Point(const vector<XMFLOAT3>& vAllpoints, const XMFLOAT3& point1, const XMFLOAT3& point2)
{
    _float fMinDistance = FLT_MAX;
    XMFLOAT3 closestPoint = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

    for (const auto& point : vAllpoints)
    {
        if (point.x == point1.x && point.y == point1.y && point.z == point1.z)
            continue;
        if (point.x == point2.x && point.y == point2.y && point.z == point2.z)
            continue;

        _float fDist1 = Compute_Cell_Distance(point, point1);
        _float fDist2 = Compute_Cell_Distance(point, point2);
        _float fTotalDist = fDist1 + fDist2;

        if (fTotalDist < fMinDistance)
        {
            fMinDistance = fTotalDist;
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

_uint CLevel_GamePlay::Determine_FloorNumber(_float3 _fPickPos)
{
    /* if (_fPickPos.y < 9.0f)
         return 1;
     else if (_fPickPos.y < 18.5f)
         return 2;
     else if (_fPickPos.y > 19.0f)
         return 3;*/

    return 1;
}

HRESULT CLevel_GamePlay::Delete_Cell_Mode(_uint _iFloorNumber)
{
    if (m_pGameInstance->Get_DIKeyState(DIK_F) & 0x80)
    {
        m_bDeleteMode = true;

        if (!m_mapFloorPickedPoints[_iFloorNumber].empty())
        {
            Delete_Cell(_iFloorNumber);

            m_mapFloorPickedPoints[_iFloorNumber].clear();
        }
    }
    else
    {
        m_bDeleteMode = false;
    }

    return S_OK;
}

HRESULT CLevel_GamePlay::Delete_Cell(_uint _iFloorNumber)
{
    if (m_mapFloorPickedPoints[_iFloorNumber].empty())
        return E_FAIL;

    XMFLOAT3 vPickedPoint = m_mapFloorPickedPoints[_iFloorNumber][0];

    for (auto iter = m_mapWholeCellPoints[_iFloorNumber].begin(); iter != m_mapWholeCellPoints[_iFloorNumber].end(); ++iter)
    {
        const auto& pCell = *iter;

        if (Is_Point_InTriangle(XMLoadFloat3(&vPickedPoint), XMLoadFloat3(&pCell.fCellPoints[0]), XMLoadFloat3(&pCell.fCellPoints[1]), XMLoadFloat3(&pCell.fCellPoints[2])))
        {
            m_pNavigation->Delete_Cell(pCell.fCellPoints);

            m_mapWholeCellPoints[_iFloorNumber].erase(iter);

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
    _uint iWholeFloorCount = m_mapFloorPickedPoints.size();

    WriteFile(hFile, &iWholeFloorCount, sizeof(_uint), &dwByte, nullptr);

    WriteFile(hFile, &m_iNumCellCount, sizeof(_uint), &dwByte, nullptr);

    for (_uint i = 0; i < iWholeFloorCount; ++i)
    {
        for (auto& pCellPoints : m_mapWholeCellPoints[i + 1])
        {
            WriteFile(hFile, pCellPoints.fCellPoints, sizeof(_float3) * 3, &dwByte, nullptr);
        }
    }

    MSG_BOX("Success Save");
    CloseHandle(hFile);

    return S_OK;
}

HRESULT CLevel_GamePlay::Load_Navi(_uint _iFloorNumber)
{
    wstring fileName; OpenFileDialoge(L"Select Navigation Data", L"Text Files\0*.TXT\0All Files\0*.*\0", fileName);
    if (fileName.empty())
    {
        MSG_BOX("No file selected!");
        return E_FAIL;
    }
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MSG_BOX("Failed To Open NavigationData File!");
        return E_FAIL;
    }

    DWORD dwByte = 0;
    _uint iWholeFloorCount = 0;
    ReadFile(hFile, &iWholeFloorCount, sizeof(_uint), &dwByte, nullptr);

    _uint iLoadedCellCount = 0;
    ReadFile(hFile, &iLoadedCellCount, sizeof(_uint), &dwByte, nullptr);

    for (_uint k = 0; k < iWholeFloorCount; ++k)
    {
        for (_uint i = 0; i < iLoadedCellCount; ++i)
        {
            CELL_POINTS cellPoints;
            ReadFile(hFile, cellPoints.fCellPoints, sizeof(_float3) * 3, &dwByte, nullptr);

            _bool bIsDuplicate = false;

            for (const auto& existingCell : m_mapWholeCellPoints[k + 1])
            {
                if (memcmp(existingCell.fCellPoints, cellPoints.fCellPoints, sizeof(_float3) * 3) == 0)
                {
                    bIsDuplicate = true;
                    break;
                }
            }
            if (!bIsDuplicate)
            {
                m_pNavigation->Create_Cell(cellPoints.fCellPoints);
                m_mapWholeCellPoints[_iFloorNumber].push_back(cellPoints);
                m_iNumCellCount++;
            }
        }
    }

    CloseHandle(hFile);
    MSG_BOX("Navigation Data Loaded Successfully!");
    return S_OK;
}

HRESULT CLevel_GamePlay::Show_MouseRange(MENU_TYPE _eMenuType, _float _fTimeDelta)
{
    m_fPickPos = m_pCamera->Terrain_PickPoint(g_hWnd, static_cast<CVIBuffer_Terrain*>(m_pTerrain->Find_Component(TEXT("Com_VIBuffer_Terrain"))), m_pTerrain->Get_Transfrom());

    m_pTerrain->Set_TerrainPickPos(m_fPickPos, m_fInstallRange);

    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_TerrainMasking()
{
    D3D11_TEXTURE2D_DESC			TextureDesc{};

    TextureDesc.Width = 256;
    TextureDesc.Height = 256;
    TextureDesc.MipLevels = 1;
    TextureDesc.ArraySize = 1;
    TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    TextureDesc.SampleDesc.Quality = 0;
    TextureDesc.SampleDesc.Count = 1;
    TextureDesc.Usage = D3D11_USAGE_STAGING;
    TextureDesc.BindFlags = 0;
    TextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
    TextureDesc.MiscFlags = 0;

    _uint			iNumPixels = TextureDesc.Width * TextureDesc.Height;

    m_pPixels = new _uint[iNumPixels];
    ZeroMemory(m_pPixels, sizeof(_uint) * iNumPixels);

    D3D11_SUBRESOURCE_DATA		InitialDesc{};
    InitialDesc.pSysMem = m_pPixels;
    InitialDesc.SysMemPitch = 4 * TextureDesc.Width;

    if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, &InitialDesc, &m_pMaskTexture)))
        return E_FAIL;

    D3D11_TEXTURE2D_DESC gpuTextureDesc = TextureDesc;
    gpuTextureDesc.Usage = D3D11_USAGE_DEFAULT;
    gpuTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    gpuTextureDesc.CPUAccessFlags = 0;

    if (FAILED(m_pDevice->CreateTexture2D(&gpuTextureDesc, nullptr, &m_pCopyMaskTexture)))
        return E_FAIL;

    D3D11_SHADER_RESOURCE_VIEW_DESC gpuSRVDesc = { DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_SRV_DIMENSION_TEXTURE2D, 0, 0 };
    gpuSRVDesc.Texture2D.MipLevels = 1;
    gpuSRVDesc.Texture2D.MostDetailedMip = 0;

    if (FAILED(m_pDevice->CreateShaderResourceView(m_pCopyMaskTexture, &gpuSRVDesc, &m_pCopyMaskSRV)))
        return E_FAIL;

    //물기 텍스쳐 생성

    D3D11_TEXTURE2D_DESC			WaterMapTextureDesc{};

    WaterMapTextureDesc.Width = 256;
    WaterMapTextureDesc.Height = 256;
    WaterMapTextureDesc.MipLevels = 1;
    WaterMapTextureDesc.ArraySize = 1;
    WaterMapTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    WaterMapTextureDesc.SampleDesc.Quality = 0;
    WaterMapTextureDesc.SampleDesc.Count = 1;
    WaterMapTextureDesc.Usage = D3D11_USAGE_STAGING;
    WaterMapTextureDesc.BindFlags = 0;
    WaterMapTextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
    WaterMapTextureDesc.MiscFlags = 0;

    _uint			iWaterNumPixels = WaterMapTextureDesc.Width * WaterMapTextureDesc.Height;

    m_pWaterMapPixels = new _uint[iWaterNumPixels];
    ZeroMemory(m_pWaterMapPixels, sizeof(_uint) * iWaterNumPixels);


    D3D11_SUBRESOURCE_DATA		WaterInitialDesc{};
    WaterInitialDesc.pSysMem = m_pWaterMapPixels;
    WaterInitialDesc.SysMemPitch = 4 * WaterMapTextureDesc.Width;

    if (FAILED(m_pDevice->CreateTexture2D(&WaterMapTextureDesc, &InitialDesc, &m_pWaterMapTexture)))
        return E_FAIL;

    D3D11_TEXTURE2D_DESC gpuWaterTextureDesc = WaterMapTextureDesc;
    gpuWaterTextureDesc.Usage = D3D11_USAGE_DEFAULT;
    gpuWaterTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    gpuWaterTextureDesc.CPUAccessFlags = 0;

    if (FAILED(m_pDevice->CreateTexture2D(&gpuWaterTextureDesc, nullptr, &m_pCopyWaterMapTexture)))
        return E_FAIL;

    D3D11_SHADER_RESOURCE_VIEW_DESC gpuWaterSRVDesc = { DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_SRV_DIMENSION_TEXTURE2D, 0, 0 };
    gpuWaterSRVDesc.Texture2D.MipLevels = 1;
    gpuWaterSRVDesc.Texture2D.MostDetailedMip = 0;

    if (FAILED(m_pDevice->CreateShaderResourceView(m_pCopyWaterMapTexture, &gpuWaterSRVDesc, &m_pCopyWaterMapSRV)))
        return E_FAIL;

    //_uint			iNumPixels = TextureDesc.Width * TextureDesc.Height;

    //_uint* pPixels = new _uint[iNumPixels];
    //ZeroMemory(pPixels, sizeof(_uint) * iNumPixels);

    //D3D11_SUBRESOURCE_DATA		InitialDesc{};
    //InitialDesc.pSysMem = pPixels;
    //InitialDesc.SysMemPitch = 4 * TextureDesc.Width;

    //if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, &InitialDesc, &pTexture2D)))
    ////	return E_FAIL;

    //D3D11_MAPPED_SUBRESOURCE	SubResource{};

    /////* 텍스체에 값을 채운다. 수정 변경한다. */
    //m_pContext->Map(m_pMaskTexture, 0, D3D11_MAP_READ_WRITE, 0, &SubResource);

    //_uint* pMappedPixel = static_cast<_uint*>(SubResource.pData);

    //for (size_t i = 0; i < TextureDesc.Height; i++)
    //{
    //	for (size_t j = 0; j < TextureDesc.Width; j++)
    //	{
    //		_uint		iIndex = i * TextureDesc.Width + j;

    //		pMappedPixel[iIndex] = 0x00000000;
    //	}
    //}



    //m_pContext->Unmap(m_pMaskTexture, 0);


    //string strDataPath = "../Bin/DataFiles/Mask/MaskData";

    //strDataPath = strDataPath + to_string(iFileIndex) + ".dds";

    //_tchar		szLastPath[MAX_PATH] = {};

    //MultiByteToWideChar(CP_ACP, 0, strDataPath.c_str(), static_cast<_int>(strlen(strDataPath.c_str())), szLastPath, MAX_PATH);

    ///* 텍스쳐를 파일로 저장한다. */
    //if (FAILED(SaveDDSTextureToFile(m_pContext, pTexture2D, szLastPath)))
    //	return E_FAIL;

    //Safe_Release(pTexture2D);

    //Safe_Delete_Array(pPixels);

    return S_OK;
}

HRESULT CLevel_GamePlay::Make_MaskTexture(_vector vPickPos)
{
    D3D11_MAPPED_SUBRESOURCE	SubResource{};

    /* 텍스체에 값을 채운다. 수정 변경한다. */
    m_pContext->Map(m_pMaskTexture, 0, D3D11_MAP_READ_WRITE, 0, &SubResource);

    _uint* pMappedPixel = static_cast<_uint*>(SubResource.pData);

    //m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(30.0f, 0.0f, -150.0f, 1.0f)); -> TerrainPos


    _uint		iIndex = ((_int)((XMVectorGetZ(vPickPos) + 150.f) * (256.f / 150.f)) * 256 + ((_int)(XMVectorGetX(vPickPos) - 30.f) * (256.f / 150.f)));

    for (_int k = -m_fInstallRange; k < m_fInstallRange; k++)
    {
        if (iIndex + (k * 256) > 0 && iIndex + (k * 256) < 256 * 256)
            pMappedPixel[iIndex + (k * 256)] = 0xffffffff;

        for (_int j = -m_fInstallRange; j < m_fInstallRange; j++)
        {
            if ((iIndex + (k * 256) + j) > 0 && ((iIndex + (k * 256) + j) < 256 * 256))
                pMappedPixel[iIndex + (k * 256) + j] = 0xffffffff;
        }
    }

    m_pContext->Unmap(m_pMaskTexture, 0);

    m_pContext->CopyResource(m_pCopyMaskTexture, m_pMaskTexture);

    return S_OK;
}



HRESULT CLevel_GamePlay::Erase_MaskTexture(_vector vPickPos)
{
    D3D11_MAPPED_SUBRESOURCE	SubResource{};

    /* 텍스체에 값을 채운다. 수정 변경한다. */
    m_pContext->Map(m_pMaskTexture, 0, D3D11_MAP_READ_WRITE, 0, &SubResource);

    _uint* pMappedPixel = static_cast<_uint*>(SubResource.pData);

    //m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(30.0f, 0.0f, -150.0f, 1.0f)); -> TerrainPos


    _uint		iIndex = ((_int)((XMVectorGetZ(vPickPos) + 150.f) * (256.f / 150.f)) * 256 + ((_int)(XMVectorGetX(vPickPos) - 30.f) * (256.f / 150.f)));

    for (_int k = -m_fInstallRange; k < m_fInstallRange; k++)
    {
        if (iIndex + (k * 256) > 0 && iIndex + (k * 256) < 256 * 256)
            pMappedPixel[iIndex + (k * 256)] = 0xff000000;

        for (_int j = -m_fInstallRange; j < m_fInstallRange; j++)
        {
            if ((iIndex + (k * 256) + j) > 0 && ((iIndex + (k * 256) + j) < 256 * 256))
                pMappedPixel[iIndex + (k * 256) + j] = 0xff000000;
        }
    }

    m_pContext->Unmap(m_pMaskTexture, 0);

    m_pContext->CopyResource(m_pCopyMaskTexture, m_pMaskTexture);

    return S_OK;
}


HRESULT CLevel_GamePlay::Make_WaterMapTexture(_vector vPickPos)
{
    D3D11_MAPPED_SUBRESOURCE	SubResource{};

    /* 텍스체에 값을 채운다. 수정 변경한다. */
    m_pContext->Map(m_pWaterMapTexture, 0, D3D11_MAP_READ_WRITE, 0, &SubResource);

    _uint* pMappedPixel = static_cast<_uint*>(SubResource.pData);

    //m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(30.0f, 0.0f, -150.0f, 1.0f)); -> TerrainPos


    _uint		iIndex = ((_int)((XMVectorGetZ(vPickPos) + 150.f) * (256.f / 150.f)) * 256 + ((_int)(XMVectorGetX(vPickPos) - 30.f) * (256.f / 150.f)));

    for (_int k = -m_fInstallRange; k < m_fInstallRange; k++)
    {
        if (iIndex + (k * 256) > 0 && iIndex + (k * 256) < 256 * 256)
            pMappedPixel[iIndex + (k * 256)] = 0xffffffff;

        for (_int j = -m_fInstallRange; j < m_fInstallRange; j++)
        {
            if ((iIndex + (k * 256) + j) > 0 && ((iIndex + (k * 256) + j) < 256 * 256))
                pMappedPixel[iIndex + (k * 256) + j] = 0xffffffff;
        }
    }

    m_pContext->Unmap(m_pWaterMapTexture, 0);

    m_pContext->CopyResource(m_pCopyWaterMapTexture, m_pWaterMapTexture);

    return S_OK;
}

HRESULT CLevel_GamePlay::Erase_WaterMapTexture(_vector vPickPos)
{
    D3D11_MAPPED_SUBRESOURCE	SubResource{};

    /* 텍스체에 값을 채운다. 수정 변경한다. */
    m_pContext->Map(m_pWaterMapTexture, 0, D3D11_MAP_READ_WRITE, 0, &SubResource);

    _uint* pMappedPixel = static_cast<_uint*>(SubResource.pData);

    //m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(30.0f, 0.0f, -150.0f, 1.0f)); -> TerrainPos


    _uint		iIndex = ((_int)((XMVectorGetZ(vPickPos) + 150.f) * (256.f / 150.f)) * 256 + ((_int)(XMVectorGetX(vPickPos) - 30.f) * (256.f / 150.f)));

    for (_int k = -m_fInstallRange; k < m_fInstallRange; k++)
    {
        if (iIndex + (k * 256) > 0 && iIndex + (k * 256) < 256 * 256)
            pMappedPixel[iIndex + (k * 256)] = 0xff000000;

        for (_int j = -m_fInstallRange; j < m_fInstallRange; j++)
        {
            if ((iIndex + (k * 256) + j) > 0 && ((iIndex + (k * 256) + j) < 256 * 256))
                pMappedPixel[iIndex + (k * 256) + j] = 0xff000000;
        }
    }

    m_pContext->Unmap(m_pWaterMapTexture, 0);

    m_pContext->CopyResource(m_pCopyWaterMapTexture, m_pWaterMapTexture);

    return S_OK;
}

HRESULT CLevel_GamePlay::Save_MaskTexture(_int iFileIndex)
{

    string strDataPath = "E:/Github/Thymesia_MapTool_Test/Client/Bin/DataFiles/Mask/MaskData";

    strDataPath = strDataPath + to_string(iFileIndex) + ".dds";

    _tchar		szLastPath[MAX_PATH] = {};

    MultiByteToWideChar(CP_ACP, 0, strDataPath.c_str(), static_cast<_int>(strlen(strDataPath.c_str())), szLastPath, MAX_PATH);

    /* 텍스쳐를 파일로 저장한다. */
    HRESULT hr = SaveDDSTextureToFile(m_pContext, m_pMaskTexture, szLastPath);

    return hr;
}


HRESULT CLevel_GamePlay::Save_WaterMapTexture(_int iFileIndex)
{

    string strDataPath = "E:/Github/Thymesia_MapTool_Test/Client/Bin/DataFiles/Mask/WaterMapData";

    strDataPath = strDataPath + to_string(iFileIndex) + ".dds";

    _tchar		szLastPath[MAX_PATH] = {};

    MultiByteToWideChar(CP_ACP, 0, strDataPath.c_str(), static_cast<_int>(strlen(strDataPath.c_str())), szLastPath, MAX_PATH);

    /* 텍스쳐를 파일로 저장한다. */
    HRESULT hr = SaveDDSTextureToFile(m_pContext, m_pWaterMapTexture, szLastPath);

    return hr;
}



HRESULT CLevel_GamePlay::Load_MaskTexture(_int iFileIndex)
{

    string strDataPath = "../Bin/DataFiles/Mask/MaskData";

    strDataPath = strDataPath + to_string(iFileIndex) + ".dds";

    _tchar		szLastPath[MAX_PATH] = {};

    MultiByteToWideChar(CP_ACP, 0, strDataPath.c_str(), static_cast<_int>(strlen(strDataPath.c_str())), szLastPath, MAX_PATH);


    ID3D11Texture2D* pTempTexture = nullptr;
    /* 텍스쳐를 파일로 저장한다. */
    HRESULT hr = CreateDDSTextureFromFile(m_pDevice, szLastPath, (ID3D11Resource**)&pTempTexture, nullptr);

    if (hr == E_FAIL)
    {
        MSG_BOX("Wrong_Path");

        return hr;
    }

    m_pContext->CopySubresourceRegion(m_pMaskTexture, 0, 0, 0, 0, pTempTexture, 0, nullptr);

    pTempTexture->Release();

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    hr = m_pContext->Map(m_pMaskTexture, 0, D3D11_MAP_READ, 0, &mappedResource);

    D3D11_TEXTURE2D_DESC desc;
    m_pMaskTexture->GetDesc(&desc);

    if (SUCCEEDED(hr))
    {
        _uint rowPitch = mappedResource.RowPitch;
        _uint pixelSize = 4;

        for (_uint y = 0; y < desc.Height; y++)
        {
            memcpy(
                m_pPixels + y * desc.Width,
                (BYTE*)mappedResource.pData + y * rowPitch,
                desc.Width * pixelSize
            );
        }
    }

    m_pContext->Unmap(m_pMaskTexture, 0);

    m_pContext->CopyResource(m_pCopyMaskTexture, m_pMaskTexture);

    return hr;
}



HRESULT CLevel_GamePlay::Load_WaterMapTexture(_int iFileIndex)
{

    string strDataPath = "E:/Github/Thymesia_MapTool_Test/Client/Bin/DataFiles/Mask/MaskData";

    strDataPath = strDataPath + to_string(iFileIndex) + ".dds";

    _tchar		szLastPath[MAX_PATH] = {};

    MultiByteToWideChar(CP_ACP, 0, strDataPath.c_str(), static_cast<_int>(strlen(strDataPath.c_str())), szLastPath, MAX_PATH);


    ID3D11Texture2D* pTempTexture = nullptr;
    /* 텍스쳐를 파일로 저장한다. */
    HRESULT hr = CreateDDSTextureFromFile(m_pDevice, szLastPath, (ID3D11Resource**)&pTempTexture, nullptr);

    if (hr == E_FAIL)
    {
        MSG_BOX("Wrong_Path");

        return hr;
    }

    m_pContext->CopySubresourceRegion(m_pWaterMapTexture, 0, 0, 0, 0, pTempTexture, 0, nullptr);

    pTempTexture->Release();

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    hr = m_pContext->Map(m_pWaterMapTexture, 0, D3D11_MAP_READ, 0, &mappedResource);

    D3D11_TEXTURE2D_DESC desc;
    m_pWaterMapTexture->GetDesc(&desc);

    if (SUCCEEDED(hr))
    {
        _uint rowPitch = mappedResource.RowPitch;
        _uint pixelSize = 4;

        for (_uint y = 0; y < desc.Height; y++)
        {
            memcpy(
                m_pPixels + y * desc.Width,
                (BYTE*)mappedResource.pData + y * rowPitch,
                desc.Width * pixelSize
            );
        }
    }

    m_pContext->Unmap(m_pWaterMapTexture, 0);

    m_pContext->CopyResource(m_pCopyWaterMapTexture, m_pWaterMapTexture);

    return hr;
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

    for (auto& pSRV : m_vecTriggerObjectSRVs)
        Safe_Release(pSRV);
    m_vecTriggerObjectSRVs.clear();

    Safe_Release(m_pMaskTexture);
    Safe_Release(m_pCopyMaskTexture);
    Safe_Release(m_pCopyMaskSRV);
    Safe_Delete_Array(m_pPixels);

    Safe_Release(m_pWaterMapTexture);
    Safe_Release(m_pCopyWaterMapSRV);
    Safe_Release(m_pCopyWaterMapTexture);
    Safe_Delete_Array(m_pWaterMapPixels);
}
