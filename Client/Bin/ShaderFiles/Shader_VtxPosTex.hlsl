#include "../../../EngineSDK/hlsl/Engine_Shader_Defines.hlsli"

/* hlsl 용 벡터타입 : float2, float3, float4, vector */
float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
Texture2D		g_Texture;
float			g_HpState; 
float			g_MpState;


/* 이펙트 관련 상수 버퍼들 */ 
Texture2D g_HitEffect0;
Texture2D g_HitEffect1;     
Texture2D g_HitEffect2;     

float g_fAlpha; 
float g_RotationAngle;   // 라디안 단위 회전각 


float g_Alpha; 
float2 g_vTexcoord;
float2 g_vOffSetTexcoord;


//sampler LinearSampler = sampler_state
//{ 
//	Filter = MIN_MAG_MIP_LINEAR;
//};

/* 1. 정점과 인덱스 버퍼 + 셰이더 바인딩해서 그린다. */
/* 2. 인덱스버퍼에 저장되어있는 인덱스에 해당하는 정점을 하나 꺼내서, */
/* 3. 정점쉐이더함수를 호출하며 인자로 정점(로컬스페이스기준)을 전달해준다. */
/* 4. 정점 쉐이더에서 정점에 필요한 연산을 수행한다.(ex> 정점의 로컬위치에다가 월드, 뷰, 투영행려을 곱한다. ) */
/* 5. 정점의 변환을 수행한다(4) + 정점의 구성 정보를 추가 또는 삭제한다. */

float4 AlphaOver(float4 base, float4 over)
{
    float alphaA = over.a;
    float alphaB = base.a;
    
    // 최종 알파
    float outAlpha = alphaA + alphaB * (1 - alphaA);

    float3 outColor = float3(0, 0, 0);
    if (outAlpha > 1e-6) // 0이 아니어야 나눗셈 가능
    {
        outColor = (over.rgb * alphaA + base.rgb * alphaB * (1 - alphaA)) / outAlpha;
    }

    return float4(outColor, outAlpha);
}

struct VS_IN
{
	float3			vPosition : POSITION;	
	float2			vTexcoord : TEXCOORD0;	
};

struct VS_OUT
{
	float4			vPosition : SV_POSITION;
	float2			vTexcoord : TEXCOORD0;
	float4			vWorldPos : TEXCOORD1;
};

VS_OUT VS_MAIN(VS_IN In)
{	
	VS_OUT			Out = (VS_OUT)0;

	Out.vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	Out.vWorldPos = Out.vPosition;

	Out.vPosition = mul(Out.vPosition, g_ViewMatrix);
	Out.vPosition = mul(Out.vPosition, g_ProjMatrix);	
	Out.vTexcoord = In.vTexcoord;

	return Out;
}



VS_OUT VS_MAIN_SPRITE(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;

    Out.vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);  
    Out.vWorldPos = Out.vPosition;  

    Out.vPosition = mul(Out.vPosition, g_ViewMatrix);
    Out.vPosition = mul(Out.vPosition, g_ProjMatrix);
    Out.vTexcoord = In.vTexcoord * g_vTexcoord + g_vOffSetTexcoord; 

    return Out;
}

/* 5. 정점쉐이더가 끝나게 되면 그리는 형태에따라 추가적인 정점의 결과를 기다리낟. */
/* 5-1. D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST 였다면 추가로 두개의 정점이 정점쉐이더를 통과할때 까지 기다리낟. */
/* 6. 내가 그릴려고하는 도형의 형태에 맞게끔 정점이 모두 리턴된다면 각 정점에게 w나누기연산(원근투영)을 수행한다. 투영스페이스로 갔다. */
/* 7. 뷰포트로 정점의 위치를 변환하게된다. 윈도우 좌표로 정점들을 모두 다 옮겨낸다. */
/* 8. 래스터라이즈를 수행하게된다. (래스터라이즈 : 정점들의 정보를 기반으로 하여 픽셀의 정보를 생성한다) => 픽셀을 만들었다. */
/* 9. 만들어낸 픽셀을 PS_MAIN함수를 호출하면서 인자로 전달해 준다. */
/* 10. 픽셀 쉐이더에서 전달받은 픽셀의 정보를 기반으로하여 최종적인 픽셀의 색을 결정하여 리턴하게되고 */
/* 11. 리턴된 최종적인 색으로 백버퍼를 채우게 된다. */

struct PS_IN
{
	float4			vPosition : SV_POSITION;
	float2			vTexcoord : TEXCOORD0;
	float4			vWorldPos : TEXCOORD1;
};

struct PS_OUT
{
	float4			vColor : SV_TARGET0;
};

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);

    
    if (0.5f >= Out.vColor.a)
        discard;


    return Out;
}

PS_OUT PS_MAIN_HIT_EFFECT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)
    
    //float fAlphaHit_Effect0 = g_fAlpha; 
    //float fAlphaHit_Effect1 = g_HitEffect1.Sample(LinearSampler, In.vTexcoord).a;          
    //float fAlphaHit_Effect2 = g_HitEffect2.Sample(LinearSampler, In.vTexcoord).a;   
    
    
    float4 Color_Hit_Effect0 = g_HitEffect0.Sample(LinearSampler, In.vTexcoord);          
    //float4 Color_Hit_Effect1 = g_HitEffect1.Sample(LinearSampler, In.vTexcoord);       
    //float4 Color_Hit_Effect2 = g_HitEffect2.Sample(LinearSampler, In.vTexcoord);           
    //
    
    Color_Hit_Effect0.a = g_fAlpha;              
    //Color_Hit_Effect1.a = 0.5f;     
    //Color_Hit_Effect2.a = 0.2f;         
  
   
    Out.vColor = Color_Hit_Effect0;//+Color_Hit_Effect1; // + Color_Hit_Effect2;
        
    //Out.vColor = g_HitEffect0.Sample(LinearSampler, In.vTexcoord)
    //+ g_HitEffect1.Sample(LinearSampler, In.vTexcoord)
    //+ g_HitEffect2.Sample(LinearSampler, In.vTexcoord);

    vector YellowTint = vector(1.0f, 1.0f, 0.0f, 1.0f); 
    vector orange = vector(1.0f, 0.76f, 0.4f, 1.0f);
    
    Out.vColor = Out.vColor * orange;   


    // float3 Color = { 0.0f, 0.0f, 0.0f };
	////if(In.vTexcoord.x > g_State)		
	////	Out.vColor.rgb = 0.f;		
	////
    //   if (Out.vColor.rgb == Color)
    //       discard;
    
    float threshold = 0.99f;

    // color.rgb의 길이가 threshold 미만이면 clip
    if (length(Out.vColor.rgb) < threshold)
    {
        clip(-1);
    }
    

	return Out;
}



PS_OUT PS_MAIN_BULLET_EFFECT(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);

    if(Out.vColor.r < 0.1f)
        discard;
    
    //float threshold = 0.99f;

    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (length(Out.vColor.rgb) < threshold)
    //{
    //    clip(-1);
    //}
    

    return Out;
}

PS_OUT PS_MAIN_HP(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);

	

    if (In.vTexcoord.x > g_HpState)		
        Out.vColor.rgb = 0.f;
	//
    if (0.1f >= Out.vColor.a)
        discard;

    return Out;
}


PS_OUT PS_MAIN_MP(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);

	

    if (In.vTexcoord.x > g_MpState)		
        Out.vColor.rgb = 0.f;
	//
    if (0.1f >= Out.vColor.a)
        discard;

    return Out;
}


PS_OUT PS_MAIN_UI(PS_IN In) 
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/   
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)  
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord); 

    float threshold = 0.99f;        

    // color.rgb의 길이가 threshold 미만이면 clip
    if (length(Out.vColor.rgb) > threshold) 
    {
        clip(-1);       
    }
    
    return Out; 
}



PS_OUT PS_MAIN_UI_ALPHA(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/   
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)  
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);
    
    if(Out.vColor.a < 0.2f)
        discard;    

    //float threshold = 0.99f;

    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (length(Out.vColor.rgb) > threshold)
    //{
    //    clip(-1);
    //}
    
    return Out;
}

PS_OUT PS_MAIN_UI_ALPHA_BLEND(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/   
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)  
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);
    Out.vColor.a = 0.85f;
    //if (Out.vColor.a < 0.2f)
    //    discard;

    //float threshold = 0.01f;
    //
    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (length(Out.vColor.rgb) < threshold)
    //{
    //    clip(-1);
    //}
    
    return Out;
}


PS_OUT PS_MAIN_PORTAL(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/   
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)  
    //Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);

    //float threshold = 0.1f;

    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (length(Out.vColor.rgb) < threshold)
    //{
    //    clip(-1);
    //}
    
    //1. 텍스처 중심 (0.5,0.5)
    float2 center = float2(0.5f, 0.5f);
    
    //2. UV 좌표를 텍스처 중심을 기준으로 이동 (중심값 빼기) 
    float2 uv = In.vTexcoord - center; 
    
    //3. 회전 행렬 적용 : 회전각에 대한 sin, cos 계산 
    float s = sin(g_RotationAngle);
    float c = cos(g_RotationAngle);
    float2 rotatedUV = float2(uv.x * c - uv.y * s,
                              uv.x * s + uv.y * c);
    
    
    //4. 회전 후 원래 좌표계로 복귀 (중심값 더하기) 
    rotatedUV += center; 
    
    //5. 회전된 UV좌표로 텍스처 샘플링 
    Out.vColor = g_Texture.Sample(LinearSampler_Clamp, rotatedUV);
    
    
    
    //float threshold = 0.1f;
        
    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (length(Out.vColor.rgb) < threshold) 
    //{
    //    clip(-1);
    //}   
    
    if (Out.vColor.g <= 0.1f)   
        discard;    
    
    
    return Out;
}


PS_OUT PS_FADE_IN_OUI_UI(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/   
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)  
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);

    Out.vColor.a -= g_Alpha; 
    //float threshold = 0.99f;

    //// color.rgb의 길이가 threshold 미만이면 clip
    //if (length(Out.vColor.rgb) > threshold)
    //{
    //    clip(-1);
    //}
    
    return Out;
}

PS_OUT PS_MAIN_CRACK_EFFECT(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/   
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)  
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord); 
    
    //float3 gray = { 1.f, 0.7f, 0.f };
    //Out.vColor.rgb = gray;
    
    
    if(Out.vColor.r < 0.1f)
        discard;
    
    return Out; 
}


PS_OUT PS_MAIN_CLAW_EFFECT(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/   
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)  
    Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);
    
    //float3 gray = { 1.f, 0.7f, 0.f };
    //Out.vColor.rgb = gray;
    
    
    if (Out.vColor.b > 0.1f)
        discard;
    
    return Out;
}


technique11 DefaultTechnique
{
    // 0번
	pass DefaultPass
	{
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

    // 1번
    pass HP_Bar
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();	
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_HP();	
    }

    // 2번
    pass MP_Bar
    {
        SetRasterizerState(RS_Default);	
        SetDepthStencilState(DSS_Default, 0);	
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);	

        VertexShader = compile vs_5_0 VS_MAIN();	
        GeometryShader = NULL;	
        PixelShader = compile ps_5_0 PS_MAIN_MP();	
    }

    // 3번
    pass Hit_Effect
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_AlphaBlend, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_HIT_EFFECT();  
    }

    // 4번
    pass UI
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_UI();
    }

    // 5번
    pass Portal
    {

        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_PORTAL();
    }

    // 6번
    pass UI_Alpha
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_UI_ALPHA();
    }

    // 7번
    pass UI_Alpha_Blend
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_AlphaBlend, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_UI_ALPHA_BLEND();
    }

    // 8번

    pass Bullet_Effect
    {
        SetRasterizerState(RS_Default); 
        SetDepthStencilState(DSS_Default, 0);   
        SetBlendState(BS_AlphaBlend, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);   
    
        VertexShader = compile vs_5_0 VS_MAIN();    
        GeometryShader = NULL;  
        PixelShader = compile ps_5_0 PS_MAIN_BULLET_EFFECT();
    }

    // 9번
    pass UI_FadeInOut
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_AlphaBlend, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);   

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_FADE_IN_OUI_UI();   
    }

    // 10번 

    pass Crack_Effect
    {
        SetRasterizerState(RS_Default); 
        SetDepthStencilState(DSS_Default, 0);   
        SetBlendState(BS_Blend, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);  

        VertexShader = compile vs_5_0 VS_MAIN(); 
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_CRACK_EFFECT();        
    }

    // 11번
    pass Claw_Effect
    {
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_Default, 0);
        SetBlendState(BS_Blend, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN_CLAW_EFFECT();
    }
}
