#ifndef ATBPATTERN_H
#define ATBPATTERN_H

class Engine::CObject;

class CATBPattern abstract
{
public:
	explicit CATBPattern(void);
	virtual	~CATBPattern(void);

public:
	virtual void Pattern(Engine::CObject* pOwner) PURE;
	virtual void CoolTime(_float& curTime, _float maxTime, _bool& readyType); // ���� ��Ÿ��, �ƽ� ��Ÿ��, ��Ÿ�� Ÿ��
	virtual _float GetCost() { return m_cost; }

protected:
	_float m_cost = 0;
};
#endif
