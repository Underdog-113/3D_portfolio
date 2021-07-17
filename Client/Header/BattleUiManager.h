#ifndef BATTLEUIMANAGER_H
#define BATTLEUIMANAGER_H

#include "Button.h"
#include "Slider.h"
#include "ScrollViewObject.h"
#include "Canvas.h"
#include "ImageObject.h"

//public enum 
// 0 : 일반공격
// 1 : 회피
// 2 : 필살기
// 3 : 특수공격



class CBattleUiManager final
{
public:
	enum Button_Type
	{
		BasicButton,
		EvasionButton,
		SpecialButton,
		SkillButton
	};

	enum SkillPoint_Type
	{
		SpecialSp,
		SkillSp
	};
public:
	DECLARE_SINGLETON(CBattleUiManager)
public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

	void KeyPad(_int value); // 방향키 변경
	void HitCount(_float lifeTime); // 콤보박스
	void MonsterState(std::wstring name, _float hpMax, _float hp, _int hpCount, std::wstring property, _float brakeMaxValue, _float brakeValue); // 몬스터 체력바 속성 이름 표시
	void MonsterStateTimerReset();
	void MonsterStateEnd();
	bool IsMonsterStateOn();

	void WaitingPlayerState(std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1,  _float playerSp1,
					 std::wstring playerTexture2, std::wstring playerProperty2, _float playerHp2, _float playerSp2);

	void WaitingPlayerState(_uint num, std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1, _float playerSp1, _float swapCollTime);

	void PlayerSkillActivation(_int value);

	// HP SP 버튼4개 스킬포인트2개
	void PlayerChange(std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3, std::wstring buttonUI4,
		_int specialSP, _int skillSP,
		_float coolTime1, _float coolTime2, _float coolTime3);
	void PlayerChange(std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3,
		_int specialSP,
		_float coolTime1, _float coolTime2);
	
	void OnTargetUI(SP(Engine::CObject) object, _float value);
	void OffTargetUI();

	void MonsterHpDown(_float value);
	void MonsterHpUp(_float value);
	void BreakGaugeSetting(_float value);
	void SetBreakGaugeValue(_float value);
	void BreakGaugeDown(_float value);
	void PlayerHp(_float value);
	void PlayerHpMax(_float value);
	void PlayerHpDown(_float value);
	void PlayerHpUp(_float value);

	void PlayerSp(_float value);
	void PlayerSpMax(_float value);
	void PlayerSpDown(_float value);
	void PlayerSpUp(_float value);

	void SpecialUICanvasOn();
	void SpecialUICanvasOff();
	void SpecialUIUp();
	void SpecialUIDwon();

	bool SkillExecution(_int value, _int spValue, _float collTime);
	bool SkillExecution_Switching(_int value, _int spValue, _float remainCool, _float coolTime);
	void BattleEnd();
	void GameOver();

	void QteOn(_int value);
	void QteOff(_int value);
private:
	void skillActivationImageCheck();
	void monsterHpBarCheck();
	void SquadOff(Engine::CScene * pScene);
	void WaitingPlayerSetting();
private:
	_bool m_activation;
	_int m_monsterHpCount;

	Engine::CCanvas* m_monsterStateCanvas;
	Engine::CCanvas* m_mainCanvas;
	Engine::CCanvas* m_hitsCanvas;
	Engine::CCanvas* m_monsterTargetCanvas;
	Engine::CCanvas* m_giveUpCanvas;
	Engine::CCanvas* m_victoryCanvas;
	Engine::CCanvas* m_specialUICanvas;

	Engine::CImageObject* m_keyPad;
	Engine::CImageObject* m_hitCount;
	Engine::CImageObject* m_hits;
	Engine::CImageObject* m_monsterProperty;
	Engine::CObject* m_monsterName;
	Engine::CObject* m_monsterCount;
	Engine::CObject* m_playerHp;
	Engine::CObject* m_playerSp;
	Engine::CImageObject* m_time;


	std::vector<Engine::CImageObject*> m_playerIllustration;
	std::vector<Engine::CImageObject*> m_playerProperty;
	std::vector<Engine::CTextObject*> m_skillPoint; // 스킬사용할때 필요한 게이지
	std::vector<Engine::CImageObject*> m_target;

	std::vector<Engine::CImageObject*> m_skillImage; // 스킬버튼 이미지
	std::vector<Engine::CImageObject*> m_skillActivationImage; // 스킬이 활성화되면 나올 이미지
	std::vector<CButton*> m_skillButton; // 스킬버튼
	std::vector<Engine::CSlider*> m_coolTimeSlider;

	Engine::CSlider* m_barkGaugeBar;
	std::vector<Engine::CSlider*> m_monsterHpBar;
	std::vector<Engine::CSlider*> m_monsterWhiteHpBar;
	std::vector<Engine::CSlider*> m_playerHpBar;
	Engine::CSlider* m_playerSpBar;
	std::vector<Engine::CSlider*> m_playerChange;
	std::vector<Engine::CSlider*> m_waitingPlayerHpBar;
	std::vector<Engine::CSlider*> m_waitingPlayerSpBar;
	std::vector<Engine::CSlider*> m_specialUBar;

	std::vector<Engine::CObject*> m_vQte;
};


#endif