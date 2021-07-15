#pragma once

#include "RenderComponent.h"

BEGIN(Engine)
class CParticle;
class CGraphicsC;
class ENGINE_DLL CParticleSystemC final : public CRenderComponent
{
public:
	CParticleSystemC(void);
	~CParticleSystemC(void);

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

public:
	GETTOR_SETTOR(_float3, m_vParticlesminPos, _float3(0.f, 0.f, 0.f), vParticlesminPos)
	GETTOR_SETTOR(_float3, m_vParticlesmaxPos, _float3(0.f, 0.f, 0.f), vParticlesmaxPos)

private:
	_float3					m_origin;                // 파티클이 시작되는 위치
	_float                  m_emitRate     = 0.f;    // 초당 파티클의 수
	_int                    m_maxParticles = 0;      // 최대 파티클의 개수
	_float                  m_size		   = 0.3f;    // 모든 파티클의 크기
	LPDIRECT3DDEVICE9       m_pGraphicDevice;
	IDirect3DVertexBuffer9* m_pVertexBuffer;
	IDirect3DBaseTexture9*  m_pTexture;

private:
	_float m_LifeTime = 0.f;
	GETTOR(std::vector<SP(CParticle)>, m_vParticles, {}, vParticles)

};
END
