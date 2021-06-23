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

	// 검색
	CCaptainData* FindCaptainData();
	CInStockValkyrieData* FindInStockValkyrieData();
	CValkyrieStatusData* FindvalkyrieStatusData(std::wstring keyValue);
	CSquadData* FindSquadData();
	CWeaponData* FindWeaponData(std::wstring keyValue);
	CItemData* FindItemData(std::wstring keyValue);
	
	// 삽입
	void CaptainInit(); // 함장
	void ValkyrieStatusDataListInit(std::wstring valkyrieName); // 발키리
	void ItemInit(std::wstring itemName); // 아이템
	void WeaponInit(std::wstring weaponName); // 무기
	void InStockValkyrieInit(std::wstring valkyrieName); // 보유 발키리
private:
	CCaptainData* m_captainData;
	CInStockValkyrieData* m_inStockValkyrieData;
	std::list<CValkyrieStatusData*> m_valkyrieStatusDataList;
	CSquadData* m_squadData;
	std::list<CWeaponData*> m_weaponDataList;
	std::list<CItemData*> m_itemDataList;
};

#endif

// 함장의 정보
// 모든 발키리의 1랩정보는 저장하고 시작하면 불러와야된다.