#ifndef ENGINESTRUCTURE_H
#define ENGINESTRUCTURE_H


namespace Engine
{
#pragma region GraphicsStructure
	typedef struct _CustomVertex
	{
		_float3	position;
		_float3 normal;
		_float2	uv;
	}CUSTOM_VERTEX;
	const _uint customFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL;

	typedef struct _CustomVertex2D
	{
		_CustomVertex2D()
			:position(0.0f, 0.0f, 0.0f),
			texture(0.0f, 0.0f)
		{}

		_CustomVertex2D(float x, float y, float z, float u, float v)
			:position(x, y, z),
			texture(u, v)
		{}

		_CustomVertex2D(const D3DXVECTOR3& v, const D3DXVECTOR3& uv)
			:position(v),
			texture(uv)
		{}

		D3DXVECTOR3 position;   // Position Vector
		D3DXVECTOR2 texture;    // Texture  Coordinate
	}CUSTOM_VERTEX2D;
	const _uint customFVF2D = (D3DFVF_XYZ | D3DFVF_TEX1);

	typedef struct _VertexNormalTex
	{
		_float3	position;
		_float3	normal;
		_float2 texUV;
	}VERTEX_VNT;
	const _uint FVF_VNT = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	typedef struct _VertexScreen
	{
		_float4 position;
		_float2 texUV;
	}VERTEX_SCR;
	const _uint FVF_SCR = D3DFVF_XYZRHW | D3DFVF_TEX1;

	typedef struct _Index16
	{
		_ushort _0, _1, _2;
	}INDEX16;

	typedef struct _Index32
	{
		_ulong _0, _1, _2;
	}INDEX32;

	typedef struct _TexData
	{
		LPDIRECT3DTEXTURE9 pTexture;
		D3DXIMAGE_INFO imageInfo;
	}TEXTURE_DATA;

	typedef struct _Face
	{
		_uint vertexIndex[3];
		_uint uvIndex[3];
		_uint normIndex[3];
	}FACE;

	typedef struct _DerivedD3DXFRAME : public D3DXFRAME
	{
		_mat		CombinedTransformMatrix;
	}D3DXFRAME_DERIVED;

	typedef struct _DerivedD3DXMESHCONTAINER : public D3DXMESHCONTAINER
	{
		LPD3DXMESH				pOriMesh;

		_ulong					numBones;

		_mat*					pFrameOffsetMatrix;
		_mat**					ppCombinedTransformMatrix;

		_mat*					pRenderingMatrix;	// 최종적으로 변환이 끝나서 그리기를 수행하기 위한 행렬 정보
													// pFrameOffsetMatrix * (*ppCombinedTransformMatrix)

		_int					texIndexStart;
	}D3DXMESHCONTAINER_DERIVED;
#pragma endregion

	class CCollider;
	struct _CollisionInfo
	{
		_CollisionInfo(const _CollisionInfo& ci)
			: pMyCollider(ci.pMyCollider), pOtherCollider(ci.pOtherCollider), hitPoint(ci.hitPoint), normal(ci.normal), penetLength(ci.penetLength)
		{
		}
		_CollisionInfo(CCollider* pMine, CCollider* pOthers, _float3 cHitPoint, _float3 cNormal, _float cPenet)
			: pMyCollider(pMine), pOtherCollider(pOthers), hitPoint(cHitPoint), normal(cNormal), penetLength(cPenet)
		{
		}

		CCollider*	pMyCollider		= nullptr;
		CCollider*	pOtherCollider	= nullptr;	
		_float3		hitPoint		= ZERO_VECTOR;
		_float3		normal			= ZERO_VECTOR;
		_float		penetLength		= 0.f;
	};

	//Text
	struct _Text
	{
		std::wstring	m_message;
		_float2			m_position;
		_float2			m_boxSize;
		_int			m_fontSize;
		DWORD			m_alignment;
		D3DXCOLOR		m_color;
		_bool			m_isVisible;
	};

	struct _TextCom
	{
		_TextCom(std::wstring message, _float2 position, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color, _bool isVisible)
		{
			m_text.m_message = message;
			m_text.m_position = position;
			m_text.m_boxSize = boxSize;
			m_text.m_fontSize = fontSize;
			m_text.m_alignment = alignment;
			m_text.m_color = color;
			m_text.m_isVisible = isVisible;
		}

		LPD3DXFONT	m_pFont;
		_Text m_text;
	};
}
#endif // !ENGINESTRUCTURE_H            `

