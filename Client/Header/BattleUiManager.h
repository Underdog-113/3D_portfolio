#ifndef BATTLEUIMANAGER_H
#define BATTLEUIMANAGER_H

#include "Button.h"
#include "Slider.h"
#include "ScrollViewObject.h"
#include "Canvas.h"
#include "ImageObject.h"

//public enum 
// 0 : �Ϲݰ���
// 1 : ȸ��
// 2 : �ʻ��
// 3 : Ư������



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

	void KeyPad(_int value); // ����Ű ����
	void HitCount(_float lifeTime); // �޺��ڽ�
	void MonsterState(std::wstring name, _float hp, _int hpCount, std::wstring property); // ���� ü�¹� �Ӽ� �̸� ǥ��
	void MonsterStateEnd();

	void WaitingPlayerState(std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1,  _float playerSp1,
					 std::wstring playerTexture2, std::wstring playerProperty2, _float playerHp2, _float playerSp2);
	void WaitingPlayerState(std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1, _float playerSp1);

	void PlayerSkillActivation(_int value);

	// HP SP ��ư4�� ��ų����Ʈ2��
	void PlayerChange(_float hpValue, _float spValue, std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3, std::wstring buttonUI4,
		std::wstring specialSP, std::wstring skillSP);
	void PlayerChange(_float hpValue, _float spValue, std::wstring buttonUI1, std::wstring buttonUI2, std::wstring buttonUI3,
		std::wstring specialSP);
	
	void TargetUI(Engine::CObject* object, _float value);

	void MonsterHpDown(_float value);
	void MonsterHpUp(_float value);
	void PlayerHp(_float value);
	void PlayerHpMax(_float value);
	void PlayerHpDown(_float value);
	void PlayerHpUp(_float value);

	void PlayerSp(_float value);
	void PlayerSpMax(_float value);
	void PlayerSpDown(_float value);
	void PlayerSpUp(_float value);

	bool SkillExecution(_int value, _int spValue, _float collTime);
	void BattleEnd();
private:
	void skillActivationImageCheck();
	void monsterHpBarCheck();
private:
	_bool m_activation;
	_int m_monsterHpCount;

	Engine::CCanvas* m_monsterStateCanvas;
	Engine::CCanvas* m_mainCanvas;
	Engine::CCanvas* m_hitsCanvas;
	Engine::CCanvas* m_monsterTargetCanvas;
	Engine::CCanvas* m_giveUpCanvas;
	Engine::CCanvas* m_victoryCanvas;

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
	std::vector<Engine::CImageObject*> m_skillPoint; // ��ų����Ҷ� �ʿ��� ������
	std::vector<Engine::CImageObject*> m_target;

	std::vector<Engine::CImageObject*> m_skillImage; // ��ų��ư �̹���
	std::vector<Engine::CImageObject*> m_skillActivationImage; // ��ų�� Ȱ��ȭ�Ǹ� ���� �̹���
	std::vector<CButton*> m_skillButton; // ��ų��ư
	std::vector<Engine::CSlider*> m_coolTimeSlider;

	std::vector<Engine::CSlider*> m_monsterHpBar;
	std::vector<Engine::CSlider*> m_monsterWhiteHpBar;
	std::vector<Engine::CSlider*> m_playerHpBar;
	Engine::CSlider* m_playerSpBar;
	std::vector<Engine::CSlider*> m_waitingPlayerHpBar;
	std::vector<Engine::CSlider*> m_waitingPlayerSpBar;

};


#endif