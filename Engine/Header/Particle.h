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
	_float GetRandomFloat(_float _lowBound, _float _highBound);			 // [lowBound, highBound] ������ �ִ� ������ �Ǽ��� ����.
	void   GetRandomVector(_float3* _Out, _float3* _min, _float3* _max); // �ּ��� min�� �ִ��� max�� ���ǵ� ���� ���� ���� ���͸� ���.
	_bool  isPointInside(_float3& p);

protected:
	LPDIRECT3DDEVICE9       m_pD3DDevice;
	_float3					m_vorigin;       // ��ƼŬ�� ���۵Ǵ� ��ġ
    BoundingBox				m_boundingBox;   // ��ƼŬ�� �̵��� �� �ִ� ����
	_float                  m_femitRate;     // �ʴ� ��ƼŬ�� ��
	_float                  m_fsize;         // ��� ��ƼŬ�� ũ��
	IDirect3DTexture9*      m_pTexture;         
	IDirect3DVertexBuffer9* m_pVIBuffer;
	std::list<ATTRIBUTE>    m_particles;     // ��ƼŬ �Ӽ��� ����Ʈ
	_int                    m_imaxParticles; // �ִ� ��ƼŬ�� ����
	DWORD m_dwvbSize;						     // ���ؽ� ���۰� ������ �� �ִ� ��ƼŬ�� ��
	DWORD m_dwvbOffset;					     // offset in vb to lock   
	DWORD m_dwvbBatchSize;					 // number of vertices to lock starting at _vbOffset
	
	
};
END
