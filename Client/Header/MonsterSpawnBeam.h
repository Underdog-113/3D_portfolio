#pragma once
#include "MeshEffect_Client.h"

class CMonster;
class CMonsterSpawnBeam : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CMonsterSpawnBeam();
	~CMonsterSpawnBeam();

public:
	static SP(CMonsterSpawnBeam) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void PreRender(LPD3DXEFFECT pEffect)override;
	void Render(LPD3DXEFFECT pEffect)override;
	void PostRender(LPD3DXEFFECT pEffect)override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void OnCollisionEnter(Engine::_CollisionInfo ci);
	void OnCollisionStay(Engine::_CollisionInfo ci) ;
	void OnCollisionExit(Engine::_CollisionInfo ci) ;

	void SetBasicName()override;
private:
	_bool m_bSpawn;
	GETTOR(SP(Engine::CCollisionC), m_spCollision, nullptr, Collision)
	GETTOR_SETTOR(SP(CMonster),	m_spMonster, nullptr, Monster)
};

