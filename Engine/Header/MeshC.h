#ifndef MESHC_H
#define MESHC_H

#include "MeshData.h"
#include "RenderComponent.h"

BEGIN(Engine)
class CMeshData;
class CGraphicsC;
class ENGINE_DLL CMeshC final : public CRenderComponent
{
public:
	explicit					CMeshC			(void);
							   ~CMeshC			(void);

public:
			SP(CComponent)		MakeClone		(CObject* pObject) override;
			void				Awake			(void) override;
			void				Start			(SP(CComponent) spThis) override;

			void				FixedUpdate		(SP(CComponent) spThis) override;
			void				Update			(SP(CComponent) spThis) override;
			void				LateUpdate		(SP(CComponent) spThis) override;

			void				PreRender		(SP(CGraphicsC) spGC);
			void				PreRender		(SP(CGraphicsC) spGC, LPD3DXEFFECT& pEffect);

			void				Render			(SP(CGraphicsC) spGC);
			void				Render			(SP(CGraphicsC) spGC, LPD3DXEFFECT& pEffect);

			void				PostRender		(SP(CGraphicsC) spGC);
			void				PostRender		(SP(CGraphicsC) spGC, LPD3DXEFFECT& pEffect);

			void				OnDestroy		(void) override;

			void				OnEnable		(void) override;
			void				OnDisable		(void) override;
public:
			void				AddMeshData		(CMeshData* pMeshData);
			void				AddMeshData		(std::wstring meshKey);
			void				GenMinMaxVtx	(void);

private:
			void				RenderStatic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex);
			void				RenderStatic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex, LPD3DXEFFECT pEffect);

			void				RenderDynamic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex);
			void				RenderDynamic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex, LPD3DXEFFECT pEffect);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Mesh;

private:
	typedef std::vector<CMeshData*> _MESHES;
	GETTOR_SETTOR	(_MESHES,	m_vMeshDatas,	{},				MeshDatas)

	GETTOR			(_float3,	m_meshSize,		ZERO_VECTOR,	MeshSize)
	GETTOR			(_float3,	m_minVertex,	MAX_VECTOR,		MinVertex)
	GETTOR			(_float3,	m_maxVertex,	-MAX_VECTOR,	MaxVertex)
	GETTOR_SETTOR	(_bool,		m_initTex,		false,			InitTex)
};
END
#endif // !MESH_H
