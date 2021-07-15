#include "stdafx.h"
#include "SupplyWapon.h"

CSupplyWapon::CSupplyWapon()
{

}

CSupplyWapon::~CSupplyWapon()
{
}

void CSupplyWapon::Start()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"SupplyCanvas")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_2")->GetComponent<Engine::CTransformC>()->SetSize(_float3(211, 58, 0));
}

void CSupplyWapon::End()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"SupplyCanvas")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_2")->GetComponent<Engine::CTransformC>()->SetSize(_float3(144, 58, 0));
}

_uint CSupplyWapon::FixedUpdate()
{
	return _uint();
}

_uint CSupplyWapon::Update()
{
	return _uint();
}

_uint CSupplyWapon::LateUpdate()
{
	return _uint();
}

void CSupplyWapon::OnDestroy(void)
{
}