#ifndef MYDEFINE_H
#define MYDEFINE_H

#define DEFAULT = default
#define NONE {}

#ifndef ENGINE_MODE
#define EDITOR_MODE
#endif

//MSG_BOX && ABORT
#define _DEBUG_MSG

//Enum define
#define UNDEFINED -1

//NewLine
#define NEW_LINE L'\n'

//UnusedParam
#define UNUSED(x) (void)(x)


#define KEY_LEFT	1ULL << 0
#define KEY_RIGHT	1ULL << 1
#define KEY_UP		1ULL << 2
#define KEY_DOWN	1ULL << 3
#define KEY_WAVE	1ULL << 4
#define KEY_TAB		1ULL << 5
#define KEY_SHIFT	1ULL << 6
#define KEY_CONTROL	1ULL << 7
#define KEY_SPACE	1ULL << 8
#define KEY_RETURN	1ULL << 9
#define KEY_ESC		1ULL << 10
#define MOUSE_LEFT	1ULL << 11
#define MOUSE_RIGHT	1ULL << 12
#define MOUSE_WHEEL	1ULL << 13
#define KEY_1		1ULL << 14
#define KEY_2		1ULL << 15
#define KEY_3		1ULL << 16
#define KEY_4		1ULL << 17
#define KEY_5		1ULL << 18
#define KEY_F1		1ULL << 19
#define KEY_F2		1ULL << 20
#define KEY_F3		1ULL << 21
#define KEY_F4		1ULL << 22
#define KEY_F5		1ULL << 23
#define KEY_Q		1ULL << 24
#define KEY_W		1ULL << 25
#define KEY_E		1ULL << 26
#define KEY_R		1ULL << 27
#define KEY_A		1ULL << 28
#define KEY_S		1ULL << 29
#define KEY_D		1ULL << 30
#define KEY_F		1ULL << 31
#define KEY_Z		1ULL << 32
#define KEY_X		1ULL << 33
#define KEY_C		1ULL << 34
#define KEY_V		1ULL << 35
#define KEY_U		1ULL << 36
#define KEY_I		1ULL << 37
#define KEY_J		1ULL << 38
#define KEY_K		1ULL << 39


#define MAX_RENDER_TARGET_NUM 4

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define GRAVITY			_float3(0,  -15.807f, 0)

#define ZERO_VEC2		_float2(0, 0);

#define ZERO_VECTOR		_float3(0,  0,  0)
#define ONE_VECTOR		_float3(1,  1,  1)
#define RIGHT_VECTOR	_float3(1,  0,  0)
#define LEFT_VECTOR		_float3(-1, 0,  0)
#define UP_VECTOR		_float3(0,  1,  0)
#define DOWN_VECTOR		_float3(0,  -1, 0)
#define FORWARD_VECTOR	_float3(0,  0,  1)
#define BACK_VECTOR		_float3(0,  0, -1)
#define MAX_VECTOR		_float3(FLT_MAX, FLT_MAX, FLT_MAX)

#define ZERO_VEC4		_float4(0, 0, 0, 0);
#define DEFAULT_VEC4	_float4(0, 0, 0, 1);
#define ONE_VEC4		_float4(1, 1, 1, 1);



#define PLAYER_RAY_DISTANCE 0.7f

#define PI 3.141592f
#define EPSILON 0.0001f

#endif // !MYDEFINE_H
