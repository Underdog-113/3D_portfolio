#ifndef EDITORDEFINE_H
#define EDITORDEFINE_H

#define WINDOWCX GetSystemMetrics(SM_CXSCREEN);
#define WINDOWCY GetSystemMetrics(SM_CYSCREEN);

#define VIEWCX 1920 * 0.81f
#define VIEWCY 1080 * 0.81f

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#endif