#include "CAWindow.h"
#include "CAMessageList.h"
HWND g_hWnd;            //이거 언제 전역핸들 달았는지 확인해보기. 190508// CAStd 에 extern 선언됨
HINSTANCE g_hInstance;
CAWindow* g_pWindow = NULL;
RECT g_rtClient;
LRESULT CALLBACK WndProc(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (g_pWindow != NULL)
    {
        g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
        I_MSG.Msg_list.push_back({ hWnd,msg,wParam,lParam });
    }
    switch (msg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);// WM_QUIT 메세지큐 등록      
        }
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam); //<- _In_ HWND hWnd, 
}                                                     //  _In_ UINT Msg,
                                                      //  _In_ WPARAM wParam,
                                                      //  _In_ LPARAM lParam);
LRESULT CAWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return 1;
}

bool CAWindow::MyRegisterClass()                      
{
    WNDCLASSEXW wcex;
    wcex.lpfnWndProc = WndProc;    //필수     프로시저
    wcex.lpszClassName = L"CA";    //필수     클레스 이름
    wcex.hInstance = m_hInstance;  //필수     인스턴스
   
    wcex.style = CS_HREDRAW | CS_VREDRAW ;       //필수 이건 거의 고정
    wcex.cbSize = sizeof(WNDCLASSEX);//사이즈 맞는지 확인해서 찾음.

    //wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DEMOWINDOW);
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    if (!RegisterClassExW(&wcex))
        return false;
    return true;
}

bool CAWindow::InitWindow(HINSTANCE hInstance, int iX, int iY, int iWidth, int iHeight)
{
    m_hInstance = hInstance;
    g_hInstance = m_hInstance;
    // 1) 윈도우 레지스터 등록
    if (!MyRegisterClass())
        return false;

    RECT rt = { iX,iY,iWidth,iHeight };//RECT 구조체 좌표x,좌표y,와이드,높이
    m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    AdjustWindowRect(&rt, m_dwStyle, FALSE);        //RECT,어떤 스타일,메뉴 여부 

    // 2) 윈도우 생성
    //HWND hWnd = CreateWindowEx(WS_EX_TOOLWINDOW,
    m_hWnd = CreateWindow(
                          L"CA",                     /*lpClassName*/
                          L"Window_Title",           /*lpWindowName*/
                          m_dwStyle,       /*dwStyle*/
                          rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top ,
                          NULL,                      /*hWndParent*/ 
                          NULL,                      /*hMenu*/
                          m_hInstance,              /*hMenu*/
                          NULL);                      /*lpParam*/
    if (!m_hWnd) return 0;
    
    g_hWnd = m_hWnd;
    GetClientRect(m_hWnd, &m_Src_rtClient);//
    GetWindowRect(m_hWnd, &m_Src_rtWindow);
    g_rtClient = m_Src_rtClient;
    CenterWindow();

    ShowWindow(m_hWnd, SW_SHOW/*nCmdShow*/);
    return true;
}


void CAWindow::CenterWindow()
{
    int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    int x = (iScreenWidth - (m_Src_rtWindow.right - m_Src_rtWindow.left)) / 2;
    int y = (iScreenHeight - (m_Src_rtWindow.bottom - m_Src_rtWindow.top)) / 2;
    MoveWindow(m_hWnd, x, y, m_Src_rtWindow.right - m_Src_rtWindow.left, m_Src_rtWindow.bottom - m_Src_rtWindow.top, true);
    //y값도 같이.
    //MoveWindow(m_hWnd, x, y, w, h, true);//마지막인자 = 리페인트유무      //w,h 는 rtwindow 의 right-left 하면, 높이도 같이.

}

CAWindow::CAWindow()
{
    m_dwStyle = WS_OVERLAPPEDWINDOW;
    g_pWindow = this;
}


CAWindow::~CAWindow()
{
}

