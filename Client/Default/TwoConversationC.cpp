#include "Stdafx.h"
#include "TwoConversationC.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

CTwoConversationC::CTwoConversationC()
{
}

CTwoConversationC::~CTwoConversationC()
{
	OnDestroy();
}

SP(Engine::CComponent) CTwoConversationC::MakeClone(Engine::CObject *pObject)
{
	SP(CTwoConversationC) spClone(new CTwoConversationC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CTwoConversationC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CTwoConversationC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_textTime = 0.05f;
	m_timer = m_textTime;
	m_conversationCount = 0;
	m_conversationCheck = false;
	m_init = true;

	m_conversationCanvas = static_cast<Engine::CCanvas*>(GetOwner()->GetScene()->FindObjectByName(L"ConversationCanvas").get());
	m_conversationCanvas->SetIsEnabled(true);

	static_cast<Engine::CCanvas*>(GetOwner()->GetScene()->FindObjectByName(L"MainCanvas").get())->SetIsEnabled(false);

	m_conversationPlayerImage = GetOwner()->GetScene()->FindObjectByName(L"ConversationCanvas_Image_0").get();
	m_conversationName = GetOwner()->GetScene()->FindObjectByName(L"ConversationCanvas_Text_0").get();

	m_conversationText.emplace_back(GetOwner()->GetScene()->FindObjectByName(L"ConversationCanvas_Text_1").get());
	m_conversationText.emplace_back(GetOwner()->GetScene()->FindObjectByName(L"ConversationCanvas_Text_2").get());

	CStageControlTower::GetInstance()->GetCurrentActor()->SetIsEnabled(false);

	Engine::CCanvas* ConversationCanvas = static_cast<Engine::CCanvas*>(GetOwner()->GetScene()->FindObjectByName(L"ConversationCanvas").get());
	ConversationCanvas->SetIsEnabled(true);

	static_cast<CButton*>(GetOwner()->GetScene()->FindObjectByName(L"ConversationCanvas_Skip_0").get())->
		AddFuncData<void(CTwoConversationC::*)(), CTwoConversationC*>(&CTwoConversationC::Skip, this);
}

void CTwoConversationC::FixedUpdate(SP(CComponent) spThis)
{

}

void CTwoConversationC::Update(SP(CComponent) spThis)
{
	Conversation();
	TextUpdate();
}

void CTwoConversationC::LateUpdate(SP(CComponent) spThis)
{

}

void CTwoConversationC::OnDestroy()
{
}

void CTwoConversationC::OnEnable()
{
	__super::OnEnable();
}

void CTwoConversationC::OnDisable()
{
	__super::OnDisable();
}

_bool CTwoConversationC::IsEnd()
{
	return m_conversationCheck;
}

void CTwoConversationC::Conversation()
{
	if (m_conversationCheck)
		return;

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_J) || m_init)
	{
		m_init = false;
		m_conversationCount++;

		m_outText[0] = L"";
		m_outText[1] = L"";

		switch (m_conversationCount)
		{
		case 1:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"Ű�Ƴ�");
			m_inText[0] = L"����, �, ���� ���� �Ƿ���, �װ�Ʈ���ǿ��� ����̳� �Ϸ���?";
			break;
		case 2:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�����");
			m_inText[0] = L"�׷� �� �𸣰�����.....�����̶�� �� Ȯ����.";
			break;
		case 3:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"Ű�Ƴ�");
			m_inText[0] = L"����, ���� �׷��� ���� ������ ���ݴµ���?";
			break;
		case 4:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�����");
			m_inText[0] = L"�׷��� ������ ����� ������ ������ �Ⱙ�� �̷��� Ű�Ƴ��� �����߷��ݾ�.";
			break;
		case 5:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"Ű�Ƴ�");
			m_inText[0] = L"�װž� ��¿ �� �����°�. ��·�� �̷��� ���� ���� ó���ߴµ�.";
			break;
		case 6:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�����");
			m_inText[0] = L"�׸��� �Ǽ��� ���� ��ư�� ��������?.";
			break;
		case 7:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"Ű�Ƴ�");
			m_inText[0] = L"��, �װ� ���?";
			break;
		case 8:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Teresa");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�׷���");
			m_inText[0] = L"��....�Ⱙ�� �̹� ����������, �� �̻� �� ������ �ٷ��� �ʴ� �� ���?";
			break;
		case 9:
			m_inText[0] = L"���� ���ͼ� ���ε�, �Գ� ���赵�� ������.... ������ �빮�� ������ �Ա��� ������?";
			break;
		case 10:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�����");
			m_inText[0] = L"�¾ƿ� �׷����.";
			break;
		case 11:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Teresa");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�׷���");
			m_inText[0] = L"�׷��ٸ� �� �⼼�� ���� �Ա��� ������� Ȯ���ϴ°� �?";
			break;
		case 12:
			End();
			break;
		}
	}
}

void CTwoConversationC::TextUpdate()
{
	m_timer -= GET_DT;

	if (m_timer <= 0)
	{
		m_timer = m_textTime;

		if (m_inText[0] != L"")
		{
			std::wstring a = m_inText[0].substr(0, 1);

			std::wstring::size_type stTmp;
			stTmp = m_inText[0].find(a, 0);
			m_inText[0].erase(stTmp, 1);

			m_outText[0] += a;
		}
		else if (m_inText[1] != L"")
		{
			std::wstring a = m_inText[1].substr(0, 1);

			std::wstring::size_type stTmp;
			stTmp = m_inText[1].find(a, 0);
			m_inText[1].erase(stTmp, 1);

			m_outText[1] += a;
		}

		m_conversationText[0]->GetComponent<Engine::CTextC>()->ChangeMessage(m_outText[0]);
		m_conversationText[1]->GetComponent<Engine::CTextC>()->ChangeMessage(m_outText[1]);
	}

}

void CTwoConversationC::End()
{
	m_conversationCheck = true;

	CStageControlTower::GetInstance()->GetCurrentActor()->SetIsEnabled(true);

	GetOwner()->GetScene()->FindObjectByName(L"MainCanvas")->SetIsEnabled(true);
	CBattleUiManager::GetInstance()->QteOff(0);
	CBattleUiManager::GetInstance()->QteOff(1);
	CBattleUiManager::GetInstance()->SquadOff(GetOwner()->GetScene());
	CBattleUiManager::GetInstance()->WaitingPlayerSetting();

	m_conversationCanvas->SetIsEnabled(false);
	GetOwner()->SetIsEnabled(false);
}

void CTwoConversationC::Skip()
{
	End();
}