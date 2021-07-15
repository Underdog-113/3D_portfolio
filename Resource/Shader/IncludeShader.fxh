\
static const float zNear = 0.1;
static const int WINCX = 1440;
static const int WINCY = 810;
static const float PI = 3.1415926535;

struct cBuffer
{
	matrix viewProj;
	matrix proj;
	matrix invView;
	matrix invProj;
	float3 worldCamPos;
	float3 worldCamLook;
	float zFar;
	float time;
};

cBuffer g_cBuffer;