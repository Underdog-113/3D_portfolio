#pragma once
#include "Scene.h"

class CEffectToolScene final : public Engine::CScene
{
private:
	CEffectToolScene();
	virtual ~CEffectToolScene() = default;

public:
	void Awake(_int numOfLayers) override;

	void Start() override;

	void FixedUpdate() override;

	void Update() override;

	void LateUpdate(void) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;

	void OnDisable(void) override;

public:
	static Engine::CScene* Create();
	void Free() override;

private:
	void InitPrototypes(void) override;
};

