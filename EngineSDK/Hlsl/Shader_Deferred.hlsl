#include "Engine_Shader_Defines.hlsli"

float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
float4x4		g_LightViewMatrix, g_LightProjMatrix;
float4x4		g_ViewMatrixInv, g_ProjMatrixInv;

Texture2D		g_Texture;

float4			g_vLightDir;
float4			g_vLightPos;
float			g_fRange;

float4			g_vLightDiffuse;
float4			g_vLightAmbient;
float4			g_vLightSpecular;

Texture2D		g_DiffuseTexture;
float4			g_vMtrlAmbient = vector(1.f, 1.f, 1.f, 1.f);
float4			g_vMtrlSpecular = vector(1.f, 1.f, 1.f, 1.f);

Texture2D		g_SpecularTexture;
Texture2D		g_NormalTexture;
Texture2D		g_ShadeTexture;
Texture2D		g_DepthTexture;
Texture2D		g_ShadowTexture;

Texture2D		g_FinalTexture;
Texture2D		g_BlurXTexture;
Texture2D		g_BlurYTexture;

float4			g_vCamPosition;


struct VS_IN
{
	float3			vPosition : POSITION;
	float2			vTexcoord : TEXCOORD0;
};

struct VS_OUT
{
	float4			vPosition : SV_POSITION;
	float2			vTexcoord : TEXCOORD0;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT			Out = (VS_OUT)0;

	matrix			matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(vector(In.vPosition, 1.f), matWVP);
	Out.vTexcoord = In.vTexcoord;

	return Out;
}


struct PS_IN
{
	float4			vPosition : SV_POSITION;
	float2			vTexcoord : TEXCOORD0;
};

struct PS_OUT
{
	float4			vColor : SV_TARGET0;
};

PS_OUT PS_MAIN_DEBUG(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);	

	return Out;
}


struct PS_OUT_LIGHT
{
	float4			vShade : SV_TARGET0;
    float4			vSpecular : SV_TARGET1;
};

PS_OUT_LIGHT PS_MAIN_DIRECTIONAL(PS_IN In)
{
	PS_OUT_LIGHT		Out = (PS_OUT_LIGHT)0;

	vector		vNormalDesc = g_NormalTexture.Sample(LinearSampler, In.vTexcoord);
	vector		vNormal = vector(vNormalDesc.xyz * 2.f - 1.f, 0.f);

    vector		vDepthDesc = g_DepthTexture.Sample(LinearSampler, In.vTexcoord);
    float		fViewZ     = vDepthDesc.y; 
	
    vector      vShade = saturate(max(dot(normalize(g_vLightDir * -1.f), normalize(vNormal)), 0.f) + (g_vLightAmbient * g_vMtrlAmbient));
    Out.vShade = g_vLightDiffuse * vShade;
	
    vector      vWorldPos;
	
   /* 투영공간상의 위치 */
   /* 로컬위치 * 월드행렬 * 뷰행렬 * 투영행렬 * 1/w */
    vWorldPos.x = In.vTexcoord.x *  2.f - 1.f;
    vWorldPos.y = In.vTexcoord.y * -2.f + 1.f;
    vWorldPos.z = vDepthDesc.x;
    vWorldPos.w = 1.f;
	
	
	/* 로컬위치 * 월드행렬 * 뷰행렬 * 투영행렬  */
    vWorldPos = vWorldPos.xyzw * fViewZ;
	
	/* 로컬위치 * 월드행렬 * 뷰행렬 */
    vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	
	/* 월드위치 */
	/* 로컬위치 * 월드행렬  */
    vWorldPos = mul(vWorldPos, g_ViewMatrixInv);
	
    vector vReflect = reflect(normalize(g_vLightDir), normalize(vNormal));
    vector vLook = vWorldPos - g_vCamPosition; // 캠에서 해당 물체를 바라보는 look 방향을 구한거 .
	
    Out.vSpecular = (g_vLightSpecular * g_vMtrlSpecular) * pow(max(dot(normalize(vReflect * -1.f), normalize(vLook)), 0.f), 90.f);

    return Out;

}

PS_OUT_LIGHT PS_MAIN_POINT(PS_IN In)
{
    PS_OUT_LIGHT Out = (PS_OUT_LIGHT) 0;

    vector vNormalDesc = g_NormalTexture.Sample(LinearSampler, In.vTexcoord);
    vector vNormal = vector(vNormalDesc.xyz * 2.f - 1.f, 0.f);

    vector vDepthDesc = g_DepthTexture.Sample(LinearSampler, In.vTexcoord);
    float fViewZ = vDepthDesc.y;

    vector vWorldPos;

	/* 투영공간상의 위치 */
	/* 로컬위치 * 월드행렬 * 뷰행렬 * 투영행렬 * 1/w */
    vWorldPos.x = In.vTexcoord.x * 2.f - 1.f;
    vWorldPos.y = In.vTexcoord.y * -2.f + 1.f;
    vWorldPos.z = vDepthDesc.x;
    vWorldPos.w = 1.f;

	/* 로컬위치 * 월드행렬 * 뷰행렬 * 투영행렬  */
    vWorldPos = vWorldPos.xyzw * fViewZ;

	/* 로컬위치 * 월드행렬 * 뷰행렬 */
    vWorldPos = mul(vWorldPos, g_ProjMatrixInv);

	/* 월드위치 */
	/* 로컬위치 * 월드행렬  */
    vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

    vector vLightDir = vWorldPos - g_vLightPos;
    float fLength = length(vLightDir);

    float fAtt = saturate((g_fRange - fLength) / g_fRange);


    vector vShade = saturate(max(dot(normalize(vLightDir * -1.f), normalize(vNormal)), 0.f) + (g_vLightAmbient * g_vMtrlAmbient));

    Out.vShade = g_vLightDiffuse * vShade * fAtt;

	// vector		vWorldPos = g_WorldTexture.Sample(PointSampler, In.vTexcoord);


    vector vReflect = reflect(normalize(vLightDir), normalize(vNormal));
    vector vLook = vWorldPos - g_vCamPosition;

    Out.vSpecular = (g_vLightSpecular * g_vMtrlSpecular) * pow(max(dot(normalize(vReflect * -1.f), normalize(vLook)), 0.f), 50.f) * fAtt;
    return Out;
}



PS_OUT PS_MAIN_DEFERRED(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector			vDiffuse = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);
	if (0.f == vDiffuse.a)
		discard;

	vector			vShade = g_ShadeTexture.Sample(LinearSampler, In.vTexcoord);
    vector			vSpecular = g_SpecularTexture.Sample(LinearSampler, In.vTexcoord);

    Out.vColor = vDiffuse * vShade; // + vSpecular;
	
    vector vDepthDesc = g_DepthTexture.Sample(LinearSampler, In.vTexcoord);	
    float fViewZ = vDepthDesc.y;	
	
    vector vWorldPos;
	
	/* 투영공간상의 위치 */
	/* 로컬위치 * 월드행렬 * 뷰행렬 * 투영행렬 * 1/w */
    vWorldPos.x = In.vTexcoord.x * 2.f - 1.f;
    vWorldPos.y = In.vTexcoord.y * -2.f + 1.f;
    vWorldPos.z = vDepthDesc.x;
    vWorldPos.w = 1.f;

	/* 로컬위치 * 월드행렬 * 뷰행렬 * 투영행렬  */
    vWorldPos = vWorldPos.xyzw * fViewZ;

	/* 로컬위치 * 월드행렬 * 뷰행렬 */
    vWorldPos = mul(vWorldPos, g_ProjMatrixInv);

	/* 월드위치 */
	/* 로컬위치 * 월드행렬  */
    vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

    vWorldPos = mul(vWorldPos, g_LightViewMatrix);
    vWorldPos = mul(vWorldPos, g_LightProjMatrix);
	
    float2 vTexcoord;	

    vTexcoord.x = (vWorldPos.x / vWorldPos.w) * 0.5f + 0.5f;	
    vTexcoord.y = (vWorldPos.y / vWorldPos.w) * -0.5f + 0.5f;	

    vector vShadowDepthDesc = g_ShadowTexture.Sample(LinearSampler, vTexcoord);	
    
    if (vShadowDepthDesc.y + 0.15f <= vWorldPos.w)
        Out.vColor = Out.vColor * 0.7f;
		
    
    float4 blurredColor = g_FinalTexture.Sample(LinearSampler, In.vTexcoord);
    
    //if (all(blurredColor.rgb > 0.01f))
    //    Out.vColor = blurredColor;
    
    Out.vColor = Out.vColor + blurredColor; 
    
    //float blendFactor = smoothstep(0.01, 0.02, blurredColor.r); // 임계값 주변에서 부드럽게 변화 
    //Out.vColor = lerp(Out.vColor, blurredColor, blendFactor);   
	
	
    // 예시: 블러 텍스처의 값이 일정 임계값 이상일 때만 블렌딩
    //if (blurredColor.a != 0.f)
    //    Out.vColor = blurredColor; // 또는 Out.vColor = lerp(deferredColor, blurredColor, blendFactor);
    //else
    //    Out.vColor = Out.vColor;//+blurredColor;
    
    
	return Out;
}

float g_fWeights[13] =
{
    0.0561, 0.1353, 0.278, 0.4868, 0.7261, 0.9231, 1.f, 0.9231, 0.7261, 0.4868, 0.278, 0.1353, 0.0561
};


//float g_fWeights[13] =
//{
//    0.00903f, 0.02178f, 0.04475f, 0.07842f, 0.11698f, 0.14866f, 0.16105f,
//    0.14866f, 0.11698f, 0.07842f, 0.04475f, 0.02178f, 0.00903f
//};





PS_OUT PS_MAIN_BLUR_X(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

    float2 vTexcoord = 0.f;

    for (int i = -6; i < 7; i++)
    {
        vTexcoord = float2(In.vTexcoord.x + (1.f / 1600.f) * i, In.vTexcoord.y);	

        Out.vColor += g_fWeights[i + 6] * g_FinalTexture.Sample(LinearSampler_Clamp, vTexcoord);	
    }

    Out.vColor /= 6.f;

    return Out;
}

PS_OUT PS_MAIN_BLUR_Y(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

    float2 vTexcoord = 0.f;

    for (int i = -6; i < 7; i++)
    {
        vTexcoord = float2(In.vTexcoord.x, In.vTexcoord.y + (1.f / 900.f) * i);

        Out.vColor += g_fWeights[i + 6] * g_BlurXTexture.Sample(LinearSampler_Clamp, vTexcoord);
    }

    Out.vColor /= 6.f;

    return Out;
}

PS_OUT PS_MAIN_FINAL(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

    vector vBlur = g_BlurYTexture.Sample(LinearSampler, In.vTexcoord);
    vector vFinal = g_FinalTexture.Sample(LinearSampler, In.vTexcoord); 
	
    Out.vColor = vBlur + vFinal;    

    return Out;
}

technique11 DefaultTechnique
{
	pass Debug
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEBUG();
	}

	pass Directional
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_SKip_Z, 0);
		SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DIRECTIONAL();
	}

	pass Point
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_SKip_Z, 0);
		SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DIRECTIONAL();
	}


	pass Deferred
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_SKip_Z, 0);
		SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEFERRED();
	}

    pass BlurX
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_SKip_Z, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_BLUR_X();
    }

    pass BlurY
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_SKip_Z, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_BLUR_Y();
    }

    pass Final
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_SKip_Z, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_FINAL();
    }

	
}
