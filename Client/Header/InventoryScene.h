#ifndef INVENTORYSCENE_H
#define INVENTORYSCENE_H

#include "ClientScene.h"

class CInventoryScene final : public CClientScene
{
private:
	explicit							CInventoryScene(void);
	~CInventoryScene(void);

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
	_bool m_init = false;
};
#endif