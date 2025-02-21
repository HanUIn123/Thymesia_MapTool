#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "Object.h"
#include "GameInstance.h"

#include "Camera_Free.h"
#include "Terrain.h"

#include "Navigation.h"
#include "Cell.h"




BEGIN(Engine)
class CShader;
class CTexture;
class CNavigation;
END



BEGIN(Client)
class CLevel_GamePlay final : public CLevel
{
public:
	enum IMGUI_TEXTURE_TYPE {IMG_ANIM_MODEL, IMG_NONANIM_MODEL, IMG_END};
	enum MENU_TYPE { MT_PICKING_ANIMMODEL, MT_PICKING_NONANIMMODEL, MT_NAVI , MT_END  };
public:
	struct CELL_POINTS
	{
		_float3 fCellPoints[3];
		_float3 fPrevPoints[3];
	};


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
	HRESULT									Resister_ObjectList_PreviewImage(const _tchar* _pImageFilePath, IMGUI_TEXTURE_TYPE _eImguiTextureType, _uint _iTextureNumber);
	vector<ID3D11ShaderResourceView*>		m_vecAnimModelSRVs;
	vector<ID3D11ShaderResourceView*>		m_vecNonAnimModelSRVs;

private:
	void									Add_NonAnimObjects();
	void									Add_AnimObjects();
	void									Setting_NonAnimObjectList();

	HRESULT									Save_Objects();

	HRESULT									Load_Objects();

	void	                                OpenFileDialoge(const _tchar* _pDefaultFileName, const _tchar* _pFilter, std::wstring& outFileName);

private:
	HRESULT									Pick_Object(MENU_TYPE _eMenuType);
	_float3									m_fPickPos = {};

private:
	HRESULT                             Picking_Points();
	_float                              Compute_Cell_Distance(const XMFLOAT3& _NewPickingPoint, const XMFLOAT3& _PrevPickedPoint);
	_bool                               Is_CWTriangle(const XMVECTOR& _NearestCellPoint1, const XMVECTOR& _NearestCellPoint2, const XMVECTOR& _PickedNewPoint);
	pair<XMFLOAT3, XMFLOAT3>            Compute_NearPoints(const vector<CELL_POINTS>& _vecTagCells, const XMFLOAT3& _newPoints);
	XMFLOAT3                            Pick_Closest_Cube(const XMFLOAT3& clickPos);
	void                                Create_Line_Between_Cubes(const XMFLOAT3& point1, const XMFLOAT3& point2);
	XMFLOAT3                            Compute_Closest_Point(const vector<XMFLOAT3>& vAllpoints, const XMFLOAT3& point1, const XMFLOAT3& point2);
	_bool                               Is_Point_InTriangle(const XMVECTOR& _Point, const XMVECTOR& _VertexPoint0, const XMVECTOR& _VertexPoint1, const XMVECTOR& _VertexPoint2);
	HRESULT                             Delete_Cell_Mode();
	HRESULT                             Delete_Cell();

	HRESULT								Save_Navi();
	HRESULT								Load_Navi();

private:
	vector<_float3>                     m_vecPickedPoints;
	vector<XMFLOAT3>                    m_vecSelectedCubes;
	_uint                               m_iNumCellCount = {};
	CELL_POINTS                         tagWholeCellPoints = {};
	vector<CELL_POINTS>                 m_vecWholeCellPoints;
	_bool                               m_bFirstPick = { true };
	_bool                               m_bConnectingMode = false;
	_bool                               m_bDeleteMode = { false };




private:
	_bool									m_bImguiHovered = { false };
	_bool									m_bNonAnimObjectMenuSelected = { false };
	_bool									m_bAnimObjectMenuSelected = { false };
	_bool									m_bNaviMenuSelected = { false };

	_bool									m_bIsMeshPickingMode = { false };
	_bool									m_bIsTerrainPickingMode = { false };


	_int									m_iNonAnimModelIndex = {};



private:
	// 오브젝트 생성할 위치

	_int    m_iObjectArray = { 0 };

	_float  m_fObjectPos[3] = { 1.f, 1.f ,1.f };
	_float  m_fMeshScale[3] = { 0.01f, 0.01f, 0.01f };
	_float  m_fObjectRotation[3] = { 0.f, 0.f, 0.f};
	_float	m_fFrustumRadius = { 1.f };

	list<CObject*> m_Objects;

	_float3  m_fMeshPickPos = { 0.f, 0.f, 0.f };

	_float   m_fPosMax[2] = { -100.f, 100.f };	
	_float   m_fScaleMax[2] = { -1.f, 1.f };	
	_float   m_fRotationMax[2] = { -180.f, 180.f };
	_float	 m_fRadiusMax = { 100.f };

private:
	CCamera_Free*							m_pCamera = { nullptr };
	CTerrain*								m_pTerrain = { nullptr };
	CNavigation*							m_pNavigation = { nullptr };

	CTransform*								m_pCurrentObjectTransformCom = { nullptr };
	CObject*								m_pCurrentObject = { nullptr };

	_float3									m_fCurrentObjectPos = { 0.f, 0.f, 0.f };

	_bool									m_bFrustumSphere = { false };
public:
	static CLevel_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;
};

END