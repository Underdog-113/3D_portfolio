#pragma once
#include "ValkyrieFSM.h"
class CValkyrieWeaponSwap :
	public CValkyrieFSM
{
public:
	CValkyrieWeaponSwap();
	virtual ~CValkyrieWeaponSwap();

	// CValkyrieFSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

	void WeaponChange();
private:
	void SelectWeapon();
private:
	Engine::CScene* m_scene;
	Engine::CObject* m_selectObject;
	static std::wstring g_selectWeaponName;
};

