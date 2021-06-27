#include "stdafx.h"
#include "ValkyrieProperty.h"


CValkyrieProperty::CValkyrieProperty()
{
}


CValkyrieProperty::~CValkyrieProperty()
{
}

void CValkyrieProperty::Start()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(false);
}

void CValkyrieProperty::End()
{
}

_uint CValkyrieProperty::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieProperty::Update()
{
	return _uint();
}

_uint CValkyrieProperty::LateUpdate()
{
	return _uint();
}

void CValkyrieProperty::OnDestroy(void)
{
}
