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
    XMFLOAT3                            Compute_ClosestInstanceModelPoint(const XMFLOAT3& _fClickPos);
    void                                Pick_InstanceModel();



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

    const char* m_strObjectNames[256] =
    {
        "HORSE_P_WoodenFrame02_05",
        "P_Rag03",
        "SM_Wall_Shelf",
        "SM_WoodFence03",
        "SM_WoodFence04",
        "SM_WoodStairs03",
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
        "Railing_base01",
        "Railing_pillar01_2",
        "Railing01_3",
        "SM_Brick_stone_stairs_1_a",
        "SM_Gate_17d",
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
        "Railing03_1",
        "P_Fortress_BossDoor_Left01",
        "P_Fortress_BossDoor_Right01",
        "SM_Debris_01a",
        "SM_Debris_02a",
        "SM_Scafold_01b",
        "SM_Scafold_01c",
        "SM_fence_14",
        "SM_fence_16",
        "SM_fence_13",
        "SM_rock_03",
        "SM_curb_02",
        "P_CemeteryStairs01",
        "Brick_Floor",
        "Grass0",
        "P_Archive_Chair01",
        "Ladder"
    };

    const char* m_strGroundObjectNamess[100] =
    {
        "Grass0",
        "Tree0",
        "House0"
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
    _float                                  m_fSpacingValue = { 1.0f };
    _float                                  m_fInterval = {};
    _float                                  m_fRadius = { 1.0f };
    VTXNORTEX* m_pVertices = { nullptr };
    vector<_float3>                         m_vecInstancedGroundObjectPos;
    vector<_float3>                         m_vecInstancedGroundObjectScale;
    vector<_float3>                         m_vecInstancedGroundObjectRotation;
    _uint                                   m_iInstancingModelSize = {};
    _bool                                   m_bDraggingInstanceModel = { false };

    _int                                   m_iSelectedInstanceIndex = -1;

public:
    static CLevel_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    virtual void                            Free() override;
};

END