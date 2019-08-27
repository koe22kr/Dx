#include "CADevice.h"

IDXGIFactory*            CADevice::m_pFactory = nullptr;
ID3D11Device*            CADevice::m_pDevice = nullptr;
ID3D11DeviceContext*     CADevice::m_pImmediate_Device_Context = nullptr;

bool CADevice::Create_Device()
{
    UINT Create_Device_Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS;

#ifdef _DEBUG
    //D3D11_CREATE_DEVICE_FLAG;                               //에서
    Create_Device_Flags |= D3D11_CREATE_DEVICE_DEBUG;   //비트연산으로 중복 가능////////////////////////////////////////////////////////////////////////////////////////
#endif // _DEBUG

    D3D_DRIVER_TYPE DT[] =
    {
        D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_REFERENCE
    };

    //D3D_FEATURE_LEVEL;
    D3D_FEATURE_LEVEL pFeature_Levels[] = { D3D_FEATURE_LEVEL_11_0 ,D3D_FEATURE_LEVEL_10_1 ,D3D_FEATURE_LEVEL_10_0 };
    UINT FL_size = ARRAYSIZE(pFeature_Levels);


    for (int DT_count = 0; DT_count < ARRAYSIZE(DT); DT_count++)
    {
        if (FAILED(hr = D3D11CreateDevice(
            NULL,
            DT[DT_count],
            NULL,
            Create_Device_Flags,
            pFeature_Levels,
            FL_size,
            D3D11_SDK_VERSION,
            &m_pDevice,
            &m_Feature_Level,
            &m_pImmediate_Device_Context
        )))
        {
            MessageBox(g_hWnd, L"D3D11CreateDevice_failed", L"CADevice", MB_OK);
            return false;
        }
        if (m_Feature_Level < D3D_FEATURE_LEVEL_11_0)
        {
            continue;
        }
        break;
    }
    return true;
}

bool CADevice::Create_DXGIFactory()
{
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pFactory);
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_DXGIFactory_Fail", L"CADevice", MB_OK);
        return false;
    }



    /////
    //if (m_pDevice == NULL) return E_FAIL;
    //HRESULT hr;// = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory) );
    //IDXGIDevice * pDXGIDevice;
    //hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

    //IDXGIAdapter * pDXGIAdapter;
    //hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

    //IDXGIFactory * pIDXGIFactory;
    //pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pFactory);

    //pDXGIDevice->Release();
    //pDXGIAdapter->Release();


    return true;
}
bool CADevice::Create_Swap_Chain()
{

    if (m_pFactory == nullptr)
    {
        MessageBox(g_hWnd, L"Create_SwapChain_m_pFacktory_is_nullptr", L"CADevice", MB_OK);
        return false;
    }



    ZeroMemory(&m_Swap_Chain_Desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    //DXGI_MODE_DESC;
    //    UINT Width;
    //    UINT Height;
    m_Swap_Chain_Desc.BufferDesc.Width = g_rtClient.right;
    m_Swap_Chain_Desc.BufferDesc.Height = g_rtClient.bottom;

    //    DXGI_RATIONAL RefreshRate;
    //        UINT Numerator;
    //        UINT Denominator;
    m_Swap_Chain_Desc.BufferDesc.RefreshRate.Denominator = 1;
    m_Swap_Chain_Desc.BufferDesc.RefreshRate.Numerator = 60;

    //    DXGI_FORMAT Format = DXGI_FORMAT_R8G8_UNORM;
    //    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    //    DXGI_MODE_SCALING Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    m_Swap_Chain_Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    m_Swap_Chain_Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    m_Swap_Chain_Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    //DXGI_SAMPLE_DESC SampleDesc;
    //    UINT Count;
    //    UINT Quality;
    m_Swap_Chain_Desc.SampleDesc.Count = 1;
    m_Swap_Chain_Desc.SampleDesc.Quality = 0;


    //    DXGI_USAGE BufferUsage;
    //
    //    #define DXGI_USAGE_SHADER_INPUT             0x00000010UL
    //    #define DXGI_USAGE_RENDER_TARGET_OUTPUT     0x00000020UL
    //    #define DXGI_USAGE_BACK_BUFFER              0x00000040UL
    //    #define DXGI_USAGE_SHARED                   0x00000080UL
    //    #define DXGI_USAGE_READ_ONLY                0x00000100UL
    //    #define DXGI_USAGE_DISCARD_ON_PRESENT       0x00000200UL
    //    #define DXGI_USAGE_UNORDERED_ACCESS         0x00000400UL
    m_Swap_Chain_Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    //UINT BufferCount;
    m_Swap_Chain_Desc.BufferCount = 1;

    //HWND OutputWindow;
    m_Swap_Chain_Desc.OutputWindow = g_hWnd;

    //BOOL Windowed;
    m_Swap_Chain_Desc.Windowed = true;

    //DXGI_SWAP_EFFECT SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    //
    //DXGI_SWAP_EFFECT_DISCARD = 0,
    //DXGI_SWAP_EFFECT_SEQUENTIAL = 1,
    //DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
    //DXGI_SWAP_EFFECT_FLIP_DISCARD = 4};
    m_Swap_Chain_Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    //DXGI_SWAP_CHAIN_FLAG;
    //UINT Flags = DXGI_SWAP_CHAIN_FLAG_NONPREROTATED;
    m_Swap_Chain_Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;






    hr = m_pFactory->CreateSwapChain(
        /* [in] */ m_pDevice,
        /* [in] */ &m_Swap_Chain_Desc,
        /* [out] */&m_pSwap_Chain
    );
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_Swap_Chain_Fail_", L"CADevice", MB_OK);
        return false;
    }
    return true;
}

bool CADevice::Set_Render_Target_View()
{

    
    hr= m_pSwap_Chain->GetBuffer(
        /* [in] UINT Buffer */ 0,                    //버퍼 갯수 0 = 1개;
        /*const IID __uuidof()*/__uuidof(ID3D11Texture2D),
        /*[_COM_Outptr_]*/ (void**)&m_pBack_Buffer
    );
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_Render_Target_View_Fail", L"CADevice", MB_OK);
        return false;
    }

    hr = m_pDevice->CreateRenderTargetView(
        /* [in]_In_  ID3D11Resource *pResource */
        m_pBack_Buffer,
        /* [in]_In_opt_  const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, */
        NULL,
        /* [_COM_Outptr_opt_]  ID3D11RenderTargetView **ppRTView */
        &m_pRender_Target_View
    );
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_Render_Target_View_Fail", L"CADevice", MB_OK);
        return false;
    }

    

    return true;
}
bool CADevice::Set_View_Port(float pos_x, float pos_y, float width, float height, float min_depth, float max_depth)
{
    //FLOAT TopLeftX;
    //FLOAT TopLeftY;
    //FLOAT Width;
    //FLOAT Height;
    //FLOAT MinDepth;
    //FLOAT MaxDepth;
    m_View_Port.TopLeftX = pos_x;
    m_View_Port.TopLeftY = pos_y;
    m_View_Port.Width = width;
    m_View_Port.Height = height;
    m_View_Port.MinDepth = min_depth;
    m_View_Port.MaxDepth = max_depth;
    m_pImmediate_Device_Context->RSSetViewports(1, &m_View_Port);

    return true;
}

void CADevice::Resize()
{
    m_pImmediate_Device_Context->OMSetRenderTargets(0, NULL, NULL);
    m_pRender_Target_View->Release();

    hr = m_pSwap_Chain->ResizeBuffers(m_Swap_Chain_Desc.BufferCount, g_rtClient.right, g_rtClient.bottom, m_Swap_Chain_Desc.BufferDesc.Format, m_Swap_Chain_Desc.Flags);

    Set_Render_Target_View();
    Set_View_Port();

}

bool CADevice::Init()
{

    Create_Device();
    Create_DXGIFactory();

    Create_Swap_Chain();

    Set_Render_Target_View();

    Set_View_Port();
    //Set_View_Port(100, 100, 100, 100, 0, 1.0);


    
    
    
    return true;
}
bool CADevice::Frame()
{
    m_pImmediate_Device_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return true;
}
bool CADevice::Pre_Render()
{
    float ClearColor[4] = { 0.6f,0.2f,0.6f,1 };//RGBA
    m_pImmediate_Device_Context->ClearRenderTargetView(m_pRender_Target_View, ClearColor);
    Set_View_Port();
    m_pImmediate_Device_Context->OMSetRenderTargets(
        /* [_In_range_(0, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) ] */
        1,
        /* [_In_reads_opt_(NumViews)]ID3D11RenderTargetView *const  */
        &m_pRender_Target_View,
        /* [_In_opt_  ID3D11DepthStencilView] */
        NULL
    );
    


    return true;
}
bool CADevice::Post_Render()
{   
    m_pSwap_Chain->Present(0 ,0);//

    return true;
}
bool CADevice::Render()
{
    
   
    return true;
}


bool CADevice::Release()
{


    if (m_pImmediate_Device_Context)m_pImmediate_Device_Context->ClearState();
    if (m_pRender_Target_View)m_pRender_Target_View->Release();
    if (m_pSwap_Chain)m_pSwap_Chain->Release();
    if (m_pImmediate_Device_Context)m_pImmediate_Device_Context->Release();
    if (m_pDevice)m_pDevice->Release();
    if (m_pFactory)m_pFactory->Release();
    if(m_pBack_Buffer)m_pBack_Buffer->Release();
    

    
    m_pBack_Buffer = NULL;
    m_pRender_Target_View = NULL;
    m_pSwap_Chain = NULL;
    m_pImmediate_Device_Context = NULL;
    m_pDevice = NULL;
    m_pFactory = NULL;
    return true;
}


CADevice::CADevice()
{
    m_pBack_Buffer = NULL;
    m_pRender_Target_View = NULL;
    m_pSwap_Chain = NULL;
    m_pImmediate_Device_Context = NULL;
    m_pDevice = NULL;
    m_pFactory = NULL;

}


CADevice::~CADevice()
{
}
