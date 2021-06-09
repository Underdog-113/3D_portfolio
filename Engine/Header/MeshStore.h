#ifndef MESHSTORE_H
#define MESHSTORE_H

#include "ResourceStore.h"

BEGIN(Engine)
class CMeshData;
class ENGINE_DLL CMeshStore final : public CResourceStore
{
private:
	explicit					CMeshStore			(void);
	virtual					   ~CMeshStore			(void);
public:
	static	CMeshStore*			Create				(void);
			void				Free				(void);

			void				Awake				(void) override;
			void				OnDestroy			(void) override;

			void				ClearCurResource	(void) override;

			CMeshData*			GetMeshData			(std::wstring meshKey);
			void				InitMeshForScene	(std::wstring curScene, _bool isStatic = false);

			void				FindMeshesInSection	(std::wstring sectionKey, std::vector<std::wstring>& vMeshkeys);
private:
			void				ParsingMesh			(std::wstring filePath, 
													 std::wstring fileName);


private:
	typedef std::unordered_map<std::wstring, CMeshData*> _MeshMap;
				_MeshMap	m_mCurSceneMeshData;
	static		_MeshMap	m_s_mStaticMeshData;
	
	static		_uint		m_s_usage;
};
END
#endif // !MESHSTORE_H
