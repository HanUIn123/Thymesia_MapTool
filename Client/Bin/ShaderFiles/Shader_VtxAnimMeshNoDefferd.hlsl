#include "../../../EngineSDK/hlsl/Engine_Shader_Defines.hlsli"

float4x4 g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

/* 이 메시(정점들에)에 영향을 주는 뼈 행렬들 */
//float4x4 g_BoneMatrices[256];
StructuredBuffer<float4x4> g_BoneMatrices;

vector g_vLightDir;
vector g_vLightDiffuse;
vector g_vLightAmbient;
vector g_vLightSpecular;
Texture2D g_DiffuseTexture;

vector g_vCamPosition;


vector g_vMtrlAmbient = vector(1.f, 1.f, 1.f, 1.f);
vector g_vMtrlSpecular = vector(1.f, 1.f, 1.f, 1.f);


float g_fTimer;


struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
    float3 vTangent : TANGENT;

    uint4 vBlendIndex : BLENDINDEX;
    float4 vBlendWeight : BLENDWEIGHT;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float4 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
    float4 vWorldPos : TEXCOORD1;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;

    matrix matWV, matWVP;

    matWV = mul(g_WorldMatrix, g_ViewMatrix);
    matWVP = mul(matWV, g_ProjMatrix);

    float fWeightW = 1.f - (In.vBlendWeight.x + In.vBlendWeight.y + In.vBlendWeight.z);

    matrix BoneMatrix = g_BoneMatrices[In.vBlendIndex.x] * In.vBlendWeight.x +
		g_BoneMatrices[In.vBlendIndex.y] * In.vBlendWeight.y +
		g_BoneMatrices[In.vBlendIndex.z] * In.vBlendWeight.z +
		g_BoneMatrices[In.vBlendIndex.w] * fWeightW;

	/* 로컬스페이스 상에서 변환을 한다. */
    vector vPosition = mul(vector(In.vPosition, 1.f), BoneMatrix);
    vector vNormal = mul(vector(In.vNormal, 0.f), BoneMatrix);

    Out.vPosition = mul(vPosition, matWVP);
    Out.vNormal = mul(vNormal, g_WorldMatrix);
    Out.vTexcoord = In.vTexcoord;
    Out.vWorldPos = mul(vPosition, g_WorldMatrix);

    return Out;
}

struct PS_IN
{
    float4 vPosition : SV_POSITION;
    float4 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
    float4 vWorldPos : TEXCOORD1;
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

    vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);

    if (vMtrlDiffuse.a < 0.3f)
        discard;

    vector vShade = max(dot(normalize(g_vLightDir) * -1.f,
		normalize(In.vNormal)), 0.f) + (g_vLightAmbient * g_vMtrlAmbient);

    vector vReflect = reflect(normalize(g_vLightDir), normalize(In.vNormal));
    vector vLook = In.vWorldPos - g_vCamPosition;

	/* 0 ~ 1 */
    float fSpecular = pow(max(dot(normalize(vReflect) * -1.f,
		normalize(vLook)), 0.f), 50.f);

    //Out.vColor = (g_vLightDiffuse * vMtrlDiffuse) * saturate(vShade);
		//+ fSpecular * (g_vLightSpecular * g_vMtrlSpecular);
    Out.vColor = vMtrlDiffuse;
    
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
        PixelShader = compile ps_5_0 PS_MAIN();
    }
}
