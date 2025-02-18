#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	struct ENGINE_DESC	
	{ 
		HINSTANCE		hInstance;
		HWND			hWnd;
		unsigned int	iNumLevels;
		bool			isWindowed;
		unsigned int	iViewportWidth;
		unsigned int	iViewportHeight;
	};

	struct LIGHT_DESC	
	{
		enum TYPE {TYPE_DIRECTIONAL, TYPE_POINT, TYPE_SPOT, TYPE_END };

		TYPE	eType;

		XMFLOAT4		vDirection;

		XMFLOAT4		vDiffuse;
		XMFLOAT4		vAmbient;
		XMFLOAT4		vSpecular;		
	};


	struct MATERIAL_DESC	
	{
		XMFLOAT4		vDiffuse;
		XMFLOAT4		vAmbient;
		XMFLOAT4		vSpecular;
		float			fPower;
		XMFLOAT4		vEmissive;
	};

	struct ENGINE_DLL VTXPOS	
	{
		XMFLOAT3  vPosition; 

		const static unsigned int					iNumElements = 1; 
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	};

	struct ENGINE_DLL VTXPOSTEX	
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vTexcoord;

		const static unsigned int					iNumElements = 2;
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];		
	};

	struct ENGINE_DLL VTXPOSTEXAGE
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vTexcoord;
		float			fAge; 

		const static unsigned int					iNumElements = 3;
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	};

	struct ENGINE_DLL VTXCUBE
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vTexcoord;

		const static unsigned int					iNumElements = 2;
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	};

	struct ENGINE_DLL VTXPOINT
	{
		XMFLOAT3		vPosition;
		float			fPSize;

		const static unsigned int					iNumElements = 2;
		const static D3D11_INPUT_ELEMENT_DESC       Elements[iNumElements];
	};

	struct ENGINE_DLL VTXNORTEX
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexcoord;

		const static unsigned int					iNumElements = 3;
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	};


	struct ENGINE_DLL VTXMESH	
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexcoord;
		XMFLOAT3		vTangent;

		const static unsigned int					iNumElements = 4;
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	};


	struct ENGINE_DLL VTXANIMMESH	
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexcoord;
		XMFLOAT3		vTangent;

		/* 이 정점이 어떤 뼈를 따라가야하는지에 대한 뼈 인덱스 최대 4개. */
		XMUINT4			vBlendIndex;

		/* 각 뼈의 상태를 얼마나 적용해야하는가? */
		/* x + y + z + w = 1 */
		XMFLOAT4		vBlendWeight;

		const static unsigned int					iNumElements = 6;
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	};
	
	struct KEYFRAME
	{
		XMFLOAT3  vScale; 
		XMFLOAT4  vRotation; 
		XMFLOAT3  vTranslation;
		

		float     fTrackPosition;  /* 어떤 시간의 상태인지 */

	};


	struct ENGINE_DLL VTX_PARTICLE_INSTANCE 
	{
		XMFLOAT4	   vRight; 
		XMFLOAT4       vUp; 
		XMFLOAT4	   vLook; 
		XMFLOAT4       vTranslation;
		XMFLOAT2       vLifeTime;
		XMFLOAT2       vBornTime;
		XMFLOAT2       vTexcoord;
		unsigned int   iFrame; 
		float          fDurationTime; 
	};

	/* 그리기용 정점과 인스턴싱용 정점을 합한 정보 */
	struct ENGINE_DLL VTX_RECT_INSTANCE	
	{
		const static unsigned int					iNumElements = 7;	
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];	
	};	


	struct ENGINE_DLL VTX_POINT_INSTANCE	
	{
		const static unsigned int					iNumElements = 9;	
		const static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];	
	};	

}


#endif // Engine_Struct_h__
