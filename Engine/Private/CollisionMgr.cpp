#include "CollisionMgr.h"
#include "Collider.h"
#include "GameObject.h"

CCollisionMgr::CCollisionMgr()
    :m_arrCheck{}   
{
}

HRESULT CCollisionMgr::Initialize()
{
    return S_OK;
}

HRESULT CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::GROUP_END; ++iRow)	
	{

		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::GROUP_END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);	
			}
		}
	}

    return S_OK;    
}

HRESULT CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)	
{
	// 더 작은 값의 그룹 타입을 행으로, 
	// 큰 값을 열(비트) 로 사용

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}

	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
    return S_OK;    
}

HRESULT CCollisionMgr::Add_ObjCollider(GROUP_TYPE _GroupType, CGameObject* _pGameObject)
{
	if (_pGameObject == nullptr || (UINT)_GroupType >= (UINT)GROUP_TYPE::GROUP_END)
		return E_FAIL; 

	if (Find_GameObject(_GroupType, _pGameObject) == nullptr)	
	{
		Safe_AddRef(_pGameObject);	
		m_arrObjCollider[(UINT)_GroupType].push_back(_pGameObject);		
	}

	return S_OK;		
}

HRESULT CCollisionMgr::Sub_ObjCollider(GROUP_TYPE _GroupType, CGameObject* _pGameObject)
{
	if (_pGameObject == nullptr || (UINT)_GroupType >= (UINT)GROUP_TYPE::GROUP_END)	
		return E_FAIL;	


	if (m_arrObjCollider[(UINT)_GroupType].size() > 0)
	{

		for (auto& iter = m_arrObjCollider[(UINT)_GroupType].begin(); iter != m_arrObjCollider[(UINT)_GroupType].end();)
		{
			if (*iter == _pGameObject)
			{
				m_arrObjCollider[(UINT)_GroupType].erase(iter);
				Safe_Release(_pGameObject);
				return S_OK;	
			}

			else
				iter++;
		}
	}

	return S_OK;
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{

	const vector<CGameObject*>& vecLeft  = m_arrObjCollider[(UINT)_eLeft];	
	const vector<CGameObject*>& vecRight = m_arrObjCollider[(UINT)_eRight];	

	map<ULONGLONG, bool>::iterator iter; 

	for(size_t i=0; i< vecLeft.size(); ++i)
	{
		for(size_t j=0; j< vecRight.size(); ++j)
		{
			CCollider* pLeftCol  = dynamic_cast<CCollider*>(vecLeft[i]->Find_Component(TEXT("Com_Collider")));
			CCollider* pRightCol = dynamic_cast<CCollider*>(vecRight[j]->Find_Component(TEXT("Com_Collider")));


			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID; 
			ID.Left_id  = pLeftCol->Get_ID();
			ID.Right_id = pRightCol->Get_ID();
			ID.ID;

			iter = m_mapColInfo.find(ID.ID);

			if (vecLeft[i] == vecRight[j])	
			{
				continue; //다시 증감자 문으로 감.아래로안가고 ( 자기 자신과 충돌체크 하는 경우를 제외시키는 것 ) 
			}

			// 충돌 정보가 미 등록 상태인 경우 등록 ( 충돌하지 않았다로) 즉 처음 맵에 insert 되는 경우

			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);	
			}

			if(isCollision(pLeftCol, pRightCol))	
			{
				int a = 4; 

				if (iter->second)
				{
					// 지금도 충돌중인데 이전에도 충돌하고 있는 경우
					vecLeft[i]->OnCollision(vecRight[j]);	
					vecRight[j]->OnCollision(vecLeft[i]);	
				}
				else
				{
					// 이전에는 충돌하지 않았다.
					vecLeft[i]->OnCollisionEnter(vecRight[j]);	
					vecRight[j]->OnCollisionEnter(vecLeft[i]);	
					iter->second = true;	
				}

			}

			else
			{
				//현재 충돌 안할 경우 
				if (iter->second)	
				{
					// 이전에는 충돌하고 있었다.
					vecLeft[i]->OnCollisionExit(vecRight[j]);	
					vecRight[j]->OnCollisionExit(vecLeft[i]);	
					iter->second = false;
				}
			}

		}
	}


}

bool CCollisionMgr::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	//_pRightCol->Intersect(_pLeftCol);	 이거 해줘야지 색깔이 변하네 이건 내일 다시해보기 !!!! 01_10
	// 그럼 m_isColl을 true로해줘야하네. 

	bool leftResult = _pLeftCol->Intersect(_pRightCol);		
	bool rightResult = _pRightCol->Intersect(_pLeftCol);			

	return leftResult || rightResult;		
}

CGameObject* CCollisionMgr::Find_GameObject(GROUP_TYPE _GroupType, CGameObject* _pGameObject)	
{

	for (auto& iter : m_arrObjCollider[(UINT)_GroupType])		
	{	
		if (iter == _pGameObject)			
			return _pGameObject;			
	}
	

	return nullptr;	
}

CCollisionMgr* CCollisionMgr::Create()
{
    CCollisionMgr* pInstance = new CCollisionMgr(); 

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CollisionMgr");
        Safe_Release(pInstance);    
    }
    
    return pInstance;
}

void CCollisionMgr::Free()
{
    __super::Free();    

	for(int i =0; i< (UINT)GROUP_TYPE::GROUP_END; i++)
	{
		for (auto& pGameObject : m_arrObjCollider[i])
			Safe_Release(pGameObject);

		m_arrObjCollider[i].clear();	
	}


}
