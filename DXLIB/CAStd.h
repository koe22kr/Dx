#pragma once
#include <WinSock2.h>

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <cstdlib>
#include <set>
#include <algorithm>
#pragma comment( lib, "msimg32") //msing32.lib
#pragma comment(lib,"fmod_vc.lib")
//#pragma comment (lib, "CAWindow_Lib.lib") //이놈은 좋은놈이다.
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")

#if defined(DEBUG) || (_DEBUG)
#pragma comment(lib,"DXLIB.lib")
#else
#pragma commnet(lib,"DXLIB.lib")
#endif

//

using namespace std;

//#define Fir
#ifdef Fir
#define WINMAIN int APIENTRY  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){
#define WINRUN_DEFAULT Sample test_window; test_window.InitWindow(hInstance,0,0,800,600); test_window.Run();}
#define WINRUN(x,y,width,height) Sample test_window; test_window.InitWindow(hInstance,x,y,width,height); test_window.Run();}
#else

#define WINRUN_DEFAULT int APIENTRY  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){Sample test_window; test_window.InitWindow(hInstance,0,0,800,600); test_window.Run();}
#define WINRUN(x,y,width,height) int APIENTRY  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){Sample test_window; test_window.InitWindow(hInstance,x,y,width,height); test_window.Run();}
#endif 


extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
//extern CAInputMap g_ActionInput;
extern float g_fSecondPerFrame;  //프레임당 sec
extern float g_fGameTimer;    //총시간

extern RECT g_rtClient;


//struct CAInputMap //TInputActionMap; 이라고도 함.
//{
//    DWORD bWKey;
//    DWORD bSKey;
//    DWORD bAKey;
//    DWORD bDKey;
//    DWORD bLeftClick;
//    DWORD bRightClick;
//    DWORD bExit;
//    DWORD bSpace;
//
//};

//typedef basic_string<TCHAR> T_STR;
//typedef basic_string<WCHAR> W_STR;
//typedef basic_string<char> C_STR;
using T_STR = basic_string<TCHAR>;
using W_STR = basic_string<WCHAR>;
using C_STR = basic_string<char>;
        
template<class T>
class CASingleton
{
public:
    static T& GetInstance()
    {
        static T singleton;
        return singleton;
    }
};
//getinstance I_~~~로 매크로화.




struct WINT
{
    int x = 0;
    int y = 0;
    WINT() {};
    WINT(int a, int b):x(a),y(b) {};
    WINT(const WINT& wint) :x(wint.x), y(wint.y) {};
    WINT(int& a, int&b) : x(a), y(b) {};
    ~WINT() {};
    WINT operator +(WINT& wint) { return WINT(x + wint.x, y + wint.y); };
    WINT operator +(POINT& point) { return WINT(x + point.x, y + point.y); };
    WINT& operator =(WINT& src_wint)
    {
       // x = y = x = y;
        if (this == &src_wint)
        {
            return *this;
        }
        this->x = src_wint.x;
        this->y = src_wint.y;

        return *this;
    }
};
struct WFLOAT
{
    float x = 0.0f;
    float y = 0.0f;
    WFLOAT() {};
    WFLOAT(float a, float b) :x(a), y(b) {};
    WFLOAT& operator =(WFLOAT& src_float)
    {
        if (this == &src_float)
        {
            return *this;
        }
        this->x = src_float.x;
        this->y = src_float.y;

        return *this;
    }
};
