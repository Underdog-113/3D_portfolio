float4x4 mWVP;
float4x4 mWV;
float gFar;

texture      g_BaseTexture;

matrix      g_matWorld;         // 상수 테이블
matrix      g_matView;
matrix      g_matProj;

// 샘플러 : 텍스처의 품질 및 출력 옵션을 결정하는 구조체
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

struct VS_IN
{
	vector      vPosition   : POSITION;      // 시만틱 : 속성 지시자
	float2      vTexUV      : TEXCOORD0;
};

struct VS_OUT
{
	float4 Pos        : POSITION;
	float4 Depth    : TEXCOORD0;
};

// 버텍스쉐이더

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Depth = mul(vector(In.vPosition.xyz, 1.f), matWVP);

	return Out;
}


struct PS_IN
{
	float2       vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector      vColor : COLOR0;
};

// 픽셀 쉐이더

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT      Out = (PS_OUT)0;
	Out.vColor = tex2D(BaseSampler, In.vTexUV);

	/*
	1. 모든 오브젝트를 그린다.
	2. SSD 상자를 그린다.
	3. 각 픽셀마다 장면 깊이를 읽어온다.
	4. 그 깊이로부터 3D위치를 계산한다.
	5. 그 3D 위치가 SSD 상자의 밖이라면 배제한다.
	6. 그렇지 않다면 데칼 텍스처를 그린다.
	*/

	/*
	다른 픽셀들과 나의 깊이를 비교해서 나보다 멀리있는것중에서 가장 가까운놈을 찾는다.
	나의 위치를 해당 픽셀로 옯긴다.

	데칼을 만들때 생길수있는문제
	1. 알파 블렌딩 (블랜딩 파워를 적용해서 해결 일반 알파블렌딩으로는 해결할수없음 파워라는 개념을 적용하여 해결해야함)
	2. 움직이는 물체들 (그냥 움직이는 물체는 데칼을 붙여버리면되는데 스키닝부분에는 문제가 발생 포프님은 그냥 그런곳에는 데칼안쓰고 스탠실버퍼로 해결함)
	3. 옆면이 늘어난다. (SSD상자가 투영면을 완전히 충돌하지 않을때 발생된다. SSD상자의 투영방향과 Gbuffer의 법선방향의각이 커지면 리젝션 시켜버린다. 각도는 아티스트가 설정할수있게 하는게좋음)
	(다른방법으로는 정점법선이 이루는 각이 커지면 데칼을 서서히 사라지게 하였으나 둥근 파이프에서는 안이쁨)
	4. 짤린 데칼 (SSD상자가 카메라 안으로 들어오는경우)
	(카메라와 데칼이 충돌하면 뒷면을 대신 그려서 해결할수있음 깊이 테스트 방향도 뒤짚어야함 하지만 성능이 마구 떨어지는단점이 존재한다.)
	*/
	return Out;
}

technique Default_Device
{
	pass   // 기능의 캡슐화, PASS는 이름과 상관없이 선언된 순서대로 위부터 인덱스 값이 0이 지정되고 자동적으로 하나씩 증가함
	{
		//zwriteenable = false;
		cullmode = none;

		vertexshader = compile vs_3_0 VS_MAIN();   // 진입점 함수 명시
		pixelshader = compile ps_3_0 PS_MAIN();
	}
};