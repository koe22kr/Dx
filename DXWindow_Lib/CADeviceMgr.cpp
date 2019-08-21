#include "CADeviceMgr.h"

bool CADeviceMgr::Create_Vertex_Buffer_F3(FLOAT3* float_2d, int obj_num, ID3D11Buffer*& pVertex_buffer)
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
        MessageBox(g_hWnd, L"Create_Vertex_Buffer_Fail", L"CADeviceMgr", MB_OK);
        return false;
    }

    return true;
}

bool CADeviceMgr::Create_Index_Buffer(DWORD* Idata, int m_Index_Num, ID3D11Buffer*& pIndex_buffer)
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
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADeviceMgr", MB_OK);
        return false;
    }
    return true;
}

bool CADeviceMgr::Create_Vertex_And_Index_Buffer(FLOAT3* vertex_array, int vertex_size,  ID3D11Buffer*& pVertex_Buffer, DWORD* index_array, int index_size, ID3D11Buffer*& pIndex_Buffer, bool index_drawing)
{

    Create_Vertex_Buffer_F3(vertex_array, vertex_size, pVertex_Buffer);
    Create_Index_Buffer(index_array, index_size, pIndex_Buffer);


    if (index_drawing)
    {
        m_Index_Draw_Flag = true;
        m_Draw_Count = index_size;
    }
    else
    {
        m_Draw_Count = vertex_size;
    }

    return true;
}

bool CADeviceMgr::Create_Const_Buffer(ID3D11Buffer*& pConst_buffer)
{
    Const_Data cb;
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DYNAMIC;
    BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BD.ByteWidth = sizeof(Const_Data);
    BD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
    SD.pSysMem = (void*)&cb;

    if (FAILED(hr = m_pDevice->CreateBuffer(&BD, NULL, &pConst_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADeviceMgr", MB_OK);
        return false;
    }
    return true;
}


bool CADeviceMgr::Load_VS_And_Set_Input_Layout(ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC Lay_Out)
{
    ID3D10Blob* pVS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"VS.vsh", NULL, NULL, VS_name, "vs_5_0",
        NULL, NULL, NULL, &pVS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"CADeviceMgr", MB_OK);
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
        MessageBox(g_hWnd, L"Create_Vertex_Shader", L"CADeviceMgr", MB_OK);
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
        MessageBox(g_hWnd, L"Create_Input_Layout", L"CADeviceMgr", MB_OK);
        return false;
    }
    ////
    if (pVS != nullptr)pVS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}


bool CADeviceMgr::Load_PS(ID3D11PixelShader*& pPixel_Shader, const char* PS_name)
{
    ID3D10Blob* pPS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"PS.psh", NULL, NULL, PS_name, "ps_5_0",
        NULL, NULL, NULL, &pPS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"CADeviceMgr", MB_OK);
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
        MessageBox(g_hWnd, L"Create_Pixel_Shader", L"CADeviceMgr", MB_OK);
        return false;
    }
    if (pPS != nullptr)pPS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}


void CADeviceMgr::Load_Texture_2D_From_File(const TCHAR* texture_full_path, int width, int height, UINT key)
{

    D3DX11_IMAGE_LOAD_INFO Load_Info;
    ZeroMemory(&Load_Info, sizeof(D3DX11_IMAGE_LOAD_INFO));
    Load_Info.Width = width;
    Load_Info.Height = height;
    Load_Info.Depth = D3DX11_DEFAULT;
    Load_Info.FirstMipLevel = 0;
    Load_Info.MipLevels = 1;	// 반드시 1 이여야 한다.
    Load_Info.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_STAGING;    
    Load_Info.CpuAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
    Load_Info.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    Load_Info.MiscFlags = 0;
    Load_Info.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    Load_Info.Filter = D3DX11_FILTER_LINEAR;
    Load_Info.MipFilter = D3DX11_FILTER_NONE;

    //    D3DX11CreateTextureFromFileW(
    //        ID3D11Device*               pDevice,
    //        LPCWSTR                     pSrcFile,
    //        D3DX11_IMAGE_LOAD_INFO      *pLoadInfo,
    //        ID3DX11ThreadPump*          pPump,
    //        ID3D11Resource**            ppTexture,
    //        HRESULT*                    pHResult);
    ID3D11Resource* pResource = NULL;

    ID3D11Texture2D* pTexture_2D = NULL;
    if (FAILED(hr = D3DX11CreateTextureFromFile(m_pDevice, texture_full_path, &Load_Info, NULL, &pResource, NULL)))
    {
        MessageBox(g_hWnd, L"Load_Texture_2D_From_File", L"CADeviceMgr", MB_OK);
        return;
    }

    pResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)pTexture_2D);
    m_pTexture_Map->insert(make_pair(texture_full_path, pTexture_2D));
    return;
}

bool CADeviceMgr::Create_Shader_Resource_View_From_Resource(const TCHAR* texture_full_path, ID3D11ShaderResourceView*& pSRV)
{
    D3D11_SHADER_RESOURCE_VIEW_DESC SRV_Desc;
    SRV_Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SRV_Desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  
    auto iter = m_pTexture_Map->find(texture_full_path);
    if (iter == m_pTexture_Map->end())
    {
        MessageBox(g_hWnd, L"CreateShaderResourceView", L"CADeviceMgr", MB_OK);
        return false;
    }
    else
    {

        m_pDevice->CreateShaderResourceView(iter->second, &SRV_Desc, &pSRV);
        if (pSRV == NULL)
        {
            MessageBox(g_hWnd, L"CreateShaderResourceView", L"CADeviceMgr", MB_OK);
            return false;
        }
        return true;
    }
}

void CADeviceMgr::Set_SRV_To_PS(ID3D11ShaderResourceView* pSRV,int start_slot)
{
    if (pSRV == NULL)
    {
        MessageBox(g_hWnd, L"Set_SRV_To_PS", L"CADeviceMgr", MB_OK);
        return;
    }
    m_pImmediate_Device_Context->PSSetShaderResources(start_slot, 1, &pSRV);

}


void CADeviceMgr::Set_Start_Location(int draw_count, int vertex_location, int index_location)
{
    m_Draw_Count = draw_count;
    m_Start_Vertex_Location = vertex_location;
    m_Start_Index_Location = index_location;
}

void CADeviceMgr::Set_Const_Buffer(ID3D11Buffer* pConst_buffer, Const_Data* const_data)
{
    D3D11_MAPPED_SUBRESOURCE MappedResourse;
    //Map  
    m_pImmediate_Device_Context->Map(pConst_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResourse);

    Const_Data* data = (Const_Data*)MappedResourse.pData;
    memcpy(data, &const_data, sizeof(Const_Data));

    m_pImmediate_Device_Context->Unmap(pConst_buffer, 0);
}

void CADeviceMgr::Set_Pipe_Line(ID3D11InputLayout* pInput_Layout,ID3D11Buffer* pVertex_buffer , ID3D11Buffer* pIndex_Buffer , ID3D11Buffer* pConst_Buffer , ID3D11VertexShader* pVertex_Shader , ID3D11HullShader* pHull_Shader , ID3D11DomainShader* pDomain_Shader , ID3D11GeometryShader* pGeometry_Shader , ID3D11PixelShader* pPixel_Shader )
{
    if (pInput_Layout)
    {
        m_pImmediate_Device_Context->IASetInputLayout(pInput_Layout);
    }
    //Num_of_buffers, start_slot 버텍스,상수 버퍼별로 준비해야. offset도 생각해봐야겟
    m_pImmediate_Device_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    if (pVertex_buffer)
    {
        UINT strid = sizeof(FLOAT3);
        UINT offset = 0;
        m_pImmediate_Device_Context->IASetVertexBuffers(0, 1, &pVertex_buffer, &strid, &offset);

    }
    if (pIndex_Buffer)
    {
        m_pImmediate_Device_Context->IASetIndexBuffer(pIndex_Buffer, DXGI_FORMAT_R32_UINT, 0);
    }
    if (pConst_Buffer)
    {
        m_pImmediate_Device_Context->VSSetConstantBuffers(0, 1, &pConst_Buffer);
    }
    if (pVertex_Shader)
    {
        m_pImmediate_Device_Context->VSSetShader(pVertex_Shader, NULL, 0);
    }
    if (pHull_Shader)
    {
        m_pImmediate_Device_Context->HSSetShader(NULL, NULL, 0);
    }
    if (pDomain_Shader)
    {
        m_pImmediate_Device_Context->DSSetShader(NULL, NULL, 0);
    }
    if (pGeometry_Shader)
    {
        m_pImmediate_Device_Context->GSSetShader(NULL, NULL, 0);
    }
    if (pPixel_Shader)
    {
        m_pImmediate_Device_Context->PSSetShader(pPixel_Shader, NULL, 0);
    }
}


bool CADeviceMgr::Draw()
{
    if (m_Index_Draw_Flag)
    {
        m_pImmediate_Device_Context->DrawIndexed(m_Draw_Count, m_Start_Index_Location, m_Start_Vertex_Location);
    }
    else
    {
        m_pImmediate_Device_Context->Draw(m_Draw_Count, m_Start_Vertex_Location);
    }
#ifdef _DEBUG
    if (m_Draw_Count == 0)
    {
        OutputDebugString(L"m_Draw_Count ==0; No_Draw_Device");
    }
#endif
    return true;
}
//
//bool CADeviceMgr::Init()
//{
//
//}
//bool CADeviceMgr::Frame()
//{
//   
//}
//bool CADeviceMgr::Render()
//{
//   
//}
//bool CADeviceMgr::Release()
//{
//   
//}
//
//CADeviceMgr::CADeviceMgr()
//{
//}
CADeviceMgr::CADeviceMgr(IDXGIFactory* pfactory, ID3D11Device* pdevice, ID3D11DeviceContext* pimmediate_device_context, map<wstring, ID3D11Texture2D*>* pTexture_Map)
{
    m_pFactory = pfactory;
    m_pDevice = pdevice;
    m_pImmediate_Device_Context = pimmediate_device_context;
    m_pTexture_Map = pTexture_Map;
}

CADeviceMgr::~CADeviceMgr()
{
}
