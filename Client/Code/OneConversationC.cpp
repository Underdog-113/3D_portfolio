#include "Stdafx.h"
#include "OneConversationC.h"
#include "StageControlTower.h"
#include "Valkyrie.h"
COneConversationC::COneConversationC()
{
}

COneConversationC::~COneConversationC()
{
	OnDestroy();
}

SP(Engine::CComponent) COneConversationC::MakeClone(Engine::CObject *pObject)
{
	SP(COneConversationC) spClone(new COneConversationC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void COneConversationC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;

}

void COneConversationC::Start(SP(CComponent) spThis)
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
		AddFuncData<void(COneConversationC::*)(), COneConversationC*>(&COneConversationC::Skip, this);

}

void COneConversationC::FixedUpdate(SP(CComponent) spThis)
{
	
}

void COneConversationC::Update(SP(CComponent) spThis)
{
	Conversation();
	TextUpdate();
}

void COneConversationC::LateUpdate(SP(CComponent) spThis)
{

}

void COneConversationC::OnDestroy()
{
}

void COneConversationC::OnEnable()
{
	__super::OnEnable();
}

void COneConversationC::OnDisable()
{
	__super::OnDisable();
}

_bool COneConversationC::IsEnd()
{
	return m_conversationCheck;
}


void COneConversationC::Conversation()
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
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Teresa");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�׷���");
			m_inText[0] = L"����~";
			break;
		case 2:
			m_inText[0] = L"�� ���� �����Ѵ�.";
			break;
		case 3:
			m_inText[0] = L"�Ǵܱ����� �ܼ��� ���з� �������� ���� �ƴ�, �������� ���� �����ս��� ����";
			m_inText[1] = L"��Ű���� �հ� ���θ� �����մϴ�.";
			break;
		case 4:
			m_inText[0] = L"�� �������� �л��� �غ��Ͻñ� �ٶ��ϴ�.";
			break;
		case 5:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�����");
			m_inText[0] = L"��? Ű�Ƴ�, �Ȼ��� �� ����? ���� ���� �߽� �԰� ��Ż�� �� �ƴ���?";
			break;
		case 6:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"Ű�Ƴ�");
			m_inText[0] = L"��, �װ� ���ĥ ���.....��� �̻��� ���� �㼭.";
			break;
		case 7:
			m_inText[0] = L"�׷��� �޿��� ���� �ƹ��͵� ��ﳪ���� �ʾ�.....";
			m_inText[1] = L"����� ���� �̿��ߴٴ� �� �����.....";
			break;
		case 8:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�����");
			m_inText[0] = L"������, ���� �����ݾ�. ���� ��Ʈ���� �����ϰž�.";
			break;
		case 9:
			m_inText[0] = L"���� ���� �����ϱ� ����������.";
			break;
		case 10:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"Ű�Ƴ�");
			m_inText[0] = L"��������? ���� . �׷� ���迡���� ������ִ� �ǰ�?";
			break;
		case 11:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"�����");
			m_inText[0] = L"�ȵ�, �װ� ����������. �ܸ� ���� � ���������� ���� �԰� ��.";
			break;
		case 12:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"Ű�Ƴ�");
			m_inText[0] = L"����~ ������ �ʹ� ���Ҷ���~";
			break;
		case 13:
			End();
			break;
		}
	}
}

void COneConversationC::TextUpdate()
{
	m_timer -= GET_DT;

	if (m_timer <= 0)
	{
		m_timer = m_textTime;

		if (m_inText[0] != L"")
		{
			std::wstring a = m_inText[0].substr(0,1);

			std::wstring::size_type stTmp;
			stTmp = m_inText[0].find(a, 0);
			m_inText[0].erase(stTmp, 1);

			m_outText[0] += a;
		}
		else if (m_inText[1] != L"")
		{
			std::wstring a = m_inText[1].substr(0,1);

			std::wstring::size_type stTmp;
			stTmp = m_inText[1].find(a, 0);
			m_inText[1].erase(stTmp, 1);

			m_outText[1] += a;
		}

		m_conversationText[0]->GetComponent<Engine::CTextC>()->ChangeMessage(m_outText[0]);
		m_conversationText[1]->GetComponent<Engine::CTextC>()->ChangeMessage(m_outText[1]);
	}

}

void COneConversationC::End()
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

void COneConversationC::Skip()
{
	End();
}
