#pragma once
#include "MeshEffect_Client.h"

class CBronya_FlashBang : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	enum FLASHBANG_STATE { SIZE_UP, SIZE_DOWN, STATE_END};

public:
	CBronya_FlashBang();
	~CBronya_FlashBang();

public:
	static SP(CBronya_FlashBang) Create(_bool isStatic, Engine::CScene* pScene);

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
	FLASHBANG_STATE m_eState;

private:
	static		_uint m_s_uniqueID;

private:
	void Movement();
};

