#ifndef BATTLEENDSCENE_H
#define BATTLEENDSCENE_H

#include "ClientScene.h"
class CLoading;
class CBattleEndScene final :public CClientScene
{
private:
	explicit							CBattleEndScene(void);
	~CBattleEndScene(void);

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

private:
	void				InitPrototypes(void) override;
private:
	bool m_init;
};

#endif