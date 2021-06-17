#ifndef DATAMANAGER_H
#define DATAMANAGER_H

class CDataManager final
{
public:
	DECLARE_SINGLETON(CDataManager)

public:
	void Awake(void);
	void Update(void);
	void OnDestroy(void);

private:
	// 인벤토리 맵
	std::unordered_map<std::wstring, 
	/*
	각각의 아이템들을 클래스로 만들어서 데이터값을 가지고있게만들고 해당 값들을 전부다 인벤토리 맵에다가 저장하자
	*/
};

#endif