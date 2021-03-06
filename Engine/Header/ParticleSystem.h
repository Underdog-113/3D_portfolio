#pragma once

BEGIN(Engine)
class ENGINE_DLL CParticleSystem
{
	SMART_DELETER_REGISTER

public:
	CParticleSystem();
	virtual ~CParticleSystem();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void PreRender(SP(CGraphicsC) spGC, IDirect3DVertexBuffer9* pBuffer, IDirect3DBaseTexture9* pTexture);
	virtual void Render(SP(CGraphicsC) spGC, IDirect3DVertexBuffer9* pBuffer);
	virtual void PostRender(SP(CGraphicsC) spGC);

	virtual void OnDestroy();

public:
	void reset();
	void resetParticle(ATTRIBUTE* _attribute);
	void RemoveDeadParticles();
	void Add_ParticleAttribute();
public:
	_bool  isPointInside(_float3& p);

protected:
	LPDIRECT3DDEVICE9       m_pGraphicDevice;
	_float3					m_origin;            // 파티클이 시작되는 위치
	_float                  m_emitRate;			 // 초당 파티클의 수
	_float                  m_size;				 // 모든 파티클의 크기
	_int                    m_maxParticles;		 // 최대 파티클의 개수
	BoundingBox				m_boundingBox;		 // 파티클이 이동할 수 있는 영역
	DWORD m_dwvbSize;							 // 버텍스 버퍼가 보관할 수 있는 파티클의 수
	DWORD m_dwvbOffset;							 // offset in vb to lock   
	DWORD m_dwvbBatchSize;						 // number of vertices to lock starting at _vbOffsetbool isDead();
	GETTOR_REF(std::list<ATTRIBUTE>, m_AttributeList, {}, AttributeList)  // 파티클 속성의 리스트

};
END

