#ifndef ONESTAGESCENE_H
#define ONESTAGESCENE_H

#include "Scene.h"
class CLoading;
class COneStageScene final : public Engine::CScene
{
private:
	explicit							COneStageScene(void);
	~COneStageScene(void);

public:
	static			Engine::CScene*		Create(void);
	void				Free(void) override;

	void				Awake(_int numOfLayers) override;
	void				Start(void) override;

	void				FixedUpdate(void) override;
	void				Update(void) override;
	void				LateUpdate(void) override;

	void				OnDestroy(void) override;

	void				OnEnable(void) override;
	void				OnDisable(void) override;

public:
	void				ChangeScene(Engine::CScene* pScene);

private:
	void				InitPrototypes(void) override;

	GETTOR(CLoading*, m_pLoading, nullptr, Loading)
};

#endif