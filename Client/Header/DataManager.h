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
	CCaptainData* FindCaptainData(); // 함장
	CValkyrieStatusData* FindInStockValkyrieData(std::wstring keyValue); // 보유 발키리
	CInStockValkyrieData* FindInStockValkyrieData(); // 보유 발키리
	CValkyrieStatusData* FindvalkyrieStatusData(std::wstring keyValue); // 모든 발키리
	CSquadData* FindSquadData(); // 파티 발키리
	CValkyrieStatusData* FindSquadData(std::wstring keyValue); // 파티 발키리
	std::vector<CWeaponData*> FindWeaponData(); // 무기
	CWeaponData* FindWeaponData(std::wstring keyValue); // 무기
	std::vector<CItemData*> FindItemData(); // 재료
	CItemData* FindItemData(std::wstring keyValue); // 재료
	
	// 삽입
	void CaptainInit(); // 함장
	void InStockValkyrieInit(std::wstring valkyrieName); // 보유 발키리
	void ValkyrieStatusDataListInit(std::wstring valkyrieName); // 모든 발키리
	void SquadInit(std::wstring valkyrieName); // 스쿼드
	void SquadInit(_int value, std::wstring valkyrieName); // 스쿼드
	void WeaponInit(std::wstring weaponName); // 무기
	void ItemInit(std::wstring itemName, _int count = 1); // 아이템


	// 삭제
	void SquadDelete(std::wstring keyValue); // 스쿼드
	void ItemDelete(std::wstring keyValue); //  재료
private:
	CCaptainData* m_pCaptainData = nullptr; // 함장
	CInStockValkyrieData* m_pInStockValkyrieData; // 보유 발키리
	std::vector<CValkyrieStatusData*> m_pValkyrieStatusDataList; // 모든 발키리
	CSquadData* m_pSquadData; // 파티 발키리
	std::vector<CWeaponData*> m_pWeaponDataList; // 무기
	std::vector<CItemData*> m_pItemDataList; // 재료
};

#endif

// 함장의 정보
// 모든 발키리의 1랩정보는 저장하고 시작하면 불러와야된다.