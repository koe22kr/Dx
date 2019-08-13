#include "Sample.h"

bool Sample::Init()
{
    Create_Vertex_Buffer();
    Create_Const_Buffer();
    Create_Index_Buffer();
    Load_Shader_And_Input_Layout();
    
    return true;
}
bool Sample::Frame()
{
    //m_Device.m_pDevice->CreateRasterizerState();


     ftime += g_fSecondPerFrame;
    float fbtime = cosf(ftime)*0.5f + 0.5f;

    D3D11_MAPPED_SUBRESOURCE MappedResourse;
    m_Device.m_pImmediate_Device_Context->Map(m_pConst_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResourse);
    CONST_BUFFER_F8* pConstData = (CONST_BUFFER_F8*)MappedResourse.pData;
    pConstData->vColor = D3DXVECTOR4(cosf(ftime), sinf(ftime), tanf(ftime), 1.0f);
    pConstData->x = fbtime;
    m_Device.m_pImmediate_Device_Context->Unmap(m_pConst_Buffer, 0);

    return true;

}
bool Sample::Render()
{
    UINT strid = sizeof(FLOAT3);
    UINT offset = 0;

    m_Device.m_pImmediate_Device_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_Device.m_pImmediate_Device_Context->IASetInputLayout(m_pInput_Layout);

    m_Device.m_pImmediate_Device_Context->IASetVertexBuffers(0, 1, &m_pVertex_Buffer, &strid, &offset);
    m_Device.m_pImmediate_Device_Context->IASetIndexBuffer(m_pIndex_Buffer, DXGI_FORMAT_R32_UINT, 0);
    m_Device.m_pImmediate_Device_Context->VSSetConstantBuffers(0, 1, &m_pConst_Buffer);
    m_Device.m_pImmediate_Device_Context->VSSetShader(m_pVertex_Shader, NULL, 0);
    m_Device.m_pImmediate_Device_Context->HSSetShader(NULL, NULL, 0);
    m_Device.m_pImmediate_Device_Context->DSSetShader(NULL, NULL, 0);
    m_Device.m_pImmediate_Device_Context->GSSetShader(NULL, NULL, 0);
    m_Device.m_pImmediate_Device_Context->PSSetShader(m_pPixel_Shader, NULL, 0);


   // m_Device.m_pImmediate_Device_Context->DrawIndexed(6, 0, 0);

    m_Device.m_pImmediate_Device_Context->Draw(6, 0);

    return true;

}
bool Sample::Release()
{
    if (m_pVertex_Buffer)m_pVertex_Buffer->Release();
    if (m_pIndex_Buffer)m_pIndex_Buffer->Release();
    if (m_pConst_Buffer)m_pConst_Buffer->Release();

    if (m_pInput_Layout)m_pInput_Layout->Release();
    if (m_pVertex_Shader)m_pVertex_Shader->Release();
    if (m_pPixel_Shader)m_pPixel_Shader->Release();
    m_pVertex_Buffer = NULL;
    m_pIndex_Buffer = NULL;
    m_pConst_Buffer = NULL;
    m_pInput_Layout = NULL;
    m_pVertex_Shader = NULL;
    m_pPixel_Shader = NULL;
    return true;

}
bool Sample::Create_Vertex_Buffer()         
{
    FLOAT3 TAG[] = {
    {1.0f, 1.0f, 0.6f} ,
    {1.0f, -1.0f, 0.6f},
    {0.0f, 0.0f, 0.6f },
    {1.0f, -1.0f, 0.6f},
    {1.0f, 1.0f, 0.6f} ,
    {-1.0f ,-1.0f,0.6f},
       
       /*  {0.0,0.2,0},
        {0.2,0.3,0},
        {-0.2,-0.5,0},

        {1, 1, 1},
        {1, -1, 1},
        {-1, -1, 0.5}*/
    };
    //D3D11_BUFFER_DESC;
    //UINT ByteWidth;
    //D3D11_USAGE Usage;
    //UINT BindFlags;
    //UINT CPUAccessFlags;
    //UINT MiscFlags;
    //UINT StructureByteStride;
 	D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));

    BD.ByteWidth = sizeof(FLOAT3)*ARRAYSIZE(TAG);
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;   ///
    
    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));

    SD.pSysMem = TAG;
    if (FAILED(m_Device.hr = m_Device.m_pDevice->CreateBuffer(&BD, &SD, &m_pVertex_Buffer)))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Buffer_Fail", L"Device",MB_OK);
        return false;
    }

}

bool Sample::Create_Index_Buffer()
{
    DWORD Idata[] = {0,1,2,2,1,3};
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BD.ByteWidth = sizeof(DWORD)*ARRAYSIZE(Idata);
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
    SD.pSysMem = Idata;

     
    if (FAILED(m_Device.hr = m_Device.m_pDevice->CreateBuffer(&BD, &SD, &m_pIndex_Buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"Device",MB_OK);
        return false;
    }
    return true;
}

bool Sample::Create_Const_Buffer()
{
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DYNAMIC;
    BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BD.ByteWidth = sizeof(DWORD) * MAX_CONST_BUFFER;
    BD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///



    if (FAILED(m_Device.hr = m_Device.m_pDevice->CreateBuffer(&BD, NULL, &m_pConst_Buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"Device",MB_OK);
        return false;
    }
    return true;
}

bool Sample::Create_Vertex_Buffer2()
{

    HRESULT hr = S_OK;

    FLOAT3 vertices[] =
    {
        0.0f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
    };

    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(FLOAT3) * 3;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = vertices;
    return m_Device.m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertex_Buffer);
}

bool Sample::Load_Shader_And_Input_Layout()
{
    ID3D10Blob* pVS;
    ID3D10Blob* pEM;

    if (FAILED(m_Device.hr = D3DX11CompileFromFile(L"VS.vsh", NULL, NULL, "VS", "vs_5_0",
        NULL, NULL, NULL, &pVS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"Device", MB_OK);
        return false;
   }

    if (FAILED(m_Device.hr = m_Device.m_pDevice->CreateVertexShader(
        /* [ __in  const void *pShaderBytecode] */
        pVS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength,] */
        pVS->GetBufferSize(),
        /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
        NULL,
        /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
     &m_pVertex_Shader
    )))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Shader", L"Device", MB_OK);
        return false;
    }
    ////////////////
    ID3D10Blob* pPS;

    if (FAILED(m_Device.hr = D3DX11CompileFromFile(L"PS.psh", NULL, NULL, "PS", "ps_5_0",
        NULL, NULL, NULL, &pPS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"Device", MB_OK);
        return false;
    }

    if (FAILED(m_Device.hr = m_Device.m_pDevice->CreatePixelShader(
        /* [ __in  const void *pShaderBytecode] */
        pPS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength,] */
        pPS->GetBufferSize(),
        /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
        NULL,
        /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
        &m_pPixel_Shader
    )))
    {
        MessageBox(g_hWnd, L"Create_Pixel_Shader", L"Device", MB_OK);
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
    
    const D3D11_INPUT_ELEMENT_DESC Lay_Out = {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT ,0,0,D3D11_INPUT_PER_VERTEX_DATA ,0  };
    
    
    if (FAILED(m_Device.hr = m_Device.m_pDevice->CreateInputLayout(
        /* [__in_ecount(NumElements)  const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,] */
        &Lay_Out,
        /* [ __in_range(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)  UINT NumElements] */
        1,
        /* [__in  const void *pShaderBytecodeWithInputSignature] */
        pVS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength] */
        pVS->GetBufferSize(),
        /* [__out_opt  ID3D11InputLayout **ppInputLayout] */
        &m_pInput_Layout
    )))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Shader", L"Device", MB_OK);
        return false;
    }


    if (pVS != nullptr)pVS->Release();
   if (pPS != nullptr)pPS->Release();
   if(pEM!=nullptr)pEM->Release();


    return true;
}

bool Sample::Load_Shader_And_Input_Layout2()
{
    HRESULT hr = S_OK;
    // Create the effect
    DWORD dwShaderFlags = 0;

    //WCHAR str[MAX_PATH];   
    ID3DBlob* pVSBuf = NULL;


    D3DX11CompileFromFile(L"Shader.txt", NULL, NULL, "VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, NULL, NULL);
    (m_Device.m_pDevice->CreateVertexShader((DWORD*)pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), NULL, &m_pVertex_Shader));

    // Compile the PS from the file
    ID3DBlob* pPSBuf = NULL;
    (D3DX11CompileFromFile(L"PS.txt", NULL, NULL, "PS", "ps_5_0", dwShaderFlags, NULL, NULL, &pPSBuf, NULL, NULL));
    (m_Device.m_pDevice->CreatePixelShader((DWORD*)pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &m_pPixel_Shader));

    // Create our vertex input layout
    const D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    (m_Device.m_pDevice->CreateInputLayout(layout, 1, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(),
        &m_pInput_Layout));

    (pVSBuf->Release());
    (pPSBuf->Release());
    return hr;
}
Sample::Sample()
{
    m_pInput_Layout = NULL;
    m_pVertex_Buffer = NULL;
    m_pVertex_Shader = NULL;
    m_pPixel_Shader = NULL;
}


Sample::~Sample()
{
}

