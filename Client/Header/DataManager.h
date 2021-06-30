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
	CValkyrieStatusData* FindSquadData(std::wstring keyValue); // ��Ƽ ��Ű��
	std::vector<CWeaponData*> FindWeaponData(); // ����
	CWeaponData* FindWeaponData(std::wstring keyValue); // ����
	std::vector<CItemData*> FindItemData(); // ���
	CItemData* FindItemData(std::wstring keyValue); // ���
	
	// ����
	void CaptainInit(); // ����
	void InStockValkyrieInit(std::wstring valkyrieName); // ���� ��Ű��
	void ValkyrieStatusDataListInit(std::wstring valkyrieName); // ��� ��Ű��
	void SquadInit(std::wstring valkyrieName); // ������
	void SquadInit(_int value, std::wstring valkyrieName); // ������
	void WeaponInit(std::wstring weaponName); // ����
	void ItemInit(std::wstring itemName, _int count = 1); // ������


	// ����
	void SquadDelete(std::wstring keyValue); // ������
	void ItemDelete(std::wstring keyValue); //  ���
private:
	CCaptainData* m_pCaptainData = nullptr; // ����
	CInStockValkyrieData* m_pInStockValkyrieData; // ���� ��Ű��
	std::vector<CValkyrieStatusData*> m_pValkyrieStatusDataList; // ��� ��Ű��
	CSquadData* m_pSquadData; // ��Ƽ ��Ű��
	std::vector<CWeaponData*> m_pWeaponDataList; // ����
	std::vector<CItemData*> m_pItemDataList; // ���
};

#endif

// ������ ����
// ��� ��Ű���� 1�������� �����ϰ� �����ϸ� �ҷ��;ߵȴ�.