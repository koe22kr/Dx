#include "CAWindow.h"
#include "CAMessageList.h"
HWND g_hWnd;            //�̰� ���� �����ڵ� �޾Ҵ��� Ȯ���غ���. 190508// CAStd �� extern �����
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
            PostQuitMessage(0);// WM_QUIT �޼���ť ���      
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
    wcex.lpfnWndProc = WndProc;    //�ʼ�     ���ν���
    wcex.lpszClassName = L"CA";    //�ʼ�     Ŭ���� �̸�
    wcex.hInstance = m_hInstance;  //�ʼ�     �ν��Ͻ�
   
    wcex.style = CS_HREDRAW | CS_VREDRAW ;       //�ʼ� �̰� ���� ����
    wcex.cbSize = sizeof(WNDCLASSEX);//������ �´��� Ȯ���ؼ� ã��.

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
    // 1) ������ �������� ���
    if (!MyRegisterClass())
        return false;

    RECT rt = { iX,iY,iWidth,iHeight };//RECT ����ü ��ǥx,��ǥy,���̵�,����
    m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    AdjustWindowRect(&rt, m_dwStyle, FALSE);        //RECT,� ��Ÿ��,�޴� ���� 

    // 2) ������ ����
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
    //y���� ����.
    //MoveWindow(m_hWnd, x, y, w, h, true);//���������� = ������Ʈ����      //w,h �� rtwindow �� right-left �ϸ�, ���̵� ����.

}

CAWindow::CAWindow()
{
    m_dwStyle = WS_OVERLAPPEDWINDOW;
    g_pWindow = this;
}


CAWindow::~CAWindow()
{
}

