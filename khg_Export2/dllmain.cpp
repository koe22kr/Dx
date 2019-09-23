// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"

extern ClassDesc2* GetExportDesc();
HINSTANCE hInstance;

//hmodule 이 핸들로 보면 된다.
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{


    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
      //  hInstance = hModule;//
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
// max - Plugins  에 넣으면 됨. 



//외부 공개 함수 리스트 있어야함 " 무조건 "
//LibDescription
//LibNumbverClasses


__declspec(dllexport)const TCHAR* LibDescription()
{
    return _T("khgExport 100");
}
__declspec(dllexport)int LibNumberClasses()
{
    return 1;
}
///////////////////////////////////
__declspec(dllexport)ClassDesc* LibClassDesc(int i)
{
    switch (i)
    {
    case 0 : return GetExportDesc();
    default:return 0;
    }
    
}
//////아래 편집

__declspec(dllexport) ULONG LibVersion()
{
    return VERSION_3DSMAX;
}

__declspec(dllexport) int LibInitialize(void)
{
    return TRUE;
}

__declspec(dllexport) int LibShutdown(void)
{
    return TRUE;
}

TCHAR *GetString(int id)
{
    static TCHAR buf[256];

    if (hInstance)
        return LoadString(hInstance, id, buf, _countof(buf)) ? buf : NULL;
    return NULL;
}



//   __declspec(dllexport) 라고 붙여야 외부에 노출됨