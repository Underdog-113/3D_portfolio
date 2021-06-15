#include "Stdafx.h"
#include "BattleUiManager.h"
#include "HitsUiC.h"
#include "LifeObjectC.h"

IMPLEMENT_SINGLETON(CBattleUiManager)
void CBattleUiManager::Start(Engine::CScene * pScene)
{
	m_mainCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"MainCanvas").get());

	m_keyPad = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_KeyPad_0").get());
	m_keyPad->GetTexture()->AddTexture(L"JoyStick_W", 0);
	m_keyPad->GetTexture()->AddTexture(L"JoyStick_A", 0);
	m_keyPad->GetTexture()->AddTexture(L"JoyStick_D", 0);
	m_keyPad->GetTexture()->AddTexture(L"JoyStick_S", 0);

	m_time = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_Time_4").get());
	m_playerIllustration.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerIllustration_5").get()));
	m_playerIllustration.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerIllustration_6").get()));
	m_playerProperty.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerProperty_7").get()));
	m_playerProperty.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerProperty_8").get()));
	m_skillPoint.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_SpecialSkillSP_13").get()));
	m_skillPoint.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_SkillSP_14").get()));


	m_playerHPBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar1_3").get()));
	m_playerHPBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar2_4").get()));
	m_playerHPBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar3_5").get()));

	m_waitingPlayerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerHPBar1_6").get()));
	m_waitingPlayerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerHPBar2_8").get()));

	m_waitingPlayerStBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerSTBar1_7").get()));
	m_waitingPlayerStBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerSTBar2_9").get()));
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_monsterStateCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"MonsterStateCanvas").get());
	m_monsterStateCanvas->AddComponent<CLifeObjectC>();

	m_monsterProperty = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterProperty_3").get());

	m_monsterHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar1_0").get()));
	m_monsterHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar2_1").get()));
	m_monsterHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar3_2").get()));
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_hitsCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"HitsCanvas").get());
	m_hitsCanvas->AddComponent<CLifeObjectC>();

	m_hitCount = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"HitsCanvas_HitCount_1").get());
	m_hitCount->AddComponent<CHitsUiC>();
	m_hits = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"HitsCanvas_Hits_2").get());
}

void CBattleUiManager::Update(void)
{
	
}

void CBattleUiManager::OnDestroy(void)
{
	m_playerIllustration.clear();
	m_playerProperty.clear();
	m_skillPoint.clear();

	m_monsterHpBar.clear();
	m_playerHPBar.clear();
	m_waitingPlayerHpBar.clear();
	m_waitingPlayerStBar.clear();
}

void CBattleUiManager::KeyPad(_int value)
{
	switch (value)
	{
	case 8: // W
		m_keyPad->GetTexture()->SetTexIndex(1);
		break;
	case 4: // A
		m_keyPad->GetTexture()->SetTexIndex(2);
		break;
	case 6: // D
		m_keyPad->GetTexture()->SetTexIndex(3);
		break;
	case 2: // S
		m_keyPad->GetTexture()->SetTexIndex(4);
		break;
	case 5: // 
		m_keyPad->GetTexture()->SetTexIndex(0);
		break;
	}
}

void CBattleUiManager::HitCount(_float lifeTime)
{
	// 오프젝트를 관리해주는게 필요할듯
	m_hitsCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(lifeTime);
	m_hitsCanvas->SetIsEnabled(true);
	m_hitCount->GetComponent<CHitsUiC>()->AddHitsCount(1);
}

void CBattleUiManager::MonsetrState(std::wstring name, _float hp, std::wstring property)
{
	// 오브젝트 켜주고 꺼주는 오브젝트가 필요할듯
	m_monsterStateCanvas->SetIsEnabled(true);
	m_monsterStateCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(10);

	for (auto object : m_monsterHpBar)
	{
		object->SetValue(hp);
	}
	m_monsterProperty->GetComponent<Engine::CTextC>()->ChangeMessage(property);
}

void CBattleUiManager::WaitingPlayerState(std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1, std::wstring playerTexture2, std::wstring playerProperty2, _float playerHp2)
{
	m_playerIllustration[0]->GetTexture()->ChangeTexture(playerTexture1, 0);
	m_playerProperty[0]->GetTexture()->ChangeTexture(playerProperty1, 0);
	m_waitingPlayerHpBar[0]->SetValue(playerHp1);

	if (playerTexture2 == L"")
	{
		m_playerIllustration[1]->SetIsEnabled(false);
		m_playerProperty[1]->SetIsEnabled(false);
		m_waitingPlayerHpBar[1]->SetIsEnabled(false);
	}
	else
	{
		m_playerIllustration[1]->SetIsEnabled(false);
		m_playerProperty[1]->SetIsEnabled(false);
		m_waitingPlayerHpBar[1]->SetIsEnabled(false);
	}

	m_playerIllustration[1]->GetTexture()->ChangeTexture(playerTexture2, 0);
	m_playerProperty[1]->GetTexture()->ChangeTexture(playerProperty2, 0);
	m_waitingPlayerHpBar[1]->SetValue(playerHp2);
}

void CBattleUiManager::PlayerSkillPoint(std::wstring specialSP, std::wstring skillSP)
{
	m_skillPoint[0]->GetTexture()->ChangeTexture(specialSP);

	if (skillSP == L"")
	{
		m_skillPoint[1]->SetIsEnabled(false);
	}
	else
	{
		m_skillPoint[1]->SetIsEnabled(true);
	}

	m_skillPoint[1]->GetTexture()->ChangeTexture(skillSP);
}

void CBattleUiManager::MonsterHpDown(_float value)
{
	for (auto object : m_monsterHpBar)
	{
		object->SetValue(object->GetValue() - value);
	}
}

void CBattleUiManager::MonsterHpUp(_float value)
{
	for (auto object : m_monsterHpBar)
	{
		object->SetValue(object->GetValue() + value);
	}
}

void CBattleUiManager::PlayerHp(_float value)
{
	for (auto object : m_playerHPBar)
	{
		object->SetValue(value);
	}
}

void CBattleUiManager::PlayerHpDown(_float value)
{
	for (auto object : m_playerHPBar)
	{
		object->SetValue(object->GetValue() - value);
	}
}

void CBattleUiManager::PlayerHpUp(_float value)
{
	for (auto object : m_playerHPBar)
	{
		object->SetValue(object->GetValue() + value);
	}
}

