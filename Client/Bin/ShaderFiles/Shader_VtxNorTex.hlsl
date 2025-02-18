#include "../../../EngineSDK/hlsl/Engine_Shader_Defines.hlsli"

float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

Texture2D       g_DiffuseTexture;

struct VS_IN
{
	float3			vPosition : POSITION;	
	float3			vNormal : NORMAL;
	float2			vTexcoord : TEXCOORD0;	
};

struct VS_OUT
{
	float4			vPosition : SV_POSITION;
	float4			vNormal   : NORMAL;
	float2			vTexcoord : TEXCOORD0;
	float4			vWorldPos : TEXCOORD1;
    float4			vProjPos : TEXCOORD2;
};

VS_OUT VS_MAIN(VS_IN In)
{	
	VS_OUT			Out = (VS_OUT)0;

	Out.vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);	

	Out.vPosition = mul(Out.vPosition, g_ViewMatrix);
	Out.vPosition = mul(Out.vPosition, g_ProjMatrix);	
    Out.vNormal   = normalize(mul(float4(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexcoord = In.vTexcoord;
	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
    Out.vProjPos  = Out.vPosition;
	
	return Out;
}

struct PS_IN
{
	float4			vPosition : SV_POSITION;
	float4			vNormal   : NORMAL;
	float2			vTexcoord : TEXCOORD0;
	float4			vWorldPos : TEXCOORD1;
    float4			vProjPos  : TEXCOORD2;
};

struct PS_OUT
{
    float4 vDiffuse : SV_TARGET0;	
    float4 vNormal  : SV_TARGET1;	
    float4 vDepth   : SV_TARGET2;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord * 30.f);	 	

	//vector		vShade = max(dot(normalize(g_vLightDir) * -1.f, 
	//	normalize(In.vNormal)), 0.f) + (g_vLightAmbient * g_vMtrlAmbient);
	//
	//vector		vReflect = reflect(normalize(g_vLightDir), normalize(In.vNormal));
	//vector		vLook = In.vWorldPos - g_vCamPosition;
	//
	///* 0 ~ 1 */
	//float		fSpecular = pow(max(dot(normalize(vReflect) * -1.f,
	//	normalize(vLook)), 0.f), 50.f);	

	//Out.vColor = (g_vLightDiffuse * vMtrlDiffuse) * saturate(vShade) 
	//	+ fSpecular * (g_vLightSpecular * g_vMtrlSpecular);
	
    Out.vDiffuse = vMtrlDiffuse;		

	/* 0 ~ 1 */   /* -1 ~ 1 */
	/* -1 -> 0, 1 -> 1 */
    Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);		

    Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w, 0.f, 0.f);
	

	return Out;
}


technique11 DefaultTechnique
{
	pass DefaultPass
	{
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}
}
