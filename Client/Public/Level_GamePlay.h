#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "Object.h"
#include "GameInstance.h"

#include "Camera_Free.h"
#include "Terrain.h"

#include "Navigation.h"
#include "Cell.h"

//#include "EnvironmentObject.h"
#include "GroundObject.h"



BEGIN(Engine)
class CShader;
class CTexture;
class CNavigation;
END



BEGIN(Client)
class CLevel_GamePlay final : public CLevel
{
public:
    enum IMGUI_TEXTURE_TYPE { IMG_ANIM_MODEL, IMG_NONANIM_MODEL, IMG_GROUND_MODEL, IMG_END };
    enum MENU_TYPE { MT_PICKING_ANIMMODEL, MT_PICKING_NONANIMMODEL, MT_NAVI, MT_GROUND, MT_END };
public:
    struct CELL_POINTS
    {
        _float3 fCellPoints[3];
        _float3 fPrevPoints[3];
    };

    typedef struct Mesh_Pos
    {
        _float fDist;
        _float3 fPosition;
        CObject* pObject;
    }MESHPOS;

private:
    CLevel_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    virtual ~CLevel_GamePlay() = default;

public:
    virtual HRESULT Initialize() override;
    virtual void Update(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    HRESULT Ready_Lights();
    HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
    HRESULT Ready_Layer_Structure(const _tchar* pLayerTag);
    HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
    HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
    HRESULT Ready_Layer_Monster(const _tchar* pLayerTag);
    HRESULT Ready_Layer_Effect(const _tchar* pLayerTag);
    HRESULT Ready_Layer_UI(const _tchar* pLayerTag);


    // 테스트용 사다리 레이어 추가
    HRESULT	Ready_Layer_Ladder(const _tchar* pLayerTag);





private:
    HRESULT								Resister_ObjectList_PreviewImage(const _tchar* _pImageFilePath, IMGUI_TEXTURE_TYPE _eImguiTextureType, _uint _iTextureNumber);
    vector<ID3D11ShaderResourceView*>	m_vecAnimModelSRVs;
    vector<ID3D11ShaderResourceView*>	m_vecNonAnimModelSRVs;
    vector<ID3D11ShaderResourceView*>	m_vecGroundModelSRVs;


private:
    void								Add_NonAnimObjects();
    void								Add_AnimObjects();
    void								Setting_NonAnimObjectList();
    void								Active_PreviewModelImage();

    void								Add_GroundObjects();
    void                                Delete_GroundObjects();
    void								Setting_GroundObjectList();

    void                                Update_InstanceObjects();
    void                                Update_InstanceMove();
    void                                Update_Instance();
    XMFLOAT3                            Compute_ClosestInstanceModelPoint(const XMFLOAT3& _fClickPos);


    HRESULT								Save_Objects();
    HRESULT								Load_Objects();
    void	                            OpenFileDialoge(const _tchar* _pDefaultFileName, const _tchar* _pFilter, std::wstring& outFileName);


private:
    HRESULT								Pick_Object(MENU_TYPE _eMenuType);
    _float3								m_fPickPos = {};

private:
    HRESULT                             Picking_Points();
    _float                              Compute_Cell_Distance(const XMFLOAT3& _NewPickingPoint, const XMFLOAT3& _PrevPickedPoint);
    _bool                               Is_CWTriangle(const XMVECTOR& _NearestCellPoint1, const XMVECTOR& _NearestCellPoint2, const XMVECTOR& _PickedNewPoint);
    pair<XMFLOAT3, XMFLOAT3>            Compute_NearPoints(const vector<CELL_POINTS>& _vecTagCells, const XMFLOAT3& _newPoints);
    XMFLOAT3                            Pick_Closest_Cube(const XMFLOAT3& clickPos, _uint _iFloorNumber);
    void                                Create_Line_Between_Cubes(const XMFLOAT3& point1, const XMFLOAT3& point2, _uint _iFloorNumber = 0);
    XMFLOAT3                            Compute_Closest_Point(const vector<XMFLOAT3>& vAllpoints, const XMFLOAT3& point1, const XMFLOAT3& point2);
    _bool                               Is_Point_InTriangle(const XMVECTOR& _Point, const XMVECTOR& _VertexPoint0, const XMVECTOR& _VertexPoint1, const XMVECTOR& _VertexPoint2);
    _uint                               Determine_FloorNumber(_float3 _fPickPos);
    HRESULT                             Delete_Cell_Mode(_uint _iFloorNumber);
    HRESULT                             Delete_Cell(_uint _iFloorNumber);

    HRESULT								Save_Navi();
    HRESULT								Load_Navi(_uint _iFloorNumber);

private:
    HRESULT                             Show_MouseRange(MENU_TYPE _eMenuType, _float _fTimeDelta);


private:
    _uint                               m_iNumCellCount = {};
    _bool                               m_bFirstPick = { true };
    _bool                               m_bConnectingMode = false;
    _bool                               m_bDeleteMode = { false };
    _bool                               m_bFinishPickingNavi_InCurrentFloor = { false };
    _uint                               m_iFloorNumber = {};


    map<_uint, vector<XMFLOAT3>>        m_mapSelectedCube;
    map<_uint, CELL_POINTS>             m_mapTagWholeCellPoints;
    map<_uint, vector<_float3>>         m_mapFloorPickedPoints;
    map<_uint, vector<CELL_POINTS>>     m_mapWholeCellPoints;



private:
    _bool								m_bImguiHovered = { false };
    _bool								m_bNonAnimObjectMenuSelected = { false };
    _bool								m_bAnimObjectMenuSelected = { false };
    _bool								m_bNaviMenuSelected = { false };
    _bool								m_bGrondMenuSelected = { false };

    _bool								m_bIsMeshPickingMode = { false };
    _bool								m_bIsTerrainPickingMode = { false };


    _int								m_iNonAnimModelIndex = {};
    _int								m_iGroundModelIndex = {};
    _int                                m_iRandGroundModelIndex = {};

    _float3								m_fWholePickPos = {};


private:
    // 오브젝트 생성할 위치

    _int                                m_iObjectArray = { 0 };
    _float                              m_fObjectPos[3] = { 1.f, 1.f ,1.f };
    _float                              m_fMeshScale[3] = { 0.01f, 0.01f, 0.01f };
    _float                              m_fObjectRotation[3] = { 0.f, 0.f, 0.f };
    _float	                            m_fFrustumRadius = { 1.f };

    list<CObject*>                      m_Objects;
    vector<CEnvironmentObject*>         m_EnvironmentObjects;

    _float3                             m_fMeshPickPos = { 0.f, 0.f, 0.f };
    _float                              m_fPosMax[2] = { -100.f, 100.f };
    _float                              m_fScaleMax[2] = { -1.f, 1.f };
    _float                              m_fRotationMax[2] = { -180.f, 180.f };
    _float	                            m_fRadiusMax = { 100.f };

    _int                                m_iGroundObjectListIndex = { -1 };
    _int                                m_iNonMoveObjectListIndex = { -1 };

    const char* m_strObjectNames[256] =
    {
        "HORSE_P_WoodenFrame02_05",
        "P_Rag03",
        "SM_Wall_Shelf",
        "P_BossAtriumCircle01",
        "P_BossCemetery_02_02",
        "P_BossCemetery_04",
        "P_BossCemetery_05",
        "P_BossCemetery_06",
        "P_BossInteriorArches02",
        "P_ChurchWindowGrilles01",
        "P_LongStairs01",
        "SM_Plains_CastleArch_Ruin_01",
        "SM_Trim_01a",
        "SM_Wall_8x8_Broken_01c",
        "SM_Wall_8x8_Broken_01d",
        "SM_Wall_8x8_Broken_01e",
        "SM_ground_Road_Middle_250x250cm_1_a",
        "T_P_BossRoomVines01",
        "P_BossArtriumCircleRailing_Down02",
        "P_BossArtriumCircleRailing_Down03",
        "P_BossArtriumCircleRailing_Down04",
        "P_BossAtriumCircleRailing_Top01",
        "P_BossAtriumCircleRailing_Up01",
        "P_BossAtriumCircleRailing_Up02",
        "P_BossAtriumCircleRailing_Up04",
        "P_BossAtriumCircleRailing_Up03",
        "P_Fortress_BossDoor_Left01",
        "P_Fortress_BossDoor_Right01",
        "SM_Debris_01a",
        "SM_Debris_02a",
        "SM_Scafold_01b",
        "SM_Scafold_01c",
        "P_CemeteryStairs01",
        "P_CemeteryStairs02",
        "P_CemeteryStairs03",
        "Brick_Floor",
        "P_Archive_Chair01",
        "Ladder",
        "SM_crypt_01",
        "SM_crypt_05",
        "SM_crypt_06",
        "SM_crypt_08",
        "SM_crypt_09",
        "SM_fence_14",
        "SM_fence_16",
        "SM_fence_01",
        "SM_fence_02",
        "SM_fence_03",
        "SM_fence_08",
        "SM_fence_15",

    };

    const char* m_strObjectUrnNames[256] =
    {
        "SM_urn_01",
        "SM_urn_02",
        "SM_urn_03",
        "SM_urn_04",
        "SM_urn_05",
        "SM_urn_06",
        "SM_urn_07",
        "SM_urn_09",
    };

    const char* m_strGroundObjectNamess[100] =
    {
        "Grass0",
        "Tree0",    
        "Railing_base01",
        "Railing_pillar01_2",
        "Railing03_1",
        "Railing01_3",
        "SM_BaseWall_01_Corner",
        "SM_BaseWall_02_Plain",
        "SM_Separator",
        "SM_Barrel_Closed",
        "SM_WoodFence03",
        "SM_WoodFence04",
        "SM_Stairs",
        "SM_Stairs02",
        "SM_LogPile_03",
        "SM_Brick_stone_stairs_1_a",
        "SM_Gate_17d",
        "SM_Fence_04",
        "SM_Wall_Combined_03",
    };

    const char* m_strGorundobjectClothesNames[9] = {

"P_Cloth01",
"P_Cloth02",
"P_Cloth03",
"P_Cloth04",
"P_Cloth05",
"P_Cloth06",
"P_Cloth07",
"P_Cloth08",
    };

    const char* m_strGroundObjectGraveStoneNames[63] =
    {

"SM_gravestone_01",
"SM_gravestone_02",
"SM_gravestone_03",
"SM_gravestone_04",
"SM_gravestone_05",
"SM_gravestone_06",
"SM_gravestone_07",
"SM_gravestone_08",
"SM_gravestone_09",
"SM_gravestone_10",
"SM_gravestone_11",
"SM_gravestone_12",
"SM_gravestone_13",
"SM_gravestone_15",
"SM_gravestone_16",
"SM_gravestone_17",
"SM_gravestone_18",
"SM_gravestone_20",
"SM_gravestone_21",
"SM_gravestone_22",
"SM_gravestone_23",
"SM_gravestone_25",
"SM_gravestone_26",
"SM_gravestone_27",
"SM_gravestone_28",
"SM_gravestone_29",
"SM_gravestone_31",
"SM_gravestone_32",
"SM_gravestone_33",
"SM_gravestone_34",
"SM_gravestone_35",
"SM_gravestone_36",
"SM_gravestone_37",
"SM_gravestone_38",
"SM_gravestone_41",
"SM_gravestone_42",
"SM_gravestone_44",
"SM_gravestone_46",
"SM_gravestone_48",
"SM_gravestone_50",
"SM_gravestone_51",
"SM_gravestone_53",
"SM_gravestone_54",
"SM_gravestone_55",
"SM_gravestone_56",
"SM_gravestone_60",
"SM_gravestone_61",
"SM_gravestone_62",
"SM_gravestone_63",

    };

    const char* m_strGroundObjectCurbNames[10] =
    { "SM_curb_01",
"SM_curb_02",
"SM_curb_03",
"SM_curb_05",
"SM_curb_06",
"SM_curb_07",
"SM_curb_08",
"SM_curb_09"
    };



    const char* m_strGroundObjectFenceNames[30] =
    {
"SM_fence_01",
"SM_fence_02",
"SM_fence_03",
"SM_fence_04",
"SM_fence_05",
"SM_fence_06",
"SM_fence_07",
"SM_fence_08",
"SM_fence_09",
"SM_fence_10",
"SM_fence_12",
"SM_fence_13",
"SM_fence_15",
"SM_fence_19",
"SM_fence_20",
"SM_fence_21",
"SM_fence_22",
"SM_fence_23",
"SM_fence_24",
"SM_fence_25",
"SM_fence_26",
"SM_fence_27",
"SM_fence_29",
"SM_fence_30",
"SM_fence_31",
"SM_fence_32",
"SM_fence_33",
"SM_fence_34",
"SM_fence_35",
    };

    const char* m_strGroundObjectRocknames[3] = {
"SM_rock_01",
"SM_rock_02",
"SM_rock_03",
    };

    const char* m_strGroundObjectDeseasednames[6] = { 
        "P_Deceased01",
"P_Deceased02",
"P_Deceased03",
"P_Deceased04",
"P_Deceased05",
"P_Deceased06",
    };

    const char* m_strGroundObjectTreenames[20] = {
"SM_DeadTree_01a",
"SM_DeadTree_01",
"SM_BigTree001",
"SM_BigTree002",
"SM_BigTree003",
"SM_BigTree004",
"SM_BigTree005",
"SM_BigTree006",
"SM_BigTree006_02",
"SM_BigTree006_03_02",
"P_TreeAerialRoot01",
"P_TreeAerialRoot02",
"P_BrokenTree01",
"P_DeadTree02",
"P_DeadTree03",
"DryTreeT3_2_SM_02",
"DryTreeT3_branches_1_SM",
"DryTreeT3_branches_1_SM_02",
"DryTreeT3_branches_3_SM",
"DryTreeT3_branches_5_SM",

    };

    const char* m_strGroundObjectStairsNames[3] = {
        "SM_WoodStairs03",
    };

private:
    CCamera_Free* m_pCamera = { nullptr };
    CTerrain* m_pTerrain = { nullptr };
    CVIBuffer_Terrain* m_pTerrainBuffer = { nullptr };
    CNavigation* m_pNavigation = { nullptr };

    CTransform* m_pCurrentObjectTransformCom = { nullptr };
    CObject* m_pCurrentObject = { nullptr };

    CTransform* m_pPrevObjectTrasnformCom = { nullptr };
    CObject* m_pPrevObject = { nullptr };


    CEnvironmentObject* m_pCurrentEnvironmentObject = { nullptr };
    CGroundObject* m_pSelectedInstancedObject = { nullptr };
    CTransform* m_pCurrentEnvironmentObjectTransformCom = { nullptr };

    _float3									m_fCurrentObjectPos = { 0.f, 0.f, 0.f };

    _bool									m_bFrustumSphere = { false };

private:
    _float                                  m_fInstallRange = { 1.0f };
    _float                                  m_fInstanceCount = { 1.0f };
    _float                                  m_fSpacingValue = { 1.0f };
    _float                                  m_fInterval = {};
    _float                                  m_fRadius = { 1.0f };
    _uint                                   m_iInstancePickModeIndex = {};
    _bool                                   m_iModeSelected = { false };

    VTXNORTEX* m_pVertices = { nullptr };
    vector<_float3>                         m_vecInstancedGroundObjectPos;
    vector<_float3>                         m_vecInstancedGroundObjectScale;
    vector<_float4>                         m_vecInstancedGroundObjectRotation;
    _uint                                   m_iInstancingModelSize = {};
    _bool                                   m_bDraggingInstanceModel = { false };

    _int                                   m_iSelectedInstanceIndex = { -1 };
    vector<_int>                            m_vecBoxSize;

    _bool                                   m_bGroundObjectMouseState = { false };

public:
    static CLevel_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    virtual void                            Free() override;
};

END