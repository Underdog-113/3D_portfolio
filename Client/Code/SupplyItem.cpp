#include "stdafx.h"
#include "SupplyItem.h"

CSupplyItem::CSupplyItem()
{

}

CSupplyItem::~CSupplyItem()
{
}

void CSupplyItem::Start()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"SupplyCanvas")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_3")->GetComponent<Engine::CTransformC>()->SetSize(_float3(211, 58, 0));
}

void CSupplyItem::End()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"SupplyCanvas")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_3")->GetComponent<Engine::CTransformC>()->SetSize(_float3(144, 58, 0));
}

_uint CSupplyItem::FixedUpdate()
{
	return _uint();
}

_uint CSupplyItem::Update()
{
	return _uint();
}

_uint CSupplyItem::LateUpdate()
{
	return _uint();
}

void CSupplyItem::OnDestroy(void)
{
}

void CSupplyItem::SelectCanvasOn()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"SelectCanvas")->SetIsEnabled(true);

	if(CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"SupplyCanvas_Button_0")
		CSupplyManager::GetInstance()->SetOutCount(20);
	if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"SupplyCanvas_Button_1")
		CSupplyManager::GetInstance()->SetOutCount(1);
}
