#pragma once
#include "ValkyrieFSM.h"
class CValkyrieWeaponLevelUp :
	public CValkyrieFSM
{
public:
	CValkyrieWeaponLevelUp();
	virtual ~CValkyrieWeaponLevelUp();

	// CValkyrieFSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

public:
	void LevelUp();
	void ItemCountUp();
	void ItemCountDown();
	void ItemCountUiHelp();

public:
	static _int g_itemCount;
private:
	Engine::CScene* m_scene;
};

