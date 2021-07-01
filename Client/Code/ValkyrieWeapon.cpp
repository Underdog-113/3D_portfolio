#include "stdafx.h"
#include "ValkyrieWeapon.h"


CValkyrieWeapon::CValkyrieWeapon()
{
}

CValkyrieWeapon::~CValkyrieWeapon()
{
}

void CValkyrieWeapon::Start()
{
	std::cout << "무기시작" <<  std::endl;

	m_scene = CValkyriegManager::GetInstance()->GetScene();

	Delegate<> delegate;
	delegate += std::bind(&CValkyrieWeapon::ChangeSelect, &CValkyrieWeapon());

	std::static_pointer_cast<CButton>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_Button_1"))->
		AddFuncData(delegate);
}

void CValkyrieWeapon::End()
{
	std::cout << "무기끝" << std::endl;
}

_uint CValkyrieWeapon::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieWeapon::Update()
{
	return _uint();
}

_uint CValkyrieWeapon::LateUpdate()
{
	return _uint();
}

void CValkyrieWeapon::OnDestroy(void)
{
}

void CValkyrieWeapon::ChangeSelect()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->ChangeFSMSelect();

}
