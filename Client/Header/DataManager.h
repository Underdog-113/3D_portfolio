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
	// �κ��丮 ��
	std::unordered_map<std::wstring, 
	/*
	������ �����۵��� Ŭ������ ���� �����Ͱ��� �������ְԸ���� �ش� ������ ���δ� �κ��丮 �ʿ��ٰ� ��������
	*/
};

#endif