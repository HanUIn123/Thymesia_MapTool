#pragma once

/* 클라이언트에 보여줘야할 컴포넌트들의 헤더를 미리 인클루드해놓는다.*/
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Cube.h"
#include "VIBuffer_Terrain.h"
#include "VIBuffer_Cell.h"
#include "VIBuffer_Rect_Instancing.h"
#include "VIBuffer_Point_Instancing.h"
#include "SwordTrail_Buffer.h"	

#include "Navigation.h"

#include "Collider.h"
#include "Bounding_AABB.h"
#include "Bounding_Sphere.h"



/*
0. 객체의 원형 + 컴포넌트의 원형. 
1. 게임내에 동적으로 생성될 수 있는 객체들의 원형객체를 보관한다. 
2. 레벨별로 원형들을 분리하여 보관한다. 
2-1. 모든 레벨에서 공유하는 원형도 따로 모아서 관리한다. 
3. 개발자의 선택에 의한 원형객체를 복제하여 사본을 만들고 리턴해주는 기능. 
*/

BEGIN(Engine)

class CPrototype_Manager final : public CBase
{
private:
	CPrototype_Manager();
	virtual ~CPrototype_Manager() = default;

public:
	HRESULT Initialize(_uint iNumLevels);
	HRESULT Add_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag, CBase* pPrototype);
	CBase* Clone_Prototype(PROTOTYPE eType, _uint iLevelIndex, const _wstring& strPrototypeTag, void* pArg);
	void Clear(_uint iLevelIndex);

private:
	_uint								m_iNumLevels = {};

	map<const _wstring, CBase*>*		m_pPrototypes = { nullptr };
	typedef map<const _wstring, CBase*>	PROTOTYPES;

private:
	CBase* Find_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag);

public:
	static CPrototype_Manager* Create(_uint iNumLevels);
	virtual void Free() override;
};

END