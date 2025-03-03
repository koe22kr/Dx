#pragma once
#include "CAStd.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <D2D1.h>
#include <wrl.h>

#include <d3dx10math.h>
#include <d3dx11.h> 

#pragma comment( lib, "d2d1.lib")

namespace DX
{
#ifdef _DEBUG
#pragma comment( lib, "d3dx10d.lib" )	
#pragma comment( lib, "d3dx11d.lib" )	
#define EM(hr,msg,_where) if (FAILED(hr)) MessageBox(NULL, L#msg, L#_where, MB_OK)

#else

#define EM(hr,msg,_where)

#endif // DEBUG




}