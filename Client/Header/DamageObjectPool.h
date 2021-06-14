#ifndef DAMAGEOBJECTPOOL_H
#define DAMAGEOBJECTPOOL_H


class CDamageObjectPool final
{
public:
	DECLARE_SINGLETON(CDamageObjectPool)

public:
	void Start(Engine::CScene* pScene);
	void Update(void);
	void OnDestroy(void);

	void AddDamage(_float3 pos, _float3 size, _float interval, _float upSpped, _float enableTime, _int damage, std::wstring color);
	void ReMoveDamage();
private:
	std::list<Engine::CObject*> m_disabledObjectList;
	std::list<Engine::CObject*> m_activationObjectList;

	_int m_damage;
	_float m_interval;
};


#endif