#ifndef EDITORMACRO_H
#define EDITORMACRO_H

#ifdef _AFX
#define ERR_MSG(msg) AfxMessageBox(msg)
#else
#define ERR_MSG(msg) MessageBox(nullptr, msg, L"System_Error", MB_OK)
#endif // _AFX

#endif