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
	CCaptainData* FindCaptainData(); // ����
	CValkyrieStatusData* FindInStockValkyrieData(std::wstring keyValue); // ���� ��Ű��
	CInStockValkyrieData* FindInStockValkyrieData(); // ���� ��Ű��
	CValkyrieStatusData* FindvalkyrieStatusData(std::wstring keyValue); // ��� ��Ű��
	CSquadData* FindSquadData(); // ��Ƽ ��Ű��
	CWeaponData* FindWeaponData(std::wstring keyValue); // ����
	CItemData* FindItemData(std::wstring keyValue); // ���
	
	// ����
	void CaptainInit(); // ����
	void InStockValkyrieInit(std::wstring valkyrieName); // ���� ��Ű��
	void ValkyrieStatusDataListInit(std::wstring valkyrieName); // ��� ��Ű��
	void SquadInit(std::wstring valkyrieName); // ������
	void WeaponInit(std::wstring weaponName); // ����
	void ItemInit(std::wstring itemName); // ������

private:
	CCaptainData* m_captainData = nullptr; // ����
	CInStockValkyrieData* m_inStockValkyrieData; // ���� ��Ű��
	std::list<CValkyrieStatusData*> m_valkyrieStatusDataList; // ��� ��Ű��
	CSquadData* m_squadData; // ��Ƽ ��Ű��
	std::vector<CWeaponData*> m_weaponDataList; // ����
	std::vector<CItemData*> m_itemDataList; // ���
};

#endif

// ������ ����
// ��� ��Ű���� 1�������� �����ϰ� �����ϸ� �ҷ��;ߵȴ�.