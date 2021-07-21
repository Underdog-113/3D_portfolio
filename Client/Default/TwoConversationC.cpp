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
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"키아나");
			m_inText[0] = L"헤헤, 어때, 나의 조종 실력이, 네겐트로피에서 몇등이나 하려나?";
			break;
		case 2:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"사쿠라");
			m_inText[0] = L"그런 건 모르겠지만.....뒤쪽이라는 건 확실해.";
			break;
		case 3:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"키아나");
			m_inText[0] = L"뭐야, 내가 그렇게 많은 적들을 없앴는데도?";
			break;
		case 4:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"사쿠라");
			m_inText[0] = L"그렇긴 하지만 사용이 가능한 유일한 기갑을 이렇게 키아나가 망가뜨렸잖아.";
			break;
		case 5:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"키아나");
			m_inText[0] = L"그거야 어쩔 수 없었는걸. 어쨌든 이렇게 많은 적을 처리했는데.";
			break;
		case 6:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"사쿠라");
			m_inText[0] = L"그리고 실수로 자폭 버튼을 누르셨죠?.";
			break;
		case 7:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Kiana");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"키아나");
			m_inText[0] = L"그, 그걸 어떻게?";
			break;
		case 8:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Teresa");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"테레사");
			m_inText[0] = L"그....기갑은 이미 망가졌으니, 더 이상 이 문제는 다루지 않는 건 어떨까?";
			break;
		case 9:
			m_inText[0] = L"말이 나와서 말인데, 함내 설계도에 따르면.... 전면의 대문을 지나면 함교란 말이지?";
			break;
		case 10:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Sakura");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"사쿠라");
			m_inText[0] = L"맞아요 테레사님.";
			break;
		case 11:
			m_conversationPlayerImage->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Teresa");
			m_conversationName->GetComponent<Engine::CTextC>()->ChangeMessage(L"테레사");
			m_inText[0] = L"그렇다면 이 기세를 몰아 함교의 제어권을 확보하는건 어때?";
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