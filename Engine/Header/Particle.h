#pragma once
#include "EngineFunction.h"

BEGIN(Engine)
class ENGINE_DLL CParticle : public CObject
{
	SMART_DELETER_REGISTER

public:
	CParticle();
	virtual ~CParticle() = default;
    
public:
	HRESULT Init(LPDIRECT3DDEVICE9 _Device, std::wstring _texFIleName);
	virtual void reset();

	virtual void resetParticle(ATTRIBUTE* _attribute) = 0;
	virtual void addParticle();
	virtual void Awake() override;
	virtual void Update() override;

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void RemoveDeadParticles();
	virtual void Release();
	_bool isEmpty();
	_bool isDead();

protected:
	_float GetRandomFloat(_float _lowBound, _float _highBound);			 // [lowBound, highBound] 범위에 있는 임의의 실수를 리턴.
	void   GetRandomVector(_float3* _Out, _float3* _min, _float3* _max); // 최소점 min과 최대점 max로 정의된 상자 내의 임의 벡터를 출력.
	_bool  isPointInside(_float3& p);

protected:
	LPDIRECT3DDEVICE9       m_pD3DDevice;
	_float3					m_vorigin;       // 파티클이 시작되는 위치
    BoundingBox				m_boundingBox;   // 파티클이 이동할 수 있는 영역
	_float                  m_femitRate;     // 초당 파티클의 수
	_float                  m_fsize;         // 모든 파티클의 크기
	IDirect3DTexture9*      m_pTexture;         
	IDirect3DVertexBuffer9* m_pVIBuffer;
	std::list<ATTRIBUTE>    m_particles;     // 파티클 속성의 리스트
	_int                    m_imaxParticles; // 최대 파티클의 개수
	DWORD m_dwvbSize;						     // 버텍스 버퍼가 보관할 수 있는 파티클의 수
	DWORD m_dwvbOffset;					     // offset in vb to lock   
	DWORD m_dwvbBatchSize;					 // number of vertices to lock starting at _vbOffset
	
	
};
END
