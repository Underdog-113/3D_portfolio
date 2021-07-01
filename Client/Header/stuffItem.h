#pragma once
#include "ValkyrieFSM.h"
class CStuffItem :
	public CValkyrieFSM
{
public:
	CStuffItem();
	virtual ~CStuffItem();

	// CValkyrieFSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void InformationWindow();

private:
	_bool m_init;
};

