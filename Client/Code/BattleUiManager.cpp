#include "Stdafx.h"
#include "BattleUiManager.h"
#include "HitsUiC.h"
#include "LifeObjectC.h"
#include "TimerUiC.h"
#include "SkillCollTimcC.h"
#include "RotationUiC.h"
#include "AlphaLifeTimeC.h"

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
	m_time->AddComponent<CTimerUiC>();
	m_playerIllustration.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerIllustration_5").get()));
	m_playerIllustration.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerIllustration_6").get()));
	m_playerProperty.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerProperty_7").get()));
	m_playerProperty.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerProperty_8").get()));
	m_skillPoint.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_SkillSP_14").get()));
	m_skillPoint.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_SpecialSkillSP_13").get())); 

	m_playerHp = pScene->GetObjectFactory()->AddClone(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"MainCanvas_PlayerHp").get();
	m_playerHp->AddComponent<Engine::CTextC>()->AddFontData(L"", _float2(-320.0f, 325.0f), _float2(0, 0), 30, DT_VCENTER + DT_CENTER + DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1), true);

	m_playerSp = pScene->GetObjectFactory()->AddClone(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"MainCanvas_PlayerSp").get();
	m_playerSp->AddComponent<Engine::CTextC>()->AddFontData(L"3 / 108", _float2(265.0f, 395.0f), _float2(0, 0), 20, DT_VCENTER + DT_CENTER + DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1), true);

	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_BasicAttack_1").get()));
	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_Evasion_0").get()));
	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_SpecialSkill_2").get()));
	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_Skill_3").get()));

	m_playerSpBar = static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerSTBar1_4").get());

	m_playerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar1_1").get()));
	m_playerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar2_2").get()));
	m_playerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar3_3").get()));

	m_waitingPlayerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerHPBar1_5").get()));
	m_waitingPlayerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerHPBar2_7").get()));

	m_waitingPlayerSpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerSTBar1_6").get()));
	m_waitingPlayerSpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerSTBar2_8").get()));

	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_13").get()));
	m_coolTimeSlider[Button_Type::BasicButton]->AddComponent<CSkillCollTimcC>();
	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_12").get()));
	m_coolTimeSlider[Button_Type::EvasionButton]->AddComponent<CSkillCollTimcC>();
	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_9").get()));
	m_coolTimeSlider[Button_Type::SpecialButton]->AddComponent<CSkillCollTimcC>();
	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_11").get()));
	m_coolTimeSlider[Button_Type::SkillButton]->AddComponent<CSkillCollTimcC>();
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_monsterStateCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"MonsterStateCanvas").get());
	m_monsterStateCanvas->AddComponent<CLifeObjectC>();

	m_monsterName =	pScene->GetObjectFactory()->AddClone(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"MonsterStateCanvas_MonsterName_0").get();
	m_monsterName->AddComponent<Engine::CTextC>()->AddFontData(L"", _float2(248.6f, -342.1f), _float2(0, 0), 50, DT_VCENTER + DT_CENTER + DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1), true);

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
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_monsterTargetCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"MonsterTargetCanvas").get());
	m_monsterTargetCanvas->AddComponent<CAlphaLifeTimeC>();

	m_target.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MonsterTargetCanvas_TargetUi_1").get()));
	m_target[0]->AddComponent<CRotationUiC>()->SetSpeed(1);
	m_target.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MonsterTargetCanvas_TargetUi_2").get()));
	m_target[1]->AddComponent<CRotationUiC>()->SetSpeed(-1);
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_giveUpCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"GiveUpCanvas").get());
	m_giveUpCanvas->AddObjectFind();
	m_giveUpCanvas->SetIsEnabled(false);

	PlayerHp(m_playerHpBar[m_playerHpBar.size() - 1]->GetMaxValue());
	PlayerSp(m_playerSpBar->GetMaxValue());

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
	m_playerHpBar.clear();
	m_waitingPlayerHpBar.clear();
	m_waitingPlayerSpBar.clear();
	m_coolTimeSlider.clear();
	m_target.clear();
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
	// ������Ʈ�� �������ִ°� �ʿ��ҵ�
	m_hitsCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(lifeTime);
	m_hitsCanvas->SetIsEnabled(true);
	m_hitCount->GetComponent<CHitsUiC>()->AddHitsCount(1);
}

void CBattleUiManager::MonsetrState(std::wstring name, _float hp, std::wstring property)
{
	// ������Ʈ ���ְ� ���ִ� ������Ʈ�� �ʿ��ҵ�
	m_monsterStateCanvas->SetIsEnabled(true);
	m_monsterStateCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(10);
	m_monsterName->GetComponent<Engine::CTextC>()->ChangeMessage(name);
	for (auto object : m_monsterHpBar)
	{
		object->SetValue(hp);
	}
	m_monsterProperty->GetComponent<Engine::CTextC>()->ChangeMessage(property);
}

void CBattleUiManager::WaitingPlayerState(std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1, _float playerSp1, std::wstring playerTexture2, std::wstring playerProperty2, _float playerHp2, _float playerSp2)
{
	m_playerIllustration[0]->GetTexture()->ChangeTexture(playerTexture1, 0);
	m_playerProperty[0]->GetTexture()->ChangeTexture(playerProperty1, 0);
	m_waitingPlayerHpBar[0]->SetValue(playerHp1);
	m_waitingPlayerSpBar[0]->SetValue(playerSp1);

	m_playerIllustration[1]->GetTexture()->ChangeTexture(playerTexture2, 0);
	m_playerProperty[1]->GetTexture()->ChangeTexture(playerProperty2, 0);
	m_waitingPlayerHpBar[1]->SetValue(playerHp2);
	m_waitingPlayerSpBar[1]->SetValue(playerSp2);
}

void CBattleUiManager::WaitingPlayerState(std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1, _float playerSp1)
{
	m_playerIllustration[0]->GetTexture()->ChangeTexture(playerTexture1, 0);
	m_playerProperty[0]->GetTexture()->ChangeTexture(playerProperty1, 0);
	m_waitingPlayerHpBar[0]->SetValue(playerHp1);
	m_waitingPlayerSpBar[0]->SetValue(playerSp1);

}

void CBattleUiManager::PlayerChange(_float hpValue, _float spValue, std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3, std::wstring buttonUI4, std::wstring specialSP, std::wstring skillSP)
{
	PlayerHp(hpValue);
	PlayerSp(spValue);

	m_skillButton[Button_Type::BasicButton]->GetTexture()->ChangeTexture(buttonUI1);
	m_skillButton[Button_Type::EvasionButton]->GetTexture()->ChangeTexture(buttonUI2);
	m_skillButton[Button_Type::SpecialButton]->GetTexture()->ChangeTexture(buttonUI3);
	m_skillButton[Button_Type::SkillButton]->GetTexture()->ChangeTexture(buttonUI4);
	m_skillButton[Button_Type::SkillButton]->SetIsEnabled(true);

	m_skillPoint[SkillPoint_Type::SpecialSp]->GetTexture()->ChangeTexture(specialSP);
	m_skillPoint[SkillPoint_Type::SpecialSp]->SetIsEnabled(true);

	m_skillPoint[SkillPoint_Type::SkillSp]->GetTexture()->ChangeTexture(skillSP);

	m_coolTimeSlider[Button_Type::SkillButton]->SetIsEnabled(true);
}

void CBattleUiManager::PlayerChange(_float hpValue, _float spValue, std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3, std::wstring specialSP)
{
	PlayerHp(hpValue);
	PlayerSp(spValue);

	m_skillButton[Button_Type::BasicButton] ->GetTexture()->ChangeTexture(buttonUI1);
	m_skillButton[Button_Type::EvasionButton]->GetTexture()->ChangeTexture(buttonUI2);
	m_skillButton[Button_Type::SpecialButton]  ->GetTexture()->ChangeTexture(buttonUI3);
	m_skillButton[Button_Type::SkillButton]->SetIsEnabled(false);

	m_skillPoint[SkillPoint_Type::SpecialSp]->GetTexture()->ChangeTexture(specialSP);
	m_skillPoint[SkillPoint_Type::SpecialSp]->SetIsEnabled(false);

	m_coolTimeSlider[Button_Type::SkillButton]->SetIsEnabled(false);
}

void CBattleUiManager::TargetUI(_float3 pos, _float value)
{
	m_monsterTargetCanvas->GetComponent<CAlphaLifeTimeC>()->SetLifeTime(value);

	m_target[0]->GetTransform()->SetPosition(pos);
	m_target[1]->GetTransform()->SetPosition(pos);

	m_monsterTargetCanvas->SetIsEnabled(true);
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
	for (auto object : m_playerHpBar)
	{
		object->SetValue(value);
	}
	m_playerHp->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring((int)value) + L" / " + std::to_wstring((int)m_playerHpBar[m_playerHpBar.size() - 1]->GetMaxValue()));
}

void CBattleUiManager::PlayerHpDown(_float value)
{
	for (auto object : m_playerHpBar)
	{
		object->SetValue(object->GetValue() - value);
	}
	m_playerHp->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring((int)m_playerHpBar[0]->GetValue()) + L" / " + std::to_wstring((int)m_playerHpBar[m_playerHpBar.size() - 1]->GetMaxValue()));
}

void CBattleUiManager::PlayerHpUp(_float value)
{
	for (auto object : m_playerHpBar)
	{
		object->SetValue(object->GetValue() + value);
	}
	m_playerHp->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring((int)m_playerHpBar[0]->GetValue()) + L" / " + std::to_wstring((int)m_playerHpBar[m_playerHpBar.size() - 1]->GetMaxValue()));
}

void CBattleUiManager::PlayerSp(_float value)
{
	m_playerSpBar->SetValue(value);
	m_playerSp->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring((int)value) + L" / " + std::to_wstring((int)m_playerSpBar->GetMaxValue()));
}

void CBattleUiManager::PlayerSpDown(_float value)
{
	m_playerSpBar->SetValue(m_playerSpBar->GetValue() - value);
	m_playerSp->GetComponent<Engine::CTextC>()->ChangeMessage((std::to_wstring((int)m_playerSpBar->GetValue()) + L" / " + std::to_wstring((int)m_playerSpBar->GetMaxValue())));
}

void CBattleUiManager::PlayerSpUp(_float value)
{
	m_playerSpBar->SetValue(m_playerSpBar->GetValue() + value);
	m_playerSp->GetComponent<Engine::CTextC>()->ChangeMessage((std::to_wstring((int)m_playerSpBar->GetValue()) + L" / " + std::to_wstring((int)m_playerSpBar->GetMaxValue())));
}

void CBattleUiManager::CollTime(_int value, _float collTime)
{
	m_coolTimeSlider[value]->SetMaxValue(collTime);
	m_coolTimeSlider[value]->SetValue(collTime);
}
