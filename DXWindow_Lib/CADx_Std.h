#pragma once
#include "CAStd.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <D2D1.h>
#include <wrl.h>

#pragma comment( lib, "d2d1.lib")

namespace DX
{
#ifdef _DEBUG

#define EM(hr,msg,_where) if (FAILED(hr)) MessageBox(NULL, L#msg, L#_where, MB_OK)

#else

#define EM(hr,msg,_where)

#endif // DEBUG




}