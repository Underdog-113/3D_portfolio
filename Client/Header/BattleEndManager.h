#pragma once
class CValkyrieFSM;
class CBattleEndManager
{
public:	enum STATE { Weapon, Item, STATEEND };
public:
	DECLARE_SINGLETON(CBattleEndManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

private:
	void ValkyrieUI();
	void CaptainUI();
	void ItemUI();

	void PlayerIS();
	void DataUpdate();
private:

	GETTOR(Engine::CScene*, m_scene, {}, Scene);
	
	_size m_squadSize;

	std::list<ItemSave> m_itemList;

	_int m_captainExp;
	_int m_addCaptainExp = 0;

	_int m_valkyrieExp;
	_int m_addValkryieExp = 0;

	_int m_gold;

	_int m_outCount;
	_float m_timer;

};


// 슬라이더바는 조금씩 오르는게 보기좋다