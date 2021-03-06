#ifndef PARTYSETTINGSCENE_H
#define PARTYSETTINGSCENE_H

#include "ClientScene.h"

class CPartySettingScene final : public CClientScene
{
private:
	explicit							CPartySettingScene(void);
	~CPartySettingScene(void);

public:
	static			CClientScene*		Create(void);
	void				Free(void) override;

	void				Awake(_int numOfLayers) override;
	void				Start(void) override;

	void				FixedUpdate(void) override;
	void				Update(void) override;
	void				LateUpdate(void) override;

	void				OnDestroy(void) override;

	void				OnEnable(void) override;
	void				OnDisable(void) override;
	void				InitLights(void) override;
private:
	void				InitPrototypes(void) override;

private:
	_bool m_init = false;
};
#endif