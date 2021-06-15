#ifndef BATTLEUIMANAGER_H
#define BATTLEUIMANAGER_H

#include "Button.h"
#include "Slider.h"
#include "ScrollViewObject.h"
#include "Canvas.h"
#include "ImageObject.h"
class CBattleUiManager final
{
public:
	DECLARE_SINGLETON(CBattleUiManager)
public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

	void KeyPad(_int value); // 방향키 변경
	void HitCount(_float lifeTime); // 콤보박스
	void MonsetrState(std::wstring name, _float hp, std::wstring property); // 몬스터 체력바 속성 이름 표시
	void WaitingPlayerState(std::wstring playerTexture1, std::wstring playerProperty1, _float playerHp1, // 대기 플레이어 상태
					 std::wstring playerTexture2, std::wstring playerProperty2, _float playerHp2);
	void PlayerSkillPoint(std::wstring specialSP, std::wstring skillSP = L""); // 현재 플레이어 hp sp

	void MonsterHpDown(_float value);
	void MonsterHpUp(_float value);
	void PlayerHp(_float value);
	void PlayerHpDown(_float value);
	void PlayerHpUp(_float value);

	void PlayerSp(_float value);
	void PlayerSpDown(_float value);
	void PlayerSpUp(_float value);
private:

private:
	Engine::CCanvas* m_monsterStateCanvas;
	Engine::CCanvas* m_mainCanvas;
	Engine::CCanvas* m_hitsCanvas;

	Engine::CImageObject* m_keyPad;
	Engine::CImageObject* m_hitCount;
	Engine::CImageObject* m_hits;
	Engine::CImageObject* m_monsterProperty;
	Engine::CObject* m_monsterName;
	Engine::CObject* m_playerHp;
	Engine::CObject* m_playerSp;
	Engine::CImageObject* m_time;
	std::vector<Engine::CImageObject*> m_playerIllustration;
	std::vector<Engine::CImageObject*> m_playerProperty;
	std::vector<Engine::CImageObject*> m_skillPoint;

	std::vector<Engine::CSlider*> m_monsterHpBar;
	std::vector<Engine::CSlider*> m_playerHPBar;
	Engine::CSlider* m_playerSTBar;
	std::vector<Engine::CSlider*> m_waitingPlayerHpBar;
	std::vector<Engine::CSlider*> m_waitingPlayerStBar;
};


#endif
