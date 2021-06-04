#ifndef HIERARCHYLOADER_H
#define HIERARCHYLOADER_H

BEGIN(Engine)
class CDynamicMeshData;
class ENGINE_DLL CHierarchyLoader final : public ID3DXAllocateHierarchy
{
private:
	explicit						CHierarchyLoader		(const std::wstring path);
								   ~CHierarchyLoader		(void);

public:
				STDMETHOD			(CreateFrame)			(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
					
				STDMETHOD			(CreateMeshContainer)	(THIS_ LPCSTR Name,
															 CONST D3DXMESHDATA *pMeshData,
															 CONST D3DXMATERIAL *pMaterials,
															 CONST D3DXEFFECTINSTANCE *pEffectInstances,
															 DWORD NumMaterials,
															 CONST DWORD *pAdjacency,
															 LPD3DXSKININFO pSkinInfo,
															 LPD3DXMESHCONTAINER *ppNewMeshContainer);

				
				STDMETHOD			(DestroyFrame)			(THIS_ LPD3DXFRAME pFrameToFree);
				STDMETHOD			(DestroyMeshContainer)	(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

public:
	static		CHierarchyLoader*	Create					(const std::wstring path, CDynamicMeshData* pOwner);
				void				Free					(void);


private:
				void				AllocateName			(char** ppName, const char* pFrameName);
private:
				std::wstring		m_path				= L"";
				CDynamicMeshData*	m_pOwner			= nullptr;
				_int				m_curTexLastIndex	= 0;
};
END
#endif