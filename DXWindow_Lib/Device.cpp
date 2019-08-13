#include "Device.h"


bool Device::Create_Device()
{
    UINT Create_Device_Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS;

#ifdef _DEBUG
    //D3D11_CREATE_DEVICE_FLAG;                               //에서
    //Create_Device_Flags |= D3D11_CREATE_DEVICE_DEBUG;   //비트연산으로 중복 가능////////////////////////////////////////////////////////////////////////////////////////
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
            MessageBox(g_hWnd, L"D3D11CreateDevice_failed", L"Device", MB_OK);
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

bool Device::Create_DXGIFactory()
{
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pFactory);
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_DXGIFactory_Fail", L"Device", MB_OK);
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
bool Device::Create_Swap_Chain()
{

    if (m_pFactory == nullptr)
    {
        MessageBox(g_hWnd, L"Create_SwapChain_m_pFacktory_is_nullptr", L"Device", MB_OK);
        return false;
    }



    DXGI_SWAP_CHAIN_DESC Swap_Chain_Desc;
    ZeroMemory(&Swap_Chain_Desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    //DXGI_MODE_DESC;
    //    UINT Width;
    //    UINT Height;
    Swap_Chain_Desc.BufferDesc.Width = g_rtClient.right;
    Swap_Chain_Desc.BufferDesc.Height = g_rtClient.bottom;

    //    DXGI_RATIONAL RefreshRate;
    //        UINT Numerator;
    //        UINT Denominator;
    Swap_Chain_Desc.BufferDesc.RefreshRate.Denominator = 1;
    Swap_Chain_Desc.BufferDesc.RefreshRate.Numerator = 60;

    //    DXGI_FORMAT Format = DXGI_FORMAT_R8G8_UNORM;
    //    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    //    DXGI_MODE_SCALING Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    Swap_Chain_Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    Swap_Chain_Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    Swap_Chain_Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    //DXGI_SAMPLE_DESC SampleDesc;
    //    UINT Count;
    //    UINT Quality;
    Swap_Chain_Desc.SampleDesc.Count = 1;
    Swap_Chain_Desc.SampleDesc.Quality = 0;


    //    DXGI_USAGE BufferUsage;
    //
    //    #define DXGI_USAGE_SHADER_INPUT             0x00000010UL
    //    #define DXGI_USAGE_RENDER_TARGET_OUTPUT     0x00000020UL
    //    #define DXGI_USAGE_BACK_BUFFER              0x00000040UL
    //    #define DXGI_USAGE_SHARED                   0x00000080UL
    //    #define DXGI_USAGE_READ_ONLY                0x00000100UL
    //    #define DXGI_USAGE_DISCARD_ON_PRESENT       0x00000200UL
    //    #define DXGI_USAGE_UNORDERED_ACCESS         0x00000400UL
    Swap_Chain_Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    //UINT BufferCount;
    Swap_Chain_Desc.BufferCount = 1;

    //HWND OutputWindow;
    Swap_Chain_Desc.OutputWindow = g_hWnd;

    //BOOL Windowed;
    Swap_Chain_Desc.Windowed = true;

    //DXGI_SWAP_EFFECT SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    //
    //DXGI_SWAP_EFFECT_DISCARD = 0,
    //DXGI_SWAP_EFFECT_SEQUENTIAL = 1,
    //DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
    //DXGI_SWAP_EFFECT_FLIP_DISCARD = 4};
    Swap_Chain_Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    //DXGI_SWAP_CHAIN_FLAG;
    //UINT Flags = DXGI_SWAP_CHAIN_FLAG_NONPREROTATED;
    Swap_Chain_Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;






    hr = m_pFactory->CreateSwapChain(
        /* [in] */ m_pDevice,
        /* [in] */ &Swap_Chain_Desc,
        /* [out] */&m_pSwap_Chain
    );
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_Swap_Chain_Fail_", L"Device", MB_OK);
        return false;
    }
    return true;
}

bool Device::Set_Render_Target_View()
{

    ID3D11Texture2D* pBack_buf;
    hr= m_pSwap_Chain->GetBuffer(
        /* [in] UINT Buffer */ 0,                    //버퍼 갯수 0 = 1개;
        /*const IID __uuidof()*/__uuidof(ID3D11Texture2D),
        /*[_COM_Outptr_]*/ (void**)&pBack_buf
    );
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_Render_Target_View_Fail", L"Device", MB_OK);
        return false;
    }

    hr = m_pDevice->CreateRenderTargetView(
        /* [in]_In_  ID3D11Resource *pResource */
        pBack_buf,
        /* [in]_In_opt_  const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, */
        NULL,
        /* [_COM_Outptr_opt_]  ID3D11RenderTargetView **ppRTView */
        &m_pRender_Target_View
    );
    if (FAILED(hr))
    {
        MessageBox(g_hWnd, L"Create_Render_Target_View_Fail", L"Device", MB_OK);
        return false;
    }

    pBack_buf->Release();

    return true;
}
bool Device::Set_View_Port(float pos_x, float pos_y, float width, float height, float min_depth, float max_depth)
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

bool Device::Create_Vertex_Buffer_F3(FLOAT3* float_2d,int obj_num, ID3D11Buffer* pVertex_buffer)
{
    //D3D11_BUFFER_DESC;
    //UINT ByteWidth;
    //D3D11_USAGE Usage;
    //UINT BindFlags;
    //UINT CPUAccessFlags;
    //UINT MiscFlags;
    //UINT StructureByteStride;
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));

    BD.ByteWidth = sizeof(FLOAT3)*obj_num;
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;   ///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));

    SD.pSysMem = float_2d;
    if (FAILED(hr = m_pDevice->CreateBuffer(&BD, &SD, &pVertex_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Buffer_Fail", L"Device", MB_OK);
        return false;
    }
}


bool Device::Create_Index_Buffer(DWORD* Idata,int m_Index_Num, ID3D11Buffer* pIndex_buffer)
{
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BD.ByteWidth = sizeof(DWORD)*m_Index_Num;
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
    SD.pSysMem = Idata;


    if (FAILED(hr = m_pDevice->CreateBuffer(&BD, &SD, &pIndex_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"Device", MB_OK);
        return false;
    }
    return true;
}

bool Device::Create_Const_Buffer(ID3D11Buffer* pConst_buffer)
{
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DYNAMIC;
    BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BD.ByteWidth = sizeof(DWORD) * MAX_CONST_BUFFER;
    BD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///

    if (FAILED(hr = m_pDevice->CreateBuffer(&BD, NULL, &pConst_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"Device", MB_OK);
        return false;
    }
    return true;
}

bool Device::Load_VS_And_Set_Input_Layout(ID3D11VertexShader* pVertex_Shader, ID3D11InputLayout* pInput_Layout)
{
    ID3D10Blob* pVS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"VS.vsh", NULL, NULL, "VS", "vs_5_0",
        NULL, NULL, NULL, &pVS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"Device", MB_OK);
        return false;
    }

    if (FAILED(hr = m_pDevice->CreateVertexShader(
        /* [ __in  const void *pShaderBytecode] */
        pVS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength,] */
        pVS->GetBufferSize(),
        /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
        NULL,
        /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
        &pVertex_Shader
    )))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Shader", L"Device", MB_OK);
        return false;
    }
    ////////////////
     //   LPCSTR SemanticName;
     //   UINT SemanticIndex;
     //   DXGI_FORMAT Format;
     //   UINT InputSlot;
     //   UINT AlignedByteOffset;
     //   D3D11_INPUT_CLASSIFICATION InputSlotClass;
     //   UINT InstanceDataStepRate;
    const D3D11_INPUT_ELEMENT_DESC Lay_Out = { "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT ,0,0,D3D11_INPUT_PER_VERTEX_DATA ,0 };

    if (FAILED(hr = m_pDevice->CreateInputLayout(
        /* [__in_ecount(NumElements)  const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,] */
        &Lay_Out,
        /* [ __in_range(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)  UINT NumElements] */
        1,
        /* [__in  const void *pShaderBytecodeWithInputSignature] */
        pVS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength] */
        pVS->GetBufferSize(),
        /* [__out_opt  ID3D11InputLayout **ppInputLayout] */
        &pInput_Layout
    )))
    {
        MessageBox(g_hWnd, L"Create_Input_Layout", L"Device", MB_OK);
        return false;
    }
    ////
    if (pVS != nullptr)pVS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}
bool Device::Load_PS(ID3D11PixelShader* pPixel_Shader)
{
    ID3D10Blob* pPS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"PS.psh", NULL, NULL, "PS", "ps_5_0",
        NULL, NULL, NULL, &pPS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"Device", MB_OK);
        return false;
    }

    if (FAILED(hr = m_pDevice->CreatePixelShader(
        /* [ __in  const void *pShaderBytecode] */
        pPS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength,] */
        pPS->GetBufferSize(),
        /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
        NULL,
        /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
        &pPixel_Shader
    )))
    {
        MessageBox(g_hWnd, L"Create_Pixel_Shader", L"Device", MB_OK);
        return false;
    }
    if (pPS != nullptr)pPS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}



bool Device::Init()
{

    Create_Device();
    Create_DXGIFactory();

    Create_Swap_Chain();

    Set_Render_Target_View();

    Set_View_Port();
    //Set_View_Port(100, 100, 100, 100, 0, 1.0);


    Load_PS(m_pPixel_Shader);
    Load_VS_And_Set_Input_Layout(m_pVertex_Shader, m_pInput_Layout);

    FLOAT3 TAG[] = {
   {1.0f, 1.0f, 0.6f} ,
   {1.0f, -1.0f, 0.6f},
   {0.0f, 0.0f, 0.6f },
   {1.0f, -1.0f, 0.6f},
   {1.0f, 1.0f, 0.6f} ,
   {-1.0f ,-1.0f,0.6f},
    };

    DWORD Idata[] = { 0,1,2,2,1,3 };

   //Draw 횟수 
   Set_Vertex_Num(ARRAYSIZE(TAG));
   Set_Index_Num(ARRAYSIZE(Idata));

   Create_Vertex_Buffer_F3(TAG, m_Vertex_Num,m_pVertex_Buffer);
   Create_Index_Buffer(Idata, m_Index_Num, m_pIndex_Buffer);
   Create_Const_Buffer(m_pConst_Buffer);
   

    
    
    return true;
}
bool Device::Frame()
{
    //m_Device.m_pDevice->CreateRasterizerState();


    //Sample용 테스트 상수버퍼 타임값.
    D3D11_MAPPED_SUBRESOURCE MappedResourse;
    //Map  
    m_pImmediate_Device_Context->Map(m_pConst_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResourse);
    CONST_BUFFER_F8* pConstData = (CONST_BUFFER_F8*)MappedResourse.pData;
    pConstData->vColor = D3DXVECTOR4(cosf(g_fGameTimer), sinf(g_fGameTimer), tanf(g_fGameTimer), 1.0f);
    pConstData->x = g_fGameTimer;
    m_pImmediate_Device_Context->Unmap(m_pConst_Buffer, 0);
    //Unmap
    return true;
}
bool Device::Pre_Render()
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
bool Device::Post_Render()
{   
    m_pSwap_Chain->Present(0, 0);//

    return true;
}
bool Device::Render()
{
    
    UINT strid = sizeof(FLOAT3);
    UINT offset = 0;

    m_pImmediate_Device_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_pImmediate_Device_Context->IASetInputLayout(m_pInput_Layout);
    //Num_of_buffers, start_slot 버텍스,상수 버퍼별로 준비해야. offset도 생각해봐야겟
    if (m_pVertex_Buffer != NULL)
    {
        m_pImmediate_Device_Context->IASetVertexBuffers(0, 1, &m_pVertex_Buffer, &strid, &offset);

    }
    if (m_pIndex_Buffer != NULL)
    {
        m_pImmediate_Device_Context->IASetIndexBuffer(m_pIndex_Buffer, DXGI_FORMAT_R32_UINT, 0);
    }
    if (m_pConst_Buffer != NULL)
    {
        m_pImmediate_Device_Context->VSSetConstantBuffers(0, 1, &m_pConst_Buffer);
    }
    if (m_pVertex_Shader != NULL)
    {
        m_pImmediate_Device_Context->VSSetShader(m_pVertex_Shader, NULL, 0);
    }
    m_pImmediate_Device_Context->HSSetShader(NULL, NULL, 0);
    m_pImmediate_Device_Context->DSSetShader(NULL, NULL, 0);
    m_pImmediate_Device_Context->GSSetShader(NULL, NULL, 0);

    if (m_pVertex_Shader != NULL)
    {
        m_pImmediate_Device_Context->PSSetShader(m_pPixel_Shader, NULL, 0);
    }
    if(Draw_Flag)
    {
        Draw();
    }
    return true;
}

bool Device::Draw()
{
    if (m_Index_Draw)
    {
        m_pImmediate_Device_Context->DrawIndexed(m_Draw_Count,m_Start_Index_Location ,m_Start_Vertex_Location);
    }
    else
    {
        m_pImmediate_Device_Context->Draw(m_Draw_Count, m_Start_Vertex_Location);
    }
#ifdef _DEBUG
    if (m_Draw_Count==0)
    {
        OutputDebugString(L"m_Draw_Count ==0; No_Draw_Device");
    }
#endif
}

bool Device::Release()
{

    if (m_pInput_Layout)m_pInput_Layout->Release();

    if (m_pVertex_Buffer)m_pVertex_Buffer->Release();
    if (m_pIndex_Buffer)m_pIndex_Buffer->Release();
    if (m_pConst_Buffer)m_pConst_Buffer->Release();

    if (m_pVertex_Shader)m_pVertex_Shader->Release();
    if (m_pPixel_Shader)m_pPixel_Shader->Release();


    if (m_pImmediate_Device_Context)m_pImmediate_Device_Context->ClearState();
    if (m_pRender_Target_View)m_pRender_Target_View->Release();
    if (m_pSwap_Chain)m_pSwap_Chain->Release();
    if (m_pImmediate_Device_Context)m_pImmediate_Device_Context->Release();
    if (m_pDevice)m_pDevice->Release();
    if (m_pFactory)m_pFactory->Release();

    

    
    m_pVertex_Buffer = NULL;
    m_pIndex_Buffer = NULL;
    m_pConst_Buffer = NULL;

    m_pInput_Layout = NULL;

    m_pVertex_Shader = NULL;
    m_pPixel_Shader = NULL;

    m_pRender_Target_View = NULL;
    m_pSwap_Chain = NULL;
    m_pImmediate_Device_Context = NULL;
    m_pDevice = NULL;
    m_pFactory = NULL;
    return true;
}


Device::Device()
{
    m_pInput_Layout = NULL;

    m_pVertex_Buffer = NULL;
    m_pIndex_Buffer = NULL;
    m_pConst_Buffer = NULL;

    m_pVertex_Shader = NULL;
    m_pPixel_Shader = NULL;

    m_pRender_Target_View = NULL;
    m_pSwap_Chain = NULL;
    m_pImmediate_Device_Context = NULL;
    m_pDevice = NULL;
    m_pFactory = NULL;

    m_Vertex_Num = 0;
    m_Index_Num = 0;

    int m_Vertex_Num = 0;
    int m_Index_Num = 0;
    bool m_Index_Draw = 0;
    int m_Start_Vertex_Location = 0;
    int m_Draw_Count = 0;
    int m_Start_Index_Location = 0;
}


Device::~Device()
{
}
