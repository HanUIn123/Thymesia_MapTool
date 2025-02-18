#include "../../../EngineSDK/hlsl/Engine_Shader_Defines.hlsli"


float4x4        g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
Texture2D       g_Texture;

struct VS_IN
{
    float3 vPosition        : POSITION;
    float2 vTexcoord        : TEXCOORD0;
    
    float4 vRight           : TEXCOORD1; 
    float4 vUp              : TEXCOORD2;
    float4 vLook            : TEXCOORD3;
    float4 vTranslation     : TEXCOORD4;
    float2 vLifeTime        : TEXCOORD5;   
};

struct VS_OUT
{
    float4 vPosition        : SV_POSITION;
    float2 vTexcoord        : TEXCOORD0;
    float4 vWorldPos        : TEXCOORD1;
    float2 vLifeTime        : TEXCOORD2; 
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;
    
    float4x4 TransformationMatrix = float4x4(In.vRight, In.vUp, In.vLook, In.vTranslation);
    
    /* 로컬 스페이스내에서 움직임을 가져간다. */
    vector vPosition = mul(vector(In.vPosition, 1.f), TransformationMatrix);
    
    matrix matWV, matWVP; 
    
    matWV  = mul(g_WorldMatrix, g_ViewMatrix);
    matWVP = mul(matWV, g_ProjMatrix);
    
    Out.vPosition = mul(vPosition, matWVP);
    Out.vTexcoord = In.vTexcoord;
    Out.vWorldPos = mul(vPosition, g_WorldMatrix);
    Out.vLifeTime = In.vLifeTime; 
        
    
    
    return Out; 
}


struct PS_IN
{
    float4 vPosition :      SV_POSITION;
    float2 vTexcoord :      TEXCOORD0;
    float4 vWorldPos :      TEXCOORD1;
    float2 vLifeTime :      TEXCOORD2;
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;
    
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);
    
    if(0.2f >= Out.vColor.a)
        discard; 
    
    if(In.vLifeTime.y >= In.vLifeTime.x)
        discard;
    
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