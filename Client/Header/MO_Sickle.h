#pragma once
#include "Monster.h"

class CMO_Sickle : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMO_Sickle();
	~CMO_Sickle();

public:
	virtual SP(CObject) MakeClone(void) override;

	virtual void Awake(void) override;

	virtual void Start(void) override;

	virtual void FixedUpdate(void) override;

	virtual void Update(void) override;

	virtual void LateUpdate(void) override;

	virtual void PreRender(LPD3DXEFFECT pEffect) override;
	virtual void Render(LPD3DXEFFECT pEffect) override;
	virtual void PostRender(LPD3DXEFFECT pEffect) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;

	virtual void OnDisable(void) override;

	virtual void SetBasicName(void) override;

	virtual void ApplyHitInfo(HitInfo info) override;

			void FindRightHand();
public:
	static		SP(CMO_Sickle)				Create				(_bool isStatic, Engine::CScene* pScene);
				void						ChaseTarget			(_float3 targetPos);
				void						SetStatus			(BaseStat stat);
				void						UpdatePivotMatrices(void);

private:
	static		_uint						m_s_uniqueID;

private:
	GETTOR(_mat*, m_pRightHand_World, nullptr, RightHandWorldMatrix)
	Engine::D3DXFRAME_DERIVED*	m_pRightHand_Frame = nullptr;
	_mat* m_pRightHand_BoneOffset = nullptr;
	_mat* m_pRightHand = nullptr;

	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,		nullptr,	RigidBody)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,		nullptr,	Collision)
	GETTOR		(SP(Engine::CDebugC),		m_spDebug,			nullptr,	Debug)
};

