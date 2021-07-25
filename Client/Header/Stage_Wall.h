#pragma once
#include "MeshEffect_Client.h"

class CStage_Wall : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CStage_Wall();
	~CStage_Wall();

public:
	static		SP(CStage_Wall)			Create(_bool isStatic, Engine::CScene* pScene);

	SP(Engine::CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void PreRender(LPD3DXEFFECT pEffect) override;
	void Render(LPD3DXEFFECT pEffect) override;
	void PostRender(LPD3DXEFFECT pEffect) override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()override;

private:
	static		_uint m_s_uniqueID;

	GETTOR			(SP(Engine::CCollisionC),		m_spCollision,		nullptr,	Collision)
	GETTOR			(SP(Engine::CDebugC),			m_spDebug,			nullptr,	Debug)

private:
	_float m_fAngle;
};

