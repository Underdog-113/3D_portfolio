#pragma once
#ifndef EFFECTTOOLENUM_H
#define EFFECTTOOLENUM_H

enum class ESceneID
{
	Changmo,
	NumOfSceneID
};

enum class EComponentID
{
	Default = 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID
};


enum class EColliderID
{
	Player = 0,
	Map = 1,
	CameraRay = 2,
	NumOfColliderID = 3
};

enum class EDataID
{
	BasicObject = 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player = 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene = 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Enemy = 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	EFFECT = 4 + (_uint)Engine::EDataID::NumOfEngineDataID,
	UI = 5 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID = 6 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	Player = 0 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Map = 1 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Enemy = 2 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Camera = 3 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID = 4 + (_int)Engine::ELayerID::NumOfEngineLayerID
};

//GraphicsComponent RenderID
enum class ERenderID
{
	Base = 0,
	NonAlpha = 1,
	WireFrame = 2,
	AlphaTest = 3,
	AlphaBlend = 4,
	Particle = 5,
	UI = 6,
	NumOfRenderID = 7
};
#endif // EFFECTTOOLENUM_H