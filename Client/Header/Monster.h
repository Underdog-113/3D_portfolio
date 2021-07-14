#pragma once

// 몬스터들의 상위 클래스
// 여기는 몬스터들의 공통된 속성을 정의하는 곳
class CAttackBall;
class CAttackBox;

class CMonster abstract : public Engine::CObject
{
	SMART_DELETER_REGISTER
public:
	enum EMonChID {
		MON_0 = 1, MON_1 = 2, MON_2 = 4, MON_3 = 8, MON_4 = 16 
	};
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

	virtual	void OnCollisionEnter(Engine::_CollisionInfo ci) {}
	virtual	void OnCollisionStay(Engine::_CollisionInfo ci) {}
	virtual	void OnCollisionExit(Engine::_CollisionInfo ci) {}

	virtual void SetBasicName(void) override;

public:
	virtual void ApplyHitInfo(HitInfo info) PURE;
	void ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat* pBoneMat, _float radius);
	void UnActiveAttackBall();

	void ActiveAttackBox(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat* pBoneMat, _float3 size, _float3 offset, _float3 rotOffset);
	void UnActiveAttackBox();

	void SelectChannelID();
	void ReturnChannelID();

	virtual void MonsterDead();

	Engine::CCollider* GetHitBox();

protected:
	static				_uint							m_s_uniqueID;
	static				_uint							m_s_channelID;
	GETTOR				(SP(Engine::CMeshC),			m_spMesh,			nullptr,						Mesh)
	GETTOR				(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,						Graphics)
	GETTOR				(SP(Engine::CTextureC),			m_spTexture,		nullptr,						Texture)
	GETTOR				(SP(Engine::CShaderC),			m_spShader,			nullptr,						Shader)	
	GETTOR				(SP(Engine::CRigidBodyC),		m_spRigidBody,		nullptr,						RigidBody)
	GETTOR				(SP(Engine::CCollisionC),		m_spCollision,		nullptr,						Collision)
	GETTOR				(SP(Engine::CDebugC),			m_spDebug,			nullptr,						Debug)
	GETTOR				(SP(Engine::CStateMachineC),	m_spStateMachine,	nullptr,						StateMachine)

protected:
	GETTOR				(M_Stat*,						m_pStat,			nullptr,						Stat)
	GETTOR				(CAttackBall*,					m_pAttackBall,		nullptr,						AttackBall)
	GETTOR				(CAttackBox*,					m_pAttackBox,		nullptr,						AttackBox)
	GETTOR				(M_SuperArmor*,					m_pSuperArmor,		nullptr,						SuperArmor)
	GETTOR_SETTOR		(EChannelID,					m_channelID,		EChannelID::NumOfChannelID,		ChannelID)
	GETTOR_SETTOR		(EChannelID,					m_hitChannelID,		EChannelID::NumOfChannelID,		HitChannelID)
	GETTOR_SETTOR		(_float,						m_spawnTimer,		UNDEFINED,						SpawnTimer)
	GETTOR_SETTOR		(SP(CPatternMachineC),			m_spPatternMachine,	nullptr,						PatternMachine)
	GETTOR_SETTOR		(V_Stat::Valkyrie_Type,			m_valkyrieType,		V_Stat::Valkyrie_Type::KIANA,	ValkyrieType)
	GETTOR_SETTOR		(_bool,							m_isBoss,			false,							IsBoss)
	GETTOR_SETTOR		(_float,						m_weakTime,			5.f,							WeakTime) // SuperArmor가 깨지고 n초 후에 breakGauge 채우기 전까지의 시간

private:
	_float m_accTime = 0.f;
};
