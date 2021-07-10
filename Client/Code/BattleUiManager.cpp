#include "Stdafx.h"
#include "BattleUiManager.h"
#include "HitsUiC.h"
#include "LifeObjectC.h"
#include "TimerUiC.h"
#include "SkillCollTimcC.h"
#include "RotationUiC.h"
#include "AlphaLifeTimeC.h"
#include "MonsterSliderC.h"
#include "GlitterC.h"
#include "SkillActivationC.h"
#include "TargetPositionC.h"

IMPLEMENT_SINGLETON(CBattleUiManager)
void CBattleUiManager::Start(Engine::CScene * pScene)
{
	m_activation = true;
	m_monsterHpCount = 0;

	m_specialUICanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"specialUICanvas").get());
	m_specialUICanvas->AddObjectFind();
	m_specialUICanvas->SetIsEnabled(false);
	m_specialUBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"specialUICanvas_specialU_0").get()));
	m_specialUBar[0]->SetValue(4);
	m_specialUBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"specialUICanvas_specialU_1").get()));
	m_specialUBar[1]->SetValue(4);
	m_specialUBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"specialUICanvas_specialU_2").get()));
	m_specialUBar[2]->SetValue(4);
	m_specialUBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"specialUICanvas_specialU_3").get()));
	m_specialUBar[3]->SetValue(4);

	//MainCanvas
	m_mainCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"MainCanvas").get());

	m_keyPad = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_KeyPad_0").get());
	m_keyPad->GetTexture()->AddTexture(L"JoyStick_Move", 0);

	m_time = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_Time_4").get());
	m_time->AddComponent<CTimerUiC>();

	m_playerIllustration.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerIllustration_5").get()));
	m_playerIllustration.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerIllustration_6").get()));

	m_playerProperty.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerProperty_7").get()));
	m_playerProperty.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_PlayerProperty_8").get()));

	m_skillPoint.emplace_back(static_cast<Engine::CTextObject*>(pScene->FindObjectByName(L"MainCanvas_SkillSP_14").get()));
	m_skillPoint.emplace_back(static_cast<Engine::CTextObject*>(pScene->FindObjectByName(L"MainCanvas_SpecialSkillSP_13").get()));

	m_playerHp = pScene->GetObjectFactory()->AddClone(L"TextObject", true, (_int)Engine::ELayerID::UI, L"MainCanvas_PlayerHp").get();
	m_playerHp->AddComponent<Engine::CTextC>()->AddFontData(L"", _float2(-320.0f, 325.0f), _float2(0, 0), 30, DT_VCENTER + DT_CENTER + DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1), true);

	m_playerSp = pScene->GetObjectFactory()->AddClone(L"TextObject", true, (_int)Engine::ELayerID::UI, L"MainCanvas_PlayerSp").get();
	m_playerSp->AddComponent<Engine::CTextC>()->AddFontData(L"3 / 108", _float2(265.0f, 395.0f), _float2(0, 0), 20, DT_VCENTER + DT_CENTER + DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1), true);

	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_BasicAttack_0").get()));
	m_skillImage.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_BasicAttack_16").get()));

	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_Evasion_1").get()));
	m_skillImage.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_Evasion_17").get()));

	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_SpecialSkill_2").get()));
	m_skillImage.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_SpecialSkill_18").get()));

	m_skillButton.emplace_back(static_cast<CButton*>(pScene->FindObjectByName(L"MainCanvas_Skill_3").get()));
	m_skillImage.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_Skill_19").get()));

	m_skillActivationImage.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_EvasionActivation_18").get()));
	m_skillActivationImage[0]->AddComponent<CSkillActivationC>();
	m_skillActivationImage.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_SpecialSkillActivation_19").get()));
	m_skillActivationImage[1]->AddComponent<CSkillActivationC>();
	m_skillActivationImage.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MainCanvas_SkillActivation_21").get()));
	m_skillActivationImage[2]->AddComponent<CSkillActivationC>();

	m_playerSpBar = static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerSTBar1_4").get());

	m_playerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar1_1").get()));
	m_playerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar2_2").get()));
	m_playerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_PlayerHPBar3_3").get()));

	m_waitingPlayerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerHPBar1_5").get()));
	m_waitingPlayerHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerHPBar2_7").get()));

	m_waitingPlayerSpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerSTBar1_6").get()));
	m_waitingPlayerSpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_WaitingPlayerSTBar2_8").get()));

	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_9").get()));
	m_coolTimeSlider[Button_Type::BasicButton]->AddComponent<CSkillCollTimcC>();
	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_10").get()));
	m_coolTimeSlider[Button_Type::EvasionButton]->AddComponent<CSkillCollTimcC>();
	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_11").get()));
	m_coolTimeSlider[Button_Type::SpecialButton]->AddComponent<CSkillCollTimcC>();
	m_coolTimeSlider.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_SkillCollTime_12").get()));
	m_coolTimeSlider[Button_Type::SkillButton]->AddComponent<CSkillCollTimcC>();

	pScene->FindObjectByName(L"MainCanvas_Image_22")->AddComponent<CSizeUpC>()->SetSize(171.3f);
	pScene->FindObjectByName(L"MainCanvas_Image_22")->GetComponent<CSizeUpC>()->SetSpeed(150.0f);
	pScene->FindObjectByName(L"MainCanvas_Image_22")->SetIsEnabled(false);
	m_vQte.emplace_back(pScene->FindObjectByName(L"MainCanvas_Image_22").get());

	pScene->FindObjectByName(L"MainCanvas_Image_23")->AddComponent<CSizeUpC>()->SetSize(171.3f);
	pScene->FindObjectByName(L"MainCanvas_Image_23")->GetComponent<CSizeUpC>()->SetSpeed(150.0f);
	pScene->FindObjectByName(L"MainCanvas_Image_23")->SetIsEnabled(false);
	m_vQte.emplace_back(pScene->FindObjectByName(L"MainCanvas_Image_23").get());
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//MonsterStateCanvas
	m_monsterStateCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"MonsterStateCanvas").get());
	m_monsterStateCanvas->AddComponent<CLifeObjectC>();

	m_monsterName = pScene->FindObjectByName(L"MonsterStateCanvas_MonsterName_0").get();
	m_monsterCount = pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHpCount_1").get();

	m_monsterProperty = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterProperty_3").get());
	m_monsterProperty->GetTexture()->AddTexture(L"icon_up", 0);

	m_monsterHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar1_0").get()));
	m_monsterHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar2_1").get()));
	m_monsterHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar3_2").get()));

	m_monsterWhiteHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar1_3").get()));
	m_monsterWhiteHpBar[0]->AddComponent<CMonsterSliderC>()->SetMonsterSlider(m_monsterHpBar[2]);
	m_monsterWhiteHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar2_4").get()));
	m_monsterWhiteHpBar[1]->AddComponent<CMonsterSliderC>()->SetMonsterSlider(m_monsterHpBar[2]);
	m_monsterWhiteHpBar.emplace_back(static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MonsterStateCanvas_MonsterHPBar3_5").get()));
	m_monsterWhiteHpBar[2]->AddComponent<CMonsterSliderC>()->SetMonsterSlider(m_monsterHpBar[2]);

	for (int i = 0; i < 3; i++)
	{
		m_monsterHpBar[i]->GetFill()->GetComponent<Engine::CTextureC>()->AddTexture(L"BossHpBarteal", 0);
		m_monsterHpBar[i]->GetFill()->GetComponent<Engine::CTextureC>()->AddTexture(L"BossHpBarBlue", 0);
		m_monsterHpBar[i]->GetFill()->GetComponent<Engine::CTextureC>()->AddTexture(L"BossHpBarPurple", 0);

		m_monsterHpBar[i]->GetBackGround()->GetComponent<Engine::CTextureC>()->AddTexture(L"BossHpBarOrange", 0);
		m_monsterHpBar[i]->GetBackGround()->GetComponent<Engine::CTextureC>()->AddTexture(L"BossHpBarteal", 0);
		m_monsterHpBar[i]->GetBackGround()->GetComponent<Engine::CTextureC>()->AddTexture(L"BossHpBarBlue", 0);
	}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//HitsCanvas
	m_hitsCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"HitsCanvas").get());
	m_hitsCanvas->AddComponent<CLifeObjectC>();

	m_hitCount = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"HitsCanvas_HitCount_1").get());

	m_hitCount->AddComponent<CHitsUiC>();
	m_hits = static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"HitsCanvas_Hits_2").get());
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//MonsterTargetCanvas
	m_monsterTargetCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"MonsterTargetCanvas").get());
	m_monsterTargetCanvas->AddComponent<CLifeObjectC>();

	m_target.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MonsterTargetCanvas_TargetUi_1").get()));
	m_target[0]->AddComponent<CRotationUiC>()->SetSpeed(1);
	m_target[0]->AddComponent<CTargetPositionC>();
	m_target[0]->AddComponent<CSkillActivationC>();
	m_target.emplace_back(static_cast<Engine::CImageObject*>(pScene->FindObjectByName(L"MonsterTargetCanvas_TargetUi_2").get()));
	m_target[1]->AddComponent<CRotationUiC>()->SetSpeed(-1);
	m_target[1]->AddComponent<CTargetPositionC>();
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// GiveUpCanvas
	m_giveUpCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"GiveUpCanvas").get());
	m_giveUpCanvas->AddObjectFind();
	m_giveUpCanvas->SetIsEnabled(false);

	m_victoryCanvas = static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"VictoryCanvas").get());
	m_victoryCanvas->AddObjectFind();
	m_victoryCanvas->SetIsEnabled(false);
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	PlayerHp(m_playerHpBar[m_playerHpBar.size() - 1]->GetMaxValue());
	PlayerSp(m_playerSpBar->GetMaxValue());
}

void CBattleUiManager::Update(void)
{
	if (!m_activation)
		return;

	skillActivationImageCheck();
	monsterHpBarCheck();

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
		m_keyPad->GetTransform()->SetRotationZ(0);
		break;
	case 7: // W
		m_keyPad->GetTexture()->SetTexIndex(1);
		m_keyPad->GetTransform()->SetRotationZ(D3DXToRadian(45));
		break;
	case 4: // A
		m_keyPad->GetTexture()->SetTexIndex(1);
		m_keyPad->GetTransform()->SetRotationZ(D3DXToRadian(90));
		break;
	case 1: // W
		m_keyPad->GetTexture()->SetTexIndex(1);
		m_keyPad->GetTransform()->SetRotationZ(D3DXToRadian(135));
		break;
	case 2: // S
		m_keyPad->GetTexture()->SetTexIndex(1);
		m_keyPad->GetTransform()->SetRotationZ(D3DXToRadian(180));
		break;
	case 3: // S
		m_keyPad->GetTexture()->SetTexIndex(1);
		m_keyPad->GetTransform()->SetRotationZ(D3DXToRadian(225));
		break;
	case 6: // D
		m_keyPad->GetTexture()->SetTexIndex(1);
		m_keyPad->GetTransform()->SetRotationZ(D3DXToRadian(270));
		break;
	case 9: // S
		m_keyPad->GetTexture()->SetTexIndex(1);
		m_keyPad->GetTransform()->SetRotationZ(D3DXToRadian(315));
		break;
	case 5: //
		m_keyPad->GetTexture()->SetTexIndex(0);
		break;
	}
}

void CBattleUiManager::HitCount(_float lifeTime)
{
	m_hitsCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(lifeTime);
	m_hitsCanvas->SetIsEnabled(true);
	m_hitCount->GetComponent<CHitsUiC>()->AddHitsCount(1);

	if (m_hitCount->GetComponent<CHitsUiC>()->GetHitsCount() == 0)
	{
		m_hitCount->GetComponent<Engine::CTextureC>()->ChangeTexture(L"HpBarKara 881168");
		m_hitCount->GetComponent<Engine::CTextureC>()->SetColor(_float4(1, 1, 1, 1));
		m_hitCount->GetTransform()->SetPosition(_float3(-589.6f, 206.48f, m_hitCount->GetTransform()->GetPosition().z));
		m_hitCount->GetTransform()->SetSize(_float3(89.6f, 84.8f, 0.0f));
	}
	if (m_hitCount->GetComponent<CHitsUiC>()->GetHitsCount() == 9)
	{
		m_hitCount->GetComponent<Engine::CTextureC>()->ChangeTexture(L"DamageBar2");
		m_hitCount->GetComponent<Engine::CTextureC>()->SetColor(_float4(0.4431f, 0.7529f, 0.6117f, 1));
		m_hitCount->GetTransform()->SetPosition(_float3(-598.34f, 206.48f, m_hitCount->GetTransform()->GetPosition().z));
		m_hitCount->GetTransform()->SetSize(_float3(87.0f, 84.8f, 0.0f));
	}
	if (m_hitCount->GetComponent<CHitsUiC>()->GetHitsCount() == 19)
	{
		m_hitCount->GetComponent<Engine::CTextureC>()->SetColor(_float4(0.5490f, 0.8509f, 0.9058f, 1));
	}
	if (m_hitCount->GetComponent<CHitsUiC>()->GetHitsCount() == 39)
	{
		m_hitCount->GetComponent<Engine::CTextureC>()->SetColor(_float4(0.9176f, 0.5803f, 0.9803f, 1));
	}
	if (m_hitCount->GetComponent<CHitsUiC>()->GetHitsCount() == 49)
	{
		m_hitCount->GetComponent<Engine::CTextureC>()->SetColor(_float4(0.8784f, 0.7215f, 0.1294f, 1));
	}
}

void CBattleUiManager::MonsterState(std::wstring name, _float hpMax, _float hp, _int hpCount, std::wstring property)
{
	m_monsterStateCanvas->SetIsEnabled(true);
	m_monsterStateCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(10);
	m_monsterName->GetComponent<Engine::CTextC>()->ChangeMessage(name);
	m_monsterHpCount = hpCount;
	m_monsterCount->GetComponent<Engine::CTextC>()->ChangeMessage(L"x" + std::to_wstring(m_monsterHpCount));

	_int a = (m_monsterHpCount -1) % 4;
	std::cout << a << std::endl;

	_float ThpMax = (hpMax / m_monsterHpCount) / 3;
	_float hpMaxSum = 0;
	for (auto object : m_monsterHpBar)
	{
		object->SetMinValue(hpMaxSum);
		hpMaxSum += ThpMax;
		object->SetMaxValue(hpMaxSum);
		object->SetValue(hp / m_monsterHpCount);
		object->GetFill()->GetComponent<Engine::CTextureC>()->SetTexIndex(a);
		object->GetBackGround()->GetComponent<Engine::CTextureC>()->SetTexIndex(a);
	}

	hpMaxSum = 0;
	for (auto object : m_monsterWhiteHpBar)
	{
		object->SetMinValue(hpMaxSum);
		hpMaxSum += ThpMax;
		object->SetMaxValue(hpMaxSum);
		object->SetValue(hp / m_monsterHpCount);
	}

	if (property == L"UP")
	{
		m_monsterProperty->GetTexture()->SetTexIndex(0);
	}
	else if (property == L"DOWN")
	{
		m_monsterProperty->GetTexture()->SetTexIndex(1);
	}
}

void CBattleUiManager::MonsterStateEnd()
{
	m_monsterStateCanvas->SetIsEnabled(false);
}

bool CBattleUiManager::IsMonsterStateOn()
{
	return m_monsterStateCanvas->GetIsEnabled();
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

void CBattleUiManager::WaitingPlayerState(_uint num, std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1, _float playerSp1)
{
	m_playerIllustration[num]->GetTexture()->ChangeTexture(playerTexture1, 0);
	m_playerProperty[num]->GetTexture()->ChangeTexture(playerProperty1, 0);
	m_waitingPlayerHpBar[num]->SetValue(playerHp1);
	m_waitingPlayerSpBar[num]->SetValue(playerSp1);
}

void CBattleUiManager::PlayerSkillActivation(_int value)
{
	m_skillActivationImage[value - 1]->SetIsEnabled(true);
}

void CBattleUiManager::PlayerChange(std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3, std::wstring buttonUI4,
	_int specialSP, _int skillSP,
	_float coolTime1, _float coolTime2, _float coolTime3)
{
	m_skillImage[Button_Type::BasicButton]->GetTexture()->ChangeTexture(buttonUI1);
	m_skillImage[Button_Type::EvasionButton]->GetTexture()->ChangeTexture(buttonUI2);
	m_skillImage[Button_Type::SpecialButton]->GetTexture()->ChangeTexture(buttonUI3);
	m_skillImage[Button_Type::SkillButton]->GetTexture()->ChangeTexture(buttonUI4);
	m_skillButton[Button_Type::SkillButton]->SetIsEnabled(true);
	m_skillImage[Button_Type::SkillButton]->SetIsEnabled(true);

	m_skillPoint[SkillPoint_Type::SpecialSp]->GetComponent<Engine::CTextC>()->ChangeMessage(L"SP : " + std::to_wstring(specialSP));
	m_skillPoint[SkillPoint_Type::SpecialSp]->SetIsEnabled(true);

	m_skillPoint[SkillPoint_Type::SkillSp]->GetComponent<Engine::CTextC>()->ChangeMessage(L"SP : " + std::to_wstring(skillSP));

	m_coolTimeSlider[Button_Type::SkillButton]->SetIsEnabled(true);

	m_coolTimeSlider[Button_Type::EvasionButton]->SetValue(coolTime1);
	m_coolTimeSlider[Button_Type::SpecialButton]->SetValue(coolTime2);
	m_coolTimeSlider[Button_Type::SkillButton]->SetValue(coolTime3);
}

void CBattleUiManager::PlayerChange(std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3,
	_int specialSP,
	_float coolTime1, _float coolTime2)
{
	m_skillImage[Button_Type::BasicButton] ->GetTexture()->ChangeTexture(buttonUI1);
	m_skillImage[Button_Type::EvasionButton]->GetTexture()->ChangeTexture(buttonUI2);
	m_skillImage[Button_Type::SpecialButton]  ->GetTexture()->ChangeTexture(buttonUI3);
	m_skillImage[Button_Type::SkillButton]->SetIsEnabled(false);
	m_skillButton[Button_Type::SkillButton]->SetIsEnabled(false);

	m_skillPoint[SkillPoint_Type::SpecialSp]->GetComponent<Engine::CTextC>()->ChangeMessage(L"SP : " + std::to_wstring(specialSP));
	m_skillPoint[SkillPoint_Type::SpecialSp]->SetIsEnabled(false);

	m_coolTimeSlider[Button_Type::SkillButton]->SetIsEnabled(false);

	m_coolTimeSlider[Button_Type::EvasionButton]->SetValue(coolTime1);
	m_coolTimeSlider[Button_Type::SpecialButton]->SetValue(coolTime2);
}

void CBattleUiManager::OnTargetUI(SP(Engine::CObject) object, _float value)
{
	m_monsterTargetCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(value);
	m_target[0]->GetComponent<CTargetPositionC>()->SetTarget(object);
	m_target[1]->GetComponent<CTargetPositionC>()->SetTarget(object);

	m_monsterTargetCanvas->SetIsEnabled(true);
}

void CBattleUiManager::OffTargetUI()
{
	m_target[0]->GetComponent<CTargetPositionC>()->SetTarget(nullptr);
	m_target[1]->GetComponent<CTargetPositionC>()->SetTarget(nullptr);

	m_monsterTargetCanvas->SetIsEnabled(false);
}

void CBattleUiManager::MonsterHpDown(_float value)
{
	m_monsterStateCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(10.f);

	for (auto object : m_monsterHpBar)
	{
		object->SetValue(object->GetValue() - value);
	}
}

void CBattleUiManager::MonsterHpUp(_float value)
{
	m_monsterStateCanvas->GetComponent<CLifeObjectC>()->SetLifeTime(m_monsterStateCanvas->GetComponent<CLifeObjectC>()->GetLifeTime() + 1);

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

void CBattleUiManager::PlayerHpMax(_float value)
{
	_float hpmax = value / 3;
	_float hp = 0;
	for (auto object : m_playerHpBar)
	{
		object->SetMinValue(hp);
		hp += hpmax;
		object->SetMaxValue(hp);
	}
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

void CBattleUiManager::PlayerSpMax(_float value)
{
	m_playerSpBar->SetMaxValue(value);
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

void CBattleUiManager::SpecialUICanvasOn()
{
	m_specialUICanvas->SetIsEnabled(true);
}

void CBattleUiManager::SpecialUICanvasOff()
{
	m_specialUICanvas->SetIsEnabled(false);
}

void CBattleUiManager::SpecialUIUp()
{
	for (auto& obj : m_specialUBar)
	{
		obj->SetValue(obj->GetValue() + 1);
	}
}

void CBattleUiManager::SpecialUIDwon()
{
	for (auto& obj : m_specialUBar)
	{
		obj->SetValue(obj->GetValue() - 1);
	}
}

bool CBattleUiManager::SkillExecution(_int value, _int spValue, _float collTime)
{
	if (m_coolTimeSlider[value]->GetValue() <= 0 && m_playerSpBar->GetValue() >= spValue)
	{
		m_coolTimeSlider[value]->SetValue(collTime);
		m_coolTimeSlider[value]->SetMaxValue(collTime);
		PlayerSpDown((_float)spValue);
	}
	return false;
}

void CBattleUiManager::BattleEnd()
{
	m_activation = false;

	m_monsterStateCanvas->SetIsEnabled(false);
	m_mainCanvas->SetIsEnabled(false);
	m_hitsCanvas->SetIsEnabled(false);
	m_monsterTargetCanvas->SetIsEnabled(false);
	m_giveUpCanvas->SetIsEnabled(false);
	m_victoryCanvas->SetIsEnabled(true);
	m_specialUICanvas->SetIsEnabled(false);

	_float m_totalTime = m_time->GetComponent<CTimerUiC>()->GetTotalTime();
	_int minute = (int)m_totalTime / 60;
	_int second = (int)m_totalTime % 60;
	Engine::GET_CUR_SCENE->FindObjectByName(L"VictoryCanvas_Image_3")->GetComponent<Engine::CTextC>()
								->ChangeMessage(std::to_wstring(minute) + L" : " + std::to_wstring(second));

	Engine::GET_CUR_SCENE->FindObjectByName(L"VictoryCanvas_Image_1")->GetComponent<Engine::CTextC>()
		->ChangeMessage(std::to_wstring(m_hitCount->GetComponent<CHitsUiC>()->GetMaxHitsCount()));
}

void CBattleUiManager::QteOn(_int value)
{
	m_vQte[value]->SetIsEnabled(true);
}

void CBattleUiManager::QteOff(_int value)
{
	m_vQte[value]->SetIsEnabled(false);
}

void CBattleUiManager::skillActivationImageCheck()
{
	if (m_playerSpBar->GetValue() >= 80 && m_coolTimeSlider[Button_Type::SpecialButton]->GetValue() <= 0)
		m_skillActivationImage[Button_Type::SpecialButton - 1]->SetIsEnabled(true);
	else
		m_skillActivationImage[Button_Type::SpecialButton - 1]->SetIsEnabled(false);

	if (m_playerSpBar->GetValue() >= 7 && m_coolTimeSlider[Button_Type::SkillButton]->GetValue() <= 0)
		m_skillActivationImage[Button_Type::SkillButton - 1]->SetIsEnabled(true);
	else
		m_skillActivationImage[Button_Type::SkillButton - 1]->SetIsEnabled(false);
}

void CBattleUiManager::monsterHpBarCheck()
{
	if (m_monsterHpBar[2]->GetValue() <= 0 && m_monsterHpCount > 1)
	{
		m_monsterHpCount--;

		for (auto object : m_monsterHpBar)
		{
			object->SetValue(m_monsterHpBar[2]->GetMaxValue());
			_int a = (m_monsterHpCount - 1) % 4;
			std::cout << a << std::endl;
			object->GetBackGround()->GetComponent<Engine::CTextureC>()->SetTexIndex(a);
			object->GetFill()->GetComponent<Engine::CTextureC>()->SetTexIndex(a);
		}

		for (auto object : m_monsterWhiteHpBar)
		{
			object->SetValue(m_monsterWhiteHpBar[2]->GetMaxValue());
		}

		m_monsterCount->GetComponent<Engine::CTextC>()->ChangeMessage(L"x" + std::to_wstring(m_monsterHpCount));
	}
	if (m_monsterHpBar[2]->GetValue() <= 0 && m_monsterHpCount == 1)
	{
		m_monsterHpCount--;
		m_monsterCount->GetComponent<Engine::CTextC>()->ChangeMessage(L"");
	}
}
