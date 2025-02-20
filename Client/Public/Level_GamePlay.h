#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "Object.h"
#include "GameInstance.h"

#include "Camera_Free.h"
#include "Terrain.h"

BEGIN(Engine)
class CShader;
class CTexture;
END



BEGIN(Client)
class CLevel_GamePlay final : public CLevel
{
public:
	enum IMGUI_TEXTURE_TYPE {IMG_ANIM_MODEL, IMG_NONANIM_MODEL, IMG_END};
	enum MENU_TYPE { MT_PICKING_ANIMMODEL, MT_PICKING_NONANIMMODEL, MT_NAVI , MT_END  };

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
	_bool									m_bImguiHovered = { false };
	_bool									m_bNonAnimObjectMenuSelected = { false };
	_bool									m_bAnimObjectMenuSelected = { false };
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

private:
	CCamera_Free*							m_pCamera = { nullptr };
	CTerrain*								m_pTerrain = { nullptr };

	CTransform* m_pCurrentObjectTransformCom = { nullptr };
	CObject* m_pCurrentObject = { nullptr };

	_float3  m_fCurrentObjectPos = { 0.f, 0.f, 0.f };

public:
	static CLevel_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;
};

END