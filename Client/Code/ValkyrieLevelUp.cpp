#include "stdafx.h"
#include "ValkyrieLevelUp.h"

std::wstring CValkyrieLevelUp::g_selectItemName = L"";
_int CValkyrieLevelUp::g_itemCount = 0;
CValkyrieLevelUp::CValkyrieLevelUp()
{
}

CValkyrieLevelUp::~CValkyrieLevelUp()
{
}

void CValkyrieLevelUp::Start()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(true);
	// 경험치 아이템 버튼 생성
}

void CValkyrieLevelUp::End()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(false);
}

_uint CValkyrieLevelUp::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieLevelUp::Update()
{
	return _uint();
	
}

_uint CValkyrieLevelUp::LateUpdate()
{
	return _uint();
}

void CValkyrieLevelUp::OnDestroy(void)
{
}

void CValkyrieLevelUp::LevelUp()
{
	/* 버튼함수 (확인)
	아이템을 없애고 겸험치를 올리는 함수
	*/

	// g_selectItemName 이름으로 데이터스토어에서 경험치값 찾아와서하면될듯
	for (int i = 0; i < g_itemCount; i++)
	{
		CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);
	}
}

void CValkyrieLevelUp::ItemCountUp()
{
	g_itemCount++;
}

void CValkyrieLevelUp::ItemCountDown()
{
	g_itemCount--;
}

// 어떤 아이템을 쓸건인지

/* 버튼함수 (+)
아이템의 사용갯수와 경험치 증가량을 올리는 함수
// 아이템의 갯수를 확인하여 레벨없이 되는지 경험치가 몇획득하는지 체크하여 UI를 게속 변경
*/

/* 버튼함수 (-)
아이템의 사용갯수를 내리고 경험치 증가량을 내리는 함수
// 아이템의 갯수를 확인하여 레벨없이 되는지 경험치가 몇획득하는지 체크하여 UI를 게속 변경
*/

// 아이템 셀렉후 몇개 사용할지 지정하고 레벨업