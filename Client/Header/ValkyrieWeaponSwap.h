#pragma once
#include "ValkyrieFSM.h"
class CValkyrieWeaponSwap :
	public CValkyrieFSM
{
public:
	CValkyrieWeaponSwap();
	virtual ~CValkyrieWeaponSwap();

	// CValkyrieFSM��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:

private:
	Engine::CScene* m_scene;

};

