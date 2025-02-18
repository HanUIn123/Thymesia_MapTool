#include "../../../EngineSDK/hlsl/Engine_Shader_Defines.hlsli"

float4x4 g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

vector g_vLightDir;
vector g_vLightDiffuse;
vector g_vLightAmbient;
vector g_vLightSpecular;
Texture2D g_DiffuseTexture;

vector g_vCamPosition;


vector g_vMtrlAmbient = vector(0.5f, 0.5f, 0.5f, 0.5f); 
vector g_vMtrlSpecular = vector(1.f, 1.f, 1.f, 1.f);    

float g_fTimeDelta; 

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
    float3 vTangent : TANGENT;

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

    Out.vPosition = mul(vector(In.vPosition, 1.f), matWVP); 
    Out.vNormal = mul(float4(In.vNormal, 0.f), g_WorldMatrix);  
    Out.vTexcoord = In.vTexcoord;
    Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);  

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

    if (vMtrlDiffuse.a < 0.1f)
        discard;
    

    Out.vColor = vMtrlDiffuse * 0.8f;

    return Out;
}


PS_OUT PS_MAIN_EFFECT(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

    //In.vTexcoord.x -= g_fTimeDelta * 0.5f; // * 3.f; 
    
    
    //In.vTexcoord.x += g_fTimeDelta * 3.f; // * 1.f;    대각선    
    In.vTexcoord.x += g_fTimeDelta; // 가로        
    //In.vTexcoord.x = 1.0 - In.vTexcoord.x;
    //In.vTexcoord.y -= g_fTimeDelta * 3.f;// * 1.f;    
    
    vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler_Clamp, In.vTexcoord);   

    if (vMtrlDiffuse.a < 0.1f)
        discard;
    
    
    
 
    vector orange = vector(1.0f, 0.5f, 0.15f, 0.01f);
    //vector orange = vector(0.6f, 0.26f, 0.0f, 0.0f);    
    
    Out.vColor = vMtrlDiffuse * 1.f;
    
    
    float threshold = 0.6f;
    float lengthColor = length(Out.vColor.rgb);
    
    if (lengthColor < threshold)
    {
        clip(-1);
    }
    
    
    Out.vColor = Out.vColor * orange;

    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (In.vTexcoord.x > 0.5f || In.vTexcoord.y > 0.5f) 
    //{
    //    clip(-1);   
    //}
    
    return Out;
}


PS_OUT PS_MAIN_EFFECT2(PS_IN In)    
{
    PS_OUT Out = (PS_OUT) 0;

    //In.vTexcoord.x -= g_fTimeDelta * 0.5f; // * 3.f; 
    
    
    //In.vTexcoord.x += g_fTimeDelta * 3.f; // * 1.f;    대각선    
    In.vTexcoord.x -= g_fTimeDelta; // 가로        
    //In.vTexcoord.x = 1.0 - In.vTexcoord.x;
    //In.vTexcoord.y -= g_fTimeDelta * 3.f;// * 1.f;    
    
    vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler_Clamp, In.vTexcoord);

    if (vMtrlDiffuse.a < 0.1f)
        discard;
    
    
    
 
    vector orange = vector(1.0f, 0.5f, 0.15f, 0.01f);
    
    Out.vColor = vMtrlDiffuse * 1.f;
    
    
    float threshold = 0.6f;
    float lengthColor = length(Out.vColor.rgb);
    
    if (lengthColor < threshold)
    {
        clip(-1);
    }
    
    
    Out.vColor = Out.vColor * orange;

    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (In.vTexcoord.x > 0.5f || In.vTexcoord.y > 0.5f) 
    //{
    //    clip(-1);   
    //}
    
    return Out;
}



PS_OUT PS_MAIN_CLAW_EFFECT1(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

    //In.vTexcoord.x -= g_fTimeDelta * 0.5f; // * 3.f; 
    
    
    //In.vTexcoord.x += g_fTimeDelta * 3.f; // * 1.f;    대각선    
    In.vTexcoord.x -= g_fTimeDelta; // 가로        
    //In.vTexcoord.x = 1.0 - In.vTexcoord.x;
    //In.vTexcoord.y -= g_fTimeDelta * 3.f;// * 1.f;    
    
    vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler_Clamp, In.vTexcoord);
    Out.vColor = vMtrlDiffuse; 
    
    if (Out.vColor.b > 0.1f)
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
        PixelShader = compile ps_5_0 PS_MAIN();
    }

    pass Effect
    {   
        SetRasterizerState(Rs_Cull_NONE);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_EFFECT();
    }

    pass Effect2
    {
        SetRasterizerState(Rs_Cull_NONE);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_EFFECT2();
    }

    pass ClawEffect
    {
        SetRasterizerState(Rs_Cull_NONE);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_CLAW_EFFECT1();
    }
}
