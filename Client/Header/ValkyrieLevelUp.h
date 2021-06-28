#pragma once
#include "ValkyrieFSM.h"
class CValkyrieLevelUp :
	public CValkyrieFSM
{
public:
	CValkyrieLevelUp();
	virtual ~CValkyrieLevelUp();

	// CValkyrieFSM��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;


private:
	void LevelUp();
	void ItemCountUp();
	void ItemCountDown();
private:
	static std::wstring g_selectItemName;
	static _int g_itemCount;
};

