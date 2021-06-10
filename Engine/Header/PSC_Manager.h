#pragma once
#include "Engine.h"

BEGIN(Engine)
class CParticleSystemC;
class ENGINE_DLL CPSC_Manager final : public CEngine
{
	DECLARE_SINGLETON(CPSC_Manager)

public:
	void Awake() override;
	void Start();
	void FixedUpdate();
	void Update();
	void LateUpdate();

	void PreRender();
	void Render();
	void PostRender();

	void OnDestroy();
	void OnEnable();
	void OnDisable();

public:
	void AddPSC(SP(CParticleSystemC) spPSC);

	_float GetRandomFloat(_float _lowBound, _float _highBound);			 // [lowBound, highBound] ������ �ִ� ������ �Ǽ��� ����.
	void   GetRandomVector(_float3* _Out, _float3* _min, _float3* _max); // �ּ��� min�� �ִ��� max�� ���ǵ� ���� ���� ���� ���͸� ���.

private:
	std::vector<SP(CParticleSystemC)> m_vParticleCom;

};
END
