#ifndef EDITORENUM_H
#define EDITORENUM_H

enum class EShaderID
{
	WaterShader			= 0 + (_int)Engine::EShaderID::NumOfShaderID,
	DamageFontShader	= 1 + (_int)Engine::EShaderID::NumOfShaderID,
	CatPawShader		= 2 + (_int)Engine::EShaderID::NumOfShaderID,
	CircularGaugeShader	= 3 + (_int)Engine::EShaderID::NumOfShaderID,
	MeshTrailShader		= 4 + (_int)Engine::EShaderID::NumOfShaderID,
	DissolveShader		= 5 + (_int)Engine::EShaderID::NumOfShaderID,
	SpawnEffectShader	= 6 + (_int)Engine::EShaderID::NumOfShaderID,
	SoftEffectShader	= 7 + (_int)Engine::EShaderID::NumOfShaderID,
	AttackRangeShader	= 8 + (_int)Engine::EShaderID::NumOfShaderID,
	AlphaMaskShader     = 9 + (_int)Engine::EShaderID::NumOfShaderID,
	FireShader			= 10 + (_int)Engine::EShaderID::NumOfShaderID,
	LaserShader  		= 11 + (_int)Engine::EShaderID::NumOfShaderID,
	OutlineShader		= 12 + (_int)Engine::EShaderID::NumOfShaderID,
	FaceShader			= 13 + (_int)Engine::EShaderID::NumOfShaderID,
	KianaBodyShader		= 14 + (_int)Engine::EShaderID::NumOfShaderID,
	NumOfShaderID		= 15 + (_int)Engine::EShaderID::NumOfShaderID
};

enum class ESceneID
{
	Changmo,
	NumOfSceneID
};

enum class EComponentID
{
	Default = 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID
};


enum class ECollisionID
{
	Floor				= 0 + (_uint)Engine::ECollisionID::NumOfColliderID,
	Wall				= 1 + (_uint)Engine::ECollisionID::NumOfColliderID,
	Player				= 2 + (_uint)Engine::ECollisionID::NumOfColliderID,
	Enemy				= 3 + (_uint)Engine::ECollisionID::NumOfColliderID,
	Trigger				= 4 + (_uint)Engine::ECollisionID::NumOfColliderID,
	PhaseChanger		= 5 + (_uint)Engine::ECollisionID::NumOfColliderID,
	NumOfColliderID		= 6 + (_uint)Engine::ECollisionID::NumOfColliderID
};

enum class EDataID
{
	BasicObject			= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player				= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene				= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Enemy				= 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Effect				= 4 + (_uint)Engine::EDataID::NumOfEngineDataID,
	UI					= 5 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Stat				= 6 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Monster				= 7 + (_uint)Engine::EDataID::NumOfEngineDataID,
	ClientObject		= 8 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID			= 9 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	Player			= 0 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Map				= 1 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Enemy			= 2 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Camera			= 3 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	UI				= 4 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID	= 5 + (_int)Engine::ELayerID::NumOfEngineLayerID
};
#endif // CLIENTENUM_H