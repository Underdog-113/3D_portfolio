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
	_float GetRandomFloat(_float _lowBound, _float _highBound);			 // [lowBound, highBound] 범위에 있는 임의의 실수를 리턴.
	void   GetRandomVector(_float3* _Out, _float3* _min, _float3* _max); // 최소점 min과 최대점 max로 정의된 상자 내의 임의 벡터를 출력.

private:
	GETTOR_REF(std::vector<CParticleSystemC*>, m_vParticleCom, {}, vParticleCom);

};
END
