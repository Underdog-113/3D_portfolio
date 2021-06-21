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
	virtual void CoolTime(_float& curTime, _float maxTime, _bool& readyType); // ÇöÀç ÄğÅ¸ÀÓ, ¸Æ½º ÄğÅ¸ÀÓ, ÄğÅ¸ÀÓ Å¸ÀÔ
	virtual _float GetCost() { return m_cost; }

protected:
	_float m_cost = 0;
};
#endif
