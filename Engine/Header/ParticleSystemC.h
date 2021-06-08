#pragma once

#include "RenderComponent.h"

BEGIN(Engine)
class CParticle;
class CGraphicsC;
class ENGINE_DLL CParticleSystemC final : public CRenderComponent
{
public:
	CParticleSystemC(void);
	~CParticleSystemC(void) = default;

public:
	SP(CComponent) MakeClone(CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

	void FixedUpdate(SP(CComponent) spThis) override;
	void Update(SP(CComponent) spThis) override;
	void LateUpdate(SP(CComponent) spThis) override;

	void PreRender(SP(CGraphicsC) spGC) override;
	void PreRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

	void Render(SP(CGraphicsC) spGC) override;
	void Render(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

	void PostRender(SP(CGraphicsC) spGC) override;
	void PostRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

public:
	HRESULT InitParticleSetting(LPDIRECT3DDEVICE9 _Device, std::wstring _texFIleName);
	void	AddParticle(CParticle* pParticle);
	static const	EComponentID		m_s_componentID = EComponentID::ParticleSystem;

private:
	_float3					m_origin;                // ��ƼŬ�� ���۵Ǵ� ��ġ
	_float                  m_emitRate     = 0.f;    // �ʴ� ��ƼŬ�� ��
	_int                    m_maxParticles = 0;      // �ִ� ��ƼŬ�� ����
	_float                  m_size		   = 0.7f;    // ��� ��ƼŬ�� ũ��
	DWORD m_dwvbSize					   = 2048;		 // ���ؽ� ���۰� ������ �� �ִ� ��ƼŬ�� ��
	DWORD m_dwvbOffset					   = 0;      // offset in vb to lock   
	DWORD m_dwvbBatchSize				   = 512;      // number of vertices to lock starting at _vbOffsetbool isDead();
	LPDIRECT3DDEVICE9       m_pGraphicDevice;
	IDirect3DVertexBuffer9* m_pVIBuffer;
	IDirect3DBaseTexture9*  m_pTexture;

private:
	_float m_LifeTime = 0.f;
	GETTOR_REF(std::vector<CParticle*>, m_vParticles, {}, vParticles);

};
END
