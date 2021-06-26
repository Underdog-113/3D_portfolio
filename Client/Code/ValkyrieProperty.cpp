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
	// 뒤로가기 버튼 재설정
	Delegate<> delegate;
	delegate += std::bind(&CValkyrieProperty::ChangeSelect, &CValkyrieProperty());

	std::static_pointer_cast<CButton>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_Button_1"))->
		AddFuncData(delegate);
	// 데이터 셋팅

	PropertyCanvas();
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

void CValkyrieProperty::PropertyCanvas()
{
	Engine::CScene* scene = CValkyriegManager::GetInstance()->GetScene();

	scene->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(true);
	scene->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(false);
	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::m_selectValkyrie);

	scene->FindObjectByName(L"PropertyCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(data->GetHp()));
	scene->FindObjectByName(L"PropertyCanvas_Text_16")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetSubName());
}

void CValkyrieProperty::ChangeSelect()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->ChangeFSM(CValkyriegManager::STATE::Select);
}
