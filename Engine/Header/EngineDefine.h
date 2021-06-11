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




/*
#define MOUSE_LEFT		1 << 0
#define MOUSE_RIGHT		1 << 1
#define KEY_LEFT		1 << 2
#define KEY_RIGHT		1 << 3
#define KEY_DOWN		1 << 4
#define KEY_UP			1 << 5
#define KEY_CONTROL		1 << 6
#define KEY_ALT			1 << 7
#define KEY_TAB			1 << 8
#define KEY_SHIFT		1 << 9
#define KEY_ENTER		1 << 10
#define KEY_SPACE		1 << 11
#define KEY_ESC			1 << 12
#define KEY_DELETE		1 << 13
#define KEY_A			1 << 14
#define KEY_B			1 << 15
#define KEY_C			1 << 16
#define KEY_D			1 << 17
#define KEY_E			1 << 18
#define KEY_F			1 << 19
#define KEY_G			1 << 20
#define KEY_H			1 << 21
#define KEY_I			1 << 22
#define KEY_J			1 << 23
#define KEY_K			1 << 24
#define KEY_L			1 << 25
#define KEY_M			1 << 26
#define KEY_N			1 << 27
#define KEY_O			1 << 28
#define KEY_P			1 << 29
#define KEY_Q			1 << 30
#define KEY_R			1 << 31
#define KEY_S			1 << 32
#define KEY_T			1 << 33
#define KEY_U			1 << 34
#define KEY_V			1 << 35
#define KEY_W			1 << 36
#define KEY_X			1 << 37
#define KEY_Y			1 << 38
#define KEY_Z			1 << 39
#define KEY_F1			1 << 40
#define KEY_F2			1 << 41
#define KEY_F3			1 << 42
#define KEY_F4			1 << 43
#define KEY_F5			1 << 44
#define KEY_F6			1 << 45
#define KEY_F7			1 << 46
#define KEY_F8			1 << 47
#define KEY_F9			1 << 48
#define KEY_F10			1 << 49
#define KEY_F11			1 << 50
#define KEY_F12			1 << 51
#define KEY_1			1 << 52
#define KEY_2			1 << 53
#define KEY_3			1 << 54
#define KEY_4			1 << 55
#define KEY_5			1 << 56
#define KEY_6			1 << 57
#define KEY_7			1 << 58
#define KEY_8			1 << 59
#define KEY_9			1 << 60
#define KEY_0			1 << 61
*/


#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define GRAVITY			_float3(0,  -15.807f, 0)

#define ZERO_VECTOR		_float3(0,  0,  0)
#define ONE_VECTOR		_float3(1,  1,  1)
#define RIGHT_VECTOR	_float3(1,  0,  0)
#define LEFT_VECTOR		_float3(-1, 0,  0)
#define UP_VECTOR		_float3(0,  1,  0)
#define DOWN_VECTOR		_float3(0,  -1, 0)
#define FORWARD_VECTOR	_float3(0,  0,  1)
#define BACK_VECTOR		_float3(0,  0, -1)
#define MAX_VECTOR		_float3(FLT_MAX, FLT_MAX, FLT_MAX)

#define PLAYER_RAY_DISTANCE 0.7f

#define PI 3.141592f
#define EPSILON 0.0001f

#endif // !MYDEFINE_H
