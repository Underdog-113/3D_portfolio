#pragma once
#include "ValkyrieFSM.h"

struct ItemInfo
{
	ItemInfo(std::wstring name, _int count)
	{
		m_name = name;
		m_count = count;
	}

	std::wstring m_name;
	_int m_count;
};

class CSupplyOut :
	public CValkyrieFSM
{
public:
	CSupplyOut();
	virtual ~CSupplyOut();

	// CValkyrieFSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void RandomBox();
	void RandoBoxList();
private:
	_bool m_init;
	std::list<ItemInfo> m_itemList;

	CScrollViewObject* m_scrollView;
	_int m_outCount;
	_float m_timer;
};

