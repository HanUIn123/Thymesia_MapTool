#include "../../../EngineSDK/hlsl/Engine_Shader_Defines.hlsli"

/* hlsl 용 벡터타입 : float2, float3, float4, vector */
float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
Texture2D		g_Texture;


//sampler LinearSampler = sampler_state
//{ 
//	Filter = MIN_MAG_MIP_LINEAR;
//};

/* 1. 정점과 인덱스 버퍼 + 셰이더 바인딩해서 그린다. */
/* 2. 인덱스버퍼에 저장되어있는 인덱스에 해당하는 정점을 하나 꺼내서, */
/* 3. 정점쉐이더함수를 호출하며 인자로 정점(로컬스페이스기준)을 전달해준다. */
/* 4. 정점 쉐이더에서 정점에 필요한 연산을 수행한다.(ex> 정점의 로컬위치에다가 월드, 뷰, 투영행려을 곱한다. ) */
/* 5. 정점의 변환을 수행한다(4) + 정점의 구성 정보를 추가 또는 삭제한다. */

struct VS_IN
{
	float3			vPosition : POSITION;	
	float2			vTexcoord : TEXCOORD0;	
    float			vAge      : TEXCOORD1;
};

struct VS_OUT
{
	float4			vPosition : SV_POSITION;
	float2			vTexcoord : TEXCOORD0;
    float			vAge      : TEXCOORD1;
};

VS_OUT VS_MAIN(VS_IN In)
{	
	VS_OUT			Out = (VS_OUT)0;

	Out.vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	//Out.vWorldPos = Out.vPosition;

	Out.vPosition = mul(Out.vPosition, g_ViewMatrix);
	Out.vPosition = mul(Out.vPosition, g_ProjMatrix);	
	Out.vTexcoord = In.vTexcoord;
    Out.vAge = In.vAge;

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
	float			Age : TEXCOORD1;
};

struct PS_OUT
{
	float4			vColor : SV_TARGET0;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* Sample : g_Texture로 부터 지정된 좌표의 색을 지정한 방식으로 얻어온다.*/
	// g_Texture.Sample(어떻게 얻어올건지(Sampler_State), 어디 색을 가져올건지)
	Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);	 

	
    //float4 texColor = gDiffuseMap.Sample(gSampler, input.TexCoord);

    //// Age 기반으로 알파 페이드
    //// Age=0 -> Alpha=1, Age=gMaxAge -> Alpha=0
    //float alpha = saturate(1.0f - (input.Age / gMaxAge));

    //texColor.a *= alpha;

    //return texColor;
	//if(In.vTexcoord.x > g_State)		
	//	Out.vColor.rgb = 0.f;		
	////
	if (0.3f >= Out.vColor.a)	
		discard;	

	return Out;
}



technique11 DefaultTechnique
{
	pass DefaultPass
	{
        SetRasterizerState(Rs_Cull_NONE);	
        SetDepthStencilState(DSS_Default, 0);	
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 0.f), 0xffffffff);	
	

		VertexShader = compile vs_5_0 VS_MAIN();	
        GeometryShader = NULL;	
		PixelShader = compile ps_5_0 PS_MAIN();	
	}

}
