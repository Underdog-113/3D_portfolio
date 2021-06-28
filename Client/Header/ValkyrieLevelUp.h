#pragma once
#include "ValkyrieFSM.h"
class CValkyrieLevelUp :
	public CValkyrieFSM
{
public:
	CValkyrieLevelUp();
	virtual ~CValkyrieLevelUp();

	// CValkyrieFSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;


public:
	void LevelUp();
	void ItemCountUp();
	void ItemCountDown();
	void ItemSelect();
private:
	static std::wstring g_selectItemName;
	static _int g_itemCount;
};

