#pragma once
class CDropItemManager
{
	DECLARE_SINGLETON(CDropItemManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

	void AllDelete();
	void AddItemList(ItemSave item);
private:
	GETTOR(std::list<ItemSave>, m_itemList, {}, ItemList)
	GETTOR_SETTOR(_int, m_gold, 0, Gold)
	GETTOR_SETTOR(_int, m_captainExp, 0, CaptainExp)
	GETTOR_SETTOR(_int, m_valkyrieExp, 0, ValkyrieExp)
};

