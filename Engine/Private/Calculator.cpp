#include "Calculator.h"
#include "GameInstance.h"
#include "Mesh.h"



CCalculator::CCalculator(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CComponent{ pDevice, pContext }
{
}

CCalculator::CCalculator(const CCalculator& Prototype)
	: CComponent( Prototype )
{
}


HRESULT CCalculator::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCalculator::Initialize(void* pArg)
{
	return S_OK;
}

_bool CCalculator::PickingOnMesh(HWND hWnd, CMesh* pMeshBufferCom, CTransform* pMeshTransformCom, _Out_ _float& _fDist, _Out_ _vector& _fPos)
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(hWnd, &ptMouse);

	_float3 vMousePos;

	D3D11_VIEWPORT vViewport;
	ZeroMemory(&vViewport, sizeof(D3D11_VIEWPORT));
	_uint iViewports = { 1 };

	m_pContext->RSGetViewports(&iViewports, &vViewport);

	vMousePos.x = ptMouse.x / (vViewport.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(vViewport.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;

	// Proj -> View
	_matrix matProj = m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_PROJ);

	XMStoreFloat3(&vMousePos, XMVector3TransformCoord(DirectX::XMLoadFloat3(&vMousePos), matProj));

	XMFLOAT3		vRayPos, vRayDir;

	vRayPos = { 0.f, 0.f, 0.f };
	DirectX::XMStoreFloat3(&vRayDir, DirectX::XMLoadFloat3(&vMousePos) - DirectX::XMLoadFloat3(&vRayPos));

	// View-> World
	_matrix matView = m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_VIEW);

	XMVECTOR fvRayPos, fvRayDir;

	fvRayDir = XMVector3Normalize(XMLoadFloat3(&vRayDir));

	fvRayPos = XMVector3TransformCoord(DirectX::XMLoadFloat3(&vRayPos), matView);
	fvRayDir = XMVector3TransformNormal(fvRayDir, matView);

	// View-> Local
	_matrix matWorld = pMeshTransformCom->Get_WorldMatrix_Inverse();

	fvRayPos = XMVector3TransformCoord(fvRayPos, matWorld);
	fvRayDir = XMVector3TransformNormal(fvRayDir, matWorld);

	fvRayDir = XMVector3Normalize(fvRayDir);

	const _float3* pMeshTexPos = pMeshBufferCom->Get_VtxPos();

	const _uint* pIndices = pMeshBufferCom->Get_Indices();

	_ulong dwVtxId[3]{};
	_float fDist = { 0.f };

	size_t VTXCNT = pMeshBufferCom->Get_VtxFaces();
	size_t iVerticeNum = pMeshBufferCom->Get_NumVertices();

	_uint j = { 0 };

	_bool isIntersect = false;

	vector<IntersectPos> m_Distance;

	//	for (size_t i = 0; i < iVerticeNum; i++)
	//	{
	for (size_t j = 0; j < VTXCNT * 3;)
	{
		if (DirectX::TriangleTests::Intersects(
			fvRayPos,
			fvRayDir,
			XMLoadFloat3(&pMeshTexPos[pIndices[j++]]),
			XMLoadFloat3(&pMeshTexPos[pIndices[j++]]),
			XMLoadFloat3(&pMeshTexPos[pIndices[j++]]),
			fDist))
		{
			INTERSECTPOS vIntersect;

			//_fPos = fvRayPos + (fvRayDir * fDist), matWorld;
			_vector v0 = XMLoadFloat3(&pMeshTexPos[pIndices[j - 3]]);
			_vector v1 = XMLoadFloat3(&pMeshTexPos[pIndices[j - 2]]);
			_vector v2 = XMLoadFloat3(&pMeshTexPos[pIndices[j - 1]]);

			isIntersect = true;

			vIntersect.fDist = fDist;

			_vector vTestRay = fvRayPos + (fDist * fvRayDir);
			vIntersect.vPos = XMVector3TransformCoord(vTestRay, XMMatrixInverse(nullptr, matWorld));


			m_Distance.push_back(vIntersect);
		}
	}
	//	}

	if (isIntersect)
	{
		sort(m_Distance.begin(), m_Distance.end(), [](INTERSECTPOS a, INTERSECTPOS b) {
			if (a.fDist < b.fDist) return true;
			else
				return false;
			});

		_fDist = m_Distance.begin()->fDist;
		_fPos = m_Distance.begin()->vPos;

		return true;
	}
	else
	{
		_fPos = {};

		_fDist = 0;

		return false;
	}
}

_bool CCalculator::PickingOnVertice(HWND hWnd, CMesh* pMeshBufferCom, CTransform* pMeshTransformCom, _Out_ _float& _fDist, _vector& _fPos)
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(hWnd, &ptMouse);

	_float3 vMousePos;

	D3D11_VIEWPORT vViewport;
	ZeroMemory(&vViewport, sizeof(D3D11_VIEWPORT));
	_uint iViewports = { 1 };

	m_pContext->RSGetViewports(&iViewports, &vViewport);

	vMousePos.x = ptMouse.x / (vViewport.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(vViewport.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;

	// Proj -> View
	_matrix matProj = m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_PROJ);

	XMStoreFloat3(&vMousePos, XMVector3TransformCoord(DirectX::XMLoadFloat3(&vMousePos), matProj));

	XMFLOAT3		vRayPos, vRayDir;

	vRayPos = { 0.f, 0.f, 0.f };
	DirectX::XMStoreFloat3(&vRayDir, DirectX::XMLoadFloat3(&vMousePos) - DirectX::XMLoadFloat3(&vRayPos));

	// View-> World
	_matrix matView = m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_VIEW);

	XMVECTOR fvRayPos, fvRayDir;

	fvRayDir = XMVector3Normalize(XMLoadFloat3(&vRayDir));

	fvRayPos = XMVector3TransformCoord(DirectX::XMLoadFloat3(&vRayPos), matView);
	fvRayDir = XMVector3TransformNormal(fvRayDir, matView);

	// View-> Local
	_matrix matWorld = pMeshTransformCom->Get_WorldMatrix_Inverse();

	fvRayPos = XMVector3TransformCoord(fvRayPos, matWorld);
	fvRayDir = XMVector3TransformNormal(fvRayDir, matWorld);

	fvRayDir = XMVector3Normalize(fvRayDir);

	const _float3* pMeshTexPos = pMeshBufferCom->Get_VtxPos();

	const _uint* pIndices = pMeshBufferCom->Get_Indices();

	_ulong dwVtxId[3]{};
	_float fDist = { 0.f };

	size_t VTXCNT = pMeshBufferCom->Get_VtxFaces();

	size_t j = 0;

	_bool isIntersect = false;

	vector<IntersectVtx> m_Distance;
	for (size_t j = 0; j < VTXCNT * 3;)
	{
		if (DirectX::TriangleTests::Intersects(
			fvRayPos,
			fvRayDir,
			XMLoadFloat3(&pMeshTexPos[pIndices[j++]]),
			XMLoadFloat3(&pMeshTexPos[pIndices[j++]]),
			XMLoadFloat3(&pMeshTexPos[pIndices[j++]]),
			fDist))
		{
			IntersectVtx vIntersect;

			//_fPos = fvRayPos + (fvRayDir * fDist), matWorld;
			_vector V0 = XMLoadFloat3(&pMeshTexPos[pIndices[j - 3]]);
			_vector V1 = XMLoadFloat3(&pMeshTexPos[pIndices[j - 2]]);
			_vector V2 = XMLoadFloat3(&pMeshTexPos[pIndices[j - 1]]);

			isIntersect = true;

			vIntersect.fDistance = fDist;

			_vector vTestRay = fvRayPos + (fDist * fvRayDir);
			vIntersect.vPoint = vTestRay;

			vIntersect.v0 = V0;
			vIntersect.v1 = V1;
			vIntersect.v2 = V2;

			m_Distance.push_back(vIntersect);
		}
	}

	if (isIntersect)
	{
		sort(m_Distance.begin(), m_Distance.end(), [](INTERSECTVTX a, INTERSECTVTX b) {
			if (a.fDistance < b.fDistance) return true;
			else
				return false;
			});
		_vector vTestVector = m_Distance.begin()->vPoint - m_Distance.begin()->v0;
		_float3 f0, f1, f2;
		XMStoreFloat3(&f0, XMVector4Length(m_Distance.begin()->vPoint - m_Distance.begin()->v0));
		XMStoreFloat3(&f1, XMVector4Length(m_Distance.begin()->vPoint - m_Distance.begin()->v1));
		XMStoreFloat3(&f2, XMVector4Length(m_Distance.begin()->vPoint - m_Distance.begin()->v2));

		VERTICEPOS fPointDistances[3];

		fPointDistances[0].vPointPosition = m_Distance.begin()->v0;
		fPointDistances[0].fPointDistance = fabs(f0.x);

		fPointDistances[1].vPointPosition = m_Distance.begin()->v1;
		fPointDistances[1].fPointDistance = fabs(f1.x);

		fPointDistances[2].vPointPosition = m_Distance.begin()->v2;
		fPointDistances[2].fPointDistance = fabs(f2.x);

		sort(fPointDistances, fPointDistances + 3, [](VERTICEPOS a, VERTICEPOS b) {
			if (a.fPointDistance < b.fPointDistance) return true;
			else
				return false;
			});

		_fPos = XMVector3TransformCoord(fPointDistances[0].vPointPosition, XMMatrixInverse(nullptr, matWorld));

		_fDist = m_Distance.begin()->fDistance;

		return true;
	}
	else
	{
		_fPos = {};

		return false;
	}
}



bool CCalculator::Intersects(
	FXMVECTOR Origin, FXMVECTOR Direction, FXMVECTOR V0,
	GXMVECTOR V1,
	HXMVECTOR V2, float& Dist, float& V3, float& V4)
{
	assert(DirectX::Internal::XMVector3IsUnit(Direction));

	XMVECTOR Zero = XMVectorZero();

	XMVECTOR e1 = XMVectorSubtract(V1, V0);
	XMVECTOR e2 = XMVectorSubtract(V2, V0);

	// p = Direction ^ e2;
	XMVECTOR p = XMVector3Cross(Direction, e2);

	// det = e1 * p;
	XMVECTOR det = XMVector3Dot(e1, p);

	XMVECTOR u, v, t;

	if (XMVector3GreaterOrEqual(det, g_RayEpsilon))
	{
		// Determinate is positive (front side of the triangle).
		XMVECTOR s = XMVectorSubtract(Origin, V0);

		// u = s * p;
		u = XMVector3Dot(s, p);

		XMVECTOR NoIntersection = XMVectorLess(u, Zero);
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(u, det));

		// q = s ^ e1;
		XMVECTOR q = XMVector3Cross(s, e1);

		// v = Direction * q;
		v = XMVector3Dot(Direction, q);

		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(v, Zero));
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(XMVectorAdd(u, v), det));

		// t = e2 * q;
		t = XMVector3Dot(e2, q);

		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(t, Zero));

		if (XMVector4EqualInt(NoIntersection, XMVectorTrueInt()))
		{
			Dist = 0.f;
			return false;
		}
	}
	else if (XMVector3LessOrEqual(det, g_RayNegEpsilon))
	{
		// Determinate is negative (back side of the triangle).
		XMVECTOR s = XMVectorSubtract(Origin, V0);

		// u = s * p;
		u = XMVector3Dot(s, p);

		XMVECTOR NoIntersection = XMVectorGreater(u, Zero);
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(u, det));

		// q = s ^ e1;
		XMVECTOR q = XMVector3Cross(s, e1);

		// v = Direction * q;
		v = XMVector3Dot(Direction, q);

		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(v, Zero));
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(XMVectorAdd(u, v), det));

		// t = e2 * q;
		t = XMVector3Dot(e2, q);

		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(t, Zero));

		if (XMVector4EqualInt(NoIntersection, XMVectorTrueInt()))
		{
			Dist = 0.f;
			return false;
		}
	}
	else
	{
		// Parallel ray.
		Dist = 0.f;
		return false;
	}

	t = XMVectorDivide(t, det);

	_vector v3, v4;

	v3 = XMVectorDivide(u, det);

	v4 = XMVectorDivide(v, det);
	// (u / det) and (v / dev) are the barycentric cooridinates of the intersection.

	// Store the x-component to *pDist
	XMStoreFloat(&Dist, t);

	XMStoreFloat(&V3, v3);

	XMStoreFloat(&V4, v4);

	return true;
}

CCalculator* CCalculator::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCalculator* pInstance = new CCalculator(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CCalculator");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CCalculator::Clone(void* pArg)
{
	CCalculator* pInstance = new CCalculator(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : CCalculator");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCalculator::Free()
{
	__super::Free();

}
