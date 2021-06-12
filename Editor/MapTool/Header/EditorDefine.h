#ifndef EDITORDEFINE_H
#define EDITORDEFINE_H

#define WINDOWCX GetSystemMetrics(SM_CXSCREEN);
#define WINDOWCY GetSystemMetrics(SM_CYSCREEN);

#define VIEWCX 1200/* * 0.81f*/
#define VIEWCY 760/* * 0.81f*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#endif