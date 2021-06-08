#pragma once
#include "EngineFunction.h"

BEGIN(Engine)
class ENGINE_DLL CParticle
{
public:
	CParticle(BoundingBox* boundingBox, _uint numParticles);
	~CParticle();

	CParticle* MakeClone();

public:
	void Awake();
	void Start();
	void Update();	
	void PreRender(SP(CGraphicsC) spGC, IDirect3DVertexBuffer9* pBuffer, IDirect3DBaseTexture9* pTexture);
	void Render(SP(CGraphicsC) spGC, IDirect3DVertexBuffer9* pBuffer);
	void PostRender(SP(CGraphicsC) spGC);

	void OnDestroy();

public:
	void reset();
	void resetParticle(ATTRIBUTE* _attribute);
	void RemoveDeadParticles();
	void Add_ParticleAttribute();
public:
	_bool  isPointInside(_float3& p);

private:
	LPDIRECT3DDEVICE9       m_pGraphicDevice;
	_float3					m_origin;            // ��ƼŬ�� ���۵Ǵ� ��ġ
	_float                  m_emitRate;			 // �ʴ� ��ƼŬ�� ��
	_float                  m_size;				 // ��� ��ƼŬ�� ũ��
	_int                    m_maxParticles;		 // �ִ� ��ƼŬ�� ����
	BoundingBox				m_boundingBox;		 // ��ƼŬ�� �̵��� �� �ִ� ����
	DWORD m_dwvbSize;							 // ���ؽ� ���۰� ������ �� �ִ� ��ƼŬ�� ��
	DWORD m_dwvbOffset;							 // offset in vb to lock   
	DWORD m_dwvbBatchSize;						 // number of vertices to lock starting at _vbOffsetbool isDead();
	GETTOR_REF(std::list<ATTRIBUTE>, m_AttributeList, {}, AttributeList)  // ��ƼŬ �Ӽ��� ����Ʈ

};
END
