#include "stdafx.h"
#include "ValkyrieWeaponSwap.h"


CValkyrieWeaponSwap::CValkyrieWeaponSwap()
{
}

CValkyrieWeaponSwap::~CValkyrieWeaponSwap()
{
}

void CValkyrieWeaponSwap::Start()
{
	std::cout << "무기시작" << std::endl;

	m_scene = CValkyriegManager::GetInstance()->GetScene();

	
}

void CValkyrieWeaponSwap::End()
{
}

_uint CValkyrieWeaponSwap::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieWeaponSwap::Update()
{
	return _uint();
}

_uint CValkyrieWeaponSwap::LateUpdate()
{
	return _uint();
}

void CValkyrieWeaponSwap::OnDestroy(void)
{
}
