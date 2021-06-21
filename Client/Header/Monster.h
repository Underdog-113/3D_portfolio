#pragma once

// 몬스터들의 상위 클래스
// 여기는 몬스터들의 공통된 속성을 정의하는 곳
class CMonster abstract : public Engine::CObject
{
	SMART_DELETER_REGISTER

protected:
	CMonster();
	virtual ~CMonster() = default;

public:
	virtual SP(CObject) MakeClone(void) override;

	virtual void Awake(void) override;

	virtual void Start(void) override;

	virtual void FixedUpdate(void) override;

	virtual void Update(void) override;

	virtual void LateUpdate(void) override;

	virtual void PreRender(LPD3DXEFFECT pEffect) PURE;
	virtual void Render(LPD3DXEFFECT pEffect) PURE;
	virtual void PostRender(LPD3DXEFFECT pEffect) PURE;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;

	virtual void OnDisable(void) override;

	virtual void SetBasicName(void) override;

public:
	virtual void ApplyHitInfo(HitInfo info);

protected:
	static		_uint							m_s_uniqueID;
	GETTOR		(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR		(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR		(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)	
		
protected:
	//GETTOR			(SP(Engine::CRigidBodyC),		m_spRigidBody,			nullptr, RigidBody)
	//GETTOR			(SP(Engine::CCollisionC),		m_spCollision,			nullptr, Collision)
	//GETTOR			(SP(Engine::CDebugC),			m_spDebug,				nullptr, Debug)

protected:
	GETTOR		(SP(Engine::CStateMachineC),	m_spStateMachine,	nullptr,	StateMachine)

protected:
	GETTOR		(M_Stat*,						m_pStat,			nullptr,	Stat)
};

