#ifndef STATICMESH_H
#define STATICMESH_H

#include "MeshData.h"

BEGIN(Engine)
class ENGINE_DLL CStaticMeshData final : public CMeshData
{
	friend class CMeshStore;
private:
	explicit						CStaticMeshData		(void);
	virtual						   ~CStaticMeshData		(void);

public:
				CMeshData*			MakeClone			(void) override;
				void				FreeClone			(void) override;

				void				Awake				(std::wstring const& filePath, 
														 std::wstring const& fileName) override;
				void				Update				(void) override;

				void				OnDestory			(void) override;

private:
	static		CStaticMeshData*	Create				(std::wstring const& filePath, 
														 std::wstring const& fileName);
				void				Free				(void) override;

private:
	GETTOR		(LPD3DXMESH,		m_pMesh,			nullptr,	Mesh)
	GETTOR		(LPD3DXBUFFER,		m_pAdjacency,		nullptr,	Adjacency)
	GETTOR		(LPD3DXBUFFER,		m_pSubset,			nullptr,	Subset)	// 서브셋의 개수 == 재질의 개수 == 텍스처의 개수
	GETTOR		(LPD3DXMATERIAL,	m_pMtrl,			nullptr,	Mtrl)
};
END

#endif