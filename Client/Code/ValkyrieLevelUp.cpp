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
	// ����ġ ������ ��ư ����
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
	/* ��ư�Լ� (Ȯ��)
	�������� ���ְ� ����ġ�� �ø��� �Լ�
	*/

	// g_selectItemName �̸����� �����ͽ����� ����ġ�� ã�ƿͼ��ϸ�ɵ�
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

// � �������� ��������

/* ��ư�Լ� (+)
�������� ��밹���� ����ġ �������� �ø��� �Լ�
// �������� ������ Ȯ���Ͽ� �������� �Ǵ��� ����ġ�� ��ȹ���ϴ��� üũ�Ͽ� UI�� �Լ� ����
*/

/* ��ư�Լ� (-)
�������� ��밹���� ������ ����ġ �������� ������ �Լ�
// �������� ������ Ȯ���Ͽ� �������� �Ǵ��� ����ġ�� ��ȹ���ϴ��� üũ�Ͽ� UI�� �Լ� ����
*/

// ������ ������ � ������� �����ϰ� ������