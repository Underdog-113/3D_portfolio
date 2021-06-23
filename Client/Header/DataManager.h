#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

class CCaptainData;
class CInStockValkyrieData;
class CValkyrieStatusData;
class CSquadData;
class CWeaponData;
class CItemData;
class CDataManager
{
public:
	DECLARE_SINGLETON(CDataManager)
public:
	void Start();
	void Update(void);
	void OnDestroy(void);

	// �˻�
	CCaptainData* FindCaptainData();
	CInStockValkyrieData* FindInStockValkyrieData();
	CValkyrieStatusData* FindvalkyrieStatusData(std::wstring keyValue);
	CSquadData* FindSquadData();
	CWeaponData* FindWeaponData(std::wstring keyValue);
	CItemData* FindItemData(std::wstring keyValue);
	
	// ����
	void CaptainInit(); // ����
	void ValkyrieStatusDataListInit(std::wstring valkyrieName); // ��Ű��
	void ItemInit(std::wstring itemName); // ������
	void WeaponInit(std::wstring weaponName); // ����
	void InStockValkyrieInit(std::wstring valkyrieName); // ���� ��Ű��
private:
	CCaptainData* m_captainData;
	CInStockValkyrieData* m_inStockValkyrieData;
	std::list<CValkyrieStatusData*> m_valkyrieStatusDataList;
	CSquadData* m_squadData;
	std::list<CWeaponData*> m_weaponDataList;
	std::list<CItemData*> m_itemDataList;
};

#endif

// ������ ����
// ��� ��Ű���� 1�������� �����ϰ� �����ϸ� �ҷ��;ߵȴ�.