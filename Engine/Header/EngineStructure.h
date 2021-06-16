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

	typedef struct _VertexTexF3
	{
		_float3 position;
		_float3 texUV;
	}VERTEX_VT3;

	const _ulong FVF_VT3 = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);


	typedef struct _VertexScreen
	{
		_float4 position;
		_float2 texUV;
	}VERTEX_SCR;
	const _ulong FVF_SCR = D3DFVF_XYZRHW | D3DFVF_TEX1;

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
		IDirect3DBaseTexture9* pTexture;
		D3DXIMAGE_INFO imageInfo;
		_bool includeAlpha;
		std::wstring sectionKey;
	}TEXTURE_DATA;



	typedef struct _DerivedD3DXFRAME : public D3DXFRAME
	{
		_mat		CombinedTransformMatrix;
		_DerivedD3DXFRAME* pParentFrame;
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

#pragma region Particle


	// Particle
	typedef struct tagParticle
	{
		_float3	  _pos;
		D3DXCOLOR _color;
		_float    _size;
	}PARTICLE_DESC;
	const DWORD FVF_Particle = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	typedef struct tagAttribute
	{
		tagAttribute()
		{
			_lifeTime = 0.0f;
			_age = 0.0f;
			_isAlive = true;
		}

		_float3      _position;	    // 월드 스페이스 내의 파티클 위치
		_float3      _velocity;	    // 파티클의 속도
		_float3      _acceleration; // 파티클의 가속
		_float       _lifeTime;     // 파티클 유지 시간
		_float       _age;          // 파티클의 나이
		D3DXCOLOR    _color;        // 파티클의 컬러
		D3DXCOLOR    _colorFade;    // 파티클의 컬러가 시간의 흐름에 따라 퇴색할건지
		_bool        _isAlive;      // 파티클이 생존한 경우 True, 소멸한 경우 false
	}ATTRIBUTE;

	typedef struct tagBoundingBox
	{
		tagBoundingBox() {};

		_float3 _min;
		_float3 _max;
	}BoundingBox;
	const _float _INFINITY = FLT_MAX;

#pragma endregion
	struct _TextCom
	{
		_TextCom() {}

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

