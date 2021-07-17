#pragma once
#include "MeshEffect_Client.h"
#include "DecoObject.h"

class CAttackRange_Circle : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER
		
public:
	CAttackRange_Circle();
	~CAttackRange_Circle();

public:
	static		SP(CAttackRange_Circle)			Create(_bool isStatic, Engine::CScene* pScene);

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

private:
	_float m_fSize = 0.f;

private:
	SP(CDecoObject) m_pAttackRange_Circle_Diffuse;

};

